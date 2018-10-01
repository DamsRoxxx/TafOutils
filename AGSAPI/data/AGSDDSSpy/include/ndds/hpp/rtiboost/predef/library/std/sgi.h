/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_SGI_H
#define RTIBOOST_PREDEF_LIBRARY_STD_SGI_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_SGI`]

[@http://www.sgi.com/tech/stl/ SGI] Standard C++ library.
If available version number as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__STL_CONFIG_H`] [__predef_detection__]]

    [[`__SGI_STL`] [V.R.P]]
    ]
 */

#define RTIBOOST_LIB_STD_SGI RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__STL_CONFIG_H)
#   undef RTIBOOST_LIB_STD_SGI
#   if defined(__SGI_STL)
#       define RTIBOOST_LIB_STD_SGI RTIBOOST_PREDEF_MAKE_0X_VRP(__SGI_STL)
#   else
#       define RTIBOOST_LIB_STD_SGI RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if RTIBOOST_LIB_STD_SGI
#   define RTIBOOST_LIB_STD_SGI_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_SGI_NAME "SGI"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_SGI,RTIBOOST_LIB_STD_SGI_NAME)
