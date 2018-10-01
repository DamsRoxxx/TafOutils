/*
Copyright Charly Chevalier 2015
Copyright Joel Falcou 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_HARDWARE_SIMD_PPC_H
#define RTIBOOST_PREDEF_HARDWARE_SIMD_PPC_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/hardware/simd/ppc/versions.h>

/*`
 [heading `RTIBOOST_HW_SIMD_PPC`]

 The SIMD extension for PowerPC (*if detected*).
 Version number depends on the most recent detected extension.

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__VECTOR4DOUBLE__`] [__predef_detection__]]

     [[`__ALTIVEC__`] [__predef_detection__]]
     [[`__VEC__`] [__predef_detection__]]

     [[`__VSX__`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__VECTOR4DOUBLE__`] [RTIBOOST_HW_SIMD_PPC_QPX_VERSION]]

     [[`__ALTIVEC__`] [RTIBOOST_HW_SIMD_PPC_VMX_VERSION]]
     [[`__VEC__`] [RTIBOOST_HW_SIMD_PPC_VMX_VERSION]]

     [[`__VSX__`] [RTIBOOST_HW_SIMD_PPC_VSX_VERSION]]
     ]

 */

#define RTIBOOST_HW_SIMD_PPC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#undef RTIBOOST_HW_SIMD_PPC
#if !defined(RTIBOOST_HW_SIMD_PPC) && defined(__VECTOR4DOUBLE__)
#   define RTIBOOST_HW_SIMD_PPC RTIBOOST_HW_SIMD_PPC_QPX_VERSION
#endif
#if !defined(RTIBOOST_HW_SIMD_PPC) && defined(__VSX__)
#   define RTIBOOST_HW_SIMD_PPC RTIBOOST_HW_SIMD_PPC_VSX_VERSION
#endif
#if !defined(RTIBOOST_HW_SIMD_PPC) && (defined(__ALTIVEC__) || defined(__VEC__))
#   define RTIBOOST_HW_SIMD_PPC RTIBOOST_HW_SIMD_PPC_VMX_VERSION
#endif

#if !defined(RTIBOOST_HW_SIMD_PPC)
#   define RTIBOOST_HW_SIMD_PPC RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE
#else
#   define RTIBOOST_HW_SIMD_PPC_AVAILABLE
#endif

#define RTIBOOST_HW_SIMD_PPC_NAME "PPC SIMD"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_HW_SIMD_PPC, RTIBOOST_HW_SIMD_PPC_NAME)
