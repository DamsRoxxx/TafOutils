/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_METAWARE_H
#define RTIBOOST_PREDEF_COMPILER_METAWARE_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_HIGHC`]

MetaWare High C/C++ compiler.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__HIGHC__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_COMP_HIGHC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__HIGHC__)
#   define RTIBOOST_COMP_HIGHC_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#ifdef RTIBOOST_COMP_HIGHC_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_HIGHC_EMULATED RTIBOOST_COMP_HIGHC_DETECTION
#   else
#       undef RTIBOOST_COMP_HIGHC
#       define RTIBOOST_COMP_HIGHC RTIBOOST_COMP_HIGHC_DETECTION
#   endif
#   define RTIBOOST_COMP_HIGHC_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_HIGHC_NAME "MetaWare High C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_HIGHC,RTIBOOST_COMP_HIGHC_NAME)

#ifdef RTIBOOST_COMP_HIGHC_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_HIGHC_EMULATED,RTIBOOST_COMP_HIGHC_NAME)
#endif
