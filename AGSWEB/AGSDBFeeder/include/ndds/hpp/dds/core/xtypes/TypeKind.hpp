#ifndef OMG_DDS_CORE_XTYPES_TYPE_KIND_HPP_
#define OMG_DDS_CORE_XTYPES_TYPE_KIND_HPP_

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

#include <bitset>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/SafeEnumeration.hpp>
#include <dds/core/detail/conformance.hpp>

#if defined(OMG_DDS_X_TYPES_DYNANIC_TYPE_SUPPORT)

// --- Shared meta-data: -------------------------------------------------

namespace dds {
  namespace core {
    namespace xtypes {
      /**
       * @ingroup DDSXTypesModule
       * @brief The definition of TypeKind
       */
      struct TypeKind_def {
        /**
         * @brief The underlying \p enum type
         */
        enum type {
          NO_TYPE           =  0, // sentinel indicating "null" value
          /**
           * @brief Flag indicating a primitive type
           * @see is_primitive_type
           */
          PRIMITIVE_TYPE    = 0x4000,
          /**
           * @brief Flag indicating a constructed type
           * @see is_constructed_type
           */
          CONSTRUCTED_TYPE  = 0x8000,
          /**
           * @brief Flag indicating a collection type
           * @see is_collection_type
           */
          COLLECTION_TYPE   = 0x0200,
          /**
           * @brief Flag indicating an aggreation type
           * @see is_aggregation_type
           */
          AGGREGATION_TYPE  = 0x0100,
          ANNOTATION_TYPE   = 0x0080,

          /**
           * @see PrimitiveType
           */
          BOOLEAN_TYPE     =  PRIMITIVE_TYPE | 0x0001,
          /**
           * @see PrimitiveType
           */
          UINT_8_TYPE      =  PRIMITIVE_TYPE | 0x0002,
          /**
           * @see PrimitiveType
           */
          INT_16_TYPE      =  PRIMITIVE_TYPE | 0x0003,
          /**
           * @see PrimitiveType
           */
          UINT_16_TYPE     =  PRIMITIVE_TYPE | 0x0004,
          /**
           * @see PrimitiveType
           */
          INT_32_TYPE      =  PRIMITIVE_TYPE | 0x0005,
          /**
           * @see PrimitiveType
           */
          UINT_32_TYPE     =  PRIMITIVE_TYPE | 0x0006,
          /**
           * @see PrimitiveType
           */
          INT_64_TYPE      =  PRIMITIVE_TYPE | 0x0007,
          /**
           * @see PrimitiveType
           */
          UINT_64_TYPE     =  PRIMITIVE_TYPE | 0x0008,
          /**
           * @see PrimitiveType
           */
          FLOAT_32_TYPE    =  PRIMITIVE_TYPE | 0x0009,
          /**
           * @see PrimitiveType
           */
          FLOAT_64_TYPE    =  PRIMITIVE_TYPE | 0x000A,
          /**
           * @brief Indicates a PrimitiveType<rti::core::LongDouble>
           * @see PrimitiveType
           */
          FLOAT_128_TYPE   =  PRIMITIVE_TYPE | 0x000B,
          /**
           * @see PrimitiveType
           */
          CHAR_8_TYPE      =  PRIMITIVE_TYPE | 0x000C,
          CHAR_32_TYPE     =  PRIMITIVE_TYPE | 0x000D,

          /**
           * @brief Indicates an EnumType
           */
          ENUMERATION_TYPE = CONSTRUCTED_TYPE | 0x0001,
          BITSET_TYPE      = CONSTRUCTED_TYPE | 0x0002,

          /**
           * @brief Indicates an AliasType
           */
          ALIAS_TYPE       = CONSTRUCTED_TYPE | 0x0003,
          /**
           * @brief Indicates an ArrayType
           */
          ARRAY_TYPE       = CONSTRUCTED_TYPE | COLLECTION_TYPE | 0x0004,
          /**
           * @brief Indicates a SequenceType
           */
          SEQUENCE_TYPE    = CONSTRUCTED_TYPE | COLLECTION_TYPE | 0x0005,
          /**
           * @brief Indicates a StringType
           */
          STRING_TYPE      = CONSTRUCTED_TYPE | COLLECTION_TYPE | 0x0006,
          /**
           * @brief Indicates a WStringType
           */
          // Spec Issue: missing WSTRING kind
          WSTRING_TYPE     = CONSTRUCTED_TYPE | COLLECTION_TYPE | 0x0008,
          MAP_TYPE         = CONSTRUCTED_TYPE | COLLECTION_TYPE | 0x0007,
          /**
           * @brief Indicates a UnionType
           */
          UNION_TYPE       = CONSTRUCTED_TYPE | AGGREGATION_TYPE | 0x0008,
          /**
           * @brief Indicates a StructType
           */
          STRUCTURE_TYPE   = CONSTRUCTED_TYPE | AGGREGATION_TYPE | 0x0009,
          UNION_FWD_DECL_TYPE       = CONSTRUCTED_TYPE | AGGREGATION_TYPE | 0x000A,
          STRUCTURE_FWD_DECL_TYPE   = CONSTRUCTED_TYPE | AGGREGATION_TYPE | 0x000B
        };
      };

      /**
       * @ingroup DDSXTypesModule
       * @brief The different type kinds
       *
       * The actual enumeration is in TypeKind_def.
       *
       * @see DynamicType::kind()
       */
      typedef dds::core::safe_enum<TypeKind_def> TypeKind;
    }
  }
}

#endif  // OMG_DDS_X_TYPES_DYNANIC_TYPE_SUPPORT
#endif // !defined(OMG_DDS_CORE_XTYPES_TYPE_KIND_HPP_)
