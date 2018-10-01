/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_INTEL_H
#define RTIBOOST_PREDEF_COMPILER_INTEL_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_INTEL`]

[@http://en.wikipedia.org/wiki/Intel_C%2B%2B Intel C/C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__INTEL_COMPILER`] [__predef_detection__]]
    [[`__ICL`] [__predef_detection__]]
    [[`__ICC`] [__predef_detection__]]
    [[`__ECC`] [__predef_detection__]]

    [[`__INTEL_COMPILER`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_INTEL RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || \
    defined(__ECC)
#   if !defined(RTIBOOST_COMP_INTEL_DETECTION) && defined(__INTEL_COMPILER)
#       define RTIBOOST_COMP_INTEL_DETECTION RTIBOOST_PREDEF_MAKE_10_VRP(__INTEL_COMPILER)
#   endif
#   if !defined(RTIBOOST_COMP_INTEL_DETECTION)
#       define RTIBOOST_COMP_INTEL_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_INTEL_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_INTEL_EMULATED RTIBOOST_COMP_INTEL_DETECTION
#   else
#       undef RTIBOOST_COMP_INTEL
#       define RTIBOOST_COMP_INTEL RTIBOOST_COMP_INTEL_DETECTION
#   endif
#   define RTIBOOST_COMP_INTEL_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_INTEL_NAME "Intel C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_INTEL,RTIBOOST_COMP_INTEL_NAME)

#ifdef RTIBOOST_COMP_INTEL_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_INTEL_EMULATED,RTIBOOST_COMP_INTEL_NAME)
#endif
