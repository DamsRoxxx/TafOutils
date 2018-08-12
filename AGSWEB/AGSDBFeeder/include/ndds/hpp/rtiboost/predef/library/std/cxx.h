/*
Copyright Rene Rivera 2011-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_CXX_H
#define RTIBOOST_PREDEF_LIBRARY_STD_CXX_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_CXX`]

[@http://libcxx.llvm.org/ libc++] C++ Standard Library.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`_LIBCPP_VERSION`] [__predef_detection__]]

    [[`_LIBCPP_VERSION`] [V.0.P]]
    ]
 */

#define RTIBOOST_LIB_STD_CXX RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(_LIBCPP_VERSION)
#   undef RTIBOOST_LIB_STD_CXX
#   define RTIBOOST_LIB_STD_CXX RTIBOOST_PREDEF_MAKE_10_VPPP(_LIBCPP_VERSION)
#endif

#if RTIBOOST_LIB_STD_CXX
#   define RTIBOOST_LIB_STD_CXX_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_CXX_NAME "libc++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_CXX,RTIBOOST_LIB_STD_CXX_NAME)
