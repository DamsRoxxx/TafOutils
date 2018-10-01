#ifndef OMG_DDS_CORE_DETAIL_INT_TYPES_HPP_
#define OMG_DDS_CORE_DETAIL_INT_TYPES_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This implementation-defined header stands in for the C99 header files
 * inttypes.h. Under toolchains that support inttypes.h, this header can
 * simply include that one. Under toolchains that do not, this header must
 * provide equivalent definitions.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
   typedef signed __int8    int8_t;
   typedef signed __int16   int16_t;
   typedef signed __int32   int32_t;
   typedef unsigned __int8  uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef signed __int64   int64_t;
   typedef unsigned __int64 uint64_t;
#elif defined(_WRS_KERNEL) && (_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR < 9)
   #include <types/vxTypes.h>
   typedef unsigned char uint8_t;
   typedef short int16_t;
   typedef unsigned short uint16_t;
   typedef long long int64_t;
   typedef unsigned long long uint64_t;
#elif defined(_WRS_KERNEL) // 6.9 and above
    #include <stdint.h>
#else
    #include <inttypes.h>
#endif

#include "dds_c/dds_c_common.h"

namespace rti { namespace core {

// ::int64_t and DDS_LongLong (long long) are not exactly equivalent in all
// platforms. In some cases the alignment is different. For that reason in
// generated IDL code we need to use rti::core::int64_t.

// TODO: document (where?)
typedef DDS_LongLong int64;
typedef DDS_UnsignedLongLong uint64;

} }

#endif /* OMG_DDS_CORE_DETAIL_INT_TYPES_HPP_ */
