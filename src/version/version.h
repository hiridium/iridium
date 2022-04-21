// Copyright (c) 2014-2019 Coin Sciences Ltd
// Iridium code distributed under the GPLv3 license, see COPYING file.

#ifndef IRIDIUMVERSION_H
#define	IRIDIUMVERSION_H

#define IRIDIUM_VERSION_MAJOR     1
#define IRIDIUM_VERSION_MINOR     0
#define IRIDIUM_VERSION_REVISION  0
#define IRIDIUM_VERSION_STAGE     2
#define IRIDIUM_VERSION_BUILD     2

#define IRIDIUM_PROTOCOL_VERSION 10008
#define IRIDIUM_PROTOCOL_SUPPORTED "10004 - 10008, 20001"


#ifndef STRINGIZE
#define STRINGIZE(X) DO_STRINGIZE(X)
#endif

#ifndef DO_STRINGIZE
#define DO_STRINGIZE(X) #X
#endif

#define IRIDIUM_BUILD_DESC_WITH_SUFFIX(maj, min, rev, build, suffix) \
    DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build) "-" DO_STRINGIZE(suffix)

#define IRIDIUM_BUILD_DESC_FROM_UNKNOWN(maj, min, rev, build) \
    DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build)


#define IRIDIUM_BUILD_DESC "1.0 beta 2"
#define IRIDIUM_BUILD_DESC_NUMERIC 10000202


#ifndef IRIDIUM_BUILD_DESC
#ifdef BUILD_SUFFIX
#define IRIDIUM_BUILD_DESC IRIDIUM_BUILD_DESC_WITH_SUFFIX(IRIDIUM_VERSION_MAJOR, IRIDIUM_VERSION_MINOR, IRIDIUM_VERSION_REVISION, IRIDIUM_VERSION_BUILD, BUILD_SUFFIX)
#else
#define IRIDIUM_BUILD_DESC IRIDIUM_BUILD_DESC_FROM_UNKNOWN(IRIDIUM_VERSION_MAJOR, IRIDIUM_VERSION_MINOR, IRIDIUM_VERSION_REVISION, IRIDIUM_VERSION_BUILD)
#endif
#endif

#define IRIDIUM_FULL_DESC(build, protocol) \
    "build " build " protocol " DO_STRINGIZE(protocol)


#ifndef IRIDIUM_FULL_VERSION
#define IRIDIUM_FULL_VERSION IRIDIUM_FULL_DESC(IRIDIUM_BUILD_DESC, IRIDIUM_PROTOCOL_VERSION)
#endif


#define IRIDIUM_VERSION_CODE_PROTOCOL_THIS              0
#define IRIDIUM_VERSION_CODE_PROTOCOL_MIN               1
#define IRIDIUM_VERSION_CODE_PROTOCOL_MIN_DOWNGRADE     2
#define IRIDIUM_VERSION_CODE_PROTOCOL_MIN_NO_DOWNGRADE  3
#define IRIDIUM_VERSION_CODE_PROTOCOL_FOR_RELEVANCE     4
#define IRIDIUM_VERSION_CODE_BUILD                     16
#define IRIDIUM_VERSION_CODE_MIN_VALID               1000

#endif	/* IRIDIUMVERSION_H */
