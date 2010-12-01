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
        char* lookupTable;
        int sizeOfLookupTable;
    public:
        //! Constructor for the UniqueHash class
        UniqueHash();

        //! Destructor for the UniqueHash class
        ~UniqueHash();

        //! Get a unique hash
        /*!
         * \param ptr char pointer to store the hash into
         * \param hashSize the size of ptr
         */
        void GetHash(char* ptr, int hashSize);
};

#endif
