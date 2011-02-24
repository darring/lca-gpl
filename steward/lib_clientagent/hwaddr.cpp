/*
    hwaddr.cpp
    ----------
    Hardware address tools
 */

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <string.h>
#include <unistd.h>

#include "hwaddr.h"

//! The maximum number of nics we will run through looking for activity before giving up
#define MAX_NICS 8

//! The maximum length of a HW address
#define MAX_HWADDR 32

bool getHwAddr(char **hwaddr)
{
    /*
     This is probably a bit crazy, I realize, but I'd like to avoid potential
     char memory issues as much as possible here, and really, how many NICs do
     we want to run through before giving up anyway?
     */
    static const char potential_nics[][MAX_NICS] = {
        "eth0",
        "eth1",
        "eth2",
        "eth3",
        "eth4",
        "eth5",
        "eth6",
        "eth7"
    };

    int s, i;
    int retval;
    struct ifreq buffer;
    char rethwaddr[MAX_HWADDR];
    bool found = false;

    s = socket(PF_INET, SOCK_DGRAM, 0);

    memset(&buffer, 0x00, sizeof(buffer));

    for(i = 0; i < MAX_NICS; i++) {
        strcpy(buffer.ifr_name, potential_nics[i]);

        retval = ioctl(s, SIOCGIFHWADDR, &buffer);
        if (retval >= 0) {
            found = true;
            break;
        }
    }

    close(s);

    i = 0;
    if(found) {
        for( s = 0; s < 6; s++ )
        {
            snprintf(&rethwaddr[i], MAX_HWADDR, "%.2X",
                    (unsigned char)buffer.ifr_hwaddr.sa_data[s]);
            if(s < 5)
                sprintf(&rethwaddr[i+2], ":");
            i += 3;
        }
        *hwaddr = rethwaddr;
    }

    return found;
}
