/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_GUID_HPP_
#define RTI_DDS_CORE_GUID_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/array.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

class GuidAdapter {
public:
    typedef struct DDS_GUID_t native_type;

    static void initialize(native_type& native_value)
    {
        native_value = DDS_GUID_UNKNOWN;
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_GUID_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_GUID_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

class Guid;

template <>
struct native_type_traits<Guid> {
    typedef rti::core::GuidAdapter adapter_type;
    typedef DDS_GUID_t native_type;
};

/** 
 * @ingroup DDSInfrastructureModule 
 * @RTI_class_definition class Guid 
 * @headerfile "rti/core/Guid.hpp"
 *  
 * @brief @extension @st_value_type Class for GUID (Global Unique Identifier)
 * representation   
 */
class OMG_DDS_API Guid : public NativeValueType<Guid> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Guid)

    typedef NativeValueType<Guid> Base;
    typedef dds::core::array<uint8_t, 16> ByteArray;

    /**
     * @brief The number of elements of a Guid
     */
    static const size_t LENGTH = 16;

    /**
     * @brief Create a default Guid representing the unknown guid
     */
    Guid()
    {
    }

    Guid(const struct DDS_GUID_t &native_guid) : Base(native_guid)
    {
    }

    /**
     * @brief Unknown GUID.
     */
    static Guid unknown()
    {
        return Guid(DDS_GUID_UNKNOWN);
    }

    /**
     * @brief Construct a Guid indicating that RTI Connext should choose an
     * appropriate virtual GUID.
     *
     * @dref_GUID_t_AUTO
     */
    static Guid automatic()
    {
        return Guid(DDS_GUID_AUTO);
    }

    /**
     * @brief Get a reference to value of the Guid at position index
     */
    uint8_t& operator[](uint32_t index);

    /**
     * @brief Get const reference to the value of the Guid at position index
     */
    const uint8_t& operator[](uint32_t index) const;
    
    /**
     * @brief Compare two Guids for a less-than relationship
     */
    bool operator<(const Guid& other) const;

    /**
     * @brief Compare two Guids for a less-than-or-equal relationship
     */
    bool operator<=(const Guid& other) const;

    /**
     * @brief Compare two Guids for a greater-than relationship
     */
    bool operator>(const Guid& other) const;

    /**
     * @brief Compare two Guids for a greater-than-or-equal relationship
     */
    bool operator>=(const Guid& other) const;

};

/**
 * @relates rti::core::Guid
 *
 * @brief Prints a Guid to an output stream
 */
OMG_DDS_API
std::ostream& operator<<(std::ostream& out, const Guid& guid);

} } // namespace rti::core

#endif // RTI_DDS_CORE_GUID_HPP_
