/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_MICROTEC_H
#define RTIBOOST_PREDEF_COMPILER_MICROTEC_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_MRI`]

[@http://www.mentor.com/microtec/ Microtec C/C++] compiler.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`_MRI`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_COMP_MRI RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(_MRI)
#   define RTIBOOST_COMP_MRI_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#ifdef RTIBOOST_COMP_MRI_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_MRI_EMULATED RTIBOOST_COMP_MRI_DETECTION
#   else
#       undef RTIBOOST_COMP_MRI
#       define RTIBOOST_COMP_MRI RTIBOOST_COMP_MRI_DETECTION
#   endif
#   define RTIBOOST_COMP_MRI_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_MRI_NAME "Microtec C/C++"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_MRI,RTIBOOST_COMP_MRI_NAME)

#ifdef RTIBOOST_COMP_MRI_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_MRI_EMULATED,RTIBOOST_COMP_MRI_NAME)
#endif
