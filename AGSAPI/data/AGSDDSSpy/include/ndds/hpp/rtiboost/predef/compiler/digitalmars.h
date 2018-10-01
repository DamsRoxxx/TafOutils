/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_DIGITALMARS_H
#define RTIBOOST_PREDEF_COMPILER_DIGITALMARS_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_DMC`]

[@http://en.wikipedia.org/wiki/Digital_Mars Digital Mars] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__DMC__`] [__predef_detection__]]

    [[`__DMC__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_DMC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__DMC__)
#   define RTIBOOST_COMP_DMC_DETECTION RTIBOOST_PREDEF_MAKE_0X_VRP(__DMC__)
#endif

#ifdef RTIBOOST_COMP_DMC_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_DMC_EMULATED RTIBOOST_COMP_DMC_DETECTION
#   else
#       undef RTIBOOST_COMP_DMC
#       define RTIBOOST_COMP_DMC RTIBOOST_COMP_DMC_DETECTION
#   endif
#   define RTIBOOST_COMP_DMC_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_DMC_NAME "Digital Mars"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_DMC,RTIBOOST_COMP_DMC_NAME)

#ifdef RTIBOOST_COMP_DMC_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_DMC_EMULATED,RTIBOOST_COMP_DMC_NAME)
#endif
