/*
 * assetHelper.h
 */

/*! \page assetHelper Asset Helper
 *
 */

#ifndef assetHelper_H
#define assetHelper_H

//! Determines if the asset info is fresh, and ready to be uploaded to CCMS
/*!
 * Quite simply, when you call this helper if checks to see if the system has
 * recently booted and if there is a fresh asset info file available for
 * submittal to CCMS. If it is, it returns a true and sets the char assetInfo
 * to the contents of the asset info file.
 *
 * More specifically, the proper way to use this is to maintain a flag of your
 * own and to call this until it returns "true". Once it returns true, you
 * really should never call it again (though, calling it again certainly will
 * not hurt anything, it simply will be unnecessary).
 *
 * \param assetInfo A character array pointer which will hold the asset info
 * \returns True if asset info is ready. False if it is not.
 */
bool assetReady(char *assetInfo);

#endif
