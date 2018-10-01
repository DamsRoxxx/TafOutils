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
#ifndef OMG_DDS_CORE_XTYPES_DYNAMIC_TYPE_HPP_
#define OMG_DDS_CORE_XTYPES_DYNAMIC_TYPE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/xtypes/detail/DynamicType.hpp>

/**
 * @defgroup DDSXTypesModule DynamicType and DynamicData
 * @ingroup DDSInfrastructureModule
 *
 * @brief Describes dds::core::xtypes::DynamicType, dds::core::xtypes::DynamicData
 * and related types and functions.
 *
 * DynamicType is a mechanism for representing
 * a type at runtime and DynamicData the way to instantiate data samples of a
 * DynamicType and manipulate data reflectively.
 */

namespace dds { namespace core { namespace xtypes {

typedef detail::DynamicType DynamicType;

/**
 * @relatesalso DynamicType
 * @brief Determines if a DynamicType is a PrimitiveType
 */
OMG_DDS_API
bool is_primitive_type(const DynamicType& t);

/**
 * @relatesalso DynamicType
 * @brief Determines if a DynamicType is a constructed type.
 *
 * This includes EnumType, AliasType, collection types and aggregation types.
 *
 * @see is_collection_type
 * @see is_aggregation_type
 */
OMG_DDS_API
bool is_constructed_type(const DynamicType& t);

/**
 * @relatesalso DynamicType
 * @brief Determines if a DynamicType is a CollectionType
 *
 * This includes ArrayType, SequenceType, StringType, and WStringType.
 */
OMG_DDS_API
bool is_collection_type(const DynamicType& t);

/**
 * @relatesalso DynamicType
 * @brief Determines if a DynamicType is an aggregation type
 *
 * This includes StructType and UnionType.
 */
OMG_DDS_API
bool is_aggregation_type(const DynamicType& t);

} } }

#endif // OMG_DDS_CORE_XTYPES_DYNAMIC_TYPE_HPP_
