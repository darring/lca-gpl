/*
 * assetHelper.cpp
 * ---------------
 * Basic helper functions for asset info integration
 */

#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "assetHelper.h"

bool assetReady(char *assetInfo)
{
    /*
     * We keep this around as a toggle so we don't waste effort once we've
     * established we're done.
     */
    static bool alreadyRepliedOrPast = false;

    if(!alreadyRepliedOrPast) {
        struct sysinfo info;
        if (sysinfo(&info) == 0) {
            /*
             * Alright, we only assume we want to update after a certain
             * period after boot. After this period, we figure it's been too
             * long, and the asset info will never show up.
             */
            if(info.uptime < ASSET_TIMEOUT) {
                // Check for the existence of the file
                struct stat buf;
                if(stat(ASSET_INFO_FILE, &buf)) {
                    //
                } else {
                    // File isn't there (or can't be read
                    // FIXME probably should check errno(3)
                    return false;
                }
            } else {
                alreadyRepliedOrPast = true;
                return false;
            }
        } else {
            // FIXME probably should check errno(3)
            return false;
        }
    } else {
        return false;
    }
}
