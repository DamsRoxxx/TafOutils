/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_MSL_H
#define RTIBOOST_PREDEF_LIBRARY_STD_MSL_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_MSL`]

[@http://www.freescale.com/ Metrowerks] Standard C++ Library.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__MSL_CPP__`] [__predef_detection__]]
    [[`__MSL__`] [__predef_detection__]]

    [[`__MSL_CPP__`] [V.R.P]]
    [[`__MSL__`] [V.R.P]]
    ]
 */

#define RTIBOOST_LIB_STD_MSL RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__MSL_CPP__) || defined(__MSL__)
#   undef RTIBOOST_LIB_STD_MSL
#   if defined(__MSL_CPP__)
#       define RTIBOOST_LIB_STD_MSL RTIBOOST_PREDEF_MAKE_0X_VRPP(__MSL_CPP__)
#   else
#       define RTIBOOST_LIB_STD_MSL RTIBOOST_PREDEF_MAKE_0X_VRPP(__MSL__)
#   endif
#endif

#if RTIBOOST_LIB_STD_MSL
#   define RTIBOOST_LIB_STD_MSL_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_MSL_NAME "Metrowerks"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_MSL,RTIBOOST_LIB_STD_MSL_NAME)
