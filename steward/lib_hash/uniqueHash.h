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

//! The maximum size of the hash (this may be too big)
#define RETURN_STORAGE_MAX_SIZE 40

class UniqueHash
{
    private:
        char* hashCommand;
        //char* internalReturnStorage;
    public:
        //! Constructor for the UniqueHash class
        UniqueHash();

        //! Destructor for the UniqueHash class
        ~UniqueHash();

        //! Get a unique hash
        char* GetHash();
};

#endif
