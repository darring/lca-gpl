#!/usr/bin/env python

'''
nmsa_handler.py
---------------
The main handler daemon for the various NMSA features and functionality

- Note: While the dispatcher/steward combo proper was designed with Python as
"off the table", for the NMSA handler, we can use it because it automatically
requires platforms with a full Python stack.
'''

import sys, time
import logging
import ConfigParser as configparser

# NMSA specific modules
sys.path.append('/opt/intel/eil/clientagent/lib')
from nmsa_daemon import Daemon

class HandlerDaemon(Daemon):
    __log_file = '/opt/intel/eil/clientagent/home/nmsa_handler.log'
    __conf_file = '/opt/intel/eil/clientagent/home/nmsa_handler.cfg'
    __sleep_timer = 30

    def local_init(self):
        self.conf = 

    def run(self):
        while True:
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
