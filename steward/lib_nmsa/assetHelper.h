/*
 * assetHelper.h
 */

/*! \page assetHelper Asset Helper
 *
 * The asset helper consists of the following tools and definitions:
 * \li assetReady(char *assetInfo)
 * \li ASSET_TIMEOUT
 * \li ASSET_INFO_FILE
 */

#ifndef assetHelper_H
#define assetHelper_H

//! The asset timeout
/*!
 * This determines how long we should wait before "giving up" on the asset info
 * script after boot and just moving on. It should be in seconds.
 *
 * The reason we have this timeout is because:
 *
 * \li The asset collection script may or may not be present on the system. If
 * the script is not present on the system, we do not want to keep probing for
 * the asset info file forever as this is wasteful and a potential security
 * hole.
 *
 * \li There might be a problem with the asset collection script which might
 * require external user diagnostic. If this is the case, there is nothing the
 * Linux client agent can do about it, so, again, we do not want to keep probing
 * for the asset info file.
 *
 * \li Due to the fact that the asset collection script runs \b after the
 * steward starts up, we have to have some delay to give it a chance to
 * complete. If we simply assumed it was ready, there would exist the potential
 * for a race condition, which would be bad.
 */
#define ASSET_TIMEOUT 8*60

//! The location of the asset info file
#define ASSET_INFO_FILE "/opt/intel/assetinfo"

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
