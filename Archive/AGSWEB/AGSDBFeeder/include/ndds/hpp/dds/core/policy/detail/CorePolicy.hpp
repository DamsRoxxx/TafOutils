#ifndef OMG_DDS_QOS_DETAIL_CORE_POLICY_HPP_
#define OMG_DDS_QOS_DETAIL_CORE_POLICY_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/policy/CorePolicy.hpp>
#include <dds/core/policy/TCorePolicy.hpp>

namespace dds { namespace core { namespace policy { namespace detail {


typedef dds::core::policy::TUserData<rti::core::policy::UserDataImpl>
    UserData;

typedef dds::core::policy::TDurability<rti::core::policy::DurabilityImpl>
    Durability;

typedef dds::core::policy::TPresentation<rti::core::policy::PresentationImpl>
    Presentation;

typedef dds::core::policy::TDeadline<rti::core::policy::DeadlineImpl>
    Deadline;

typedef dds::core::policy::TLatencyBudget<rti::core::policy::LatencyBudgetImpl>
    LatencyBudget;

typedef dds::core::policy::TOwnership<rti::core::policy::OwnershipImpl>
    Ownership;

#ifdef OMG_DDS_OWNERSHIP_SUPPORT
typedef dds::core::policy::TOwnershipStrength<rti::core::policy::OwnershipStrengthImpl>
    OwnershipStrength;
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

typedef dds::core::policy::TPartition<rti::core::policy::PartitionImpl>
    Partition;

typedef dds::core::policy::TLiveliness<rti::core::policy::LivelinessImpl> Liveliness;
typedef dds::core::policy::TReliability<rti::core::policy::ReliabilityImpl> Reliability;
typedef dds::core::policy::TDestinationOrder<rti::core::policy::DestinationOrderImpl> DestinationOrder;
typedef dds::core::policy::TTopicData<rti::core::policy::TopicDataImpl> TopicData;
typedef dds::core::policy::TGroupData<rti::core::policy::GroupDataImpl> GroupData;

#if 0

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    typedef dds::core::policy::TDataRepresentation<rti::core::policy::DataRepresentationImpl>
        DataRepresentation;
#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    
#endif

#ifdef  OMG_DDS_PERSISTENCE_SUPPORT
    typedef dds::core::policy::TDurabilityService<rti::core::policy::DurabilityServiceImpl>
        DurabilityService;
#endif  // OMG_DDS_PERSISTENCE_SUPPORT
    
    typedef dds::core::policy::TEntityFactory<rti::core::policy::EntityFactoryImpl>
        EntityFactory;
    typedef dds::core::policy::THistory<rti::core::policy::HistoryImpl> History;

    
    typedef dds::core::policy::TLifespan<rti::core::policy::LifespanImpl>
        Lifespan;
    
    typedef dds::core::policy::TReaderDataLifecycle<rti::core::policy::ReaderDataLifecycleImpl>
        ReaderDataLifecycle;
    
    typedef dds::core::policy::TResourceLimits<rti::core::policy::ResourceLimitsImpl>
        ResourceLimits;
    
    typedef dds::core::policy::TTimeBasedFilter<rti::core::policy::TimeBasedFilterImpl>
        TimeBasedFilter;
    
    typedef dds::core::policy::TTransportPriority<rti::core::policy::TransportPriorityImpl>
        TransportPriority;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    typedef dds::core::policy::TTypeConsistencyEnforcement<rti::core::policy::TypeConsistencyEnforcementImpl>
        TypeConsistencyEnforcement;
#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    typedef dds::core::policy::TWriterDataLifecycle<rti::core::policy::WriterDataLifecycleImpl>
        WriterDataLifecycle;
    

} } } } // namespace dds::core::policy::detail


#endif /* OMG_DDS_QOS_DETAIL_CORE_POLICY_HPP_ */
