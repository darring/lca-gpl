#!/usr/bin/env python

'''
nmsa_handler.py
---------------
The main handler daemon for the various NMSA features and functionality
'''

import sys, time
sys.path.append('/opt/intel/eil/clientagent/lib')
from nmsa_daemon import Daemon

class HandlerDaemon(Daemon):
    def run(self):
        while True:
            time.sleep(1)

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
