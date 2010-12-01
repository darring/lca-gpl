/*
 * UniqueHash Header
 */

/*! \mainpage Unique Hash generator for the EIL Client Agent Steward
 *
 * \section intro_sec Introduction
 *
 * This is a helper function which provides hash generation utilities for the
 * Linux EIL Client Agent Steward.
 */

#ifndef uniqueHash_H
#define uniqueHash_H

//! Function which generates the unique hash
/*!
 * Call this function to generate a unique hash
 * \param ptr pointer to the character array for the hash
 * \param hashSize the size of the hash
 */
static void generateUniqueHash(char *ptr, int hashSize);

#endif
