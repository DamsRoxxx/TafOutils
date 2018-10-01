/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
-------------------- 
1.7a,27feb14,eam Added ResourceLimits 
1.0a,22feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_PUB_DATAWRITER_QOS_IMPL_HPP_
#define RTI_DDS_PUB_DATAWRITER_QOS_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <dds/topic/qos/TopicQos.hpp>
#include <rti/core/detail/QosPolicyMacros.hpp>

#include "ndds/ndds_c.h"

/** @RTI_namespace_start dds::pub::qos */
namespace rti { namespace pub { namespace qos {

class DataWriterQosImpl;

OMG_DDS_API
void swap(DataWriterQosImpl& left, DataWriterQosImpl& right) OMG_NOEXCEPT;

/** 
 * @RTI_class_definition class DataWriterQos
 * @headerfile dds/pub/qos/DataWriterQos.hpp
 * @ingroup DDSWriterModule
 *
 * @brief @st_value_type Container of the QoS policies that a
 * dds::pub::DataWriter supports
 *
 * @section DataWriterQos_policies DataWriterQos policies
 *
 * A DataWriterQos contains the following policies:
 *  - dds::core::policy::Durability,
 *  - dds::core::policy::DurabilityService,
 *  - dds::core::policy::Deadline,
 *  - dds::core::policy::LatencyBudget,
 *  - dds::core::policy::Liveliness,
 *  - dds::core::policy::Reliability,
 *  - dds::core::policy::DestinationOrder,
 *  - dds::core::policy::History,
 *  - dds::core::policy::ResourceLimits,
 *  - dds::core::policy::TransportPriority,
 *  - dds::core::policy::Lifespan,
 *  - dds::core::policy::UserData,
 *  - dds::core::policy::Ownership,
 *  - dds::core::policy::OwnershipStrength,
 *  - dds::core::policy::WriterDataLifecycle,
 *  - rti::core::policy::DataWriterResourceLimits,
 *  - rti::core::policy::DataWriterProtocol,
 *  - rti::core::policy::TransportSelection,
 *  - rti::core::policy::TransportUnicast,
 *  - rti::core::policy::TransportEncapsulation,
 *  - rti::core::policy::PublishMode,
 *  - rti::core::policy::Property,
 *  - rti::core::policy::Service,
 *  - rti::core::policy::Batch,
 *  - rti::core::policy::MultiChannel,
 *  - rti::core::policy::Availability,
 *  - rti::core::policy::EntityName,
 *  - rti::core::policy::TopicQueryDispatch,
 *  - rti::core::policy::TypeSupport
 *
 * To get or set policies use the policy() getters and setters or operator <<
 * (see \ref DDSQosModule_set_qos "examples").
 *
 * @details \dref_details_DataWriterQos
 *
 * @see DDSQosExampleModule
 */
class OMG_DDS_API DataWriterQosImpl {
public:

    /**
     * @brief Creates a DataWriterQos with the default value for each policy
     */
    DataWriterQosImpl();

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    DataWriterQosImpl(DataWriterQosImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    DataWriterQosImpl& operator=(DataWriterQosImpl&& other) OMG_NOEXCEPT
    {
        DataWriterQosImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    void copy_topic_qos(const dds::topic::qos::TopicQos& topic_qos);

    /**
     * @brief Copies into this DataWriterQos those policies that are also in TopicQos
     *
     * @param topic_qos The TopicQos to copy the common policies from.
     */
    DataWriterQosImpl& operator=(const dds::topic::qos::TopicQos& topic_qos)
    {
        copy_topic_qos(topic_qos);
        return *this;
    }

    bool operator==(const DataWriterQosImpl& other) const;

    DDS_DataWriterQos * native()
    {
        return reinterpret_cast<DDS_DataWriterQos *>(this);
    }

    const DDS_DataWriterQos * native() const
    {
        return reinterpret_cast<const DDS_DataWriterQos *>(this);
    }

    /**
     * @brief Gets a QoS policy by const reference
     *
     * @tparam Policy One of the \ref DataWriterQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename Policy>
    const Policy& policy() const;

    /**
     * @brief Gets a QoS policy by reference
     *
     * @tparam Policy One of the \ref DataWriterQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename Policy>
    Policy& policy();

    /** @RTI_copydoc dds/core/TEntityQos.hpp EntityQosCopy TEntityQos::DataWriterQos */

public:
    // Important: the order of these members needs to match that of dds_c.
    dds::core::policy::Durability durability;
    dds::core::policy::DurabilityService durability_service;
    dds::core::policy::Deadline deadline;
    dds::core::policy::LatencyBudget latency_budget;
    dds::core::policy::Liveliness liveliness;
    dds::core::policy::Reliability reliability;
    dds::core::policy::DestinationOrder destination_order;
    dds::core::policy::History history;
    dds::core::policy::ResourceLimits resource_limits;
    dds::core::policy::TransportPriority transport_priority;
    dds::core::policy::Lifespan lifespan;
    dds::core::policy::UserData user_data;
    dds::core::policy::Ownership ownership;
    dds::core::policy::OwnershipStrength ownership_strength;
    dds::core::policy::WriterDataLifecycle writer_data_lifecycle;

    rti::core::policy::DataWriterResourceLimits writer_resource_limits;
    rti::core::policy::DataWriterProtocol protocol;
    rti::core::policy::TransportSelection transport_selection;
    rti::core::policy::TransportUnicast unicast;
    rti::core::policy::TransportEncapsulation encapsulation;
    rti::core::policy::PublishMode publish_mode;
    rti::core::policy::Property property;
    rti::core::policy::Service service;
    rti::core::policy::Batch batch;
    rti::core::policy::MultiChannel multi_channel;
    rti::core::policy::Availability availability;
    rti::core::policy::EntityName publication_name;
    rti::core::policy::TopicQueryDispatch topic_query_dispatch;
    rti::core::policy::TypeSupport type_support;
};

// Doxygen gets confused by these macros
#ifndef DOXYGEN_DOCUMENTATION_ONLY

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::Durability, durability)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::Deadline, deadline)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::LatencyBudget, latency_budget)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::UserData, user_data)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::Ownership, ownership)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::OwnershipStrength, ownership_strength)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::Liveliness, liveliness)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::Reliability, reliability)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::History, history)

RTI_DECL_POLICY_GETTER(
   DataWriterQosImpl, dds::core::policy::ResourceLimits, resource_limits)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::WriterDataLifecycle, writer_data_lifecycle)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::EntityName, publication_name)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::TransportPriority, transport_priority)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::Lifespan, lifespan)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::DestinationOrder, destination_order)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, dds::core::policy::DurabilityService, durability_service)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::Property, property)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::TransportUnicast, unicast)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::Service, service)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::MultiChannel, multi_channel)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::PublishMode, publish_mode)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::Batch, batch)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::DataWriterResourceLimits, writer_resource_limits)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::TransportSelection, transport_selection)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::Availability, availability)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::DataWriterProtocol, protocol)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::TopicQueryDispatch, topic_query_dispatch)

RTI_DECL_POLICY_GETTER(
    DataWriterQosImpl, rti::core::policy::TypeSupport, type_support)

#endif // !DOXYGEN_DOCUMENTATION_ONLY

/** @RTI_namespace_end dds::pub::qos */
} } } // namespace rti::pub::qos

#endif // RTI_DDS_PUB_DATAWRITER_QOS_IMPL_HPP_
