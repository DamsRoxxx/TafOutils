/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_PROTOCOL_VERSION_HPP_
#define RTI_DDS_CORE_PROTOCOL_VERSION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

class ProtocolVersionAdapter {
public:
    typedef struct DDS_ProtocolVersion_t native_type;

    static void initialize(native_type& native_value)
    {
        native_value.major = 0;
        native_value.minor = 0;
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        destination = source;
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (first.major == second.major && 
                first.minor == second.minor);
    }
};

class ProtocolVersion;

template <>
struct native_type_traits<ProtocolVersion> {
    typedef rti::core::ProtocolVersionAdapter adapter_type;
    typedef DDS_ProtocolVersion_t native_type;
};

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @RTI_class_definition class ProtocolVersion
 * @headerfile rti/core/ProtocolVersion.hpp
 *
 * @brief @extension Represents the current version of \ndds
 */
class ProtocolVersion : public NativeValueType<ProtocolVersion> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ProtocolVersion)

    typedef NativeValueType<ProtocolVersion> Base;
public:

    /**
     * @brief Creates an invalid protocol version
     */
    ProtocolVersion()
    {
    }

    /**
     * @brief Creates a version with the given major and minor values
     */
    ProtocolVersion(uint8_t major, uint8_t minor)
    {
        native().major = major;
        native().minor = minor;
    }


    ProtocolVersion(const struct DDS_ProtocolVersion_t &native_protocol_version) 
      : Base(native_protocol_version)
    {
    }

    /**
     * @brief The major version number
     */
    uint8_t major_version() const
    {
        return native().major;
    }

    /**
     * @brief The minor version number
     */
    uint8_t minor_version() const
    {
        return native().minor;
    }

    /**
     * \dref_ProtocolVersion_t_PROTOCOLVERSION
     */
    static ProtocolVersion current()
    {
        static const DDS_ProtocolVersion_t current_version
            = DDS_PROTOCOLVERSION;
        return current_version;
    }
};

} }

#endif // RTI_DDS_CORE_PROTOCOL_VERSION_HPP_
