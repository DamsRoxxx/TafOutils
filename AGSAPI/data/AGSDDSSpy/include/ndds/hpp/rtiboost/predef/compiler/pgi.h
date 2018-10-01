/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_PGI_H
#define RTIBOOST_PREDEF_COMPILER_PGI_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_PGI`]

[@http://en.wikipedia.org/wiki/The_Portland_Group Portland Group C/C++] compiler.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__PGI`] [__predef_detection__]]

    [[`__PGIC__`, `__PGIC_MINOR__`, `__PGIC_PATCHLEVEL__`] [V.R.P]]
    ]
 */

#define RTIBOOST_COMP_PGI RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__PGI)
#   if !defined(RTIBOOST_COMP_PGI_DETECTION) && (defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__))
#       define RTIBOOST_COMP_PGI_DETECTION RTIBOOST_VERSION_NUMBER(__PGIC__,__PGIC_MINOR__,__PGIC_PATCHLEVEL__)
#   endif
#   if !defined(RTIBOOST_COMP_PGI_DETECTION)
#       define RTIBOOST_COMP_PGI_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#ifdef RTIBOOST_COMP_PGI_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_PGI_EMULATED RTIBOOST_COMP_PGI_DETECTION
#   else
#       undef RTIBOOST_COMP_PGI
#       define RTIBOOST_COMP_PGI RTIBOOST_COMP_PGI_DETECTION
#   endif
#   define RTIBOOST_COMP_PGI_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_PGI_NAME "Portland Group C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_PGI,RTIBOOST_COMP_PGI_NAME)

#ifdef RTIBOOST_COMP_PGI_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_PGI_EMULATED,RTIBOOST_COMP_PGI_NAME)
#endif
