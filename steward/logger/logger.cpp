/*
   logger.cpp
   ----------
   Basic logging class for the EIL Linux Client Agent Steward
 */

//! Logger for the EIL Client Agent Steward
class StewardLogger
{
    private:
        int verbose = 0;
        char *logFilename;
        bool isLogging = false;
        FILE *logPipe;
    public:
        //! Constructor for the EIL Client Agent Steward Logger
        /*
            \param logFile is a character string which details the path to the log file
            \param verbosity is an integer determining the default verbosity of the logger (0 is default, 9 is max)
        */
        StewardLogger(char *logFile, int verbosity)
        {
            verbose = verbosity;
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

            close(logPipe);
        }

}