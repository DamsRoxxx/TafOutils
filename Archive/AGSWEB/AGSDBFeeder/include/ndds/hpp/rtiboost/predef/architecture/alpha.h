/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_ARCHITECTURE_ALPHA_H
#define RTIBOOST_PREDEF_ARCHITECTURE_ALPHA_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/make.h>

/*`
[heading `RTIBOOST_ARCH_ALPHA`]

[@http://en.wikipedia.org/wiki/DEC_Alpha DEC Alpha] architecture.

[table
    [[__predef_symbol__] [__predef_version__]]
    [[`__alpha__`] [__predef_detection__]]
    [[`__alpha`] [__predef_detection__]]
    [[`_M_ALPHA`] [__predef_detection__]]

    [[`__alpha_ev4__`] [4.0.0]]
    [[`__alpha_ev5__`] [5.0.0]]
    [[`__alpha_ev6__`] [6.0.0]]
    ]
 */

#define RTIBOOST_ARCH_ALPHA RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__alpha__) || defined(__alpha) || \
    defined(_M_ALPHA)
#   undef RTIBOOST_ARCH_ALPHA
#   if !defined(RTIBOOST_ARCH_ALPHA) && defined(__alpha_ev4__)
#       define RTIBOOST_ARCH_ALPHA RTIBOOST_VERSION_NUMBER(4,0,0)
#   endif
#   if !defined(RTIBOOST_ARCH_ALPHA) && defined(__alpha_ev5__)
#       define RTIBOOST_ARCH_ALPHA RTIBOOST_VERSION_NUMBER(5,0,0)
#   endif
#   if !defined(RTIBOOST_ARCH_ALPHA) && defined(__alpha_ev6__)
#       define RTIBOOST_ARCH_ALPHA RTIBOOST_VERSION_NUMBER(6,0,0)
#   endif
#   if !defined(RTIBOOST_ARCH_ALPHA)
#       define RTIBOOST_ARCH_ALPHA RTIBOOST_VERSION_NUMBER_AVAILABLE
#   endif
#endif

#if RTIBOOST_ARCH_ALPHA
#   define RTIBOOST_ARCH_ALPHA_AVAILABLE
#endif

#define RTIBOOST_ARCH_ALPHA_NAME "DEC Alpha"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_ARCH_ALPHA,RTIBOOST_ARCH_ALPHA_NAME)
