/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_C_ZOS_H
#define RTIBOOST_PREDEF_LIBRARY_C_ZOS_H

#include <rtiboost/predef/library/c/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_C_ZOS`]

z/OS libc Standard C library.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__LIBREL__`] [__predef_detection__]]

    [[`__LIBREL__`] [V.R.P]]
    [[`__TARGET_LIB__`] [V.R.P]]
    ]
 */

#define RTIBOOST_LIB_C_ZOS RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__LIBREL__)
#   undef RTIBOOST_LIB_C_ZOS
#   if !defined(RTIBOOST_LIB_C_ZOS) && defined(__LIBREL__)
#       define RTIBOOST_LIB_C_ZOS RTIBOOST_PREDEF_MAKE_0X_VRRPPPP(__LIBREL__)
#   endif
#   if !defined(RTIBOOST_LIB_C_ZOS) && defined(__TARGET_LIB__)
#       define RTIBOOST_LIB_C_ZOS RTIBOOST_PREDEF_MAKE_0X_VRRPPPP(__TARGET_LIB__)
#   endif
#   if !defined(RTIBOOST_LIB_C_ZOS)
#       define RTIBOOST_LIB_C_ZOS RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if RTIBOOST_LIB_C_ZOS
#   define RTIBOOST_LIB_C_ZOS_AVAILABLE
#endif

#define RTIBOOST_LIB_C_ZOS_NAME "z/OS"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_C_ZOS,RTIBOOST_LIB_C_ZOS_NAME)
