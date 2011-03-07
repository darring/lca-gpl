/*
 * assetHelper_test.cpp
 * --------------------
 * Test for the assetHelper
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "logger.h"
#include "assetHelper.h"

/*!
 * Usage:
 * assetHelper_test outFile logFile
 * \return 0 on success. -1 on error.
 */
int main(int argc, char *argv[])
{
    if(argc != 3) {
        // We must be run with three arguments!
        printf("ERROR! %i\n", argc);
        return -1;
    }

    StewardLogger logger(argv[2]);

    logger.QuickLog("assetHelper_test: Running test");

    int result;
    char *assetInfo;

    result = assetReady(assetInfo, &logger);
    if(result > 0) {
        int fd = open(argv[1], O_WRONLY);
        if(fd == -1) {
            logger.ErrLog("Error opening file '%s'", argv[1]);
            return -1;
        }

        
    } else {
        logger.ErrLog("Asset wasn't ready");
        return -1;
    }
}
