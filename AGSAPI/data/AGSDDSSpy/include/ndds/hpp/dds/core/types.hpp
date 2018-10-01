#ifndef OMG_DDS_CORE_TYPES_HPP_
#define OMG_DDS_CORE_TYPES_HPP_

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

// ISO C++ Includes
#include <string>
#include <vector>

// DDS Includes

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/detail/inttypes.hpp>
#include <dds/core/detail/conformance.hpp>

#ifdef RTI_NO_CXX11_HDR_TYPE_TRAITS
#include <rtiboost/type_traits/integral_constant.hpp>
#else
#include <type_traits>
#endif

/**
 * @defgroup DDSCPP2SupportingTypes Supporting Types and Constants
 * @ingroup DDSInfrastructureModule
 *
 * @brief Miscellaneous, general-purpose types and constants
 */

namespace dds { namespace core {

/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief A vector of bytes
 */
typedef std::vector<uint8_t> ByteSeq;

/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief A vector of strings
 */
typedef std::vector<std::string> StringSeq;

// DDS Null-Reference
#ifdef RTI_NO_CXX11_NULLPTR
/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief The type of dds::core::null
 */
class null_type {
};
#else

#include <cstddef>
/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief @st_cpp11 The type of dds::core::null
 */
typedef std::nullptr_t null_type;
#endif

/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief Indicates an empty reference
 * @see @st_ref_type
 */
extern OMG_DDS_API_VARIABLE const null_type null;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT    
namespace policy {

typedef uint16_t DataRepresentationId;
typedef std::vector<DataRepresentationId> DataRepresentationIdSeq;
}
#endif

namespace policy {
/**
 * @ingroup DDSQosTypesModule
 * @brief Identifies a Qos policy
 */
typedef uint32_t QosPolicyId;
}

#ifdef RTI_NO_CXX11_HDR_TYPE_TRAITS
typedef ::rtiboost::true_type true_type;
typedef ::rtiboost::false_type false_type;
#else
/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief True type used by trait types
 */
typedef ::std::true_type true_type;
/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief False type used by trait types
 */
typedef ::std::false_type false_type;
#endif

} } // namespace rti::core

#endif /* OMG_DDS_CORE_TYPES_HPP_ */
