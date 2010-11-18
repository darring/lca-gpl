/*
 * StewardLogger header
 */

/*! \mainpage Logger for the EIL Client Agent Steward
 *
 * \section intro_sec Introduction
 *
 * This is the class which handles the logging for the EIL Linux Client Agent.
 */

// Constants

//! Maximum length of the log line
#define LOG_LINE_LENGTH 512

#ifndef logger_H
#define logger_H

//! Logger for the EIL Client Agent Steward
class StewardLogger
{
    private:
        char *logFilename;
        bool isLogging;
        FILE *logPipe;
        char logLine[LOG_LINE_LENGTH];
        time_t timer;
        struct tm *ts;
        char timeStamp[80];
    public:
        //! Constructor for the EIL Client Agent Steward Logger
        /*!
         *  \param logFile is a character string which details the path to the log file
         */
        StewardLogger(char *logFile);

        //! Destructor for the EIL Client Agent Steward Logger
        ~StewardLogger();

        //! Begin a logging session
        /*!
         * Call this when you are ready to begin logging. The logger
         * will prepare the log file and put itself in a state where
         * future writes can be made.
         *
         * \return True on success, false on failure.
         */
        bool BeginLogging();

        //! End a logging session
        /*!
         * Call this when you are ready to end a logging session. Note
         * that you should not call this unless you are currently logging,
         * e.g., unless you have previously called BeginLogging().
         *
         * \return True on success, false on failure.
         */
        bool EndLogging();

        //! Determine if we are in a logging session or not
        /*!
         * \return True if we are currently in a logging session, false if not
         */
        bool InLoggingSession();

        //! Log an entry
        /*!
         * Called when you wish to log an entry. Note that you should
         * only call this during a logging session (between calls to
         * BeginLogging() and EndLogging()). If in doubt, consult
         * InLoggingSession().
         *
         * \return True if entry was successful, false if not.
         */
        bool LogEntry(char *text);

        //! Quickly log an entry
        /*!
         * Call this when you wish to quickly log an entry without having
         * to call begin/end. Note that this does NOT eliminate the steps
         * required to enable logging, it simply masks them. This log
         * method should only be used when a quick one-liner is to be
         * logged, not when there are extended log entries to be written.
         */
        void QuickLog(char *text);
};

#endif
