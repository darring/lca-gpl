/*
 * UniqueHash Header
 */

/*! \mainpage Unique Hash generator for the EIL Client Agent Steward
 *
 * \section intro_sec Introduction
 *
 * This is a helper class which provides hash generation utilities for the
 * Linux EIL Client Agent Steward.
 */

#ifndef uniqueHash_H
#define uniqueHash_H

class UniqueHash
{
    private:
        char* base36chars;
    public:
        //! Constructor for the UniqueHash class
        UniqueHash();

        //! Destructor for the UniqueHash class
        ~UniqueHash();

        //! Get a unique hash
        /*!
         * The default GetHash method takes no arguments and returns a hash
         * based upon the system time and a psuedo-random number.
         */
        char* GetHash();

        //! Get a unique hash
        /*!
         * If GetHash is called with a seed integer, then this is used as a seed
         * instead of system time and a unique hash is generated using this and
         * a psuedo-random number.
         * \param seed the integer to use as seed
         */
        char* GetHash(int seed);
};

#endif
