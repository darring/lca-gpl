/*
 uniqueHash.cpp
 ------------------
 A basic helper class which provides unique hashes for the steward library
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "uniqueHash.h"

UniqueHash::UniqueHash()
{
    char l_lookupTable[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    sizeOfLookupTable = sizeof(l_lookupTable)/sizeof(l_lookupTable[0]);

    lookupTable = l_lookupTable;

    srandom(time(NULL));
}

UniqueHash::~UniqueHash()
{
    free(lookupTable);
}

void UniqueHash::GetHash(char* ptr, int hashSize)
{
    int spot;

    // Jumble the characters
    for (int i = 0; i < hashSize; i++)
    {
        spot = random() % sizeOfLookupTable;
        ptr[i] = lookupTable[spot];
    }
}
