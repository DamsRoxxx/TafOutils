/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_RTPS_WELL_KNOWN_PORTS_HPP_
#define RTI_DDS_CORE_RTPS_WELL_KNOWN_PORTS_HPP_

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

typedef PODNativeAdapter<DDS_RtpsWellKnownPorts_t> RtpsWellKnownPortsAdapter;

class RtpsWellKnownPorts;

template <>
struct native_type_traits<RtpsWellKnownPorts> {
    typedef rti::core::RtpsWellKnownPortsAdapter adapter_type;
    typedef DDS_RtpsWellKnownPorts_t native_type;
};

/**
 * @RTI_class_definition class RtpsWellKnownPorts
 * @ingroup DDSWireProtocolQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the mapping of the RTPS well-known ports
 *
 * @details \dref_details_RtpsWellKnownPorts_t
 */
class RtpsWellKnownPorts : public NativeValueType<RtpsWellKnownPorts> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(RtpsWellKnownPorts)

    typedef NativeValueType<RtpsWellKnownPorts> Base;

    /**
     * @brief Creates an instance that contains the default RTPS well-known ports
     */
    RtpsWellKnownPorts() 
    {
        static const DDS_RtpsWellKnownPorts_t DEFAULT = 
            DDS_RTPS_WELL_KNOWN_PORTS_DEFAULT;
        native() = DEFAULT;
    }

    /**
     * @brief Creates an instance with the specified ports
     *
     * See individual setters.
     */
    RtpsWellKnownPorts(
        int32_t the_port_base, 
        int32_t the_domain_id_gain, 
        int32_t the_participant_id_gain, 
        int32_t the_builtin_multicast_port_offset, 
        int32_t the_builtin_unicast_port_offset, 
        int32_t the_user_multicast_port_offset, 
        int32_t the_user_unicast_port_offset)
    {
        port_base(the_port_base);
        domain_id_gain(the_domain_id_gain);
        participant_id_gain(the_participant_id_gain);
        builtin_multicast_port_offset(the_builtin_multicast_port_offset);
        builtin_unicast_port_offset(the_builtin_unicast_port_offset);
        user_multicast_port_offset(the_user_multicast_port_offset);
        user_unicast_port_offset(the_user_unicast_port_offset);
    }

    RtpsWellKnownPorts(const struct DDS_RtpsWellKnownPorts_t& native_locator) 
      : Base(native_locator)
    {
    }

    /**
     * @brief Returns an instance containing the port mapping compliant with
     * the OMG DDS Interoperability wire protocol
     *
     * @details \dref_details_INTEROPERABLE_RTPS_WELL_KNOWN_PORTS
     */
    static RtpsWellKnownPorts Interoperable()
    {
        return RtpsWellKnownPorts().native() = 
            DDS_INTEROPERABLE_RTPS_WELL_KNOWN_PORTS;
    }

    /**
     * @brief Returns an instance containing the port mapping compatible with
     * previous versions of \ndds
     *
     * @details \dref_details_RTI_BACKWARDS_COMPATIBLE_RTPS_WELL_KNOWN_PORTS
     */
    static RtpsWellKnownPorts BackwardsCompatible()
    {
        return RtpsWellKnownPorts().native() = 
            DDS_RTI_BACKWARDS_COMPATIBLE_RTPS_WELL_KNOWN_PORTS;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t port_base() const 
    {
        return native().port_base;
    }

    /**
     * \dref_RtpsWellKnownPorts_t_port_base
     */
    RtpsWellKnownPorts& port_base(int32_t the_port_base)
    {
        native().port_base = the_port_base;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t domain_id_gain() const 
    {
        return native().domain_id_gain;
    }

    /**
     * \dref_RtpsWellKnownPorts_t_domain_id_gain
     */

    RtpsWellKnownPorts& domain_id_gain(int32_t the_domain_id_gain)
    {
        native().domain_id_gain = the_domain_id_gain;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t participant_id_gain() const 
    {
        return native().participant_id_gain;
    }

    /**
     * \dref_RtpsWellKnownPorts_t_participant_id_gain
     */
    RtpsWellKnownPorts& participant_id_gain(int32_t the_participant_id_gain)
    {
        native().participant_id_gain = the_participant_id_gain;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t builtin_multicast_port_offset() const 
    {
        return native().builtin_multicast_port_offset;
    }

    /**
     * \dref_RtpsWellKnownPorts_t_builtin_multicast_port_offset
     */
    RtpsWellKnownPorts& builtin_multicast_port_offset(
        int32_t the_builtin_multicast_port_offset)
    {
        native().builtin_multicast_port_offset = 
            the_builtin_multicast_port_offset;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t builtin_unicast_port_offset() const 
    {
        return native().builtin_unicast_port_offset;
    }

    /**
     * \dref_RtpsWellKnownPorts_t_builtin_unicast_port_offset
     */
    RtpsWellKnownPorts& builtin_unicast_port_offset(
        int32_t the_builtin_unicast_port_offset)
    {
        native().builtin_unicast_port_offset = the_builtin_unicast_port_offset;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t user_multicast_port_offset() const 
    {
        return native().user_multicast_port_offset;
    }

    /**
     * \dref_RtpsWellKnownPorts_t_user_multicast_port_offset
     */
    RtpsWellKnownPorts& user_multicast_port_offset(
        int32_t the_user_multicast_port_offset)
    {
        native().user_multicast_port_offset = the_user_multicast_port_offset;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t user_unicast_port_offset() const 
    {
        return native().user_unicast_port_offset;
    }

    /**
     * \dref_RtpsWellKnownPorts_t_user_unicast_port_offset
     */
    RtpsWellKnownPorts& user_unicast_port_offset(
        int32_t the_user_unicast_port_offset)
    {
        native().user_unicast_port_offset = the_user_unicast_port_offset;
        return *this;
    }
};

} }

#endif // RTI_DDS_CORE_RTPS_WELL_KNOWN_PORTS_HPP_
