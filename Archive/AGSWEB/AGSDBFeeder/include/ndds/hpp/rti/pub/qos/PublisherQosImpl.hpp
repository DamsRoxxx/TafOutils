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

#ifndef RTI_DDS_PUB_PUBLISHER_QOS_IMPL_HPP_
#define RTI_DDS_PUB_PUBLISHER_QOS_IMPL_HPP_

#include <new> // for bad_alloc

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <rti/core/detail/QosPolicyMacros.hpp>

#include "ndds/ndds_c.h"

/** @RTI_namespace_start dds::pub::qos */
namespace rti { namespace pub { namespace qos {

class PublisherQosImpl;

/**
 * @brief Swap the contents of two PublisherQos objects
 * @relatesalso dds::pub::qos::PublisherQos
 *
 * @param left A PublisherQos
 * @param right The other PublisherQos
 *
 */
OMG_DDS_API
void swap(PublisherQosImpl& left, PublisherQosImpl& right) OMG_NOEXCEPT;

/** 
 * @RTI_class_definition class PublisherQos 
 * @headerfile dds/pub/qos/PublisherQos.hpp
 * @ingroup DDSPublisherModule
 *  
 * @brief @st_value_type Container of the QoS policies that a
 * dds::pub::Publisher supports
 *  
 * @section PublisherQos_policies PublisherQos Policies
 *
 * A PublisherQos contains the following policies:
 *  - dds::core::policy::Presentation,
 *  - dds::core::policy::Partition,
 *  - dds::core::policy::GroupData,
 *  - dds::core::policy::EntityFactory,
 *  - rti::core::policy::AsynchronousPublisher,
 *  - rti::core::policy::ExclusiveArea,
 *  - rti::core::policy::EntityName
 *
 * To get or set policies use the policy() getters and setters or operator <<
 * (see \ref DDSQosModule_set_qos "examples").
 *
 * @details \dref_details_PublisherQos
 *
 * @see DDSQosExampleModule
 */
class OMG_DDS_API PublisherQosImpl {
public:

    PublisherQosImpl() {}

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    PublisherQosImpl(PublisherQosImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    PublisherQosImpl& operator=(PublisherQosImpl&& other) OMG_NOEXCEPT
    {
        PublisherQosImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const PublisherQosImpl& other) const;

    DDS_PublisherQos * native()
    {
        return reinterpret_cast<DDS_PublisherQos *>(this);
    }

    const DDS_PublisherQos * native() const
    {
        return reinterpret_cast<const DDS_PublisherQos *>(this);
    }

    /**
     * @brief Gets a QoS policy by const reference
     *
     * @tparam Policy One of the \ref PublisherQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    const POLICY& policy() const;

    /**
     * @brief Gets a QoS policy by reference
     *
     * @tparam Policy One of the \ref PublisherQos_policies
     *
     * @see \ref DDSQosModule_set_qos
     */
    template<typename POLICY>
    POLICY& policy();

    /** @RTI_copydoc dds/core/TEntityQos.hpp EntityQosCopy TEntityQos::PublisherQos */

    // Important: the order of these members needs to match that of dds_c.
    dds::core::policy::Presentation presentation;
    dds::core::policy::Partition partition;
    dds::core::policy::GroupData group_data;
    dds::core::policy::EntityFactory entity_factory;

    // --- Extensions: --------------------------------------------------------
    rti::core::policy::AsynchronousPublisher asynchronous_publisher;
    rti::core::policy::ExclusiveArea  exclusive_area;
    rti::core::policy::PublisherProtocol protocol;
    rti::core::policy::EntityName publisher_name;
};

// Doxygen gets confused by these macros
#ifndef DOXYGEN_DOCUMENTATION_ONLY

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, dds::core::policy::Presentation, presentation)

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, dds::core::policy::Partition, partition)

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, dds::core::policy::EntityFactory, entity_factory)

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, rti::core::policy::EntityName, publisher_name)

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, dds::core::policy::GroupData, group_data)

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, rti::core::policy::AsynchronousPublisher, asynchronous_publisher)

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, rti::core::policy::ExclusiveArea, exclusive_area)

RTI_DECL_POLICY_GETTER(
    PublisherQosImpl, rti::core::policy::PublisherProtocol, protocol)

#endif // !DOXYGEN_DOCUMENTATION_ONLY

/** @RTI_namespace_end dds::pub::qos */
} } } // namespace rti::pub::qos

#endif // RTI_DDS_PUB_PUBLISHER_QOS_IMPL_HPP_
