/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_OS_WINDOWS_H
#define RTIBOOST_PREDEF_OS_WINDOWS_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_OS_WINDOWS`]

[@http://en.wikipedia.org/wiki/Category:Microsoft_Windows Microsoft Windows] operating system.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`_WIN32`] [__predef_detection__]]
    [[`_WIN64`] [__predef_detection__]]
    [[`__WIN32__`] [__predef_detection__]]
    [[`__TOS_WIN__`] [__predef_detection__]]
    [[`__WINDOWS__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_OS_WINDOWS RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(RTIBOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(_WIN32) || defined(_WIN64) || \
    defined(__WIN32__) || defined(__TOS_WIN__) || \
    defined(__WINDOWS__) \
    )
#   undef RTIBOOST_OS_WINDOWS
#   define RTIBOOST_OS_WINDOWS RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#if RTIBOOST_OS_WINDOWS
#   define RTIBOOST_OS_WINDOWS_AVAILABLE
#   include <rtiboost/predef/detail/os_detected.h>
#endif

#define RTIBOOST_OS_WINDOWS_NAME "Microsoft Windows"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_OS_WINDOWS,RTIBOOST_OS_WINDOWS_NAME)
