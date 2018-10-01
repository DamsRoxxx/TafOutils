/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_SGI_MIPSPRO_H
#define RTIBOOST_PREDEF_COMPILER_SGI_MIPSPRO_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_SGI`]

[@http://en.wikipedia.org/wiki/MIPSpro SGI MIPSpro] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__sgi`] [__predef_detection__]]
    [[`sgi`] [__predef_detection__]]

    [[`_SGI_COMPILER_VERSION`] [V.R.P]]
    [[`_COMPILER_VERSION`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_SGI RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__sgi) || defined(sgi)
#   if !defined(RTIBOOST_COMP_SGI_DETECTION) && defined(_SGI_COMPILER_VERSION)
#       define RTIBOOST_COMP_SGI_DETECTION RTIBOOST_PREDEF_MAKE_10_VRP(_SGI_COMPILER_VERSION)
#   endif
#   if !defined(RTIBOOST_COMP_SGI_DETECTION) && defined(_COMPILER_VERSION)
#       define RTIBOOST_COMP_SGI_DETECTION RTIBOOST_PREDEF_MAKE_10_VRP(_COMPILER_VERSION)
#   endif
#   if !defined(RTIBOOST_COMP_SGI_DETECTION)
#       define RTIBOOST_COMP_SGI_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_SGI_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_SGI_EMULATED RTIBOOST_COMP_SGI_DETECTION
#   else
#       undef RTIBOOST_COMP_SGI
#       define RTIBOOST_COMP_SGI RTIBOOST_COMP_SGI_DETECTION
#   endif
#   define RTIBOOST_COMP_SGI_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_SGI_NAME "SGI MIPSpro"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_SGI,RTIBOOST_COMP_SGI_NAME)

#ifdef RTIBOOST_COMP_SGI_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_SGI_EMULATED,RTIBOOST_COMP_SGI_NAME)
#endif
