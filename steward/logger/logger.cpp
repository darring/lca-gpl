/*
   logger.cpp
   ----------
   Basic logging class for the EIL Linux Client Agent Steward
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

#include "logger.h"

StewardLogger::StewardLogger(char *logFile)
{
    logFilename = logFile;

    isLogging = false;
    useAltPipe = false;
}

StewardLogger::StewardLogger(FILE *altPipe)
{
    logPipe = altPipe;
    useAltPipe = true;
    isLogging = true;
}

StewardLogger::~StewardLogger()
{
    if(isLogging)
    {
        // TODO close out logging
        EndLogging();
    }
}

bool StewardLogger::BeginLogging()
{
    if(useAltPipe) {
        return true;
    } else if(!isLogging) {
        if ( !(logPipe = (FILE*)fopen(logFilename, "a+")) )
        {
            perror("Problems opening CCMS log file for appending!");
            return false;
        }
        isLogging = true;

        return true;
    } else {
        return false;
    }
}

bool StewardLogger::EndLogging()
{
    if(useAltPipe) {
        return true;
    } else if(isLogging)
    {
        fclose(logPipe);
        isLogging = false;

        return true;
    } else {
        return false;
    }
}

bool StewardLogger::InLoggingSession()
{
    return isLogging;
}

bool StewardLogger::innerLogEntry()
{
    if(isLogging)
    {
        fputs(logLine, logPipe);
        return true;
    } else {
        return false;
    }
}

bool StewardLogger::LogEntry(char *text, ...)
{
    if(isLogging)
    {
        va_list argp;
        timer = time(NULL);
        ts = localtime(&timer);
        strftime(timeStamp, sizeof(timeStamp),
                 "%Y-%m-%d %H:%M:%S %Z", ts);
        va_start(argp, text);
        if( !(vsnprintf(tempLine, TEMP_LINE_LENGTH,
            text, argp)) )
        {
            perror("Log entry too long!");
            perror(text);
            return false;
        }
        va_end(argp);

        if( !(snprintf(
            logLine, LOG_LINE_LENGTH,
            "%s : %s\n", timeStamp, tempLine)) )
        {
            perror("Log entry too long!");
            perror(text);
            return false;
        }

        return innerLogEntry();
    } else {
        return false;
    }
}

void StewardLogger::QuickLog(char *text, ...)
{
    if(isLogging) {
        // If we are already logging, then we must do the logical thing for
        // a quick log function, and that is:
        // - Log our entry
        // - Flush the cache
        // - Begin logging again, thus restoring state
        va_list argp;
        timer = time(NULL);
        ts = localtime(&timer);
        strftime(timeStamp, sizeof(timeStamp),
                 "%Y-%m-%d %H:%M:%S %Z", ts);
        va_start(argp, text);
        if( !(vsnprintf(tempLine, TEMP_LINE_LENGTH,
            text, argp)) )
        {
            perror("Log entry too long!");
            perror(text);
        }
        va_end(argp);

        if( !(snprintf(
            logLine, LOG_LINE_LENGTH,
            "%s : %s\n", timeStamp, tempLine)) )
        {
            perror("Log entry too long!");
            perror(text);
        }

        innerLogEntry();
        EndLogging();
        BeginLogging();
    } else {
        BeginLogging();
        va_list argp;
        timer = time(NULL);
        ts = localtime(&timer);
        strftime(timeStamp, sizeof(timeStamp),
                 "%Y-%m-%d %H:%M:%S %Z", ts);
        va_start(argp, text);
        if( !(vsnprintf(tempLine, TEMP_LINE_LENGTH,
            text, argp)) )
        {
            perror("Log entry too long!");
            perror(text);
        }
        va_end(argp);

        if( !(snprintf(
            logLine, LOG_LINE_LENGTH,
            "%s : %s\n", timeStamp, tempLine)) )
        {
            perror("Log entry too long!");
            perror(text);
        }

        innerLogEntry();
        EndLogging();
    }
}
