/*
 uniqueHash.cpp
 ------------------
 A basic helper function which provides unique hashes for the steward library
 */

#include <stdlib.h>
#include <math.h>

#include "uniqueHash.h"

static void generateUniqueHash(char *ptr, int hashSize)
{
    static const char lookupTable[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWYZ";

    static const int lookupTableLen = 36;

    int spot;

    for (int i = 0; i < hashSize; i++)
    {
        spot = remainder(random(), lookupTableLen);

        ptr[i] = lookupTable[spot];
    }
}
