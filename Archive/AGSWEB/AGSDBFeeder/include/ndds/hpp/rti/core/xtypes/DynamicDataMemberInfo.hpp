/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_DYNAMICDATAMEMBERINFO_HPP_
#define RTI_DDS_CORE_XTYPES_DYNAMICDATAMEMBERINFO_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_dynamicdata.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/String.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core { namespace xtypes {

class DynamicDataMemberInfo;

} // namespace xtypes

typedef PODNativeAdapter<DDS_DynamicDataMemberInfo> DynamicDataMemberInfoNativeAdapter;

template <>
struct native_type_traits<xtypes::DynamicDataMemberInfo> {
    typedef DynamicDataMemberInfoNativeAdapter adapter_type;
    typedef DynamicDataMemberInfoNativeAdapter::native_type native_type;
};

namespace xtypes {

/**
 * @ingroup DDSXTypesModule
 * @RTI_class_definition class DynamicDataMemberInfo
 * @brief Contains information about a DynamicData member
 *
 * @see DynamicData::member_info()
 */
class OMG_DDS_API DynamicDataMemberInfo :
    public NativeValueType<DynamicDataMemberInfo> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DynamicDataMemberInfo)

public:
    DynamicDataMemberInfo()
    {
    }

    /**
     * @brief The member index
     *
     * @see \ref DDSDynamicDataModule_member_name_id.
     */
    uint32_t member_index() const;

    /**
     * @brief The member name
     *
     * @see \ref DDSDynamicDataModule_member_name_id.
     */
    const dds::core::string& member_name() const;

    /**
     * @brief The type kind of the member
     *
     * This a convenience function, equivalent to looking up the member's
     * DynamicType::kind().
     *
     * @see DynamicData::type()
     * @see DynamicType::kind()
     */
    dds::core::xtypes::TypeKind member_kind() const;
    uint32_t representation_count() const;

    /**
     * @brief The number of elements in this member
     *
     * Only applies to members of ArrayType and SequenceType. For any other
     * type this is always zero.
     */
    uint32_t element_count() const;

    /**
     * @brief The type kind of the member
     *
     * This a convenience function, equivalent to looking up the member's
     * type's element type.
     *
     * @see DynamicData::type()
     * @see CollectionType::content_type()
     */
    dds::core::xtypes::TypeKind element_kind() const;
};

} } } // namespace rti::core::xtypes

#endif // RTI_DDS_CORE_XTYPES_DYNAMICDATAMEMBERINFO_HPP_
