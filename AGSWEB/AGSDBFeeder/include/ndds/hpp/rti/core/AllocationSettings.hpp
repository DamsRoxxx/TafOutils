/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_ALLOCATION_SETTINGS_HPP_
#define RTI_DDS_CORE_ALLOCATION_SETTINGS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

typedef PODNativeAdapter<DDS_AllocationSettings_t> AllocationSettingsAdapter;

class AllocationSettings;

template <>
struct native_type_traits<AllocationSettings> {
    typedef rti::core::AllocationSettingsAdapter adapter_type;
    typedef DDS_AllocationSettings_t native_type;
};

/**
 * @RTI_class_definition class AllocationSettings
 * @ingroup DDSDomainParticipantResourceLimitsQosModule
 * @headerfile rti/core/AllocationSettings.hpp
 *
 * @brief @extension Resource allocation settings
 *
 * @details \dref_details_AllocationSettings_t
 */
class AllocationSettings : public NativeValueType<AllocationSettings> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(AllocationSettings)

    typedef NativeValueType<AllocationSettings> Base;
public:
    /**
     * @brief Creates an instance with an initial, max and incremental count
     * set to zero.
     */
    AllocationSettings() 
    {
    }

    /**
     * @brief Creates an instance with the given initial, maximum and
     * incremental values
     */
    AllocationSettings(
        int32_t the_initial_count, 
        int32_t the_max_count,
        int32_t the_incremental_count)
    {
        initial_count(the_initial_count);
        max_count(the_max_count);
        incremental_count(the_incremental_count);
    }

    AllocationSettings(const DDS_AllocationSettings_t& native_settings) 
      : Base(native_settings)
    {
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_count() const 
    {
        return native().initial_count;
    }

    /**
     * @brief Sets the initial count of resources
     *
     * @details \dref_details_AllocationSettings_t_initial_count
     */
    AllocationSettings& initial_count(int32_t the_initial_count)
    {
        native().initial_count = the_initial_count;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_count() const 
    {
        return native().max_count;
    }

    /**
     * @brief Sets the maximum count of resources
     *
     * @details \dref_details_AllocationSettings_t_max_count
     */
    AllocationSettings& max_count(int32_t the_max_count)
    {
        native().max_count = the_max_count;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t incremental_count() const
    {
        return native().incremental_count;
    }

    /**
     * @brief Sets the incremental count of resources
     *
     * @details \dref_details_AllocationSettings_t_incremental_count
     */
    AllocationSettings& incremental_count(int32_t the_incremental_count)
    {
        native().incremental_count = the_incremental_count;
        return *this;
    }
};

} }

#endif // RTI_DDS_CORE_ALLOCATION_SETTINGS_HPP_
