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

    def __init__(self):
        self.is_registered = false
        self.logger = logging.getLogger('MasterControl')
        self.logger.debug('Class initialized')

    def __register(self):
        self.logger.info('Registering system...')
        # FIXME - Roll this into current script for efficiency?
        nmsa_reg_script = '/opt/intel/eil/clientagent/tools/nmsa_reg.sh'

        # FIXME - error handling
        # Really ugly that we're limitted by the ancient python in RHEL
        stream = os.popen(nmsa_reg_script)
        uri = stream.read().strip()
        stream.close()

        uri = 'http://nmsa01%s' % uri

        # FIXME - error handling
        stream = urllib2.urlopen(uri)
        result = stream.read().strip()
        stream.close()

    def run(self):
        if self.is_registered:
            #
        else:
            self.__register()

# vim:set ai et sts=4 sw=4 tw=80:
