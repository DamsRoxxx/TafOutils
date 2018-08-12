/*
Copyright Charly Chevalier 2015
Copyright Joel Falcou 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef RTIBOOST_PREDEF_HARDWARE_SIMD_ARM_H
#define RTIBOOST_PREDEF_HARDWARE_SIMD_ARM_H

#include <rtiboost/predef/version_number.h>
#include <rtiboost/predef/hardware/simd/arm/versions.h>

/*`
 [heading `RTIBOOST_HW_SIMD_ARM`]

 The SIMD extension for ARM (*if detected*).
 Version number depends on the most recent detected extension.

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__ARM_NEON__`] [__predef_detection__]]
     [[`__aarch64__`] [__predef_detection__]]
     [[`_M_ARM`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__ARM_NEON__`] [RTIBOOST_HW_SIMD_ARM_NEON_VERSION]]
     [[`__aarch64__`] [RTIBOOST_HW_SIMD_ARM_NEON_VERSION]]
     [[`_M_ARM`] [RTIBOOST_HW_SIMD_ARM_NEON_VERSION]]
     ]

 */

#define RTIBOOST_HW_SIMD_ARM RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE

#undef RTIBOOST_HW_SIMD_ARM
#if !defined(RTIBOOST_HW_SIMD_ARM) && (defined(__ARM_NEON__) || defined(__aarch64__) || defined (_M_ARM))
#   define RTIBOOST_HW_SIMD_ARM RTIBOOST_HW_SIMD_ARM_NEON_VERSION
#endif

#if !defined(RTIBOOST_HW_SIMD_ARM)
#   define RTIBOOST_HW_SIMD_ARM RTIBOOST_VERSION_NUMBER_NOT_AVAILABLE
#else
#   define RTIBOOST_HW_SIMD_ARM_AVAILABLE
#endif

#define RTIBOOST_HW_SIMD_ARM_NAME "ARM SIMD"

#endif

#include <rtiboost/predef/detail/test.h>
RTIBOOST_PREDEF_DECLARE_TEST(RTIBOOST_HW_SIMD_ARM, RTIBOOST_HW_SIMD_ARM_NAME)
