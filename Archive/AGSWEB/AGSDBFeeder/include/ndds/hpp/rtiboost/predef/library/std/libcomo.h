/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_LIBCOMO_H
#define RTIBOOST_PREDEF_LIBRARY_STD_LIBCOMO_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_COMO`]

[@http://www.comeaucomputing.com/libcomo/ Comeau Computing] Standard C++ Library.
Version number available as major.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__LIBCOMO__`] [__predef_detection__]]

    [[`__LIBCOMO_VERSION__`] [V.0.0]]
    ]
 */

#define RTIBOOST_LIB_STD_COMO RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__LIBCOMO__)
#   undef RTIBOOST_LIB_STD_COMO
#   define RTIBOOST_LIB_STD_COMO RTIBOOST_VERSION_NUMBER(__LIBCOMO_VERSION__,0,0)
#endif

#if RTIBOOST_LIB_STD_COMO
#   define RTIBOOST_LIB_STD_COMO_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_COMO_NAME "Comeau Computing"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_COMO,RTIBOOST_LIB_STD_COMO_NAME)
