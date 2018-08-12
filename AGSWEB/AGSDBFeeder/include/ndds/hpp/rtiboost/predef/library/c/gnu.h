/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_LIBRARY_C_GNU_H
#define RTIBOOST_PREDEF_LIBRARY_C_GNU_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

#include <rtiboost/predef/library/c/_prefix.h>

#if defined(__STDC__)
#include <stddef.h>
#elif defined(__cplusplus)
#include <cstddef>
#endif

/*`
[heading `RTIBOOST_LIB_C_GNU`]

[@http://en.wikipedia.org/wiki/Glibc GNU glibc] Standard C library.
Version number available as major, and minor.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__GLIBC__`] [__predef_detection__]]
    [[`__GNU_LIBRARY__`] [__predef_detection__]]

    [[`__GLIBC__`, `__GLIBC_MINOR__`] [V.R.0]]
    [[`__GNU_LIBRARY__`, `__GNU_LIBRARY_MINOR__`] [V.R.0]]
    ]
 */

#define RTIBOOST_LIB_C_GNU RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__GLIBC__) || defined(__GNU_LIBRARY__)
#   undef RTIBOOST_LIB_C_GNU
#   if defined(__GLIBC__)
#       define RTIBOOST_LIB_C_GNU \
            RTIBOOST_VERSION_NUMBER(__GLIBC__,__GLIBC_MINOR__,0)
#   else
#       define RTIBOOST_LIB_C_GNU \
            RTIBOOST_VERSION_NUMBER(__GNU_LIBRARY__,__GNU_LIBRARY_MINOR__,0)
#   endif
#endif

#if RTIBOOST_LIB_C_GNU
#   define RTIBOOST_LIB_C_GNU_AVAILABLE
#endif

#define RTIBOOST_LIB_C_GNU_NAME "GNU"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_LIB_C_GNU,RTIBOOST_LIB_C_GNU_NAME)
