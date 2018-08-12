/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_THREAD_SETTINGS_HPP_
#define RTI_DDS_CORE_THREAD_SETTINGS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/SafeEnumeration.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/vector.hpp>
#include <rti/core/NativeValueType.hpp>
#include <bitset>

namespace rti { namespace core {

/** 
 * \dref_ThreadSettingsCpuRotationKind
 */
struct ThreadSettingsCpuRotationKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * \dref_ThreadSettingsCpuRotationKind_THREAD_SETTINGS_CPU_NO_ROTATION
       */
      NO_ROTATION = DDS_THREAD_SETTINGS_CPU_NO_ROTATION,
      /**
       * \dref_ThreadSettingsCpuRotationKind_THREAD_SETTINGS_CPU_RR_ROTATION
       */
      ROUND_ROBIN = DDS_THREAD_SETTINGS_CPU_RR_ROTATION
  };
};

/** 
 * @ingroup DDSThreadSettingsModule
 * @brief @ref SafeEnumModule of @ref ThreadSettingsCpuRotationKind_def 
 * @see @ref ThreadSettingsCpuRotationKind_def 
 */ 
typedef dds::core::safe_enum<ThreadSettingsCpuRotationKind_def> ThreadSettingsCpuRotationKind;

/**
 * @RTI_class_definition class ThreadSettingsKindMask : public std::bitset<4>
 * @ingroup DDSThreadSettingsModule
 * @headerfile rti/core/ThreadSettings.hpp
 *
 * @brief @extension A collection of flags used to configure threads of execution
 *
 * Not all of these options may be relevant for all operating
 * systems. Consult \ref_url_platform_notes for additional details.
 */
class ThreadSettingsKindMask : public std::bitset<4> {
public:
    /**
     * @brief The base type, a std::bitset
     */
    typedef std::bitset<4> MaskType;

public:
    /**
     * @brief The dfault thread settings mask
     */
    ThreadSettingsKindMask()
        : MaskType((int)DDS_THREAD_SETTINGS_KIND_MASK_DEFAULT)
    {
    }

    /**
     * @brief Create from the bits in an integer
     */
    explicit ThreadSettingsKindMask(uint64_t mask) 
        : MaskType(mask)
    {
    }

    /**
     * @brief Create from a std::bitset
     */
    ThreadSettingsKindMask(const MaskType& mask) 
        : MaskType(mask)
    {
    }

    /**
     * \dref_ThreadSettingsKind_THREAD_SETTINGS_FLOATING_POINT
     */
    static const ThreadSettingsKindMask floating_point()
    {
        return ThreadSettingsKindMask(DDS_THREAD_SETTINGS_FLOATING_POINT);
    }

    /**
     * \dref_ThreadSettingsKind_THREAD_SETTINGS_STDIO
     */
    static const ThreadSettingsKindMask stdio()
    {
        return ThreadSettingsKindMask(DDS_THREAD_SETTINGS_STDIO);
    }

    /**
     * \dref_ThreadSettingsKind_THREAD_SETTINGS_REALTIME_PRIORITY
     */
    static const ThreadSettingsKindMask realtime_priority()
    {
        return ThreadSettingsKindMask(DDS_THREAD_SETTINGS_REALTIME_PRIORITY);
    }

    /**
     * \dref_ThreadSettingsKind_THREAD_SETTINGS_PRIORITY_ENFORCE
     */
    static const ThreadSettingsKindMask priority_enforce()
    {
        return ThreadSettingsKindMask(DDS_THREAD_SETTINGS_PRIORITY_ENFORCE);
    }

    /**
     * \dref_ThreadSettingsKind_THREAD_SETTINGS_CANCEL_ASYNCHRONOUS
     */
    static const ThreadSettingsKindMask cancel_asynchronous()
    {
        return ThreadSettingsKindMask(DDS_THREAD_SETTINGS_CANCEL_ASYNCHRONOUS);
    }
};

class ThreadSettingsAdapter {
public:
    typedef struct DDS_ThreadSettings_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_ThreadSettings_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_ThreadSettings_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_ThreadSettings_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_ThreadSettings_is_equal(&first, &second) == RTI_TRUE);
    }
};

class ThreadSettings;

template <>
struct native_type_traits<ThreadSettings> {
    typedef rti::core::ThreadSettingsAdapter adapter_type;
    typedef DDS_ThreadSettings_t native_type;
};

/**
 * @RTI_class_definition class ThreadSettings
 * @ingroup DDSThreadSettingsModule
 * @headerfile rti/core/ThreadSettings.hpp
 *
 * @brief @extension The properties of a thread of execution.
 *
 * Consult \ref_url_platform_notes for additional platform specific details.
 *
 * @details \dref_details_ThreadSettings_t
 */
class OMG_DDS_API ThreadSettings : public NativeValueType<ThreadSettings> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ThreadSettings)

    typedef NativeValueType<ThreadSettings> Base;
public:
    /**
     * @brief Creates the default thread settings
     */
    ThreadSettings() { }

    /**
     * @brief Creates an instance with all the specified parameters
     */
    ThreadSettings(
        ThreadSettingsKindMask the_mask,
        int32_t the_priority, 
        int32_t the_stack_size, 
        dds::core::vector<int32_t> the_cpu_list, 
        ThreadSettingsCpuRotationKind::type the_cpu_rotation);

    ThreadSettings(const DDS_ThreadSettings_t& native_settings) 
      : Base(native_settings)
    {
    }

public:
    /**
     * @brief Getter (see setter with the same name)
     */
    ThreadSettingsKindMask mask() const;
    /**
     * \dref_ThreadSettings_t_mask
     */
    ThreadSettings& mask(ThreadSettingsKindMask the_mask);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t priority() const;
    /**
     * \dref_ThreadSettings_t_priority
     */
    ThreadSettings& priority(int32_t the_priority);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t stack_size() const;
    /**
     * \dref_ThreadSettings_t_stack_size
     */
    ThreadSettings& stack_size(int32_t the_stack_size);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::vector<int32_t> cpu_list() const;
    /**
     * \dref_ThreadSettings_t_cpu_list
     */
    ThreadSettings& cpu_list(const dds::core::vector<int32_t>& the_cpu_list);

    /**
     * @brief Getter (see setter with the same name)
     */
    ThreadSettingsCpuRotationKind cpu_rotation() const;
    /**
     * \dref_ThreadSettings_t_cpu_rotation
     */
    ThreadSettings& cpu_rotation(
        ThreadSettingsCpuRotationKind the_cpu_rotation);
};

} }

#endif // RTI_DDS_CORE_THREAD_SETTINGS_HPP_
