/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.7a,07may14,eam Created
============================================================================= */

#ifndef RTI_DDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_QOS_IMPL_HPP_
#define RTI_DDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_QOS_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <rti/core/Exception.hpp>
#include <rti/core/detail/QosPolicyMacros.hpp>

#include "ndds/ndds_c.h"

/** @RTI_namespace_start dds::domain::qos */
namespace rti { namespace domain { namespace qos {

class DomainParticipantFactoryQosImpl;

OMG_DDS_API
void swap(
    DomainParticipantFactoryQosImpl& left,
    DomainParticipantFactoryQosImpl& right) OMG_NOEXCEPT;

/** 
 * @RTI_class_definition class DomainParticipantFactoryQos 
 * @headerfile DomainParticipantFactoryQos.hpp "dds/domain/qos/DomainParticipantFactoryQos.hpp"
 * @ingroup DDSDomainParticipantModule 
 *  
 * @brief @st_value_type Container of the QoS policies that do not apply to a 
 * specific entity  
 *
 * To set or get this policies, use DomainParticipant::participant_factory_qos().
 *
 * @see DDSQosExampleModule
 *  
 */
class OMG_DDS_API DomainParticipantFactoryQosImpl {
public:
    DomainParticipantFactoryQosImpl();

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    DomainParticipantFactoryQosImpl(
        DomainParticipantFactoryQosImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    DomainParticipantFactoryQosImpl& operator=(
        DomainParticipantFactoryQosImpl&& other) OMG_NOEXCEPT
    {
        DomainParticipantFactoryQosImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const DomainParticipantFactoryQosImpl& other) const;

    DDS_DomainParticipantFactoryQos * native()
    {
        return reinterpret_cast<DDS_DomainParticipantFactoryQos *>(this);
    }

    const DDS_DomainParticipantFactoryQos * native() const
    {
        return reinterpret_cast<const DDS_DomainParticipantFactoryQos *>(this);
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
     * @tparam Policy One of the DomainParticipantFactory QoS policies:
     *  - dds::core::policy::EntityFactory,
     *  - rti::core::policy::SystemResourceLimits
     *
     * @see DDSQosModule_set_qos
     */
    template<typename POLICY>
    POLICY& policy();


public:

    dds::core::policy::EntityFactory  entity_factory;

    // ---- Extensions --------------------------------------------------------
    rti::core::policy::SystemResourceLimits  resource_limits;    

    // This policy is not exposed. To configure how to load qos profiles we have
    // the QosProviderParams. This member is here only to ensure that the
    //  memory layout of this class is the same as the C struct.
    rti::core::policy::Profile profile;

    // This policy is not exposed. To configure logging we have the
    // the rti::config::Logger. This member is here only to ensure that the
    //  memory layout of this class is the same as the C struct.
    rti::core::policy::Logging logging;
};

RTI_DECL_POLICY_GETTER(
    DomainParticipantFactoryQosImpl, dds::core::policy::EntityFactory, entity_factory)

RTI_DECL_POLICY_GETTER(
    DomainParticipantFactoryQosImpl, rti::core::policy::SystemResourceLimits, resource_limits)

/*
RTI_DECL_POLICY_GETTER(
    DomainParticipantFactoryQosImpl, rti::core::policy::Logging, logging)
*/

/** @RTI_namespace_end dds::domain::qos */
} } } // namespace rti::domain::qos

#endif // RTI_DDS_DOMAIN_DOMAIN_PARTICIPANT_FACTORY_QOS_HPP_
