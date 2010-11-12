/*
   logger.cpp
   ----------
   Basic logging class for the EIL Linux Client Agent Steward
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "logger.h"

StewardLogger::StewardLogger(char *logFile)
{
    logFilename = logFile;

    isLogging = false;
}

StewardLogger::~StewardLogger()
{
    if(isLogging)
    {
        // TODO close out logging
    }

    fclose(logPipe);
}

bool StewardLogger::BeginLogging()
{
    if(!isLogging) {
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
    if(isLogging)
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

bool StewardLogger::LogEntry(char *text)
{
    if(isLogging)
    {
        if( !(snprintf(
            logLine, LOG_LINE_LENGTH,
            "%s : %s", ctime(NULL), text)) )
        {
            perror("Log entry too long!");
            perror(text);
            return false;
        }

        fputs(logLine, logPipe);
        return true;
    } else {
        return false;
    }
}

void StewardLogger::QuickLog(char *text)
{
    BeginLogging();
    LogEntry(text);
    EndLogging();
}
