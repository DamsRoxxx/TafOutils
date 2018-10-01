#ifndef OMG_DDS_CORE_DETAIL_CORE_FWD_HPP_
#define OMG_DDS_CORE_DETAIL_CORE_FWD_HPP_

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

#include <dds/core/detail/conformance.hpp>
#include <dds/core/detail/inttypes.hpp>
#include <rti/core/corefwd.hpp>


namespace dds { namespace core {

template <typename DELEGATE>
class TEntity;

template <typename DELEGATE>
class TInstanceHandle;

template <typename DELEGATE>
class TBytesTopicType;

template <typename DELEGATE>
class TKeyedBytesTopicType;

template <typename DELEGATE>
class TStringTopicType;

template <typename DELEGATE>
class TKeyedStringTopicType;

namespace cond {
    template <typename DELEGATE>
    class TCondition;

    template <typename DELEGATE>
    class TStatusCondition;

    template <typename DELEGATE>
    class TGuardCondition;

    template <typename DELEGATE>
    class TWaitSet;
}


namespace policy {
#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    template <typename DELEGATE>
    class TDataRepresentation;
#endif  // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    template <typename DELEGATE>
    class TDeadline;

    template <typename DELEGATE>
    class TDestinationOrder;

    template <typename DELEGATE>
    class TDurability;

#ifdef OMG_DDS_PERSISTENCE_SUPPORT
    template <typename DELEGATE>
    class TDurabilityService;
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    template <typename DELEGATE>
    class TEntityFactory;

    template <typename DELEGATE>
    class TGroupData;

    template <typename DELEGATE>
    class THistory;

    template <typename DELEGATE>
    class TLatencyBudget;

    template <typename DELEGATE>
    class TLifespan;

    template <typename DELEGATE>
    class TLiveliness;

    template <typename DELEGATE>
    class TOwnership;

#ifdef OMG_DDS_OWNERSHIP_SUPPORT
    template <typename DELEGATE>
    class TOwnershipStrength;
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

    template <typename DELEGATE>
    class TPartition;

    template <typename DELEGATE>
    class TPresentation;

    template <typename DELEGATE>
    class TResourceLimits;

    template <typename DELEGATE>
    class TQosPolicyCount;

    template <typename DELEGATE>
    class TReaderDataLifecycle;

    template <typename DELEGATE>
    class TReliability;

    template <typename DELEGATE>
    class TTimeBasedFilter;

    template <typename DELEGATE>
    class TTopicData;

    template <typename DELEGATE>
    class TTransportPriority;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    template <typename DELEGATE>
    class TTypeConsistencyEnforcement;
#endif  // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    template <typename DELEGATE>
    class TUserData;

    template <typename DELEGATE>
    class TWriterDataLifecycle;
}


template <typename DELEGATE>
class TEntityQos;


namespace status {
    template <typename D>
    class TInconsistentTopicStatus;

    template <typename D>
    class TSampleLostStatus;

    template <typename D>
    class TSampleRejectedStatus;

    template <typename D>
    class TLivelinessLostStatus;

    template <typename D>
    class TLivelinessChangedStatus;

    template <typename D>
    class TOfferedDeadlineMissedStatus;

    template <typename D>
    class TRequestedDeadlineMissedStatus;

    template <typename D>
    class TOfferedIncompatibleQosStatus;

    template <typename D>
    class TRequestedIncompatibleQosStatus;

    template <typename D>
    class TPublicationMatchedStatus;

    template <typename D>
    class TSubscriptionMatchedStatus;
}

namespace detail {

    using rti::core::optional;

    typedef dds::core::TEntity<rti::core::Entity> Entity;

    typedef dds::core::TInstanceHandle<rti::core::InstanceHandle>
        InstanceHandle;

    typedef TBytesTopicType<rti::core::BytesTopicTypeImpl> BytesTopicType;
    typedef TStringTopicType<rti::core::StringTopicTypeImpl> StringTopicType;
    typedef TKeyedBytesTopicType<rti::core::KeyedBytesTopicTypeImpl> KeyedBytesTopicType;
    typedef TKeyedStringTopicType<rti::core::KeyedStringTopicTypeImpl> KeyedStringTopicType;

} // namespace dds::core::detail


namespace cond { namespace detail {

    typedef ::dds::core::cond::TCondition<rti::core::cond::Condition> Condition;

//    typedef ::dds::core::cond::TGuardCondition<rti::core::GuardCondition>
//        GuardCondition;

    typedef dds::core::cond::TStatusCondition<rti::core::cond::StatusCondition>
        StatusCondition;

    typedef dds::core::cond::TWaitSet<rti::core::cond::WaitSetImpl> WaitSet;

} } // namespace dds::core::cond::detail


namespace policy { namespace detail {
#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
//    typedef dds::core::policy::TDataRepresentation<rti::core::policy::DataRepresentationImpl>
//    DataRepresentation;
#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    typedef dds::core::policy::TDeadline<rti::core::policy::DeadlineImpl>
    Deadline;

    typedef dds::core::policy::TDestinationOrder<rti::core::policy::DestinationOrderImpl>
    DestinationOrder;

    typedef dds::core::policy::TDurability<rti::core::policy::DurabilityImpl>
    Durability;

#ifdef  OMG_DDS_PERSISTENCE_SUPPORT
    typedef dds::core::policy::TDurabilityService<rti::core::policy::DurabilityServiceImpl>
    DurabilityService;
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    typedef dds::core::policy::TEntityFactory<rti::core::policy::EntityFactoryImpl>
    EntityFactory;

//    typedef dds::core::policy::TGroupData<rti::core::policy::GroupDataImpl>
//    GroupData;

    typedef dds::core::policy::THistory<rti::core::policy::HistoryImpl>
    History;

    typedef dds::core::policy::TLatencyBudget<rti::core::policy::LatencyBudgetImpl>
    LatencyBudget;

    typedef dds::core::policy::TLifespan<rti::core::policy::LifespanImpl>
    Lifespan;

    typedef dds::core::policy::TLiveliness<rti::core::policy::LivelinessImpl>
    Liveliness;

    typedef dds::core::policy::TOwnership<rti::core::policy::OwnershipImpl>
    Ownership;

#ifdef  OMG_DDS_OWNERSHIP_SUPPORT
    typedef dds::core::policy::TOwnershipStrength<rti::core::policy::OwnershipStrengthImpl>
    OwnershipStrength;
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

    typedef dds::core::policy::TPartition<rti::core::policy::PartitionImpl>
    Partition;

    typedef dds::core::policy::TPresentation<rti::core::policy::PresentationImpl>
    Presentation;

    typedef ::dds::core::policy::TQosPolicyCount<rti::core::policy::QosPolicyCountImpl>
    QosPolicyCount;

    typedef dds::core::policy::TReaderDataLifecycle<rti::core::policy::ReaderDataLifecycleImpl>
    ReaderDataLifecycle;

    typedef dds::core::policy::TReliability<rti::core::policy::ReliabilityImpl>
    Reliability;

    typedef dds::core::policy::TResourceLimits<rti::core::policy::ResourceLimitsImpl>
    ResourceLimits;

//    typedef dds::core::policy::TTimeBasedFilter<rti::core::policy::TimeBasedFilterImpl>
//    TimeBasedFilter;
//
//    typedef dds::core::policy::TTopicData<rti::core::policy::TopicDataImpl>
//    TopicData;

    typedef dds::core::policy::TTransportPriority<rti::core::policy::TransportPriorityImpl>
    TransportPriority;

#ifdef OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT
    typedef dds::core::policy::TTypeConsistencyEnforcement<rti::core::policy::TypeConsistencyEnforcementImpl>
    TypeConsistencyEnforcement;
#endif // OMG_DDS_EXTENSIBLE_AND_DYNAMIC_TOPIC_TYPE_SUPPORT

    typedef dds::core::policy::TUserData<rti::core::policy::UserDataImpl>
    UserData;

    typedef dds::core::policy::TWriterDataLifecycle<rti::core::policy::WriterDataLifecycleImpl>
    WriterDataLifecycle;
} } // namespace dds::core::policy::detail


namespace status { namespace detail {
    typedef dds::core::status::TInconsistentTopicStatus< rti::core::status::InconsistentTopicStatus >
    InconsistentTopicStatus;

    typedef dds::core::status::TLivelinessChangedStatus <rti::core::status::LivelinessChangedStatus>
    LivelinessChangedStatus;

    typedef dds::core::status::TLivelinessLostStatus<rti::core::status::LivelinessLostStatus>
    LivelinessLostStatus;

    typedef dds::core::status::TOfferedDeadlineMissedStatus<rti::core::status::OfferedDeadlineMissedStatus>
    OfferedDeadlineMissedStatus;

    typedef dds::core::status::TOfferedIncompatibleQosStatus<rti::core::status::OfferedIncompatibleQosStatus>
    OfferedIncompatibleQosStatus;

    typedef dds::core::status::TPublicationMatchedStatus<rti::core::status::PublicationMatchedStatus>
    PublicationMatchedStatus;

    typedef dds::core::status::TSampleRejectedStatus< rti::core::status::SampleRejectedStatus >
    SampleRejectedStatus;

    typedef dds::core::status::TRequestedDeadlineMissedStatus<rti::core::status::RequestedDeadlineMissedStatus>
    RequestedDeadlineMissedStatus;

    typedef dds::core::status::TRequestedIncompatibleQosStatus<rti::core::status::RequestedIncompatibleQosStatus>
    RequestedIncompatibleQosStatus;

    typedef dds::core::status::TSampleLostStatus<rti::core::status::SampleLostStatus>
    SampleLostStatus;

    typedef dds::core::status::TSubscriptionMatchedStatus<rti::core::status::SubscriptionMatchedStatus>
    SubscriptionMatchedStatus;
} } // namespace dds::core::status::detail


namespace xtypes { namespace detail {

typedef rti::core::xtypes::DynamicTypeImpl DynamicType;
typedef rti::core::xtypes::StructTypeImpl StructType;
typedef rti::core::xtypes::EnumTypeImpl EnumType;
typedef rti::core::xtypes::UnionTypeImpl UnionType;
typedef rti::core::xtypes::MemberImpl Member;
typedef rti::core::xtypes::UnionMember UnionMember;
typedef rti::core::xtypes::EnumMemberImpl EnumMember;

typedef rti::core::xtypes::DynamicDataImpl DynamicData;

} } // namespace xtypes::detail


} }

#endif /* OMG_DDS_CORE_DETAIL_CORE_FWD_HPP_ */
