/*
Copyright (c) Microsoft Corporation 2014
Copyright Rene Rivera 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_PLAT_WINDOWS_PHONE_H
#define RTIBOOST_PREDEF_PLAT_WINDOWS_PHONE_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>
#include <rtiboost/predef/os/windows.h>

/*`
[heading `RTIBOOST_PLAT_WINDOWS_PHONE`]

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_PLAT_WINDOWS_PHONE RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if RTIBOOST_OS_WINDOWS && defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#   undef RTIBOOST_PLAT_WINDOWS_PHONE
#   define RTIBOOST_PLAT_WINDOWS_PHONE RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif
 
#if RTIBOOST_PLAT_WINDOWS_PHONE
#   define RTIBOOST_PLAT_WINDOWS_PHONE_AVAILABLE
#   include <rtiboost/predef/detail/platform_detected.h>
#endif

#define RTIBOOST_PLAT_WINDOWS_PHONE_NAME "Windows Phone"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_PLAT_WINDOWS_PHONE,RTIBOOST_PLAT_WINDOWS_PHONE_NAME)
