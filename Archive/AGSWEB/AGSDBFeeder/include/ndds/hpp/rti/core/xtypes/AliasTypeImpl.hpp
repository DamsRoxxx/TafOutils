/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_ALIASTYPE_HPP_
#define RTI_DDS_CORE_XTYPES_ALIASTYPE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/vector.hpp>
#include <dds/core/xtypes/DynamicType.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

/**
 * @RTI_class_definition class AliasType : public DynamicType
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/AliasType.hpp
 * @brief @st_value_type Represents and IDL \p typedef
 */
class OMG_DDS_API AliasTypeImpl : public DynamicTypeImpl {
public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(AliasTypeImpl, DynamicTypeImpl)

    /**
     * @brief Creates an alias with a name and a related type
     *
     * @param name The name of this alias
     * @param related_type The aliased type
     * @param is_pointer Whether this alias makes the type a pointer
     *
     * For example, to create the following two IDL aliases:
     * \code
     * typedef long my_long;
     * typedef long * my_long_ptr;
     * \endcode
     *
     * We can use the following code:
     * \code
     * AliasType my_long("my_long", primitive_type<int32_t>());
     * AliasType my_long_ptr("my_long_ptr", primitive_type<int32_t>(), true);
     * \endcode
     */
    AliasTypeImpl(
        const std::string& name,
        const DynamicTypeImpl& related_type,
        bool is_pointer = false);

    /**
     * @brief Gets the related type
     */
    const dds::core::xtypes::DynamicType& related_type() const;

    /**
     * @brief @extension Gets whether this alias makes related_type a pointer.
     */
    bool is_pointer() const;
};

} } } // closing and reopening namespace for documentation purposes

namespace rti { namespace core { namespace xtypes {

/**
 * @relatesalso dds::core::xtypes::AliasType
 * @brief @extension If the type is an alias returns its related type recursively until
 * it is not an alias.
 */
OMG_DDS_API
const dds::core::xtypes::DynamicType& resolve_alias(
    const dds::core::xtypes::DynamicType& type);

} } } // namespace rti::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_ALIASTYPE_HPP_
