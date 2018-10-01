/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_DIAB_H
#define RTIBOOST_PREDEF_COMPILER_DIAB_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_DIAB`]

[@http://www.windriver.com/products/development_suite/wind_river_compiler/ Diab C/C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__DCC__`] [__predef_detection__]]

    [[`__VERSION_NUMBER__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_DIAB RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__DCC__)
#   define RTIBOOST_COMP_DIAB_DETECTION RTIBOOST_PREDEF_MAKE_10_VRPP(__VERSION_NUMBER__)
#endif

#ifdef RTIBOOST_COMP_DIAB_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_DIAB_EMULATED RTIBOOST_COMP_DIAB_DETECTION
#   else
#       undef RTIBOOST_COMP_DIAB
#       define RTIBOOST_COMP_DIAB RTIBOOST_COMP_DIAB_DETECTION
#   endif
#   define RTIBOOST_COMP_DIAB_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_DIAB_NAME "Diab C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_DIAB,RTIBOOST_COMP_DIAB_NAME)

#ifdef RTIBOOST_COMP_DIAB_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_DIAB_EMULATED,RTIBOOST_COMP_DIAB_NAME)
#endif
