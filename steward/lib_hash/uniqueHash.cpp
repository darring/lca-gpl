/*
 uniqueHash.cpp
 ------------------
 A basic helper class which provides unique hashes for the steward library
 */

#include "uniqueHash.h"

UniqueHash::UniqueHash()
{
    base36chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

UniqueHash::~UniqueHash()
{

}

char* UniqueHash::GetHash()
{
    return GetHash(0);
}

char* UniqueHash::GetHash(int seed)
{
    char *messageID; // Temp place holder

    // FIXME for now we just hardcode this, but later on, we want to
    // generate this more dynamically
    // urn:uuid:75a4a1d6-7d17-48e5-bcfb-83307aeaf321
    // urn:uuid:2bb49d8d-d1cf-40fa-a378-b39af8fbe558

    messageID = "urn:uuid:6789";
    //messageID = "urn:uuid:75a4a1d6-7d17-48e5-bcfb-83307aeaf321";

    return messageID;
}