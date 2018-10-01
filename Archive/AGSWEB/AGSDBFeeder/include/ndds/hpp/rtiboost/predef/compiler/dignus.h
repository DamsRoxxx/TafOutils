/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_DIGNUS_H
#define RTIBOOST_PREDEF_COMPILER_DIGNUS_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_SYSC`]

[@http://www.dignus.com/dcxx/ Dignus Systems/C++] compiler.
Version number available as major, minor, and patch.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__SYSC__`] [__predef_detection__]]

    [[`__SYSC_VER__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_SYSC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__SYSC__)
#   define RTIBOOST_COMP_SYSC_DETECTION RTIBOOST_PREDEF_MAKE_10_VRRPP(__SYSC_VER__)
#endif

#ifdef RTIBOOST_COMP_SYSC_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_SYSC_EMULATED RTIBOOST_COMP_SYSC_DETECTION
#   else
#       undef RTIBOOST_COMP_SYSC
#       define RTIBOOST_COMP_SYSC RTIBOOST_COMP_SYSC_DETECTION
#   endif
#   define RTIBOOST_COMP_SYSC_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_SYSC_NAME "Dignus Systems/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_SYSC,RTIBOOST_COMP_SYSC_NAME)

#ifdef RTIBOOST_COMP_SYSC_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_SYSC_EMULATED,RTIBOOST_COMP_SYSC_NAME)
#endif
