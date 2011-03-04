/*
 * errLogger.cpp
 * -------------
 *  Generic Error Logger
 */

#include <stdarg.h>
#include <errno.h>

#include "errLogger.h"

ErrLogger:ErrLogger(StewardLogger *myLogger)
{
    logger = myLogger;

    logger->QuickLog("ErrLogger> Generic error logger initialized..");
}

ErrLogger::~ErrLogger()
{
    // TODO anything?
}

void ErrLogger::LogEntry()
{
}

void ErrLogger::LogEntry(char *text, ...)
{
}
