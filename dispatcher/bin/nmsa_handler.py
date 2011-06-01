#!/usr/bin/env python

'''
nmsa_handler.py
---------------
The main handler daemon for the various NMSA features and functionality

- Note: While the dispatcher/steward combo proper was designed with Python as
"off the table", for the NMSA handler, we can use it because it automatically
requires platforms with a full Python stack.
'''

import sys, time, os
import logging
import ConfigParser as configparser

# NMSA specific modules
sys.path.append('/opt/intel/eil/clientagent/lib')
from nmsa_daemon import Daemon
from nmsa_conf import setup_conf

class HandlerDaemon(Daemon):
    __log_file = '/opt/intel/eil/clientagent/home/nmsa_handler.log'
    __conf_file = '/opt/intel/eil/clientagent/home/nmsa_handler.cfg'
    __sleep_timer = 30
    __debug_level = logging.WARNING

    def local_init(self):
        logging.basicConfig(
            filename=self.__log_file,
            format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')

        self.logger = logging.getLogger()

        self.config = setup_conf(self.__conf_file)
        if self.config.has_option('main', 'sleep_timer'):
            self.__sleep_timer = self.config.getint('main', 'sleep_timer')

        if self.config.has_option('main', 'log_level'):
            log_level = self.config.getint('main', 'log_level')
            if log_level == 0:
                self.__debug_level = logging.CRITICAL
            elif log_level == 1:
                self.__debug_level = logging.ERROR
            elif log_level == 3:
                self.__debug_level = logging.WARNING
            elif log_level == 4:
                self.__debug_level = logging.INFO
            else:
                self.__debug_level = logging.DEBUG

        self.logger.setLevel(self.__debug_level)

        self.logger.info('Handler start up...')

    def run(self):
        while True:
            self.logger.debug('Starting NMSA handler activity...')
            time.sleep(self.__sleep_timer)

def usage():
    print "Usage:\n"
    print "\tnmsa_handler.py COMMAND"
    print "\t\twhere 'COMMAND' is one of the following:\n"
    print "\tstart\t\tStart the daemon"
    print "\tstop\t\tStop the daemon"
    print "\trestart\t\tRestart the daemon"

if __name__ == "__main__":
    daemon = HandlerDaemon('/opt/intel/eil/clientagent/home/nmsa_handler.pid')
    if len(sys.argv) == 2:
        if 'start' == sys.argv[1]:
            daemon.start()
        elif 'stop' == sys.argv[1]:
            daemon.stop()
        elif 'restart' == sys.argv[1]:
            daemon.restart()
        else:
            print "Unknown command"
            sys.exit(2)
        sys.exit(0)
    else:
        usage()
        sys.exit(2)

# vim:set ai et sts=4 sw=4 tw=80:
