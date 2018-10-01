/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,07feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_POLICY_ADAPTER_HPP_
#define RTI_DDS_CORE_POLICY_ADAPTER_HPP_

/*i @file
 *
 * This file defines:
 *  1) Adapters between native policy structures and their corresponding
 *     C++ classes
 *
 *  2) The native_type_traits that associate a C++ class with its native type
 *     and the adapter class.
 *
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_infrastructure_impl.h"

#include <rti/core/NativeValueType.hpp>
#include <stdexcept>
#include <rti/core/policy/policyfwd.hpp>

/*
 */
#define RTI_POLICY_DEFINE_ADAPTER(POLICY_CLASS)                                \
class POLICY_CLASS ## Adapter {                                                \
public:                                                                        \
    typedef DDS_ ## POLICY_CLASS ## QosPolicy native_type;                     \
                                                                               \
    static void initialize(native_type& native_value)                          \
    {                                                                          \
        DDS_ ## POLICY_CLASS ## QosPolicy_initialize(&native_value);           \
    }                                                                          \
                                                                               \
    static void finalize(native_type& native_value)                            \
    {                                                                          \
        DDS_ ## POLICY_CLASS ## QosPolicy_finalize(&native_value);             \
    }                                                                          \
                                                                               \
    static void copy(native_type& destination, const native_type& source)      \
    {                                                                          \
        DDS_ ## POLICY_CLASS ## QosPolicy_copy(&destination, &source);         \
    }                                                                          \
                                                                               \
    static bool equals(const native_type& first, const native_type& second)    \
    {                                                                          \
        return (DDS_ ## POLICY_CLASS ## QosPolicy_equals(&first, &second)      \
                != DDS_BOOLEAN_FALSE);                                         \
    }                                                                          \
};

#define RTI_POLICY_DEFINE_SIMPLE_ADAPTER(POLICY_CLASS, DEFAULT_CONSTANT)       \
class POLICY_CLASS ## Adapter :                                                \
    public SimpleTypeAdapter<DDS_ ## POLICY_CLASS ## QosPolicy> {              \
public:                                                                        \
    static void initialize(native_type& native_value)                          \
    {                                                                          \
        static const native_type DEFAULT = DEFAULT_CONSTANT;                   \
        native_value = DEFAULT;                                                \
    }                                                                          \
                                                                               \
    static bool equals(const native_type& first, const native_type& second)    \
    {                                                                          \
        return (DDS_ ## POLICY_CLASS ## QosPolicy_equals(&first, &second)      \
                != DDS_BOOLEAN_FALSE);                                         \
    }                                                                          \
};

/*
 * This macro declares the native_type_traits for a specific policy
 */
#define RTI_POLICY_DECLARE_ADAPTER_TRAITS(POLICY_CLASS, ADAPTER_CLASS)         \
template<>                                                                     \
struct native_type_traits<rti::core::policy::POLICY_CLASS> {                   \
    typedef rti::core::policy::ADAPTER_CLASS adapter_type;                     \
    typedef rti::core::policy::ADAPTER_CLASS::native_type native_type;     \
};


namespace rti { namespace core { namespace policy {

// --- Native-type adapters: --------------------------------------------------

// --- Standard:

RTI_POLICY_DEFINE_ADAPTER(UserData)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Durability, DDS_DURABILITY_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Presentation, DDS_PRESENTATION_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Deadline, DDS_DEADLINE_QOS_POLICY_DEFAULT)
#define DDS_LatencyBudgetQosPolicy_equals DDS_LatencyBudgetQosPolicy_equalI
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(LatencyBudget, DDS_LATENCY_BUDGET_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Ownership, DDS_OWNERSHIP_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(OwnershipStrength, DDS_OWNERSHIP_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Liveliness, DDS_LIVELINESS_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(ReaderDataLifecycle, DDS_READER_DATA_LIFECYCLE_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(TimeBasedFilter, DDS_TIME_BASED_FILTER_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(Partition)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(ResourceLimits, DDS_RESOURCE_LIMITS_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Reliability, DDS_RELIABILITY_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(EntityFactory, DDS_ENTITY_FACTORY_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(History, DDS_HISTORY_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(WriterDataLifecycle, DDS_WRITER_DATA_LIFECYCLE_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Lifespan, DDS_LIFESPAN_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(DestinationOrder, DDS_DESTINATION_ORDER_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(TransportPriority, DDS_TRANSPORT_PRIORITY_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(DurabilityService, DDS_DURABILITY_SERVICE_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(TopicData)
RTI_POLICY_DEFINE_ADAPTER(GroupData)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(TypeConsistencyEnforcement, DDS_TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_DEFAULT)

// --- Extensions:
RTI_POLICY_DEFINE_ADAPTER(Database)
RTI_POLICY_DEFINE_ADAPTER(Discovery)
RTI_POLICY_DEFINE_ADAPTER(EntityName)
RTI_POLICY_DEFINE_ADAPTER(DomainParticipantResourceLimits)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(TransportBuiltin, DDS_TRANSPORT_BUILTIN_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(LocatorFilter)
RTI_POLICY_DEFINE_ADAPTER(TransportUnicast)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Service, DDS_SERVICE_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(MultiChannel)
RTI_POLICY_DEFINE_ADAPTER(PublishMode)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(WireProtocol, DDS_WIRE_PROTOCOL_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Batch, DDS_BATCH_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(SystemResourceLimits, DDS_SYSTEM_RESOURCE_LIMITS_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(DataWriterResourceLimits, DDS_DATA_WRITER_RESOURCE_LIMITS_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(DataReaderResourceLimits, DDS_DATA_READER_RESOURCE_LIMITS_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(TransportSelection)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(DataReaderProtocol, DDS_DATA_READER_PROTOCOL_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(AsynchronousPublisher)
RTI_POLICY_DEFINE_ADAPTER(Event)
RTI_POLICY_DEFINE_ADAPTER(Availability)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(DataWriterProtocol, DDS_DATA_WRITER_PROTOCOL_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(ExclusiveArea, DDS_EXCLUSIVE_AREA_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(ReceiverPool)
RTI_POLICY_DEFINE_ADAPTER(DiscoveryConfig)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(TypeSupport, DDS_TYPESUPPORT_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(TransportMulticast)
RTI_POLICY_DEFINE_ADAPTER(TransportMulticastMapping)
RTI_POLICY_DEFINE_ADAPTER(TransportEncapsulation)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(DomainParticipantProtocol, DDS_DOMAIN_PARTICIPANT_PROTOCOL_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(TopicProtocol, DDS_TOPIC_PROTOCOL_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(SubscriberProtocol, DDS_SUBSCRIBER_PROTOCOL_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(PublisherProtocol, DDS_PUBLISHER_PROTOCOL_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_ADAPTER(Profile)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(Logging, DDS_LOGGING_QOS_POLICY_DEFAULT)
RTI_POLICY_DEFINE_SIMPLE_ADAPTER(TopicQueryDispatch, DDS_TOPIC_QUERY_DISPATCH_QOS_POLICY_DEFAULT)

#define DDS_USER_OBJECT_DEFAULT_W_ALIGNMENT \
{{0,8}, {0,8}, {0,8}, {0,8}, {0,8}, {0,8}, {0,8}, {0,8}, {0,8}, {0,8}, {0,8}}

RTI_POLICY_DEFINE_SIMPLE_ADAPTER(UserObject, DDS_USER_OBJECT_DEFAULT_W_ALIGNMENT)

class PropertyAdapter {
public:
    typedef DDS_PropertyQosPolicy native_type;

    static void initialize(native_type& native_value)
    {
        DDS_PropertyQosPolicy_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_PropertyQosPolicy_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_PropertyQosPolicy_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_PropertyQosPolicy_equals(&first, &second, DDS_BOOLEAN_FALSE)
                == DDS_BOOLEAN_TRUE);
    }
};

} // namespace policy

// --- Native policy traits: --------------------------------------------------

// --- Standard:

RTI_POLICY_DECLARE_ADAPTER_TRAITS(UserDataImpl, UserDataAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DurabilityImpl, DurabilityAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(PresentationImpl, PresentationAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DeadlineImpl, DeadlineAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(LatencyBudgetImpl, LatencyBudgetAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(OwnershipImpl, OwnershipAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(OwnershipStrengthImpl, OwnershipStrengthAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(LivelinessImpl, LivelinessAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(ReaderDataLifecycleImpl, ReaderDataLifecycleAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TimeBasedFilterImpl, TimeBasedFilterAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(PartitionImpl, PartitionAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(ResourceLimitsImpl, ResourceLimitsAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(EntityFactoryImpl, EntityFactoryAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(ReliabilityImpl, ReliabilityAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(HistoryImpl, HistoryAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(WriterDataLifecycleImpl, WriterDataLifecycleAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(LifespanImpl, LifespanAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DestinationOrderImpl, DestinationOrderAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TransportPriorityImpl, TransportPriorityAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DurabilityServiceImpl, DurabilityServiceAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TopicDataImpl, TopicDataAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(GroupDataImpl, GroupDataAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TypeConsistencyEnforcementImpl, TypeConsistencyEnforcementAdapter)

// --- Extensions:
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Database, DatabaseAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Discovery, DiscoveryAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(EntityName, EntityNameAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DomainParticipantResourceLimits, DomainParticipantResourceLimitsAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TransportBuiltin, TransportBuiltinAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Property, PropertyAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(LocatorFilter, LocatorFilterAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TransportUnicast, TransportUnicastAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(UserObject, UserObjectAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Service, ServiceAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(MultiChannel, MultiChannelAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(PublishMode, PublishModeAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(WireProtocol, WireProtocolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Batch, BatchAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(SystemResourceLimits, SystemResourceLimitsAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DataWriterResourceLimits, DataWriterResourceLimitsAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DataReaderResourceLimits, DataReaderResourceLimitsAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TransportSelection, TransportSelectionAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DataReaderProtocol, DataReaderProtocolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(AsynchronousPublisher, AsynchronousPublisherAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Event, EventAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Availability, AvailabilityAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DataWriterProtocol, DataWriterProtocolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(ExclusiveArea, ExclusiveAreaAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(ReceiverPool, ReceiverPoolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DiscoveryConfig, DiscoveryConfigAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TypeSupport, TypeSupportAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TransportMulticast, TransportMulticastAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TransportMulticastMapping, TransportMulticastMappingAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TransportEncapsulation, TransportEncapsulationAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(DomainParticipantProtocol, DomainParticipantProtocolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TopicProtocol, TopicProtocolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(SubscriberProtocol, SubscriberProtocolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(PublisherProtocol, PublisherProtocolAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Profile, ProfileAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(Logging, LoggingAdapter)
RTI_POLICY_DECLARE_ADAPTER_TRAITS(TopicQueryDispatch, TopicQueryDispatchAdapter)

} } // namespace rti::core

#endif // RTI_DDS_CORE_POLICY_ADAPTER_HPP_
