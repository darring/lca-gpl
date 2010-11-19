#ifndef machineType_H
#define machineType_H

//! Machine Type enumeration
/*!
 * Defines the various types of machines. This is a direct import from the
 * Windows C#/.NET client, however the original hardcoded integer values have
 * not been retained.
 */
enum MachineType
{
    ANY,
    HOST_WILDCARD,
    HOST,
    FQDN,
    UUID,
    COLLECTION
};

#endif