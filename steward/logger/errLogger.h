/*
 * errLogger.h
 */

/*! \page errLogger Generic Error Logger
 *
 * This class handles the generic error logging functionalities for the steward
 * that aren't handled elsewhere in the daemon.
 *
 * Specifically, this deals with logging of errors defined in the errno(3)
 * Linux header file, which are very generic errors.
 *
 * \section usage Usage
 *
 * The Error Logger is created using the ErrLogger::ErrLogger(StewardLogger *logger)
 * constructor.
 */

#ifndef errLogger_H
#define errLogger_H

class StewardLogger logger;

class ErrLogger
{
    private:
        StewardLogger *logger;

    public:
        //! Constructor
        /*!
         * \param logger the StewardLogger instance
         */
        ErrLogger(StewardLogger *logger);

        //! Destructor
        ~ErrLogger();

        //! Generic log entry
        void LogEntry();

        //! Generic log entry with text
        /*!
         * This method can be called with additional text to be added to the
         * generic text that otherwise would be added to the logs.
         */
        void LogEntry(char *text, ...);
};

#endif
