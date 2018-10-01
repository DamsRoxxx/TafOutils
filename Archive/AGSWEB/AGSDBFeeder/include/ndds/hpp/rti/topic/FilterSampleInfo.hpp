/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_FILTER_SAMPLE_INFO_HPP_
#define RTI_DDS_CORE_FILTER_SAMPLE_INFO_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/SampleIdentity.hpp>

namespace rti { namespace topic {
     class FilterSampleInfo;
} }


namespace rti { namespace core {

class FilterSampleInfoAdapter {
public:
    typedef struct DDS_FilterSampleInfo native_type;

    static void initialize(native_type& native_value)
    {
        DDS_FilterSampleInfo_initialize(&native_value);
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_FilterSampleInfo_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return 
            (DDS_FilterSampleInfo_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

template <>
struct native_type_traits<rti::topic::FilterSampleInfo> {
    typedef rti::core::FilterSampleInfoAdapter adapter_type;
    typedef DDS_FilterSampleInfo native_type;
};

} } // namespace rti::core

namespace rti { namespace topic {

/** 
 * @ingroup DDSCustomContentFilterModule
 * @headerfile rti/topic/FilterSampleInfo.hpp 
 * @RTI_class_definition class FilterSampleInfo 
 * @brief @extension @st_value_type Provides meta information associated with 
 * the sample. 
 *  
 * \dref_details_FilterSampleInfo 
 *  
 */
class FilterSampleInfo : public rti::core::NativeValueType<FilterSampleInfo> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(FilterSampleInfo)

    typedef rti::core::NativeValueType<FilterSampleInfo> Base;
public:
    FilterSampleInfo() 
    {
    }

    FilterSampleInfo(const struct DDS_FilterSampleInfo &native_filter_sample_info) 
      : Base(native_filter_sample_info)
    {
    }

    /**
     * @brief Get the identity of another sample related to this one. 
     *  
     * \dref_details_FilterSampleInfo_related_sample_identity
     */
    rti::core::SampleIdentity related_sample_identity() const
    {
        return native().related_sample_identity;
    }

    /**
     * @brief Get a positive integer designating the relative priority of the 
     * sample, used to determine the transmission order of pending transmissions.
     *  
     * \dref_details_FilterSampleInfo_priority
     */
    int32_t priority() const
    {
        return native().priority;
    }

};

} } // namespace rti::topic

#endif // RTI_DDS_CORE_FILTER_SAMPLE_INFO_HPP_
