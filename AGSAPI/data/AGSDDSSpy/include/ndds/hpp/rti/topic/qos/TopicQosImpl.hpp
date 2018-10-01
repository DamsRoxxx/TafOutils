/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,12feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_DOMAIN_DOMAIN_PUBLISHER_QOS_HPP_
#define RTI_DDS_DOMAIN_DOMAIN_PUBLISHER_QOS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <rti/core/detail/QosPolicyMacros.hpp>

#include "ndds/ndds_c.h"

/** @RTI_namespace_start dds::topic::qos */
namespace rti { namespace topic { namespace qos {

class TopicQosImpl;

OMG_DDS_API
void swap(TopicQosImpl& left, TopicQosImpl& right) OMG_NOEXCEPT;

/** 
 * @RTI_class_definition class TopicQos 
 * @headerfile dds/topic/qos/TopicQos.hpp
 * @ingroup DDSTopicEntityModule 
 *  
 * @brief @st_value_type Container of the QoS policies that a
 * dds::topic::Topic supports
 *
 * @section TopicQos_policies TopicQos Policies
 *
 * A TopicQos contains the following policies:
 *  - dds::core::policy::TopicData,
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
 *  - dds::core::policy::Ownership
 *  
 * To get or set policies use the policy() getters and setters or operator <<
 * (see \ref DDSQosModule_set_qos "examples").
 *
 * @details \dref_details_TopicQos
 *
 * @see DDSQosExampleModule
 */
class OMG_DDS_API TopicQosImpl {
public:

    /**
     * @brief Creates a TopicQos with the default value for each policy
     */
    TopicQosImpl() {}

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    TopicQosImpl(TopicQosImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    TopicQosImpl& operator=(TopicQosImpl&& other) OMG_NOEXCEPT
    {
        TopicQosImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const TopicQosImpl& other) const;

    DDS_TopicQos * native()
    {
        return reinterpret_cast<DDS_TopicQos *>(this);
    }

    const DDS_TopicQos * native() const
    {
        return reinterpret_cast<const DDS_TopicQos *>(this);
    }

    /**
     * @brief Gets a QoS policy by const reference
     *
     * @tparam Policy One of the \ref TopicQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    const POLICY& policy() const;

    /**
     * @brief Gets a QoS policy by reference
     *
     * @tparam Policy One of the \ref TopicQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    POLICY& policy();

    /** @RTI_copydoc dds/core/TEntityQos.hpp EntityQosCopy TEntityQos::TopicQos */

    // Important: the order of these members needs to match that of dds_c.
    dds::core::policy::TopicData topic_data;
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
    dds::core::policy::Ownership ownership;

    // Extensions:
    rti::core::policy::TopicProtocol protocol;

};

// Doxygen gets confused by these macros
#ifndef DOXYGEN_DOCUMENTATION_ONLY

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::Durability, durability)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::Deadline, deadline)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::LatencyBudget, latency_budget)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::Ownership, ownership)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::ResourceLimits, resource_limits)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::TransportPriority, transport_priority)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::Lifespan, lifespan)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::TopicData, topic_data)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::DurabilityService, durability_service)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::Liveliness, liveliness)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::Reliability, reliability)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::DestinationOrder, destination_order)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, dds::core::policy::History, history)

RTI_DECL_POLICY_GETTER(
    TopicQosImpl, rti::core::policy::TopicProtocol, protocol)

#endif // !DOXYGEN_DOCUMENTATION_ONLY

/** @RTI_namespace_end dds::topic::qos */
} } } // namespace rti::pub::qos

#endif // RTI_DDS_DOMAIN_DOMAIN_PUBLISHER_QOS_HPP_
