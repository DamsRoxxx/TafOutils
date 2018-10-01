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

#ifndef RTI_DDS_SUB_DATA_READER_QOS_IMPL_HPP_
#define RTI_DDS_SUB_DATA_READER_QOS_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <dds/topic/qos/TopicQos.hpp>
#include <rti/core/detail/QosPolicyMacros.hpp>

#include "ndds/ndds_c.h"

/** @RTI_namespace_start dds::sub::qos */
namespace rti { namespace sub { namespace qos {

class DataReaderQosImpl;

OMG_DDS_API
void swap(DataReaderQosImpl& left, DataReaderQosImpl& right) OMG_NOEXCEPT;

/** 
 * @RTI_class_definition class DataReaderQos 
 * @headerfile dds/sub/qos/DataReaderQos.hpp
 * @ingroup DDSReaderModule 
 *  
 * @brief @st_value_type Container of the QoS policies that a
 * dds::sub::DataReader supports
 *  
 * @section DataReaderQos_policies DataReaderQos policies
 *
 * A DataReaderQos contains the following policies:
 *  - dds::core::policy::Durability,
 *  - dds::core::policy::Deadline,
 *  - dds::core::policy::LatencyBudget,
 *  - dds::core::policy::Liveliness,
 *  - dds::core::policy::Reliability,
 *  - dds::core::policy::DestinationOrder,
 *  - dds::core::policy::History,
 *  - dds::core::policy::ResourceLimits,
 *  - dds::core::policy::UserData,
 *  - dds::core::policy::Ownership,
 *  - dds::core::policy::TimeBasedFilter,
 *  - dds::core::policy::ReaderDataLifecycle,
 *  - dds::core::policy::TransportPriority,
 *  - dds::core::policy::TypeConsistencyEnforcement,
 *  - rti::core::policy::DataReaderResourceLimits,
 *  - rti::core::policy::DataReaderProtocol,
 *  - rti::core::policy::TransportSelection,
 *  - rti::core::policy::TransportUnicast,
 *  - rti::core::policy::TransportMulticast,
 *  - rti::core::policy::Property,
 *  - rti::core::policy::Service,
 *  - rti::core::policy::Availability,
 *  - rti::core::policy::EntityName,
 *  - rti::core::policy::TypeSupport
 *
 * To get or set policies use the policy() getters and setters or operator <<
 * (see \ref DDSQosModule_set_qos "examples").
 *
 * @details \dref_details_DataReaderQos
 *
 * @see DDSQosExampleModule
 */
class OMG_DDS_API DataReaderQosImpl {
public:

    /**
     * @brief Creates a DataReaderQos with the default value for each policy
     */
    DataReaderQosImpl() {}

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    DataReaderQosImpl::DataReaderQosImpl(DataReaderQosImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    DataReaderQosImpl& DataReaderQosImpl::operator=(
        DataReaderQosImpl&& other) OMG_NOEXCEPT
    {
        DataReaderQosImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    void copy_topic_qos(const dds::topic::qos::TopicQos& topic_qos);

    /**
     * @brief Copies into this DataReaderQos those policies that are also in TopicQos
     *
     * @param topic_qos The TopicQos to copy the common policies from.
     */
    DataReaderQosImpl& operator=(const dds::topic::qos::TopicQos& topic_qos)
    {
        copy_topic_qos(topic_qos);
        return *this;
    }

    bool operator==(const DataReaderQosImpl& other) const;

    DDS_DataReaderQos * native()
    {
        return reinterpret_cast<DDS_DataReaderQos *>(this);
    }

    const DDS_DataReaderQos * native() const
    {
        return reinterpret_cast<const DDS_DataReaderQos *>(this);
    }

    /**
     * @brief Gets a QoS policy by const reference
     *
     * @tparam Policy One of the \ref DataReaderQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    const POLICY& policy() const;

    /**
     * @brief Gets a QoS policy by reference
     *
     * @tparam Policy One of the \ref DataReaderQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    POLICY& policy();

    /** @RTI_copydoc dds/core/TEntityQos.hpp EntityQosCopy TEntityQos::DataReaderQos */

public:
    // Important: the order of these members needs to match that of dds_c.
    dds::core::policy::Durability durability;
    dds::core::policy::Deadline deadline;
    dds::core::policy::LatencyBudget latency_budget;
    dds::core::policy::Liveliness liveliness;
    dds::core::policy::Reliability reliability;
    dds::core::policy::DestinationOrder destination_order;
    dds::core::policy::History history;
    dds::core::policy::ResourceLimits resource_limits;
    dds::core::policy::UserData user_data;
    dds::core::policy::Ownership ownership;
    dds::core::policy::TimeBasedFilter time_based_filter;
    dds::core::policy::ReaderDataLifecycle reader_data_lifecycle;
    dds::core::policy::TypeConsistencyEnforcement type_consistency;

    /* --- Extensions: ---------------------------------------------------- */
    rti::core::policy::DataReaderResourceLimits reader_resource_limits;
    rti::core::policy::DataReaderProtocol protocol;
    rti::core::policy::TransportSelection transport_selection;
    rti::core::policy::TransportUnicast unicast;
    rti::core::policy::TransportMulticast multicast;
    rti::core::policy::TransportEncapsulation encapsulation;
    rti::core::policy::Property property;
    rti::core::policy::Service service;
    rti::core::policy::Availability availability;
    rti::core::policy::EntityName subscription_name;
    dds::core::policy::TransportPriority transport_priority;

    /* ========================== */
    /* leave type_support at last */
    /* ========================== */
    rti::core::policy::TypeSupport type_support;
};

// Doxygen gets confused by these macros
#ifndef DOXYGEN_DOCUMENTATION_ONLY

RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::Durability, durability)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::Deadline, deadline)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::LatencyBudget, latency_budget)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::Liveliness, liveliness)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::Reliability, reliability)
RTI_DECL_POLICY_GETTER(
   DataReaderQosImpl, dds::core::policy::DestinationOrder, destination_order)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::History, history)
RTI_DECL_POLICY_GETTER(
   DataReaderQosImpl, dds::core::policy::ResourceLimits, resource_limits)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::UserData, user_data)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::Ownership, ownership)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::TimeBasedFilter, time_based_filter)
RTI_DECL_POLICY_GETTER(
   DataReaderQosImpl, rti::core::policy::EntityName, subscription_name)
RTI_DECL_POLICY_GETTER(
   DataReaderQosImpl, dds::core::policy::TransportPriority, transport_priority)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, dds::core::policy::ReaderDataLifecycle, reader_data_lifecycle)
RTI_DECL_POLICY_GETTER(
   DataReaderQosImpl, dds::core::policy::TypeConsistencyEnforcement, type_consistency)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::DataReaderResourceLimits, reader_resource_limits)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::DataReaderProtocol, protocol)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::TransportSelection, transport_selection)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::TransportUnicast, unicast)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::TransportMulticast, multicast)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::TransportEncapsulation, encapsulation)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::Property, property)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::Service, service)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::Availability, availability)
RTI_DECL_POLICY_GETTER(
    DataReaderQosImpl, rti::core::policy::TypeSupport, type_support)

#endif // !DOXYGEN_DOCUMENTATION_ONLY

/** @RTI_namespace_end dds::sub::qos */
} } } // namespace rti::sub::qos

#endif // RTI_DDS_SUB_DATA_READER_QOS_IMPL_HPP_
