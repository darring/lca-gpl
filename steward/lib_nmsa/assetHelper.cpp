/*
 * assetHelper.cpp
 * ---------------
 * Basic helper functions for asset info integration
 */

#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include "assetHelper.h"
#include "logger.h"

bool assetReady(char *assetInfo, StewardLogger *logger)
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
                    if(buf.st_size > 0) {
                        assetInfo = (char *)malloc(buf.st_size * sizeof(char));
                        //
                    } else {
                        // Hmm, well that's odd, asset info is zero size
                        return false;
                    }
                } else {
                    // File isn't there (or can't be read
                    logger->ErrLog("Asset file is expected, but isn't there or cannot be read.");
                    return false;
                }
            } else {
                alreadyRepliedOrPast = true;
                return false;
            }
        } else {
            logger->ErrLog();
            return false;
        }
    } else {
        return false;
    }
    // We shouldn't ever get here, but this is for completeness
    return false;
}
