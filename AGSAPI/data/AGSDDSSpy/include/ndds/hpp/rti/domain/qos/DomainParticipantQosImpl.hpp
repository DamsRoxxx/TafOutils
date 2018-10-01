/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,12feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_DOMAIN_DOMAIN_PARTICIPANT_QOS_IMPL_HPP_
#define RTI_DDS_DOMAIN_DOMAIN_PARTICIPANT_QOS_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <rti/core/detail/QosPolicyMacros.hpp>

#include "ndds/ndds_c.h"

/** @RTI_namespace_start dds::domain::qos */
namespace rti { namespace domain { namespace qos {

class DomainParticipantQosImpl;

OMG_DDS_API
void swap(
    DomainParticipantQosImpl& left,
    DomainParticipantQosImpl& right) OMG_NOEXCEPT;

/** 
 * @ingroup DDSDomainParticipantModule
 * @headerfile dds/domain/qos/DomainParticipantQos.hpp
 * @RTI_class_definition class DomainParticipantQos
 *  
 * @brief @st_value_type Container of the QoS policies that a
 * dds::domain::DomainParticipant supports
 * @section DomainParticipantQos_policies DomainParticipantQos Policies
 *
 * A DomainParticipantQos contains the following policies:
 *  - dds::core::policy::UserData,
 *  - dds::core::policy::EntityFactory,
 *  - rti::core::policy::WireProtocol,
 *  - rti::core::policy::TransportBuiltin,
 *  - rti::core::policy::TransportUnicast,
 *  - rti::core::policy::Discovery,
 *  - rti::core::policy::DomainParticipantResourceLimits,
 *  - rti::core::policy::Event,
 *  - rti::core::policy::ReceiverPool,
 *  - rti::core::policy::Database,
 *  - rti::core::policy::DiscoveryConfig,
 *  - rti::core::policy::ExclusiveArea,
 *  - rti::core::policy::Property,
 *  - rti::core::policy::EntityName,
 *  - rti::core::policy::TransportMulticastMapping
 *  - rti::core::policy::Service
 * 
 * To get or set policies use the policy() getters and setters or operator <<
 * (see \ref DDSQosModule_set_qos "examples").
 *
 * @details \dref_details_DomainParticipantQos
 *
 * @see DDSQosExampleModule
 */
class OMG_DDS_API DomainParticipantQosImpl {
public:
    /**
     * @brief Creates a DomainParticipantQos with the default value for each
     * policy
     */
    DomainParticipantQosImpl();

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    DomainParticipantQosImpl(
        DomainParticipantQosImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    DomainParticipantQosImpl& operator=(
        DomainParticipantQosImpl&& other) OMG_NOEXCEPT
    {
        DomainParticipantQosImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const DomainParticipantQosImpl& other) const;

    DDS_DomainParticipantQos * native()
    {
        return reinterpret_cast<DDS_DomainParticipantQos *>(this);
    }

    const DDS_DomainParticipantQos * native() const
    {
        return reinterpret_cast<const DDS_DomainParticipantQos *>(this);
    }

public:

    /**
     * @brief Gets a QoS policy by const reference
     *
     * @tparam Policy One of the \ref DomainParticipantQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    const POLICY& policy() const;

    /**
     * @brief Gets a QoS policy by reference
     *
     * @tparam Policy One of the \ref DomainParticipantQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    POLICY& policy();

    /** @RTI_copydoc dds/core/TEntityQos.hpp EntityQosCopy TEntityQos::DomainParticipantQos */


public:
    dds::core::policy::UserData user_data;
    dds::core::policy::EntityFactory entity_factory;

    // Extensions:
    rti::core::policy::WireProtocol wire_protocol;
    rti::core::policy::TransportBuiltin transport_builtin;
    rti::core::policy::TransportUnicast default_unicast;
    rti::core::policy::Discovery discovery;
    rti::core::policy::DomainParticipantResourceLimits resource_limits;
    rti::core::policy::Event event;
    rti::core::policy::ReceiverPool receiver_pool;
    rti::core::policy::Database database;
    rti::core::policy::DiscoveryConfig discovery_config;
    rti::core::policy::ExclusiveArea exclusive_area;
    rti::core::policy::Property property;
    rti::core::policy::EntityName participant_name;
    rti::core::policy::TransportMulticastMapping multicast_mapping;

    // Not exposed:
    rti::core::policy::Service service;
    rti::core::policy::UserObject user_object;
    rti::core::policy::DomainParticipantProtocol protocol;
    rti::core::policy::TypeSupport type_support;
};

// Doxygen gets confused by these macros
#ifndef DOXYGEN_DOCUMENTATION_ONLY

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, dds::core::policy::UserData, user_data)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, dds::core::policy::EntityFactory, entity_factory)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::Database, database)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::EntityName, participant_name)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::Discovery, discovery)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::WireProtocol, wire_protocol)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::TransportBuiltin, transport_builtin)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::TransportUnicast, default_unicast)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::DomainParticipantResourceLimits, resource_limits)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::Event, event)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::ReceiverPool, receiver_pool)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::DiscoveryConfig, discovery_config)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::Property, property)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::TransportMulticastMapping, multicast_mapping)

RTI_DECL_POLICY_GETTER(
        DomainParticipantQosImpl,
        rti::core::policy::Service,
        service)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::DomainParticipantProtocol, protocol)

RTI_DECL_POLICY_GETTER(
    DomainParticipantQosImpl, rti::core::policy::TypeSupport, type_support)

#endif // !DOXYGEN_DOCUMENTATION_ONLY

/** @RTI_namespace_end dds::domain::qos */
} } } // namespace rti::domain::qos

#endif // RTI_DDS_DOMAIN_DOMAIN_PARTICIPANT_QOS_IMPL_HPP_
