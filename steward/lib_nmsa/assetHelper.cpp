/*
 * assetHelper.cpp
 * ---------------
 * Basic helper functions for asset info integration
 */

#include <sys/sysinfo.h>

#include "assetHelper.h"

bool assetReady(char *assetInfo)
{
    /*
     * We keep this around as a toggle so we don't waste effort once we've
     * established we're done.
     */
    static bool alreadyReplied = false;

    if(!alreadyReplied) {
        struct sysinfo info;
        if (sysinfo(&info) == 0) {
            /*
             * Alright, we only assume we want to update after a certain
             * period after boot. After this period, we figure it's been too
             * long, and the asset info will never show up.
             */
        } else {
            // FIXME probably should check errno(3)
            return false;
        }
    } else {
        return false;
    }
}
