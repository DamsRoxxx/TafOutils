/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_COMPILER_GCC_XML_H
#define RTIBOOST_PREDEF_COMPILER_GCC_XML_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_COMP_GCCXML`]

[@http://www.gccxml.org/ GCC XML] compiler.

[table
    [[__predef_symbol__] [__predef_version__]]

    [[`__GCCXML__`] [__predef_detection__]]
    ]
 */

#define RTIBOOST_COMP_GCCXML RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__GCCXML__)
#   define RTIBOOST_COMP_GCCXML_DETECTION RTIBOOST_VERSION_NUMBER_AVAILABLE
#endif

#ifdef RTIBOOST_COMP_GCCXML_DETECTION
#   if defined(RTIBOOST_PREDEF_DETAIL_COMP_DETECTED)
#       define RTIBOOST_COMP_GCCXML_EMULATED RTIBOOST_COMP_GCCXML_DETECTION
#   else
#       undef RTIBOOST_COMP_GCCXML
#       define RTIBOOST_COMP_GCCXML RTIBOOST_COMP_GCCXML_DETECTION
#   endif
#   define RTIBOOST_COMP_GCCXML_AVAILABLE
#   include <rtiboost/predef/detail/comp_detected.h>
#endif

#define RTIBOOST_COMP_GCCXML_NAME "GCC XML"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_GCCXML,RTIBOOST_COMP_GCCXML_NAME)

#ifdef RTIBOOST_COMP_GCCXML_EMULATED
#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_COMP_GCCXML_EMULATED,RTIBOOST_COMP_GCCXML_NAME)
#endif
