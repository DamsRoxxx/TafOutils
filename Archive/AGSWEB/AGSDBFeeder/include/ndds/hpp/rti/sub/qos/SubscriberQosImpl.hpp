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

#ifndef RTI_DDS_SUB_SUBSCRIBER_QOS_IMPL_HPP_
#define RTI_DDS_SUB_SUBSCRIBER_QOS_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <rti/core/detail/QosPolicyMacros.hpp>

#include "ndds/ndds_c.h"

/** @RTI_namespace_start dds::sub::qos */
namespace rti { namespace sub { namespace qos {

class SubscriberQosImpl;

OMG_DDS_API
void swap(SubscriberQosImpl& left, SubscriberQosImpl& right) OMG_NOEXCEPT;

/** 
 * @RTI_class_definition class SubscriberQos 
 * @headerfile SubscriberQos.hpp "dds/sub/qos/SubscriberQos.hpp"
 * @ingroup DDSSubscriberModule 
 *  
 * @brief @st_value_type Container of the QoS policies that a
 * dds::sub::Subscriber supports
 *  
 * @details \dref_details_SubscriberQos
 *
 * @see DDSQosExampleModule
 */
class OMG_DDS_API SubscriberQosImpl {
public:

    SubscriberQosImpl() {}

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    SubscriberQosImpl(SubscriberQosImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    SubscriberQosImpl& operator=(SubscriberQosImpl&& other) OMG_NOEXCEPT
    {
        SubscriberQosImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const SubscriberQosImpl& other) const;

public:
    DDS_SubscriberQos * native()
    {
        return reinterpret_cast<DDS_SubscriberQos *>(this);
    }

    const DDS_SubscriberQos * native() const
    {
        return reinterpret_cast<const DDS_SubscriberQos *>(this);
    }

public:

    /**
     * @brief Gets a QoS policy by const reference
     *
     * @see policy()
     */
    template<typename POLICY>
    const POLICY& policy() const;

    /**
     * @brief Gets a QoS policy by reference
     *
     * @tparam Policy One of the Subscriber QoS policies:
     *  - dds::core::policy::Presentation, 
     *  - dds::core::policy::Partition,
     *  - dds::core::policy::GroupData,
     *  - dds::core::policy::EntityFactory,
     *  - rti::core::policy::ExclusiveArea,
     *  - rti::core::policy::EntityName
     *
     * @see DDSQosModule_set_qos
     */
    template<typename POLICY>
    POLICY& policy();


public:
    dds::core::policy::Presentation presentation;
    dds::core::policy::Partition partition;
    dds::core::policy::GroupData group_data;
    dds::core::policy::EntityFactory entity_factory;

    /* --- Extensions: ---------------------------------------------------- */
    rti::core::policy::ExclusiveArea exclusive_area;
    rti::core::policy::SubscriberProtocol protocol;
    rti::core::policy::EntityName subscriber_name;

};

// Doxygen gets confused by these macros
#ifndef DOXYGEN_DOCUMENTATION_ONLY

RTI_DECL_POLICY_GETTER(
    SubscriberQosImpl, dds::core::policy::Presentation, presentation)

RTI_DECL_POLICY_GETTER(
    SubscriberQosImpl, dds::core::policy::Partition, partition)

RTI_DECL_POLICY_GETTER(
    SubscriberQosImpl, dds::core::policy::EntityFactory, entity_factory)

RTI_DECL_POLICY_GETTER(
    SubscriberQosImpl, rti::core::policy::EntityName, subscriber_name)

RTI_DECL_POLICY_GETTER(
    SubscriberQosImpl, dds::core::policy::GroupData, group_data)

RTI_DECL_POLICY_GETTER(
    SubscriberQosImpl, rti::core::policy::ExclusiveArea, exclusive_area)

RTI_DECL_POLICY_GETTER(
    SubscriberQosImpl, rti::core::policy::SubscriberProtocol, protocol)

#endif // !DOXYGEN_DOCUMENTATION_ONLY

/** @RTI_namespace_end dds::sub::qos */
} } } // namespace rti::sub::qos

#endif // RTI_DDS_SUB_SUBSCRIBER_QOS_IMPL_HPP_
