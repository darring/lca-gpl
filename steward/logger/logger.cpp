/*
   logger.cpp
   ----------
   Basic logging class for the EIL Linux Client Agent Steward
 */

// Constants

//! Maximum length of the log line
#define LOG_LINE_LENGTH 512

#include <stdio.h>
#include <time.h>
#include <unistd.h>

//! Logger for the EIL Client Agent Steward
class StewardLogger
{
    private:
        char *logFilename;
        bool isLogging;
        FILE *logPipe;
        char logLine[LOG_LINE_LENGTH];
    public:
        //! Constructor for the EIL Client Agent Steward Logger
        /*
         *  \param logFile is a character string which details the path to the log file
         *  \param verbosity is an integer determining the default verbosity of the logger (0 is default, 9 is max)
         */
        StewardLogger(char *logFile)
        {
            logFilename = logFile;

            isLogging = false;
        }

        //! Destructor for the EIL Client Agent Steward Logger
        ~StewardLogger()
        {
            if(isLogging)
            {
                // TODO close out logging
            }

            fclose(logPipe);
        }

        //! Begin a logging session
        /*
         * Call this when you are ready to begin logging. The logger
         * will prepare the log file and put itself in a state where
         * future writes can be made.
         *
         * \return True on success, false on failure.
         */
        bool BeginLogging()
        {
            if(!isLogging) {
                if ( !logPipe = (FILE*)fopen(logFilename, "a+") )
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

        //! End a logging session
        /*
         * Call this when you are ready to end a logging session. Note
         * that you should not call this unless you are currently logging,
         * e.g., unless you have previously called BeginLogging().
         *
         * \return True on success, false on failure.
         */
        bool EndLogging()
        {
            if(isLogging)
            {
                close(logPipe);
                isLogging = false;

                return true;
            } else {
                return false;
            }
        }

        //! Determine if we are in a logging session or not
        /*
         * \return True if we are currently in a logging session, false if not
         */
        bool InLoggingSession()
        {
            return isLogging;
        }

        //! Log an entry
        /*
         * Called when you wish to log an entry. Note that you should
         * only call this during a logging session (between calls to
         * BeginLogging() and EndLogging()). If in doubt, consult
         * InLoggingSession().
         *
         * \return True if entry was successful, false if not.
         */
        bool LogEntry(char *text)
        {
            if(isLogging)
            {
                if( !(sprintf(
                    logLine, LOG_LINE_LENGTH,
                    "%s : %s", ctime(null), text)) )
                {
                    perror("Log entry too long! '%s'", text);
                    return false;
                }

                fputs(logLine, logFile);
                return true;
            } else {
                return false;
            }
        }

        //! Quickly log an entry
        /*
         * Call this when you wish to quickly log an entry without having
         * to call begin/end. Note that this does NOT eliminate the steps
         * required to enable logging, it simply masks them. This log
         * method should only be used when a quick one-liner is to be
         * logged, not when there are extended log entries to be written.
         */
        void QuickLog(char *text)
        {
            BeginLogging();
            LogEntry(text);
            EndLogging();
        }
}
