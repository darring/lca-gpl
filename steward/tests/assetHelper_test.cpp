/*
 * assetHelper_test.cpp
 * --------------------
 * Test for the assetHelper
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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
    char *assetInfo = NULL;

    result = assetReady(&assetInfo, &logger, true);
    if(result > 0) {
        int fd = open(argv[1], O_WRONLY | O_CREAT);
        if(fd == -1) {
            logger.ErrLog("Error opening file '%s'", argv[1]);
            close(fd);
            free(assetInfo);
            return -1;
        }

        size_t size_out = write(fd, assetInfo, result);
        free(assetInfo);
        if(size_out != (unsigned)result) {
            logger.ErrLog("Size out mismatch");
            close(fd);
            return -1;
        } else {
            logger.QuickLog("File written FD:'%d'", fd);
            if(close(fd) == -1) {
                logger.ErrLog("Error closing file '%s' with FD:'%d'", argv[1], fd);
                return -1;
            }
            return 0;
        }
    } else {
        logger.ErrLog("Asset wasn't ready");
        return -1;
    }
}
