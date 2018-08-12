/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_DYNAMICDATAINFO_HPP_
#define RTI_DDS_CORE_XTYPES_DYNAMICDATAINFO_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_dynamicdata.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/String.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core { namespace xtypes {

class DynamicDataInfo;

} // namespace xtypes

typedef PODNativeAdapter<DDS_DynamicDataInfo> DynamicDataInfoNativeAdapter;

template <>
struct native_type_traits<xtypes::DynamicDataInfo> {
    typedef DynamicDataInfoNativeAdapter adapter_type;
    typedef DynamicDataInfoNativeAdapter::native_type native_type;
};

namespace xtypes {

struct DynamicDataEncapsulationKind_def {
    enum type {
        /*i \dref_DynamicDataEncapsulationKind_CDR_BE
         */
        CDR_BIG_ENDIAN = DDS_DYNAMIC_DATA_CDR_BE_ENCAPSULATION_KIND,

        /*i \dref_DynamicDataEncapsulationKind_CDR_LE
         */
        CDR_LITTLE_ENDIAN = DDS_DYNAMIC_DATA_CDR_LE_ENCAPSULATION_KIND,

        /*i \dref_DynamicDataEncapsulationKind_PL_CDR_BE
         */
        PL_CDR_BIG_ENDIAN = DDS_DYNAMIC_DATA_PL_CDR_BE_ENCAPSULATION_KIND,

        /*i \dref_DynamicDataEncapsulationKind_PL_CDR_LE
         */
        PL_CDR_LITTLE_ENDIAN = DDS_DYNAMIC_DATA_PL_CDR_LE_ENCAPSULATION_KIND,

        /*i \dref_DynamicDataEncapsulationKind_DEFAULT
         */
        DEFAULT = DDS_DYNAMIC_DATA_ENCAPSULATION_KIND_DEFAULT
    };
};

typedef dds::core::safe_enum<DynamicDataEncapsulationKind_def>
    DynamicDataEncapsulationKind;

/**
 * @ingroup DDSXTypesModule
 * @RTI_class_definition class DynamicDataInfo
 * @brief Contains information about a DynamicData sample
 *
 * @see DynamicData::info()
 */
class OMG_DDS_API DynamicDataInfo :
    public NativeValueType<DynamicDataInfo> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DynamicDataInfo)

    DynamicDataInfo() {}

    /**
     * @brief The number of members of this sample
     */
    int32_t member_count() const;

    /**
     * @brief The number of bytes currently used to store the data of this sample.
     */
    int32_t stored_size() const;

    /*i \dref_DynamicDataInfo_encapsulation_kind
     */
    DynamicDataEncapsulationKind encapsulation_kind() const;

    /*i \dref_DynamicDataInfo_is_optimized_storage
     */
    bool is_optimized_storage() const;

};

} } } // namespace rti::core::xtypes

#endif // RTI_DDS_CORE_XTYPES_DYNAMICDATAINFO_HPP_
