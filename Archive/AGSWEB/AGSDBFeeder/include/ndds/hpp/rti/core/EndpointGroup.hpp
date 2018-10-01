/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_ENDPOINT_GROUP_HPP_
#define RTI_DDS_CORE_ENDPOINT_GROUP_HPP_

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


class EndpointGroupAdapter {
public:
    typedef struct DDS_EndpointGroup_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_EndpointGroup_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_EndpointGroup_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_EndpointGroup_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_EndpointGroup_t_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

class EndpointGroup;

template <>
struct native_type_traits<EndpointGroup> {
    typedef rti::core::EndpointGroupAdapter adapter_type;
    typedef DDS_EndpointGroup_t native_type;
};

/**
 * @RTI_class_definition class EndpointGroup
 * @ingroup DDSAvailabilityQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Specifies a group of endpoints that can be collectively
 * identified by a name and satisfied by a quorum.
 *
 * @details \dref_details_EndpointGroup_t
 */
class EndpointGroup : public NativeValueType<EndpointGroup> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(EndpointGroup)

    typedef NativeValueType<EndpointGroup> Base;
public:
    // Default Ctor
    EndpointGroup() 
    {
    }

    /**
     * @brief Creates an instance with a role name and a quorum
     */
    EndpointGroup(
        const std::string& the_role_name, 
        int32_t the_quorum_count)
    {
        role_name(the_role_name);
        quorum_count(the_quorum_count);
    }

    EndpointGroup(const DDS_EndpointGroup_t& native_group) 
      : Base(native_group)
    {
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    std::string role_name() const 
    {
        if (native().role_name == NULL) {
            return "";
        }

        return native().role_name;
    }

    /**
     * \dref_EndpointGroup_t_role_name
     */
    EndpointGroup& role_name(const std::string& the_role_name)
    {
        if (!DDS_String_replace(&native().role_name, the_role_name.c_str())) {
            throw std::bad_alloc();
        }
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t quorum_count() const
    {
        return native().quorum_count;
    }

    /**
     * \dref_EndpointGroup_t_quorum_count
     */
    EndpointGroup& quorum_count(int32_t the_quorum_count)
    {
        native().quorum_count = the_quorum_count;
        return *this;
    }
};

/**
 * \dref_EndpointGroupSeq
 */
typedef dds::core::vector<EndpointGroup> EndpointGroupSeq;

} }

#endif // RTI_DDS_CORE_ENDPOINT_GROUP_HPP_
