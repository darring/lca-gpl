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
#include <fcntl.h>

#include "assetHelper.h"
#include "logger.h"

int assetReady(char **assetInfo, StewardLogger *logger, bool ignoreTimeout)
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
            if(info.uptime < ASSET_TIMEOUT || ignoreTimeout) {
                // Check for the existence of the file
                struct stat buf;
                if(stat(ASSET_INFO_FILE, &buf) == 0) {
                    if(buf.st_size > 0) {
                        *assetInfo = (char *)malloc(buf.st_size * sizeof(char));
                        int fd = open(ASSET_INFO_FILE, O_RDONLY);
                        if(fd == -1) {
                            logger->ErrLog("Asset file exists, but seems unreadable.");
                            close(fd);
                            return -1;
                        }
                        ssize_t actual = read(fd, *assetInfo, buf.st_size);
                        if(actual == -1) {
                            logger->ErrLog();
                            close(fd);
                            return -1;
                        } else if (actual != buf.st_size) {
                            logger->QuickLog("Asset size mis-match!");
                            logger->QuickLog("Expected '%d' but got '%d'!",
                                            buf.st_size, actual);
                            logger->ErrLog();
                            close(fd);
                            return -1;
                        }
                        close(fd);
                        return buf.st_size;
                    } else {
                        // Hmm, well that's odd, asset info is zero size
                        return -1;
                    }
                } else {
                    // File isn't there (or can't be read)
                    logger->ErrLog("Asset file is expected, but isn't there or cannot be read.");
                    return -1;
                }
            } else {
                alreadyRepliedOrPast = true;
                return 0;
            }
        } else {
            logger->ErrLog();
            return -1;
        }
    } else {
        return -1;
    }
    // We shouldn't ever get here, but this is for completeness
    return -1;
}
