'''
nmsa_main.py
------------
The main daemon loop controller class and functionality
'''

import logging
import os
# FIXME - Not 3.0 ready
import urllib2
import fcntl, socket, struct

class NMSA_Master:

    def __init__(self, max_reg_attempts=10, max_poll_attempts=20):
        self.__max_registration_attempts = max_reg_attempts
        self.__max_poll_attempts = max_poll_attempts

        self.is_registered = False
        self.failure = False
        self.registration_attempts = 0
        self.poll_attempts = 0
        self.logger = logging.getLogger('MasterControl')
        self.logger.debug('Class initialized')
        self._SIOCGIFHWADDR = 0x8927
        self._SIOCGIFADDR = 0x8915

    def __getIfInfo(ifname):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        hwinfo = fcntl.ioctl(s.fileno(), self._SIOCGIFHWADDR,  struct.pack('256s', ifname[:15]))
        return (''.join(['%02x:' % ord(char) for char in info[18:24]])[:-1], os.uname()[1])

    def __inc_register(self):
        self.registration_attempts = self.registration_attempts + 1
        if self.registration_attempts > self.__max_registration_attempts:
            self.failure = True
            self.logger.critical('Exceeded the maximum number of registration attempts!')
            self.logger.critical('Bailing on operations!')

    def __inc_poll(self):
        self.poll_attempts = self.poll_attempts + 1
        if self.poll_attempts > self.__max_poll_attempts and self.__max_poll_attetmps > 0:
            self.failuire = True
            self.logger.critical('Exceeded the maximum number of poll attempts with failure!')
            self.logger.critical('Bailing on operations!')

    def __register(self):
        self.logger.info('Registering system...')
        # FIXME - Roll this into current script for efficiency?
        nmsa_reg_script = '/opt/intel/eil/clientagent/tools/nmsa_reg.sh'

        uri = None
        # Really ugly that we're limitted by the ancient python in RHEL
        try:
            stream = os.popen(nmsa_reg_script)
            uri = stream.read().strip()
            stream.close()
        except:
            self.logger.info('Problem opening nmsa_reg.sh script')
            self.__inc_register()

        if uri:
            uri = 'http://nmsa01%s' % uri

            self.logger.debug("The register URI is '%s'" % uri)

            result = None
            try:
                stream = urllib2.urlopen(uri)
                result = stream.read().strip().lower()
                stream.close()
            except:
                self.logger.error('Problem making connection with NMSA')
                self.__inc_register()

            if result:
                self.logger.debug("The register request result was '%s'" % result)

                if result == 'registered':
                    self.is_registered = True
                    self.logger.info('System registration success')
                else:
                    self.__inc_register()

    def __relay(self):
        # FIXME - Right now this is terribly hackish
        self.logger.info('Relay loop begin...')

        #nmsa_relay_script = '/opt/intel/eil/laf/bin/relay.sh'

        #stream = os.popen(nmsa_relay_script)
        #output = stream.readlines()
        #stream.close()

        #for o in output:
        #    self.logger.info(o.strip())

        uri = "http://nmsa01/nmsa/client_poll.php?mac=%s&hostname=%s" % self.__getIfInfo()
        self.logger.debug("The client poll URI is: '%s'" % uri)

        result = None
        try:
            stream = urllib2.urlopen(uri)
            result = stream.read().strip()
            stream.close()
        except:
            self.logger.info('Problem making connection with NMSA')
            self.__inc_poll()

        if result.lower() == 'register':
            self.is_registered = False
        elif result.lower() == 'nothing':
            pass
        elif result.lower() == 'error':
            self.logger.error('NMSA reported error, sleeping to try again...')
        else:
            # We have a workload
            try:
                (sid, workload) = result.split()
                self.logger.info("Running workload '%s' '%s'" % (sid, workload)
                laf_script = '/opt/intel/eil/laf/bin/laf.sh %s %s' % (sid, workload)
                try:
                    stream = os.popen(laf_script)
                    output = stream.readlines()
                    stream.close()
                    workload_out = None
                    try:
                        stream = open("/opt/intel/eil/laf/output/%s" % sid)
                        workload_out = stream.readline().rstrip()
                        stream.close()
                    except:
                        self.logger.error("Error opening output for sid '%s'..." % sid)
                        self.__inc_poll()
                    if workload_out:
                        uri = "http://nmsa01/nmsa/client_push.php?mac=%s&sid=%s&comp=%s&log=nmsa_handler-%s-%s" % (self.__getIfInfo()[0], sid, output[0], 
                except:
                    self.logger.error("Problem running workload!")
                    self.__inc_poll()
            except:
                self.logger.error("Malformed workload line from NMSA: '%s'" % result)
                self.__inc_poll()

        self.logger.info('Relay end...')

    def run(self):
        if self.is_registered:
            self.__relay()
        else:
            self.__register()

# vim:set ai et sts=4 sw=4 tw=80:
