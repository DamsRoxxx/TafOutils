/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_DYNAMICDATAPROPERTY_HPP_
#define RTI_DDS_CORE_XTYPES_DYNAMICDATAPROPERTY_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_dynamicdata.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core { namespace xtypes {

class DynamicDataProperty;
class DynamicDataTypeSerializationProperty;

} // namespace xtypes

class DynamicDataPropertyNativeAdapter
    : public PODNativeAdapter<DDS_DynamicDataProperty_t> {
public:
    static void initialize(native_type& native_value)
    {
        PODNativeAdapter<DDS_DynamicDataProperty_t>::initialize(native_value);

        static DDS_DynamicDataProperty_t DEFAULT =
            DDS_DynamicDataProperty_t_INITIALIZER;
        native_value = DEFAULT;
    }
};

class DynamicDataTypeSerializationPropertyNativeAdapter
    : public PODNativeAdapter<DDS_DynamicDataTypeSerializationProperty_t> {
public:
    static void initialize(native_type& native_value)
    {
        PODNativeAdapter<DDS_DynamicDataTypeSerializationProperty_t>::initialize(native_value);

        static DDS_DynamicDataTypeSerializationProperty_t DEFAULT =
            DDS_DynamicDataTypeSerializationProperty_t_INITIALIZER;
        native_value = DEFAULT;
    }
};

template <>
struct native_type_traits<xtypes::DynamicDataProperty> {
    typedef DynamicDataPropertyNativeAdapter adapter_type;
    typedef DynamicDataPropertyNativeAdapter::native_type native_type;
};

template <>
struct native_type_traits<xtypes::DynamicDataTypeSerializationProperty> {
    typedef DynamicDataTypeSerializationPropertyNativeAdapter adapter_type;
    typedef DynamicDataTypeSerializationPropertyNativeAdapter::native_type native_type;
};

namespace xtypes {

class OMG_DDS_API DynamicDataProperty :
    public NativeValueType<DynamicDataProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DynamicDataProperty)

public:
    static OMG_DDS_API_CLASS_VARIABLE const DynamicDataProperty DEFAULT;

    DynamicDataProperty()
    {
        // Base initializes default values
    }

    DynamicDataProperty(
        int32_t the_buffer_initial_size,
        int32_t the_buffer_max_size,
        int32_t the_buffer_max_size_increment,
        bool the_buffer_check_size)
    {
        buffer_initial_size(the_buffer_initial_size);
        buffer_max_size(the_buffer_max_size);
        buffer_max_size_increment(the_buffer_max_size_increment);
        buffer_check_size(the_buffer_check_size);
    }


    int32_t buffer_initial_size() const
    {
        return native().buffer_initial_size;
    }

    DynamicDataProperty& buffer_initial_size(int32_t value)
    {
        native().buffer_initial_size = value;
        return *this;
    }

    int32_t buffer_max_size() const
    {
        return native().buffer_max_size;
    }

    DynamicDataProperty& buffer_max_size(int32_t value)
    {
        native().buffer_max_size = value;
        return *this;
    }

    int32_t buffer_max_size_increment() const
    {
        return native().buffer_max_size_increment;
    }

    DynamicDataProperty& buffer_max_size_increment(int32_t value)
    {
        native().buffer_max_size_increment = value;
        return *this;
    }

    bool buffer_check_size() const
    {
        return native().buffer_check_size == DDS_BOOLEAN_TRUE;
    }

    DynamicDataProperty& buffer_check_size(bool value)
    {
        native().buffer_check_size = value;
        return *this;
    }
};

/**
 * @RTI_class_definition class DynamicDataTypeSerializationProperty
 * @ingroup DDSXTypesModule
 * @headerfile rti/core/xtypes/DynamicDataProperty.hpp
 *
 * @brief @extension @st_value_type Configures aspects of the memory management in the serialization
 * of dds::core::xtypes::DynamicData samples.
 *
 * @see rti::domain::register_type(dds::domain::DomainParticipant&,const std::string&, const dds::core::xtypes::DynamicType&, const rti::core::xtypes::DynamicDataTypeSerializationProperty&)
 */
class OMG_DDS_API DynamicDataTypeSerializationProperty :
    public NativeValueType<DynamicDataTypeSerializationProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DynamicDataTypeSerializationProperty)

public:
    /**
     * @brief Default configuration
     */
    static const DynamicDataTypeSerializationProperty DEFAULT;

    /**
     * @brief Default configuration
     */
    DynamicDataTypeSerializationProperty()
    {
        // Base initializes default values
    }

    /**
     * @brief Specifies all the serialization parameters
     */
    DynamicDataTypeSerializationProperty(
        int32_t the_max_size_serialized,
        int32_t the_min_size_serialized,
        bool the_trim_to_size,
        bool the_enable_fast_deserialization)
    {
        max_size_serialized(the_max_size_serialized);
        min_size_serialized(the_min_size_serialized);
        trim_to_size(the_trim_to_size);
        enable_fast_deserialization(the_enable_fast_deserialization);
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    uint32_t max_size_serialized() const
    {
        return native().max_size_serialized;
    }

    /**
     * \dref_DynamicDataTypeSerializationProperty_t_max_size_serialized
     */
    DynamicDataTypeSerializationProperty& max_size_serialized(uint32_t value)
    {
        native().max_size_serialized = value;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    uint32_t min_size_serialized() const
    {
        return native().min_size_serialized;
    }

    /**
     * \dref_DynamicDataTypeSerializationProperty_t_min_size_serialized
     */
    DynamicDataTypeSerializationProperty& min_size_serialized(uint32_t value)
    {
        native().min_size_serialized = value;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool trim_to_size() const
    {
        return native().trim_to_size == DDS_BOOLEAN_TRUE;
    }

    /**
     * \dref_DynamicDataTypeSerializationProperty_t_trim_to_size
     */
    DynamicDataTypeSerializationProperty& trim_to_size(bool value)
    {
        native().trim_to_size = value;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_fast_deserialization() const
    {
        return native().enable_fast_deserialization == DDS_BOOLEAN_TRUE;
    }

    // not publicly exposed
    DynamicDataTypeSerializationProperty& enable_fast_deserialization(bool value)
    {
        native().enable_fast_deserialization = value;
        return *this;
    }
};


} } } // namespace rti::core::xtypes

#endif // RTI_DDS_CORE_XTYPES_DYNAMICDATAPROPERTY_HPP_
