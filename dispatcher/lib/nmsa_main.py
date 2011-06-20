'''
nmsa_main.py
------------
The main daemon loop controller class and functionality
'''

import logging
import os
# FIXME - Not 3.0 ready
import urllib2

class NMSA_Master:

    def __init__(self, max_reg_attempts=10):
        self.__max_registration_attempts = max_reg_attempts

        self.is_registered = False
        self.failure = False
        self.registration_attempts = 0
        self.logger = logging.getLogger('MasterControl')
        self.logger.debug('Class initialized')

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

        if uri:
            uri = 'http://nmsa01%s' % uri

            self.logger.debug("The register URI is '%s'" % uri)

            result = None
            try:
                stream = urllib2.urlopen(uri)
                result = stream.read().strip().lower()
                stream.close()
            except:
                self.logger.info('Problem making connection with NMSA')

            if result:
                self.logger.debug("The register request result was '%s'" % result)

                if result == 'registered':
                    self.is_registered = True
                    self.logger.info('System registration success')
                else:
                    self.registration_attempts = self.registration_attempts + 1
                    if self.registration_attempts > self.__max_registration_attempts:
                        self.failure = True
                        self.logger.critical('Exceeded the maximum number of registration attempts!')
                        self.logger.critical('Bailing on operations!')

    def __relay(self):
        # FIXME - Right now this is terribly hackish
        self.logger.info('Relay loop begin...')

        nmsa_relay_script = '/opt/intel/eil/laf/bin/relay.sh'

        stream = os.popen(nmsa_relay_script)
        output = stream.readlines()
        stream.close()

        for o in output:
            self.logger.info(o.strip())

        self.logger.info('Relay end...')

    def run(self):
        if self.is_registered:
            self.__relay()
        else:
            self.__register()

# vim:set ai et sts=4 sw=4 tw=80:
