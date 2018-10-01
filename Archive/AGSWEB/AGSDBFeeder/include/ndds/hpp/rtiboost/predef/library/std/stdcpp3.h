/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_STD_STDCPP3_H
#define RTIBOOST_PREDEF_LIBRARY_STD_STDCPP3_H

#include <rtiboost/predef/library/std/_prefix.h>

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_LIB_STD_GNU`]

[@http://gcc.gnu.org/libstdc++/ GNU libstdc++] Standard C++ library.
Version number available as year (from 1970), month, and day.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__GLIBCXX__`] [__predef_detection__]]
    [[`__GLIBCPP__`] [__predef_detection__]]

    [[`__GLIBCXX__`] [V.R.P]]
    [[`__GLIBCPP__`] [V.R.P]]
    ]
 */

#define RTIBOOST_LIB_STD_GNU RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__GLIBCPP__) || defined(__GLIBCXX__)
#   undef RTIBOOST_LIB_STD_GNU
#   if defined(__GLIBCXX__)
#       define RTIBOOST_LIB_STD_GNU RTIBOOST_PREDEF_MAKE_YYYYMMDD(__GLIBCXX__)
#   else
#       define RTIBOOST_LIB_STD_GNU RTIBOOST_PREDEF_MAKE_YYYYMMDD(__GLIBCPP__)
#   endif
#endif

#if RTIBOOST_LIB_STD_GNU
#   define RTIBOOST_LIB_STD_GNU_AVAILABLE
#endif

#define RTIBOOST_LIB_STD_GNU_NAME "GNU"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_STD_GNU,RTIBOOST_LIB_STD_GNU_NAME)
