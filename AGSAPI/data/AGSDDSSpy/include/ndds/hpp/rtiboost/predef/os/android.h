/*
Copyright Rene Rivera 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_ADROID_H
#define RTIBOOST_PREDEF_OS_ADROID_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_ANDROID`]

[@http://en.wikipedia.org/wiki/Android_%28operating_system%29 Android] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__ANDROID__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_ANDROID RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__ANDROID__) \
    )
#   undef RTIBOOST_OS_ANDROID
#   define RTIBOOST_OS_ANDROID RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_ANDROID
#   define RTIBOOST_OS_ANDROID_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_ANDROID_NAME "Android"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_ANDROID,RTIBOOST_OS_ANDROID_NAME)
