/*
 uniqueHash.cpp
 ------------------
 A basic helper class which provides unique hashes for the steward library
 */

#include <time.h>
#include <stdlib.h>

#include "uniqueHash.h"

UniqueHash::UniqueHash()
{
    char *internalReturnStorage =
        (char *)malloc(MAX_INTERNAL_STORAGE * sizeof(char));
}

UniqueHash::~UniqueHash()
{

}

char* UniqueHash::GetHash()
{
}
