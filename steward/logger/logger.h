/*
 * StewardLogger header
 */

class StewardLogger
{
    public:
        StewardLogger(char *logFile, int verbosity);

        ~StewardLogger();

        bool BeginLogging();

        bool EndLogging();

        bool InLoggingSession();

        bool LogEntry(char *text);

        void QuickLog(char *text);
}