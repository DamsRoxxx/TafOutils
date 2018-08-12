/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_C_VMS_H
#define RTIBOOST_PREDEF_LIBRARY_C_VMS_H

#include <rtiboost/predef/library/c/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_C_VMS`]

VMS libc Standard C library.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__CRTL_VER`] [__predef_detection__]]

    [[`__CRTL_VER`] [V.R.P]]
    ]
 */

#define RTIBOOST_LIB_C_VMS RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__CRTL_VER)
#   undef RTIBOOST_LIB_C_VMS
#   define RTIBOOST_LIB_C_VMS RTIBOOST_PREDEF_MAKE_10_VVRR0PP00(__CRTL_VER)
#endif

#if RTIBOOST_LIB_C_VMS
#   define RTIBOOST_LIB_C_VMS_AVAILABLE
#endif

#define RTIBOOST_LIB_C_VMS_NAME "VMS"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_C_VMS,RTIBOOST_LIB_C_VMS_NAME)
