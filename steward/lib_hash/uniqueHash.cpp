/*
 uniqueHash.cpp
 ------------------
 A basic helper function which provides unique hashes for the steward library
 */

#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>

#include "uniqueHash.h"

using namespace std;

void generateUniqueHash(char *ptr, int hashSize)
{
    static string lookupTable = "0123456789ABCDEFGHIJKLMNOPQRSTUVWYZ";

    static int lookupTableLen = lookupTable.length();

    // FIXME random is *horrible* at randomness! this is a stopgap at best
    // we need to get at /dev/urandom for better randomness

    srandom(time(NULL));

    for (int i = 0; i < hashSize; i++)
    {
        ptr[i] = lookupTable[random() % lookupTableLen];
    }
}
