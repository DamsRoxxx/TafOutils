/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
2.0a,24nov15,yy  CORE-7053: Support the configuration of
                 initial_active_topic_queries and max_active_topic_queries as
                 a DataWriter resource limit
1.0a,07feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_POLICY_HPP_
#define RTI_DDS_CORE_POLICY_HPP_

#include <stdexcept>
#include <bitset>
#include <map>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_infrastructure_impl.h"

#include <dds/core/types.hpp>
#include <dds/core/corefwd.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/Duration.hpp>
#include <rti/core/OptionalValue.hpp>
#include <rti/core/AllocationSettings.hpp>
#include <rti/core/LocatorFilter.hpp>
#include <rti/topic/ContentFilter.hpp>
#include <rti/core/RtpsWellKnownPorts.hpp>
#include <rti/core/ThreadSettings.hpp>
#include <rti/core/EndpointGroup.hpp>
#include <rti/core/PolicySettings.hpp>
#include <rti/core/policy/PolicyKind.hpp>

#include <rti/core/policy/CorePolicyAdapter.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/detail/NativeSequence.hpp>

#include <dds/core/policy/PolicyTraits.hpp>

/* ==========================================================
 * This list controls the order in which QoS policies show up
 * the HTML documentation under Modules, Infrastructure, 
 * QoS Policies. For external QoS, keep in alphabetical order.
 * ==========================================================*/
/** 
 * @dref_QosPoliciesGroupDocs 
 */
/**
 * @dref_AsynchronousPublisherQosGroupDocs 
 * @dref_AvailabilityQosGroupDocs 
 * @dref_BatchQosGroupDocs 
 * @dref_DatabaseQosGroupDocs 
 * @dref_DataReaderProtocolQosGroupDocs 
 * @dref_DataReaderResourceLimitsQosGroupDocs 
 * @dref_DataWriterProtocolQosGroupDocs 
 * @dref_DataWriterResourceLimitsQosGroupDocs 
 * @dref_DeadlineQosGroupDocs 
 * @dref_DestinationOrderQosGroupDocs 
 * @dref_DiscoveryQosGroupDocs 
 * @dref_DiscoveryConfigQosGroupDocs 
 * @dref_DomainParticipantResourceLimitsQosGroupDocs 
 * @dref_DurabilityQosGroupDocs 
 * @dref_DurabilityServiceQosGroupDocs 
 * @dref_EntityFactoryQosGroupDocs 
 * @dref_EntityNameQosGroupDocs 
 * @dref_EventQosGroupDocs 
 * @dref_ExclusiveAreaQosGroupDocs 
 * @dref_HistoryQosGroupDocs 
 * @dref_GroupDataQosGroupDocs 
 * @dref_LatencyBudgetQosGroupDocs 
 * @dref_LifespanQosGroupDocs 
 * @dref_LivelinessQosGroupDocs 
 * @dref_LocatorFilterQosGroupDocs 
 * @dref_LoggingQosGroupDocs 
 * @dref_MultiChannelQosGroupDocs 
 * @dref_OwnershipQosGroupDocs 
 * @dref_OwnershipStrengthQosGroupDocs 
 * @dref_PartitionQosGroupDocs 
 * @dref_PresentationQosGroupDocs 
 * @dref_ProfileQosGroupDocs 
 * @dref_PropertyQosGroupDocs 
 * @dref_PublishModeQosGroupDocs 
 * @dref_ReaderDataLifecycleQosGroupDocs 
 * @dref_ReceiverPoolQosGroupDocs 
 * @dref_ReliabilityQosGroupDocs 
 * @dref_ResourceLimitsQosGroupDocs 
 * @dref_ServiceQosGroupDocs 
 * @dref_SystemResourceLimitsQosGroupDocs 
 * @dref_TimeBasedFilterQosGroupDocs 
 * @dref_TopicDataQosGroupDocs 
 * @dref_TopicQueryDispatchQosGroupDocs 
 * @dref_TransportBuiltinQosGroupDocs 
 * @dref_TransportMulticastQosGroupDocs 
 * @dref_TransportMulticastMappingQosGroupDocs 
 * @dref_TransportPriorityQosGroupDocs 
 * @dref_TransportSelectionQosGroupDocs 
 * @dref_TransportUnicastQosGroupDocs 
 * @dref_TypeConsistencyEnforcementQosGroupDocs 
 * @dref_TypeSupportQosGroupDocs 
 * @dref_UserDataQosGroupDocs 
 * @dref_WriterDataLifecycleQosGroupDocs 
 * @dref_WireProtocolQosGroupDocs 
 */

namespace dds { namespace core { namespace policy {

// Forward declarations
typedef detail::Durability Durability;
typedef detail::ResourceLimits ResourceLimits;
typedef detail::DestinationOrder DestinationOrder;
typedef detail::ReaderDataLifecycle ReaderDataLifecycle;
typedef detail::WriterDataLifecycle WriterDataLifecycle;
typedef detail::Reliability Reliability;
typedef detail::History History;

// Policy traits

OMG_DDS_POLICY_TRAITS(rti::core::policy::WireProtocol, 1000)
OMG_DDS_POLICY_TRAITS(rti::core::policy::Discovery, 1001)
OMG_DDS_POLICY_TRAITS(rti::core::policy::DataReaderResourceLimits, 1003)
OMG_DDS_POLICY_TRAITS(rti::core::policy::DataWriterResourceLimits, 1004)
OMG_DDS_POLICY_TRAITS(rti::core::policy::DataReaderProtocol, 1005)
OMG_DDS_POLICY_TRAITS(rti::core::policy::DataWriterProtocol, 1006)
OMG_DDS_POLICY_TRAITS(rti::core::policy::DomainParticipantResourceLimits, 1007)
OMG_DDS_POLICY_TRAITS(rti::core::policy::Event, 1008)
OMG_DDS_POLICY_TRAITS(rti::core::policy::Database, 1009)
OMG_DDS_POLICY_TRAITS(rti::core::policy::ReceiverPool, 1010)
OMG_DDS_POLICY_TRAITS(rti::core::policy::DiscoveryConfig, 1011)
OMG_DDS_POLICY_TRAITS(rti::core::policy::ExclusiveArea, 1012)
OMG_DDS_POLICY_TRAITS(rti::core::policy::UserObject, 1013)
OMG_DDS_POLICY_TRAITS(rti::core::policy::SystemResourceLimits, 1014)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TransportSelection, 1015)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TransportUnicast, 1016)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TransportMulticast, 1017)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TransportBuiltin, 1018)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TypeSupport, 1019)
OMG_DDS_POLICY_TRAITS(rti::core::policy::Property, 1020)
OMG_DDS_POLICY_TRAITS(rti::core::policy::PublishMode, 1021)
OMG_DDS_POLICY_TRAITS(rti::core::policy::AsynchronousPublisher, 1022)
OMG_DDS_POLICY_TRAITS(rti::core::policy::EntityName, 1023)
OMG_DDS_POLICY_TRAITS(rti::core::policy::Service, 1025)
OMG_DDS_POLICY_TRAITS(rti::core::policy::Batch, 1026)
OMG_DDS_POLICY_TRAITS(rti::core::policy::LocatorFilter, 1028)
OMG_DDS_POLICY_TRAITS(rti::core::policy::MultiChannel, 1029)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TransportEncapsulation, 1030)
OMG_DDS_POLICY_TRAITS(rti::core::policy::PublisherProtocol, 1031)
OMG_DDS_POLICY_TRAITS(rti::core::policy::SubscriberProtocol, 1032)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TopicProtocol, 1033)
OMG_DDS_POLICY_TRAITS(rti::core::policy::DomainParticipantProtocol, 1034)
OMG_DDS_POLICY_TRAITS(rti::core::policy::Availability, 1035)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TransportMulticastMapping, 1036)
OMG_DDS_POLICY_TRAITS(rti::core::policy::TopicQueryDispatch, 1038)

} } } // namespace dds::core::policy

// Standard QoS Policies. (Extensions go in a different namespace block below)
/** @RTI_namespace_start dds::core::policy */
namespace rti { namespace core { namespace policy {

extern OMG_DDS_API_VARIABLE const uint8_t DUMMY_END;

class OMG_DDS_API UserDataImpl : public NativeValueType<UserDataImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(UserDataImpl)

public:

    typedef NativeValueType<UserDataImpl> Base;

    UserDataImpl() { };

    explicit UserDataImpl(const dds::core::ByteSeq& sequence)
    {
        value(sequence.begin(), sequence.end());
    }

    UserDataImpl(const uint8_t* value_begin, const uint8_t* value_end);

public:
    // Spec Error: CPPPSM-216: This setter confilicts with the getter which 
    // takes in a ByteSeq
    
    // UserData& value(const dds::core::ByteSeq& seq);

    template <typename OCTET_ITER>
    UserDataImpl& value(OCTET_ITER the_begin, OCTET_ITER the_end)
    {
        value_impl(
            the_begin,
            the_end,
            typename std::iterator_traits<OCTET_ITER>::iterator_category());

        return *this;
    }

    dds::core::ByteSeq value() const
    {
        return dds::core::ByteSeq(begin(), end());
    }

    dds::core::ByteSeq& value(dds::core::ByteSeq& dst) const;

    const uint8_t* begin() const;
    const uint8_t* end() const;

private:
    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::random_access_iterator_tag)
    {
        // Knowing the size of the range [begin, end) allows for an optimized
        // implementation.
        resize(the_end - the_begin);
        std::copy(the_begin, the_end, DDS_OctetSeq_get_contiguous_buffer(&native().value));
    }

    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::input_iterator_tag)
    {
        // Generic, less-efficient implementation for iterators that don't
        // support calculating the length of a range
        int sequence_index = 0;
        for (OCTET_ITER it = the_begin; it != the_end; ++it) {
            resize(sequence_index + 1);
            *DDS_OctetSeq_get_reference(&native().value, sequence_index) = *it;
            sequence_index++;
        }
    }

    void resize(size_t length);
    size_t length() const;

private:

};

// ----------------------------------------------------------------------------

/** @RTI_class_definition NA */
class OMG_DDS_API DurabilityImpl : public NativeValueType<DurabilityImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DurabilityImpl)

public:

    typedef NativeValueType<DurabilityImpl> Base;
    typedef dds::core::policy::Durability WrapperType;

    DurabilityImpl()
    {
    }

    explicit DurabilityImpl(
        dds::core::policy::DurabilityKind the_kind,
        bool the_direct_communication = true);

    DurabilityImpl(native_type& reference, bool dummy)
        : Base(reference, dummy)
    {
    }

public:
    DurabilityImpl& kind(dds::core::policy::DurabilityKind the_kind);
    dds::core::policy::DurabilityKind kind() const;

    /**
     * @memberof dds::core::policy::Durability
     *
     * @brief @extension Indicates whether or not a transient or persistent
     * dds::sub::DataReader should receive samples directly from a transient or
     * persistent dds::pub::DataWriter
     * 
     * @details \dref_details_DurabilityQosPolicy_direct_communication
     */
    dds::core::policy::Durability& direct_communication(
        bool the_direct_communication);

    /** 
     * @memberof dds::core::policy::Durability 
     * @brief @extension Getter (see setter with the same name)
     */
    bool direct_communication() const;

/** @RTI_remove_lines 1 */
};

// ----------------------------------------------------------------------------

class OMG_DDS_API PresentationImpl : public NativeValueType<PresentationImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(PresentationImpl)

  private:

    typedef NativeValueType<PresentationImpl> Base;
  public:
    PresentationImpl() { }

    PresentationImpl(
        dds::core::policy::PresentationAccessScopeKind the_access_scope,
        bool enable_coherent_access,
        bool enable_ordered_access)

    {
        access_scope(the_access_scope);
        coherent_access(enable_coherent_access);
        ordered_access(enable_ordered_access);
    }

  public:
    PresentationImpl& access_scope(
        dds::core::policy::PresentationAccessScopeKind the_access_scope);
    dds::core::policy::PresentationAccessScopeKind  access_scope() const;

    PresentationImpl& coherent_access(bool enable);
    bool coherent_access() const;

    PresentationImpl& ordered_access(bool enable);
    bool ordered_access() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API DeadlineImpl : public NativeValueType<DeadlineImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DeadlineImpl)

  private:
    typedef NativeValueType<DeadlineImpl> Base;

  public:

    DeadlineImpl() { }

    explicit DeadlineImpl(const dds::core::Duration& the_period)
    {
        period(the_period);
    }


  public:
    DeadlineImpl& period(const dds::core::Duration& the_period);
    dds::core::Duration period() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API LatencyBudgetImpl : public NativeValueType<LatencyBudgetImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(LatencyBudgetImpl)

  private:
    typedef NativeValueType<LatencyBudgetImpl> Base;

  public:

    LatencyBudgetImpl() { }

    explicit LatencyBudgetImpl(const dds::core::Duration& the_duration)
    {
        duration(the_duration);
    }


  public:
    LatencyBudgetImpl& duration(const dds::core::Duration& the_duration);
    dds::core::Duration duration() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API OwnershipImpl : public NativeValueType<OwnershipImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(OwnershipImpl)

  private:
    typedef NativeValueType<OwnershipImpl> Base;

  public:
    OwnershipImpl() { }

    explicit OwnershipImpl(dds::core::policy::OwnershipKind the_kind)

    {
        kind(the_kind);
    }


  public:
    OwnershipImpl& kind(dds::core::policy::OwnershipKind the_kind);
    dds::core::policy::OwnershipKind kind() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API OwnershipStrengthImpl
    : public NativeValueType<OwnershipStrengthImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(OwnershipStrengthImpl)

  private:
    typedef NativeValueType<OwnershipStrengthImpl> Base;

  public:
    explicit OwnershipStrengthImpl(int32_t strength)
    {
        value(strength);
    }


  public:
    OwnershipStrengthImpl& value(int32_t strength);
    int32_t value() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API LivelinessImpl : public NativeValueType<LivelinessImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(LivelinessImpl)


    typedef NativeValueType<LivelinessImpl> Base;

public:
    LivelinessImpl()
    {
        // Base() initializes C default values
    }

    LivelinessImpl(
        dds::core::policy::LivelinessKind the_kind,
        const dds::core::Duration& the_lease_duration)
    {
        kind(the_kind);
        lease_duration(the_lease_duration);
    }

public:
    LivelinessImpl& kind(dds::core::policy::LivelinessKind the_kind);
    dds::core::policy::LivelinessKind kind() const;

    LivelinessImpl& lease_duration(const dds::core::Duration& the_lease_duration);
    dds::core::Duration lease_duration() const;
};

// ----------------------------------------------------------------------------

/** @RTI_class_definition NA */
class OMG_DDS_API ReaderDataLifecycleImpl
    : public NativeValueType<ReaderDataLifecycleImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ReaderDataLifecycleImpl)

    typedef NativeValueType<ReaderDataLifecycleImpl> Base;

    typedef dds::core::policy::ReaderDataLifecycle WrapperType;
public:
    ReaderDataLifecycleImpl()
    {
        // Base() initializes C default values
    }

    ReaderDataLifecycleImpl(
        const dds::core::Duration& the_nowriter_delay,
        const dds::core::Duration& the_disposed_samples_delay)
    {
        autopurge_nowriter_samples_delay(the_nowriter_delay);
        autopurge_disposed_samples_delay(the_disposed_samples_delay);
    }

public:
    dds::core::Duration autopurge_nowriter_samples_delay() const;
    ReaderDataLifecycleImpl& autopurge_nowriter_samples_delay(
        const dds::core::Duration& d);
    dds::core::Duration autopurge_disposed_samples_delay() const;
    ReaderDataLifecycleImpl& autopurge_disposed_samples_delay(
        const dds::core::Duration& d);

    /**
     * @memberof dds::core::policy::ReaderDataLifecycle 
     * @brief @extension Minimum duration for which the DataReader will maintain
     * an instance once its \p instance_state becomes
     * InstanceStateKind::NOT_ALIVE_DISPOSED.
     *  
     * @details \dref_details_ReaderDataLifecycleQosPolicy_autopurge_disposed_instances_delay
     */
    dds::core::policy::ReaderDataLifecycle& autopurge_disposed_instances_delay(
        const dds::core::Duration& duration);

    /**
     * @memberof dds::core::policy::ReaderDataLifecycle
     * @brief @extension Getter (see setter with the same name)
     */
    dds::core::Duration autopurge_disposed_instances_delay() const;
/** @RTI_remove_lines 1 */
};

// ----------------------------------------------------------------------------

class OMG_DDS_API PartitionImpl : public NativeValueType<PartitionImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(PartitionImpl)

private:
    typedef NativeValueType<PartitionImpl> Base;

public:
    PartitionImpl() { }

    explicit PartitionImpl(const std::string& partition)
    {
        name(dds::core::StringSeq(1, partition));
    }

    explicit PartitionImpl(const dds::core::StringSeq& partitions)
    {
        name(partitions);
    }


public:
    PartitionImpl& name(const dds::core::StringSeq& partitions);
    dds::core::StringSeq name() const;
    //dds::core::StringSeq& name(dds::core::StringSeq& dst) const;
};


// ----------------------------------------------------------------------------

class OMG_DDS_API EntityFactoryImpl : public NativeValueType<EntityFactoryImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(EntityFactoryImpl)

    typedef NativeValueType<EntityFactoryImpl> Base;

    EntityFactoryImpl() { }

    explicit EntityFactoryImpl(bool the_auto_enable)
    {
        autoenable_created_entities(the_auto_enable);
    }

    EntityFactoryImpl& autoenable_created_entities(bool on);
    bool autoenable_created_entities() const;
};

// ----------------------------------------------------------------------------

/** @RTI_class_definition NA */
class OMG_DDS_API ReliabilityImpl : public NativeValueType<ReliabilityImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ReliabilityImpl)
    typedef dds::core::policy::Reliability WrapperType;

private:
  typedef NativeValueType<ReliabilityImpl> Base;

public:
    ReliabilityImpl()
    {
        // Base type will initialize to the right DDS defaults
    }

    ReliabilityImpl(
        dds::core::policy::ReliabilityKind the_kind,
        const dds::core::Duration& the_max_blocking_time)

    {
        kind(the_kind);
        max_blocking_time(the_max_blocking_time);
    }

public:
    ReliabilityImpl& kind(dds::core::policy::ReliabilityKind the_kind);
    dds::core::policy::ReliabilityKind  kind() const;

    ReliabilityImpl& max_blocking_time(const dds::core::Duration& d);
    dds::core::Duration max_blocking_time() const;

    /** 
     * @memberof dds::core::policy::Reliability  
     * @brief @extension Sets the kind of reliable acknowledgment
     * 
     * @details \dref_details_ReliabilityQosPolicy_acknowledgment_kind
     */
    dds::core::policy::Reliability& acknowledgment_kind(
        rti::core::policy::AcknowledgmentKind ack_kind);

    /**
     * @memberof dds::core::policy::Reliability   
     * @brief @extension Getter (see setter with the same name)
     */
    rti::core::policy::AcknowledgmentKind acknowledgment_kind() const;
/** @RTI_remove_lines 1 */
};

// ----------------------------------------------------------------------------

/** @RTI_class_definition NA */
class OMG_DDS_API HistoryImpl : public NativeValueType<HistoryImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(HistoryImpl)
    typedef NativeValueType<HistoryImpl> Base;
    typedef dds::core::policy::History WrapperType;

    HistoryImpl()
    {
        // base constructor takes care
    }

    HistoryImpl(dds::core::policy::HistoryKind the_kind, int32_t the_depth)
    {
        kind(the_kind);
        depth(the_depth);
    }

    dds::core::policy::HistoryKind  kind() const;
    HistoryImpl& kind(dds::core::policy::HistoryKind the_kind);

    int32_t depth() const;
    HistoryImpl& depth(int32_t the_depth);

    /**
     * @memberof dds::core::policy::History
     * @brief @extension Specifies how a writer should handle previously written
     * samples to a new reader.
     *
     * @details \dref_details_HistoryQosPolicy_refilter
     */
    dds::core::policy::History& refilter(
        rti::core::policy::RefilterKind refilter_kind);

    /**
     * @memberof dds::core::policy::History
     * @brief @extension Getter (see setter with the same name)
     */
    rti::core::policy::RefilterKind refilter() const;
};

// ----------------------------------------------------------------------------

/** @RTI_class_definition NA */
class OMG_DDS_API ResourceLimitsImpl : public NativeValueType<ResourceLimitsImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ResourceLimitsImpl)

    typedef dds::core::policy::ResourceLimits WrapperType;

private:
  typedef NativeValueType<ResourceLimitsImpl> Base;

public:
    ResourceLimitsImpl()
    {
    }

    ResourceLimitsImpl(int32_t the_max_samples,
                   int32_t the_max_instances, 
                   int32_t the_max_samples_per_instance);

public:
    ResourceLimitsImpl& max_samples(int32_t the_max_samples);
    int32_t max_samples() const; 

    ResourceLimitsImpl& max_instances(int32_t the_max_instances);
    int32_t max_instances() const;

    ResourceLimitsImpl& max_samples_per_instance(int32_t the_max_samples_per_instance);
    int32_t max_samples_per_instance() const; 

    /**
     * @memberof dds::core::policy::ResourceLimits 
     * @brief @extension Sets the number of samples that a DataWriter or
     * a DataWriter will preallocate.
     * 
     * @details \dref_details_ResourceLimitsQosPolicy_initial_samples
     */
    dds::core::policy::ResourceLimits& initial_samples(
        int32_t the_initial_samples);

    /**
     * @memberof dds::core::policy::ResourceLimits 
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_samples() const; 

    /**
     * @memberof dds::core::policy::ResourceLimits 
     * @brief @extension Sets the number of instances that a DataWriter or
     * a DataWriter will preallocate.
     * 
     * @details \dref_details_ResourceLimitsQosPolicy_initial_instances
     */
    dds::core::policy::ResourceLimits& initial_instances(
        int32_t the_initial_instances);

    /**
     * @memberof dds::core::policy::ResourceLimits 
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_instances() const;

    /**
     * @memberof dds::core::policy::ResourceLimits 
     * @brief @extension Sets the number of hash buckets for looking up instances
     * 
     * @details \dref_details_ResourceLimitsQosPolicy_instance_hash_buckets
     */
    dds::core::policy::ResourceLimits& instance_hash_buckets(
        int32_t the_instance_hash_buckets);

    /**
     * @memberof dds::core::policy::ResourceLimits 
     * @brief Getter (see setter with the same name)
     */
    int32_t instance_hash_buckets() const; 
/** @RTI_remove_lines 1 */
};

// ----------------------------------------------------------------------------

/** @RTI_class_definition NA */
class OMG_DDS_API WriterDataLifecycleImpl
    : public NativeValueType<WriterDataLifecycleImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(WriterDataLifecycleImpl)

    typedef dds::core::policy::WriterDataLifecycle WrapperType;
private:
  typedef NativeValueType<WriterDataLifecycleImpl> Base;
public:
    WriterDataLifecycleImpl()
    {
    }

    explicit WriterDataLifecycleImpl(bool autodispose)
    {
        autodispose_unregistered_instances(autodispose);
    }

public:
    bool autodispose_unregistered_instances() const;
    WriterDataLifecycleImpl& autodispose_unregistered_instances(bool b);

    /**
     * @memberof dds::core::policy::WriterDataLifecycle 
     * @brief @extension Maximum duration for which the DataWriter will maintain
     * information regarding an instance once it has unregistered the instance.
     * 
     * @details \dref_details_WriterDataLifecycleQosPolicy_autopurge_unregistered_instances_delay
     */
    dds::core::policy::WriterDataLifecycle& autopurge_unregistered_instances_delay(
        const dds::core::Duration& duration);

    /**
     * @memberof dds::core::policy::WriterDataLifecycle
     * @brief @extension Getter (see setter with the same name)
     */
    dds::core::Duration autopurge_unregistered_instances_delay() const;

    /**
     * @memberof dds::core::policy::WriterDataLifecycle 
     * @brief @extension Maximum duration for which the DataWriter will maintain
     * information regarding an instance once it has disposed the instance.
     * 
     * @details \dref_details_WriterDataLifecycleQosPolicy_autopurge_disposed_instances_delay
     */
    dds::core::policy::WriterDataLifecycle& autopurge_disposed_instances_delay(
        const dds::core::Duration& duration);

    /**
     * @memberof dds::core::policy::WriterDataLifecycle
     * @brief @extension Getter (see setter with the same name)
     */
    dds::core::Duration autopurge_disposed_instances_delay() const;
/** @RTI_remove_lines 1 */
};

// ----------------------------------------------------------------------------

class OMG_DDS_API TransportPriorityImpl
    : public NativeValueType<TransportPriorityImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportPriorityImpl)

private:
  typedef NativeValueType<TransportPriorityImpl> Base;

public:
    explicit TransportPriorityImpl(int32_t priority)
    {
        value(priority);
    }

    TransportPriorityImpl()
    {
        value(0);
    }

public:
    TransportPriorityImpl& value(int32_t prio);
    int32_t value() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API TimeBasedFilterImpl
    : public NativeValueType<TimeBasedFilterImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TimeBasedFilterImpl)

private:
  typedef NativeValueType<TimeBasedFilterImpl> Base;

public:

    TimeBasedFilterImpl() { }

    explicit TimeBasedFilterImpl(const dds::core::Duration& the_min_separation)
    {
        minimum_separation(the_min_separation);
    }

public:
    TimeBasedFilterImpl& minimum_separation(const dds::core::Duration& ms);
    dds::core::Duration minimum_separation() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API LifespanImpl : public NativeValueType<LifespanImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(LifespanImpl)

private:
  typedef NativeValueType<LifespanImpl> Base;

public:

    LifespanImpl() { }

    explicit LifespanImpl(const dds::core::Duration& d)
    {
        duration(d);
    }

public:
    LifespanImpl& duration(const dds::core::Duration& ms);
    dds::core::Duration duration() const;
};

// ----------------------------------------------------------------------------

/** @RTI_class_definition NA */
class OMG_DDS_API DestinationOrderImpl
    : public NativeValueType<DestinationOrderImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DestinationOrderImpl)

    typedef dds::core::policy::DestinationOrder WrapperType;
public:

    DestinationOrderImpl()
    {
    }

    explicit DestinationOrderImpl(
       dds::core::policy::DestinationOrderKind the_kind)
    {
        kind(the_kind);
    }

public:
    DestinationOrderImpl& kind(dds::core::policy::DestinationOrderKind the_kind);
    dds::core::policy::DestinationOrderKind kind() const;

    /**
     * @memberof dds::core::policy::DestinationOrder
     * @brief @extension Sets the destination order scope
     *
     * @details \dref_details_DestinationOrderQosPolicy_scope
     */
    DestinationOrderImpl& scope(rti::core::policy::DestinationOrderScopeKind the_scope);

    /**
     * @memberof dds::core::policy::DestinationOrder
     * @brief @extension Getter (see the setter with the same name)
     */
    rti::core::policy::DestinationOrderScopeKind scope() const;

    /** 
     * @memberof dds::core::policy::DestinationOrder 
     * @brief @extension Sets the allowed tolerance between source timestamps of
     * consecutive samples.
     * 
     * @details \dref_details_DestinationOrderQosPolicy_source_timestamp_tolerance
     */
    dds::core::policy::DestinationOrder& source_timestamp_tolerance(
        const dds::core::Duration& ms);

    /**
     * @memberof dds::core::policy::DestinationOrder
     * @brief @extension Getter (see the setter with the same name)
     */
    dds::core::Duration source_timestamp_tolerance() const;
/** @RTI_remove_lines 1 */
};

// ----------------------------------------------------------------------------

class OMG_DDS_API DurabilityServiceImpl
    : public NativeValueType<DurabilityServiceImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DurabilityServiceImpl)

private:
  typedef NativeValueType<DurabilityServiceImpl> Base;

public:

    DurabilityServiceImpl() { }

    DurabilityServiceImpl(
        const dds::core::Duration& the_service_cleanup_delay,
        dds::core::policy::HistoryKind the_history_kind,
        int32_t the_history_depth,
        int32_t the_max_samples,
        int32_t the_max_instances,
        int32_t the_max_samples_per_instance)
    {
        service_cleanup_delay(the_service_cleanup_delay);
        history_kind(the_history_kind);
        history_depth(the_history_depth);
        max_samples(the_max_samples);
        max_instances(the_max_instances);
        max_samples_per_instance(the_max_samples_per_instance);
    }


public:
    DurabilityServiceImpl& service_cleanup_delay(const dds::core::Duration& d);
    dds::core::Duration service_cleanup_delay() const;

    DurabilityServiceImpl& history_kind(dds::core::policy::HistoryKind the_kind);
    dds::core::policy::HistoryKind history_kind() const;

    DurabilityServiceImpl& history_depth(int32_t the_depth);
    int32_t history_depth() const;

    DurabilityServiceImpl& max_samples(int32_t the_max_samples);
    int32_t max_samples() const;

    DurabilityServiceImpl& max_instances(int32_t the_max_instances);
    int32_t max_instances() const;

    DurabilityServiceImpl& max_samples_per_instance(int32_t the_max_samples_per_instance);
    int32_t max_samples_per_instance() const;
};

// ----------------------------------------------------------------------------

class OMG_DDS_API TopicDataImpl : public NativeValueType<TopicDataImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TopicDataImpl)

public:

    typedef NativeValueType<TopicDataImpl> Base;

    TopicDataImpl() { };

    explicit TopicDataImpl(const dds::core::ByteSeq& sequence)
    {
        value(sequence.begin(), sequence.end());
    }

    TopicDataImpl(const uint8_t* value_begin, const uint8_t* value_end);

public:
    // Spec Error: CPPPSM-216: This setter confilicts with the getter which 
    // takes in a ByteSeq
     
   // TopicData& value(const dds::core::ByteSeq& seq);
     

    template <typename OCTET_ITER>
    TopicDataImpl& value(OCTET_ITER the_begin, OCTET_ITER the_end)
    {
        value_impl(
            the_begin,
            the_end,
            typename std::iterator_traits<OCTET_ITER>::iterator_category());

        return *this;
    }

    dds::core::ByteSeq value() const
    {
        return dds::core::ByteSeq(begin(), end());
    }

    dds::core::ByteSeq& value(dds::core::ByteSeq& dst) const;

    const uint8_t* begin() const;
    const uint8_t* end() const;

private:
    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::random_access_iterator_tag)
    {
        // Knowing the size of the range [begin, end) allows for an optimized
        // implementation.
        resize(the_end - the_begin);
        std::copy(the_begin, the_end, 
                  DDS_OctetSeq_get_contiguous_buffer(&native().value));
    }

    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::input_iterator_tag)
    {
        // Generic, less-efficient implementation for iterators that don't
        // support calculating the length of a range
        int sequence_index = 0;
        for (OCTET_ITER it = the_begin; it != the_end; ++it) {
            resize(sequence_index + 1);
            *DDS_OctetSeq_get_reference(&native().value, sequence_index) = *it;
            sequence_index++;
        }
    }

    void resize(size_t length);
    size_t length() const;

};

// ----------------------------------------------------------------------------

class OMG_DDS_API GroupDataImpl : public NativeValueType<GroupDataImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(GroupDataImpl)

public:

    typedef NativeValueType<GroupDataImpl> Base;

    GroupDataImpl() { };

    explicit GroupDataImpl(const dds::core::ByteSeq& sequence)
    {
        value(sequence.begin(), sequence.end());
    }

    GroupDataImpl(const uint8_t* value_begin, const uint8_t* value_end);

public:

    // Spec Error: CPPPSM-216: This setter confilicts with the getter which 
    // takes in a ByteSeq
     
   // GroupData& value(const dds::core::ByteSeq& seq);

    template <typename OCTET_ITER>
    GroupDataImpl& value(OCTET_ITER the_begin, OCTET_ITER the_end)
    {
        value_impl(
            the_begin,
            the_end,
            typename std::iterator_traits<OCTET_ITER>::iterator_category());

        return *this;
    }

    dds::core::ByteSeq value() const
    {
        return dds::core::ByteSeq(begin(), end());
    }

    dds::core::ByteSeq& value(dds::core::ByteSeq& dst) const;

    const uint8_t* begin() const;
    const uint8_t* end() const;

private:
    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::random_access_iterator_tag)
    {
        // Knowing the size of the range [begin, end) allows for an optimized
        // implementation.
        resize(the_end - the_begin);
        std::copy(the_begin, the_end, DDS_OctetSeq_get_contiguous_buffer(&native().value));
    }

    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::input_iterator_tag)
    {
        // Generic, less-efficient implementation for iterators that don't
        // support calculating the length of a range
        int sequence_index = 0;
        for (OCTET_ITER it = the_begin; it != the_end; ++it) {
            resize(sequence_index + 1);
            *DDS_OctetSeq_get_reference(&native().value, sequence_index) = *it;
            sequence_index++;
        }
    }

    void resize(size_t length);
    size_t length() const;

};

// ----------------------------------------------------------------------------

class OMG_DDS_API TypeConsistencyEnforcementImpl
    : public NativeValueType<TypeConsistencyEnforcementImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TypeConsistencyEnforcementImpl)

private:
  typedef NativeValueType<TypeConsistencyEnforcementImpl> Base;

public:
    TypeConsistencyEnforcementImpl() { }

    TypeConsistencyEnforcementImpl(
        dds::core::policy::TypeConsistencyEnforcementKind the_kind)
    {
        kind(the_kind);
    }

public:
    TypeConsistencyEnforcementImpl& kind(
       dds::core::policy::TypeConsistencyEnforcementKind value);

    dds::core::policy::TypeConsistencyEnforcementKind kind() const;
};

/** @RTI_namespace_end dds::core::policy */
} } } // namespace dds::core::policy

// --- Extensions: ------------------------------------------------------------

namespace rti { namespace core { namespace policy {

/** 
 * @RTI_class_definition class DomainParticipantResourceLimits 
 * @ingroup DDSDomainParticipantResourceLimitsQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the memory usage of certain
 * dds::domain::DomainParticipant resources
 *
 * @details \dref_details_DomainParticipantResourceLimitsQosPolicy
 */
class OMG_DDS_API DomainParticipantResourceLimits : 
    public NativeValueType<DomainParticipantResourceLimits> {
public:

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DomainParticipantResourceLimits)

    typedef NativeValueType<DomainParticipantResourceLimits> Base;

    DomainParticipantResourceLimits() { }

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_writer_allocation
     */
    DomainParticipantResourceLimits& 
        local_writer_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings local_writer_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_reader_allocation
     */
    DomainParticipantResourceLimits& 
        local_reader_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings local_reader_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_publisher_allocation
     */
    DomainParticipantResourceLimits& 
        local_publisher_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings local_publisher_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_subscriber_allocation
     */
    DomainParticipantResourceLimits& 
        local_subscriber_allocation(const AllocationSettings& settings);
    AllocationSettings local_subscriber_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_topic_allocation
     */
    DomainParticipantResourceLimits& 
        local_topic_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings local_topic_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_writer_allocation
     */
    DomainParticipantResourceLimits& 
        remote_writer_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings remote_writer_allocation() const;
    
    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_reader_allocation
     */
    DomainParticipantResourceLimits& 
        remote_reader_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings remote_reader_allocation() const;
    
    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_participant_allocation
     */
    DomainParticipantResourceLimits& 
        remote_participant_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings remote_participant_allocation() const;
    
    /** \dref_DomainParticipantResourceLimitsQosPolicy_matching_writer_reader_pair_allocation
     */
    DomainParticipantResourceLimits& 
        matching_writer_reader_pair_allocation(
            const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings matching_writer_reader_pair_allocation() const;
    
    /** \dref_DomainParticipantResourceLimitsQosPolicy_matching_reader_writer_pair_allocation
     */
    DomainParticipantResourceLimits& 
        matching_reader_writer_pair_allocation(
            const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings matching_reader_writer_pair_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_ignored_entity_allocation
     */
    DomainParticipantResourceLimits& 
        ignored_entity_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings ignored_entity_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_content_filtered_topic_allocation
     */
    DomainParticipantResourceLimits& 
        content_filtered_topic_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings content_filtered_topic_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_content_filter_allocation
     */
    DomainParticipantResourceLimits& 
        content_filter_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings content_filter_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_read_condition_allocation
     */
    DomainParticipantResourceLimits& 
        read_condition_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings read_condition_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_query_condition_allocation
     */
    DomainParticipantResourceLimits& 
        query_condition_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings query_condition_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_outstanding_asynchronous_sample_allocation
     */
    DomainParticipantResourceLimits& 
        outstanding_asynchronous_sample_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings outstanding_asynchronous_sample_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_flow_controller_allocation
     */
    DomainParticipantResourceLimits&
        flow_controller_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings flow_controller_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_writer_hash_buckets
     */
    DomainParticipantResourceLimits& 
        local_writer_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t local_writer_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_reader_hash_buckets
     */
    DomainParticipantResourceLimits& 
        local_reader_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t local_reader_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_publisher_hash_buckets
     */
    DomainParticipantResourceLimits& 
        local_publisher_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t local_publisher_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_subscriber_hash_buckets
     */
    DomainParticipantResourceLimits& 
        local_subscriber_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t local_subscriber_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_local_topic_hash_buckets
     */
    DomainParticipantResourceLimits& 
        local_topic_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t local_topic_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_writer_hash_buckets
     */
    DomainParticipantResourceLimits& 
        remote_writer_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t remote_writer_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_reader_hash_buckets
     */
    DomainParticipantResourceLimits& 
        remote_reader_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t remote_reader_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_participant_hash_buckets
     */
    DomainParticipantResourceLimits& 
        remote_participant_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t remote_participant_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_matching_writer_reader_pair_hash_buckets
     */
    DomainParticipantResourceLimits& 
        matching_writer_reader_pair_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t matching_writer_reader_pair_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_matching_reader_writer_pair_hash_buckets
     */
    DomainParticipantResourceLimits& 
        matching_reader_writer_pair_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t matching_reader_writer_pair_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_ignored_entity_hash_buckets
     */
    DomainParticipantResourceLimits& 
        ignored_entity_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t ignored_entity_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_content_filtered_topic_hash_buckets
     */
    DomainParticipantResourceLimits& 
        content_filtered_topic_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t content_filtered_topic_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_content_filter_hash_buckets
     */
    DomainParticipantResourceLimits& 
        content_filter_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t content_filter_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_flow_controller_hash_buckets
     */
    DomainParticipantResourceLimits& 
        flow_controller_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t flow_controller_hash_buckets() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_max_gather_destinations
     */
    DomainParticipantResourceLimits& 
        max_gather_destinations(int32_t max_destinations);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_gather_destinations() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_participant_user_data_max_length
     */
    DomainParticipantResourceLimits& 
        participant_user_data_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t participant_user_data_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_topic_data_max_length
     */
    DomainParticipantResourceLimits& 
        topic_data_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t topic_data_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_publisher_group_data_max_length
     */
    DomainParticipantResourceLimits& 
        publisher_group_data_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t publisher_group_data_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_subscriber_group_data_max_length
     */
    DomainParticipantResourceLimits& 
        subscriber_group_data_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t subscriber_group_data_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_writer_user_data_max_length
     */
    DomainParticipantResourceLimits& 
        writer_user_data_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t writer_user_data_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_reader_user_data_max_length
     */
    DomainParticipantResourceLimits& 
        reader_user_data_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t reader_user_data_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_max_partitions
     */
    DomainParticipantResourceLimits& max_partitions(int32_t partitions);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_partitions() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_max_partition_cumulative_characters
     */
    DomainParticipantResourceLimits& 
        max_partition_cumulative_characters(int32_t max_characters);
    int32_t max_partition_cumulative_characters() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_type_code_max_serialized_length
     */
    DomainParticipantResourceLimits& 
        type_code_max_serialized_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t type_code_max_serialized_length() const;
    
    /** \dref_DomainParticipantResourceLimitsQosPolicy_type_object_max_serialized_length
     */
    DomainParticipantResourceLimits& 
        type_object_max_serialized_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t type_object_max_serialized_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_type_object_max_deserialized_length
     */
    DomainParticipantResourceLimits& 
        type_object_max_deserialized_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t type_object_max_deserialized_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_deserialized_type_object_dynamic_allocation_threshold
     */
    DomainParticipantResourceLimits& 
        deserialized_type_object_dynamic_allocation_threshold(
            int32_t threshold);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t deserialized_type_object_dynamic_allocation_threshold() const;
    
    /** \dref_DomainParticipantResourceLimitsQosPolicy_contentfilter_property_max_length
     */
    DomainParticipantResourceLimits& 
        contentfilter_property_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t contentfilter_property_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_channel_seq_max_length
     */
    DomainParticipantResourceLimits& channel_seq_max_length(
        int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t channel_seq_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_channel_filter_expression_max_length
     */
    DomainParticipantResourceLimits& 
        channel_filter_expression_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t channel_filter_expression_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_participant_property_list_max_length
     */
    DomainParticipantResourceLimits& 
        participant_property_list_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t participant_property_list_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_participant_property_string_max_length
     */
    DomainParticipantResourceLimits& 
        participant_property_string_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t participant_property_string_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_writer_property_list_max_length
     */
    DomainParticipantResourceLimits& 
        writer_property_list_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t writer_property_list_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_writer_property_string_max_length
     */
    DomainParticipantResourceLimits& 
        writer_property_string_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t writer_property_string_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_reader_property_list_max_length
     */
    DomainParticipantResourceLimits& 
        reader_property_list_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t reader_property_list_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_reader_property_string_max_length
     */
    DomainParticipantResourceLimits& 
        reader_property_string_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t reader_property_string_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_max_endpoint_groups
     */
    DomainParticipantResourceLimits& max_endpoint_groups(int32_t max_groups);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_endpoint_groups() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_max_endpoint_group_cumulative_characters
     */
    DomainParticipantResourceLimits& 
        max_endpoint_group_cumulative_characters(
            int32_t max_cumulative_characters);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_endpoint_group_cumulative_characters() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_transport_info_list_max_length
     */
    DomainParticipantResourceLimits& transport_info_list_max_length(int32_t max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t transport_info_list_max_length() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_ignored_entity_replacement_kind
     */
    DomainParticipantResourceLimits& ignored_entity_replacement_kind(
        IgnoredEntityReplacementKind max_length);

    /**
     * @brief Getter (see setter with the same name)
     */
    IgnoredEntityReplacementKind ignored_entity_replacement_kind() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_topic_query_allocation
     */
    DomainParticipantResourceLimits&
    remote_topic_query_allocation(const AllocationSettings& settings);

    /**
     * @brief Getter (see setter with the same name)
     */
    AllocationSettings remote_topic_query_allocation() const;

    /** \dref_DomainParticipantResourceLimitsQosPolicy_remote_topic_query_hash_buckets
     */
    DomainParticipantResourceLimits& remote_topic_query_hash_buckets(int32_t hash_buckets);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t remote_topic_query_hash_buckets() const;

};

// ----------------------------------------------------------------------------

/** 
 * @RTI_class_definition class TransportBuiltin 
 * @ingroup DDSTransportBuiltinQosModule 
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Specifies which built-in transports to use
 *
 * @details \dref_details_TransportBuiltinQosPolicy
 */
class OMG_DDS_API TransportBuiltin : public NativeValueType<TransportBuiltin> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportBuiltin)

    typedef NativeValueType<TransportBuiltin> Base;

    /**
     * @brief Alias name for the shared-memory built-in transport
     */
    static const std::string SHMEM_ALIAS;

    /**
     * @brief Alias name for the UDPv4 built-in transport
     */
    static const std::string UDPv4_ALIAS; 

    /**
     * @brief Alias name for the UDPv6 built-in transport
     */
    static const std::string UDPv6_ALIAS; 

    /**
     * @brief Creates the default policy
     */
    TransportBuiltin() { }

    /**
     * @brief Creates an instnace with the transport selection that the mask
     * specifies
     */
    TransportBuiltin(
        const rti::core::policy::TransportBuiltinMask& the_mask)
    {
        mask(the_mask);
    }

    /**
     * @brief Creates a policy that selects TransportBuiltinMask::all()
     */
    static TransportBuiltin All()
    {
        return TransportBuiltin(rti::core::policy::TransportBuiltinMask::all());
    }

    /**
     * @brief Creates a policy that selects TransportBuiltinMask::none()
     */
    static TransportBuiltin None()
    {
        return TransportBuiltin(
            rti::core::policy::TransportBuiltinMask::none());
    }

    /**
     * @brief Creates a policy that selects TransportBuiltinMask::shmem()
     */
    static TransportBuiltin Shmem()
    {
        return TransportBuiltin(
            rti::core::policy::TransportBuiltinMask::shmem());
    }

    /**
     * @brief Creates a policy that selects TransportBuiltinMask::udpv4()
     */
    static TransportBuiltin UDPv4()
    {
        return TransportBuiltin(
            rti::core::policy::TransportBuiltinMask::udpv4());
    }

    /**
     * @brief Creates a policy that selects TransportBuiltinMask::udpv6()
     */
    static TransportBuiltin UDPv6()
    {
        return TransportBuiltin(
            rti::core::policy::TransportBuiltinMask::udpv6());
    }

    /**
     * @brief Set the selected transports through a mask
     */
    TransportBuiltin& mask(
       rti::core::policy::TransportBuiltinMask the_mask);

    /**
     * @brief Get the mask that indicates which transports are selected
     */
    rti::core::policy::TransportBuiltinMask mask() const;
};

/**
 * @RTI_class_definition class TransportUnicast
 * @ingroup DDSTransportUnicastQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Specifies a subset of transports and a port number that
 * can be used by a dds::core::Entity to receive data.
 *
 * @details \dref_details_TransportUnicastQosPolicy
 */
class OMG_DDS_API TransportUnicast : public NativeValueType<TransportUnicast> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportUnicast)

    /**
     * @brief Creates the default policy
     */
    TransportUnicast() { }

    /**
     * @brief Creates an instance with the specified settings
     */
    explicit TransportUnicast(const rti::core::TransportUnicastSettingsSeq& settings);

    /**
     * @brief Sets the unicast settings
     *
     * @details \dref_details_TransportUnicastQosPolicy_value
     */
    TransportUnicast& settings(const rti::core::TransportUnicastSettingsSeq& value);

    /**
     * @brief Gets the unicast settings
     */
    rti::core::TransportUnicastSettingsSeq settings() const;
};

// ----------------------------------------------------------------------------

/** 
 * @RTI_class_definition class Database 
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures threads and resource limits that \ndds uses to
 * control its internal database
 *
 * @details \dref_details_DatabaseQosPolicy
 */
class OMG_DDS_API Database : public NativeValueType<Database> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Database)

private:
  typedef NativeValueType<Database> Base;

public:
  Database() { }

    /**
     * @brief Sets the thread settings
     *
     * @details \dref_details_DatabaseQosPolicy_thread
     */
    Database& thread(const rti::core::ThreadSettings& the_thread);

    /**
     * @brief Gets the thread settings (by const reference)
     */
    const rti::core::ThreadSettings& thread() const;

    /**
     * @brief Gets the thread settings by reference
     *
     * @see thread(const rti::core::ThreadSettings&)
     */
    rti::core::ThreadSettings& thread();

    /**
     * \dref_details_DatabaseQosPolicy_shutdown_timeout
     */
    Database& shutdown_timeout(const dds::core::Duration& the_shutdown_timeout);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration shutdown_timeout() const;

    /**
     * \dref_details_DatabaseQosPolicy_cleanup_period
     */
    Database& cleanup_period(
        const dds::core::Duration& the_cleanup_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration cleanup_period() const;

    /**
     * \dref_details_DatabaseQosPolicy_shutdown_cleanup_period
     */
    Database& shutdown_cleanup_period(const dds::core::Duration& period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration shutdown_cleanup_period() const;

    /**
     * \dref_details_DatabaseQosPolicy_initial_records
     */
    Database& initial_records(int32_t the_initial_records);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_records() const;

    /**
     * \dref_details_DatabaseQosPolicy_max_skiplist_level
     */
    Database& max_skiplist_level(int32_t the_max_skiplist_level);
    int32_t max_skiplist_level() const;

    /**
     * \dref_details_DatabaseQosPolicy_max_weak_references
     */
    Database& max_weak_references(int32_t the_max_weak_references);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_weak_references() const;

    /**
     * \dref_details_DatabaseQosPolicy_initial_weak_references
     */
    Database& initial_weak_references(int32_t the_initial_weak_references);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_weak_references() const;
};


// ----------------------------------------------------------------------------
/**
 * @ingroup DDSDiscoveryQosModule 
 * @dref_NDDS_DISCOVERY_PEERS  
 */

/** 
 * @RTI_class_definition class Discovery 
 * @ingroup DDSDiscoveryQosModule 
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures entity discovery
 *
 * @details \dref_details_DiscoveryQosPolicy
 */
class OMG_DDS_API Discovery : public NativeValueType<Discovery> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Discovery)
    typedef NativeValueType<Discovery> Base;

    /**
     * @brief Creates the default policy
     */
    Discovery();

    /**
     * @brief Sets the transports (by their aliases) available for the
     * discovery mechanism
     *
     * @details \dref_details_DiscoveryQosPolicy_enabled_transports
     */
    Discovery& enabled_transports(
       const dds::core::StringSeq& the_enabled_transports);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::StringSeq enabled_transports() const;

    /**
     * @brief Sets the initial list of peers that the discovery mechanism will
     * contact to announce this DomainParticipant
     *
     * @details \dref_details_DiscoveryQosPolicy_initial_peers
     */
    Discovery& initial_peers(const dds::core::StringSeq& the_initial_peers);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::StringSeq initial_peers() const;

    /**
     * \dref_DiscoveryQosPolicy_multicast_receive_addresses
     */
    Discovery& multicast_receive_addresses(
       const dds::core::StringSeq& the_multicast_receive_addresses);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::StringSeq multicast_receive_addresses() const;

    /**
     * \dref_DiscoveryQosPolicy_metatraffic_transport_priority
     */
    Discovery& metatraffic_transport_priority(
       int32_t the_metatraffic_transport_priority);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t metatraffic_transport_priority() const;

    /**
     * \dref_DiscoveryQosPolicy_accept_unknown_peers
     */
    Discovery& accept_unknown_peers(bool the_accept_unknown_peers);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool accept_unknown_peers() const;

    /**
     * \dref_DiscoveryQosPolicy_enable_endpoint_discovery
     */
    Discovery& enable_endpoint_discovery(bool the_enable_endpoint_discovery);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_endpoint_discovery() const;
};

// ----------------------------------------------------------------------------

/** 
 * @RTI_class_definition class EntityName 
 * @ingroup DDSEntityNameQosModule 
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Assigns a name to a DomainParticipant, Publisher, Subscriber,
 * DataWriter or DataReader.
 *
 * Except for the Publisher and Subscriber, these names are visible during the
 * discovery process and in RTI tools to help you visualize and debug your system.
 *
 * @details \dref_details_EntityNameQosPolicy
 */
class OMG_DDS_API EntityName : public NativeValueType<EntityName> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(EntityName)

private:
  typedef NativeValueType<EntityName> Base;

public:
    /**
     * @brief Creates the default policy (no name)
     */
    EntityName() { }

    /**
     * @brief Creates an instance that specifies an entity name
     */
    explicit EntityName(const std::string& the_name)
    {
        name(the_name);
    }

    /**
     * @brief Sets the entity name.
     *
     * @param the_name An optional string. An unset value indicates that
     * this entity should have no name. A set value will set a name. The string
     * can't exceed 255 characters.
     *
     * \default Unset (no name)
     */
    EntityName& name(const rti::core::optional_value<std::string>& the_name);

    /**
     * @brief Sets the entity name
     *
     * @param the_name Can't exceed 255 characters.
     */
    EntityName& name(const char *the_name);

    /**
     * @brief Gets the entity name
     *
     * @return An optional string. An unset value indicates that the entity
     * has not been assigned a name.
     */
    rti::core::optional_value<std::string> name() const;

    /**
     * @brief Specifies an entity role name
     *
     * With Durable Subscriptions this name is used to specify to which Durable
     * Subscription the DataReader belongs.
     *
     * With Collaborative DataWriters this name is used to specify to which
     * endpoint group the DataWriter belongs.
     *
     * @param the_name An optional string. An unset value indicates that the
     * Entity will have no role name (the default). The string can't exceed 255
     * characters.
     *
     * \default Unset (no role name)
     */
    EntityName& role_name(const rti::core::optional_value<std::string>& the_name);

    /**
     * @brief Sets the role name
     *
     * @see role_name(const rti::core::optional_value<std::string>&)
     */
    EntityName& role_name(const char *the_name);

    /**
     * @brief Gets the entity role name
     *
     * @return An optional string. An unset value indicates that the entity
     * has not been assigned a role name.
     */
    rti::core::optional_value<std::string> role_name() const;
};

// ----------------------------------------------------------------------------

/** 
 * @RTI_class_definition class Property 
 * @ingroup DDSPropertyQosModule 
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Stores key/value string pairs that can configure certain
 * parameters of \ndds not exposed through QoS policies. It can also store and
 * propagate through the discovery mechanism application-specific information
 * associated to a dds::core::Entity.
 *
 * @details \dref_details_PropertyQosPolicy
 */
class OMG_DDS_API Property : public NativeValueType<Property> {
public:
    /**
     * @brief The type of the elements that Property contains
     *
     * Key/value string pairs.
     */
    typedef std::pair<std::string, std::string> Entry;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Property)

    /**
     * @brief Creates an empty Property container
     */
    Property() { }

    /**
     * @brief Creates a Property container with the entries specified by
     * an iterator range.
     *
     * @see set(EntryIter, EntryIter, bool)
     */
    template <typename EntryIter>
    Property(EntryIter begin, EntryIter end, bool is_propagate = false)
    {
        set(begin, end, is_propagate);
    }

  #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief @st_cpp11 Creates a Property container with entries from an initializer_list
     *
     * For example:
     * @code
     * Property my_properties {{"key 1", "value 1"}, {"key 2", "value 2"}};
     * @endcode
     *
     * If a key is duplicated, only one entry will be inserted, with the value
     * that comes last.
     */
    Property(std::initializer_list<Entry> entries)
    {
        set(entries);
    }
  #endif

    /**
     * @brief Returns true if a property exists
     */
    bool exists(const std::string& key) const
    {
        return try_get(key).is_set();
    }

    /**
     * @brief Returns the value of a property identified by a key if it exists.
     *
     * If the property doesn't exist it throws dds::core::PreconditionNotMetError.
     */
    std::string get(const std::string& key) const;

    /**
     * @brief Returns the value of a property identified by a key or an empty
     * optional_value if it doesn't exist.
     */
    rti::core::optional_value<std::string> try_get(const std::string& key) const;

    /**
     * @brief Adds or assigns a property from a pair of strings
     *
     * If the key doesn't exists it adds the new entry, otherwise it overrides
     * its value with the new one.
     *
     * @param property \p property.first is the key and \p property.second is the value
     * @param propagate Indicates if the property must be propagated on discovery 
     */
    Property& set(const Entry& property, bool propagate = false);

    /**
     * @brief Adds a range of properties
     *
     * If a key is duplicated, only one entry will remain, with the value
     * that comes last.
     *
     * @tparam EntryIter A forward iterator whose value type is Property::Entry,
     * such as the iterators of a \c std::map<std::string, std::string>.
     * @param begin Beginning of a range of Entry
     * @param end End of that range 
     * @param is_propagate Indicates if the property must be propagated on discovery 
     */
    template <typename EntryIter>
    Property& set(EntryIter begin, EntryIter end, bool is_propagate = false)
    {
        for (; begin != end; ++begin) {
            set(*begin, is_propagate);
        }
        return *this;
    }

    /**
     * @brief Removes the property identified by a key
     * @return true if the property was removed or false if it didn't exist.
     */
    bool remove(const std::string& key);

    /**
     * @brief Returns the number of properties
     */
    size_t size() const;

    /**
     * @brief Retrieves a copy of all the entries in a std::map
     */
    std::map<std::string, std::string> get_all() const;


  #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief @st_cpp11 Adds properties from an initializer_list
     */
    void set(std::initializer_list<Entry> entries, bool is_propagate = false)
    {
        set(entries.begin(), entries.end(), is_propagate);
    }
  #endif

    /**
     * @brief Returns whether the 'propagate' attribute for a property is set
     * or not.
     */
    bool propagate(const std::string& key) const;
};

// ----------------------------------------------------------------------------

/** 
 * @RTI_class_definition class LocatorFilter 
 * @ingroup DDSLocatorFilterQosModule 
 * @headerfile rti/core/policy/CorePolicy.hpp
 * 
 * @brief @extension Configures how the dds::topic::PublicationBuiltinTopicData
 * reports the configuration of a MultiChannel DataWriter.
 *
 * @details \dref_details_LocatorFilterQosPolicy
 */
class OMG_DDS_API LocatorFilter : public NativeValueType<LocatorFilter> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(LocatorFilter)

private:
  typedef NativeValueType<LocatorFilter> Base;

public: 

    /**
     * @brief A LocatorFilter policy is a collection of LocatorFilterElement
     */
    typedef rti::core::LocatorFilterElement Filter;

    /**
     * @brief A vector of Filter
     */
    typedef std::vector<Filter> FilterSeq;

    /**
     * @brief Creates the default policy
     */
    LocatorFilter() 
    {
        filter_name(rti::topic::stringmatch_filter_name());
    }

    /**
     * @brief Creates an instance with a sequence of filters and a filter name
     */
    LocatorFilter(
        const FilterSeq& the_locator_filters, 
        const std::string& the_filter_name = rti::topic::stringmatch_filter_name())
    {
        locator_filters(the_locator_filters);
        filter_name(the_filter_name);
    }

    /**
     * @brief Sets the locator filters
     *
     * @details \dref_details_LocatorFilterQosPolicy_locator_filters
     */
    LocatorFilter& locator_filters(
       const FilterSeq& the_locator_filters);

    /**
     * @brief Gets the locator filters
     */
    FilterSeq locator_filters() const;

    /**
     * @brief Sets the filter name
     *
     * @details \dref_details_LocatorFilterQosPolicy_filter_name
     */
    LocatorFilter& filter_name(
       const std::string& the_filter_name);

    /**
     * @brief Gets the filter name
     */
    std::string filter_name() const;
};

// This policy is for internal use only
class OMG_DDS_API UserObject : public NativeValueType<UserObject> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(UserObject)

    UserObject() {}
};

// ----------------------------------------------------------------------------

/** 
 * @RTI_class_definition class Service 
 * @ingroup DDSServiceQosModule 
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Indicates if an Entity is associated with a service and
 * if so, which one.
 *
 * @details \dref_details_ServiceQosPolicy
 */
class OMG_DDS_API Service : public NativeValueType<Service> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Service)

private:
  typedef NativeValueType<Service> Base;

public: 

    /**
     * @brief Creates the default policy (no service)
     */
    Service() { }

    /**
     * @brief Creates an instance with the specified service kind
     */
    Service(rti::core::policy::ServiceKind the_kind)
    {
        kind(the_kind);
    }

public:

    /**
     * @brief Returns a Service with ServiceKind::NO_SERVICE
     */
    static Service NoService()
    {
        return Service(ServiceKind::NO_SERVICE);
    }

    /**
     * @brief Returns a Service with ServiceKind::PERSISTENCE
     */
    static Service PersistenceService()
    {
        return Service(ServiceKind::PERSISTENCE);
    }

    /**
     * @brief Returns a Service with ServiceKind::QUEUING
     */
    static Service QueuingService()
    {
        return Service(ServiceKind::QUEUING);
    }

    /**
     * @brief Returns a Service with ServiceKind::ROUTING
     */
    static Service RoutingService()
    {
        return Service(ServiceKind::ROUTING);
    }

    /**
     * @brief Returns a Service with ServiceKind::RECORDING
     */
    static Service RecordingService()
    {
        return Service(ServiceKind::RECORDING);
    }

    /**
     * @brief Returns a Service with ServiceKind::REPLAY
     */
    static Service ReplayService()
    {
        return Service(ServiceKind::REPLAY);
    }

    /**
     * @brief Returns a Service with ServiceKind::DATABASE_INTEGRATION
     */
    static Service DatabaseIntegrationService()
    {
        return Service(ServiceKind::DATABASE_INTEGRATION);
    }

    /**
     * @brief Returns a Service with ServiceKind::WEB_INTEGRATION
     */
    static Service WebIntegrationService()
    {
        return Service(ServiceKind::WEB_INTEGRATION);
    }

    /**
     * @brief Sets the service kind
     */
    Service& kind(const rti::core::policy::ServiceKind the_kind);

    /**
     * @brief Gets the service kind
     */
    rti::core::policy::ServiceKind kind() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class MultiChannel
 * @ingroup DDSMultiChannelQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the ability of a DataWriter to send data on
 * different multicast groups (addresses) based on the value of the data.
 *
 * @details \dref_details_MultiChannelQosPolicy
 */
class OMG_DDS_API MultiChannel : public NativeValueType<MultiChannel> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(MultiChannel)

private:
  typedef NativeValueType<MultiChannel> Base;

public: 

    /**
     * @brief Creates the default policy
     */
    MultiChannel() { }

    /**
     * @brief Creates an instance with the specified channels and filter name
     */
    MultiChannel(const rti::core::ChannelSettingsSeq& the_channels,
                 const std::string& the_filter_name = 
                    rti::topic::stringmatch_filter_name())
    {
        channels(the_channels);
        filter_name(the_filter_name);
    }

    /**
     * \dref_MultiChannelQosPolicy_channels
     */
    MultiChannel& channels(const rti::core::ChannelSettingsSeq& the_channels);

    /**
     * @brief Getter (see the setter with the same name)
     */
    rti::core::ChannelSettingsSeq channels() const;

    /**
     * \dref_MultiChannelQosPolicy_filter_name
     */
    MultiChannel& filter_name(const std::string& the_filter_name);

    /**
     * @brief Getter (see the setter with the same name)
     */
    std::string filter_name() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class PublishMode
 * @ingroup DDSPublishModeQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Specifies whether a dds::pub::DataWriter sends data
 * synchronously or asynchronously.
 *
 * @details \dref_details_MultiChannelQosPolicy
 */
class OMG_DDS_API PublishMode : public NativeValueType<PublishMode> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(PublishMode)

    typedef NativeValueType<PublishMode> Base;

    /**
     * @brief Creates a PublishMode qos policy of synchronous kind
     */
    PublishMode();

    /**
     * @brief Creates a PublishMode qos policy of synchronous kind
     */
    static PublishMode Synchronous();

    /**
     * @brief Creates a PublishMode qos policy of asynchronous kind with
     * default flow controller and undefined priority
     */
    static PublishMode Asynchronous();

    /**
     * @brief Creates a PublishMode qos policy of asynchronous kind with
     * a specific flow controller and undefined priority
     */
    static PublishMode Asynchronous(const std::string& flow_controller_name);

    /**
     * @brief Creates a PublishMode qos policy of asynchronous kind with
     * specific flow controller and priority
     */
    static PublishMode Asynchronous(
        const std::string& flow_controller_name,
        int32_t priority);

    /**
     * @brief Sets the publish mode (synchronous or asynchronous) for a DataWriter
     *
     * @details @dref_details_PublishModeQosPolicy_kind
     */
    PublishMode& kind(const rti::core::policy::PublishModeKind the_kind);

    /**
     * @brief Gets the publish mode
     */
    rti::core::policy::PublishModeKind kind() const;

    /**
     * @brief Gets the flow controller name
     */
    std::string flow_controller_name() const;

    /**
     * @brief Sets the flow controller name associated to a DataWriter
     *
     * @details @dref_details_PublishModeQosPolicy_flow_controller_name
     */
    PublishMode& flow_controller_name(const std::string& name);

    /**
     * @brief Sets the priority of all samples written by a DataWriter
     *
     * @details @dref_details_PublishModeQosPolicy_priority
     */
    int32_t priority() const;

    /**
     * @brief Gets the priority
     */
    PublishMode& priority(int32_t value);
};


// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class WireProtocol
 * @ingroup DDSWireProtocolQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the write protocol of a dds::domain::DomainParticipant
 *
 * @details \dref_details_WireProtocolQosPolicy
 */
class OMG_DDS_API WireProtocol : public NativeValueType<WireProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(WireProtocol)

    typedef NativeValueType<WireProtocol> Base;

    /**
     * \dref_WireProtocolQosPolicy_RTPS_AUTO_ID
     */
    OMG_DDS_API_CLASS_VARIABLE static const uint32_t RTPS_AUTO_ID;

    /**
     * @brief Creates the default policy
     */
    WireProtocol() {}

    /**
     * \dref_WireProtocolQosPolicy_participant_id
     */
    WireProtocol& participant_id(int32_t the_participant_id);

    /**
     * @brief Getter (see the setter with the same name)
     */
    int32_t participant_id() const;

    /**
     * \dref_WireProtocolQosPolicy_rtps_host_id
     */
    WireProtocol& rtps_host_id(uint32_t the_rtps_host_id);

    /**
     * @brief Getter (see the setter with the same name)
     */
    uint32_t rtps_host_id() const;

    /**
     * \dref_WireProtocolQosPolicy_rtps_app_id
     */
    WireProtocol& rtps_app_id(uint32_t the_rtps_app_id);

    /**
     * @brief Getter (see the setter with the same name)
     */
    uint32_t rtps_app_id() const;

    /**
     * \dref_WireProtocolQosPolicy_rtps_instance_id
     */
    WireProtocol& rtps_instance_id(uint32_t the_rtps_instance_id);

    /**
     * @brief Getter (see the setter with the same name)
     */
    uint32_t rtps_instance_id() const;

    /**
     * \dref_WireProtocolQosPolicy_rtps_well_known_ports
     */
    WireProtocol& rtps_well_known_ports(
        const rti::core::RtpsWellKnownPorts& the_rtps_well_known_ports);

    /**
     * @brief Getter (see the setter with the same name)
     */
    rti::core::RtpsWellKnownPorts rtps_well_known_ports() const;

    /**
     * \dref_WireProtocolQosPolicy_rtps_reserved_port_mask
     */
    WireProtocol& rtps_reserved_port_mask(
        const RtpsReservedPortKindMask& the_rtps_reserved_port_mask);

    /**
     * @brief Getter (see the setter with the same name)
     */
    RtpsReservedPortKindMask rtps_reserved_port_mask() const;

    /**
     * \dref_WireProtocolQosPolicy_rtps_auto_id_kind
     */
    WireProtocol& rtps_auto_id_kind(
        rti::core::policy::WireProtocolAutoKind the_kind);

    /**
     * @brief Getter (see the setter with the same name)
     */
    rti::core::policy::WireProtocolAutoKind rtps_auto_id_kind() const;

    /**
     * \dref_WireProtocolQosPolicy_compute_crc
     */
    WireProtocol& compute_crc(bool crc_needed);

    /**
     * @brief Getter (see the setter with the same name)
     */
    bool compute_crc() const;

    /**
     * \dref_WireProtocolQosPolicy_check_crc
     */
    WireProtocol& check_crc(bool crc_checked);

    /**
     * @brief Getter (see the setter with the same name)
     */
    bool check_crc() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class Batch
 * @ingroup DDSBatchQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Allows a dds::pub::DataWriter to batch multiple samples
 * into a single network packet to increase throughput.
 *
 * @details \dref_details_BatchQosPolicy
 */
class OMG_DDS_API Batch : public NativeValueType<Batch> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Batch)

    typedef NativeValueType<Batch> Base;

    /**
     * @brief Creates the default policy (batching is disabled)
     */
    Batch() {}

    /**
     * @brief Returns an instance that enables batching with the default
     * max_samples() and max_data_bytes().
     */
    static Batch Enabled()
    {
        return Batch().enable(true);
    }

    /**
     * @brief Returns an instance that disables batching.
     */
    static Batch Disabled()
    {
        return Batch().enable(false);
    }

    /**
     * @brief Returns an instance that enables batching with max_data_bytes()
     *
     * For example:
     * \code
     * using namespace rti::core::policy;
     *
     * writer_qos << Batch::EnabledWithMaxDataBytes(2048);
     * \endcode
     */
    static Batch EnabledWithMaxDataBytes(int32_t the_max_bytes)
    {
        return Batch().enable(true).max_data_bytes(the_max_bytes);
    }

    /**
     * @brief Returns an instance that enables batching with max_samples()
     */
    static Batch EnabledWithMaxSamples(int32_t the_max_samples)
    {
        return Batch().enable(true).max_samples(the_max_samples);
    }

    /**
     * @brief Enables or disables batching.
     */
    Batch& enable(bool the_enable);

    /**
     * @brief Returns whether batching is enabled or not
     */
    bool enable() const;

    /**
     * @brief Sets the maximum cumulative length of all serialized samples in
     * a batch.
     *
     * @details \dref_details_BatchQosPolicy_max_data_bytes
     */
    Batch& max_data_bytes(int32_t the_max_data_bytes);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_data_bytes() const;

    /**
     * @brief Sets the maximum number of samples in a batch
     *
     * @details \dref_details_BatchQosPolicy_max_samples
     */
    Batch& max_samples(int32_t the_max_samples);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_samples() const;

    /**
     * @brief Sets the maximum delay after which a batch is flushed
     * 
     * @details \dref_details_BatchQosPolicy_max_flush_delay
     */
    Batch& max_flush_delay(const dds::core::Duration& the_max_flush_delay);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_flush_delay() const;

    /**
     * @brief Sets the timestamp resolution of the samples in a batch.
     * 
     * @details \dref_details_BatchQosPolicy_source_timestamp_resolution
     */
    Batch& source_timestamp_resolution(
        const dds::core::Duration& the_source_timestamp_resolution);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration source_timestamp_resolution() const;

    /**
     * @brief Indicates if the write operation needs to be thread-safe
     * 
     * @details \dref_details_BatchQosPolicy_thread_safe_write
     */
    Batch& thread_safe_write(bool the_thread_safe_write);

    /**
     * @brief Getter (see setter with the same name)
     */
    bool thread_safe_write() const;

};


// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class SystemResourceLimits
 * @ingroup DDSSystemResourceLimitsQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures resources that \ndds uses
 *
 * @details \dref_details_SystemResourceLimitsQosPolicy
 */
class OMG_DDS_API SystemResourceLimits : 
    public NativeValueType<SystemResourceLimits> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SystemResourceLimits)

    typedef NativeValueType<SystemResourceLimits> Base;

    /**
     * @brief Creates a SystemResourceLimits qos policy with default values 
     */
    SystemResourceLimits() {}

    /**
     * @brief Creates a SystemResourceLimits qos policy with the provided 
     * max_objects_per_thread
     */
    SystemResourceLimits(int32_t the_max_objects_per_thread)
    {
        max_objects_per_thread(the_max_objects_per_thread);
    }

    /**
     * @brief Sets the maximum number of objects that can be stored per thread
     *
     * @details \dref_details_SystemResourceLimitsQosPolicy_max_objects_per_thread
     */
    SystemResourceLimits& max_objects_per_thread(
        int32_t the_max_objects_per_thread);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_objects_per_thread() const;

};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class DataWriterResourceLimits
 * @ingroup DDSDataWriterResourceLimitsQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the memory usage of a dds::pub::DataWriter
 *
 * @details \dref_details_DataWriterResourceLimitsQosPolicy
 */
class OMG_DDS_API DataWriterResourceLimits : 
    public NativeValueType<DataWriterResourceLimits> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DataWriterResourceLimits)

    typedef NativeValueType<DataWriterResourceLimits> Base;

    /**
     * @brief Creates a DataWriterResourceLimits qos policy with default values
     */
    DataWriterResourceLimits() {}

    /**
     * \dref_DataWriterResourceLimitsQosPolicy_initial_concurrent_blocking_threads
     */
    DataWriterResourceLimits& initial_concurrent_blocking_threads(
        int32_t the_initial_concurrent_blocking_threads);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_concurrent_blocking_threads() const;
    
    /** \dref_DataWriterResourceLimitsQosPolicy_max_concurrent_blocking_threads */
    DataWriterResourceLimits& max_concurrent_blocking_threads(
        int32_t the_max_concurrent_blocking_threads);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_concurrent_blocking_threads() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_max_remote_reader_filters */
    DataWriterResourceLimits& max_remote_reader_filters(
        int32_t the_max_remote_reader_filters);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_remote_reader_filters() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_initial_batches */
    DataWriterResourceLimits& initial_batches(int32_t the_initial_batches);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_batches() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_max_batches */
    DataWriterResourceLimits& max_batches(int32_t the_max_batches);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_batches() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_cookie_max_length */
    DataWriterResourceLimits& cookie_max_length(int32_t max_length);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t cookie_max_length() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_instance_replacement */
    DataWriterResourceLimits& instance_replacement(
        DataWriterResourceLimitsInstanceReplacementKind the_instance_replacement);

    /**
     * @brief Getter (see setter with the same name)
     */
    DataWriterResourceLimitsInstanceReplacementKind instance_replacement() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_replace_empty_instances */
    DataWriterResourceLimits&  replace_empty_instances(
        bool the_replace_empty_instances);

    /**
     * @brief Getter (see setter with the same name)
     */
    bool  replace_empty_instances() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_autoregister_instances */
    DataWriterResourceLimits& autoregister_instances(
        bool the_autoregister_instances);

    /**
     * @brief Getter (see setter with the same name)
     */
    bool autoregister_instances() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_initial_virtual_writers */
    DataWriterResourceLimits& initial_virtual_writers(
        int32_t the_initial_virtual_writers);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_virtual_writers() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_max_virtual_writers */
    DataWriterResourceLimits& max_virtual_writers(
        int32_t the_max_virtual_writers); 

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_virtual_writers() const; 

    /** \dref_DataWriterResourceLimitsQosPolicy_max_remote_readers */
    DataWriterResourceLimits& max_remote_readers(
        int32_t the_max_remote_readers); 

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_remote_readers() const; 

    /** \dref_DataWriterResourceLimitsQosPolicy_max_app_ack_remote_readers */
    DataWriterResourceLimits& max_app_ack_remote_readers(
        int32_t the_max_app_ack_remote_readers); 

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_app_ack_remote_readers() const; 

    /** \dref_DataWriterResourceLimitsQosPolicy_initial_active_topic_queries */
    DataWriterResourceLimits& initial_active_topic_queries(
        int32_t the_initial_active_topic_queries);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_active_topic_queries() const;

    /** \dref_DataWriterResourceLimitsQosPolicy_max_active_topic_queries */
    DataWriterResourceLimits& max_active_topic_queries(
        int32_t the_max_active_topic_queries);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_active_topic_queries() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class DataReaderResourceLimits
 * @ingroup DDSDataReaderResourceLimitsQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the memory usage of a dds::pub::DataReader
 *
 * @details \dref_details_DataReaderResourceLimitsQosPolicy
 */
class OMG_DDS_API DataReaderResourceLimits : 
    public NativeValueType<DataReaderResourceLimits> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DataReaderResourceLimits)

    typedef NativeValueType<DataReaderResourceLimits> Base;

    /**
     * @brief Creates a DataReaderResourceLimits qos policy with default values
     */
    DataReaderResourceLimits() {}

    /** \dref_DataReaderResourceLimitsQosPolicy_max_remote_writers */
    DataReaderResourceLimits& max_remote_writers(
        int32_t the_max_remote_writers);
    /** @brief Getter (see setter with the same name) */
    int32_t max_remote_writers() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_remote_writers_per_instance */
    DataReaderResourceLimits& max_remote_writers_per_instance(
        int32_t the_max_remote_writers_per_instance);
    /** @brief Getter (see setter with the same name) */
    int32_t max_remote_writers_per_instance() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_samples_per_remote_writer */
    DataReaderResourceLimits& max_samples_per_remote_writer(
        int32_t the_max_samples_per_remote_writer);
    /** @brief Getter (see setter with the same name) */
    int32_t max_samples_per_remote_writer() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_infos */
    DataReaderResourceLimits& max_infos(int32_t the_max_infos);
    /** @brief Getter (see setter with the same name) */
    int32_t max_infos() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_initial_remote_writers */
    DataReaderResourceLimits& initial_remote_writers(
        int32_t the_initial_remote_writers);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_remote_writers() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_initial_remote_writers_per_instance */
    DataReaderResourceLimits& initial_remote_writers_per_instance(
        int32_t the_initial_remote_writers_per_instance);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_remote_writers_per_instance() const;

    DataReaderResourceLimits& initial_infos(int32_t the_initial_infos);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_infos() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_initial_outstanding_reads */
    DataReaderResourceLimits& initial_outstanding_reads(
        int32_t the_initial_outstanding_reads);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_outstanding_reads() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_outstanding_reads */
    DataReaderResourceLimits& max_outstanding_reads(
        int32_t the_max_outstanding_reads);
    /** @brief Getter (see setter with the same name) */
    int32_t max_outstanding_reads() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_samples_per_read */
    DataReaderResourceLimits& max_samples_per_read(
        int32_t the_max_samples_per_read);
    /** @brief Getter (see setter with the same name) */
    int32_t max_samples_per_read() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_disable_fragmentation_support */
    DataReaderResourceLimits& disable_fragmentation_support(
        bool the_disable_fragmentation_support);
    /** @brief Getter (see setter with the same name) */
    bool disable_fragmentation_support() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_fragmented_samples */
    DataReaderResourceLimits& max_fragmented_samples(
        int32_t the_max_fragmented_samples);
    /** @brief Getter (see setter with the same name) */
    int32_t max_fragmented_samples() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_initial_fragmented_samples */
    DataReaderResourceLimits& initial_fragmented_samples(
        int32_t the_initial_fragmented_samples);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_fragmented_samples() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_fragmented_samples_per_remote_writer */
    DataReaderResourceLimits& max_fragmented_samples_per_remote_writer(
        int32_t the_max_fragmented_samples_per_remote_writer);
    /** @brief Getter (see setter with the same name) */
    int32_t max_fragmented_samples_per_remote_writer() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_fragments_per_sample */
    DataReaderResourceLimits& max_fragments_per_sample(
        int32_t the_max_fragments_per_sample);
    /** @brief Getter (see setter with the same name) */
    int32_t max_fragments_per_sample() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_dynamically_allocate_fragmented_samples */
    DataReaderResourceLimits& dynamically_allocate_fragmented_samples(
        bool the_dynamically_allocate_fragmented_samples);
    /** @brief Getter (see setter with the same name) */
    bool dynamically_allocate_fragmented_samples() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_total_instances */
    DataReaderResourceLimits& max_total_instances(
        int32_t the_max_total_instances);
    /** @brief Getter (see setter with the same name) */
    int32_t max_total_instances() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_remote_virtual_writers */
    DataReaderResourceLimits& max_remote_virtual_writers(
        int32_t the_max_remote_virtual_writers);
    /** @brief Getter (see setter with the same name) */
    int32_t max_remote_virtual_writers() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_initial_remote_virtual_writers */
    DataReaderResourceLimits& initial_remote_virtual_writers(
        int32_t the_initial_remote_virtual_writers);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_remote_virtual_writers() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_remote_virtual_writers_per_instance */
    DataReaderResourceLimits& max_remote_virtual_writers_per_instance(
        int32_t the_max_remote_virtual_writers_per_instance);
    /** @brief Getter (see setter with the same name) */
    int32_t max_remote_virtual_writers_per_instance() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_initial_remote_virtual_writers_per_instance */
    DataReaderResourceLimits& initial_remote_virtual_writers_per_instance(
        int32_t the_initial_remote_virtual_writers_per_instance);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_remote_virtual_writers_per_instance() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_remote_writers_per_sample */
    DataReaderResourceLimits& max_remote_writers_per_sample(
        int32_t the_max_remote_writers_per_sample);
    /** @brief Getter (see setter with the same name) */
    int32_t max_remote_writers_per_sample() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_query_condition_filters */
    DataReaderResourceLimits& max_query_condition_filters(
        int32_t the_max_query_condition_filters);
    /** @brief Getter (see setter with the same name) */
    int32_t max_query_condition_filters() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_app_ack_response_length */
    DataReaderResourceLimits& max_app_ack_response_length(
        int32_t the_max_app_ack_response_length);
    /** @brief Getter (see setter with the same name) */
    int32_t max_app_ack_response_length() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_keep_minimum_state_for_instances */
    DataReaderResourceLimits& keep_minimum_state_for_instances(
        bool the_keep_minimum_state_for_instances);
    /** @brief Getter (see setter with the same name) */
    bool keep_minimum_state_for_instances() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_initial_topic_queries */
    DataReaderResourceLimits& initial_topic_queries(
        int32_t the_initial_topic_queries);
    /** @brief Getter (see setter with the same name) */
    int32_t initial_topic_queries() const;

    /** \dref_DataReaderResourceLimitsQosPolicy_max_topic_queries */
    DataReaderResourceLimits& max_topic_queries(
        int32_t the_max_topic_queries);
    /** @brief Getter (see setter with the same name) */
    int32_t max_topic_queries() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class TransportSelection
 * @ingroup DDSTransportSelectionQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Specifies the transports that a dds::pub::DataWriter or a
 * dds::sub::DataReader may use to send or receive data
 *
 * @details \dref_details_TransportSelectionQosPolicy
 */
class OMG_DDS_API TransportSelection : public NativeValueType<TransportSelection> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportSelection)

private:
    typedef NativeValueType<TransportSelection> Base;

public:
    /**
     * @brief Creates the default policy
     */
    TransportSelection() { }

    /**
     * @brief Creates an instance with the sepcified transport aliases
     */
    explicit TransportSelection(
        const dds::core::StringSeq& the_enabled_transports)
    {
        enabled_transports(the_enabled_transports);
    }

    /**
     * \dref_TransportSelectionQosPolicy_enabled_transports
     */
    TransportSelection& enabled_transports(
        const dds::core::StringSeq& the_enabled_transports);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::StringSeq enabled_transports() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class DataReaderProtocol
 * @ingroup DDSDataReaderProtocolQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures DataReader-specific aspects of the RTPS protocol
 *
 * @details \dref_details_DataReaderProtocolQosPolicy
 */
class OMG_DDS_API DataReaderProtocol : public NativeValueType<DataReaderProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DataReaderProtocol)

private:
    typedef NativeValueType<DataReaderProtocol> Base;

public:
    /**
     * @brief Creates the default policy
     */
    DataReaderProtocol() { }

    /**
     * \dref_DataReaderProtocolQosPolicy_virtual_guid
     */
    DataReaderProtocol& virtual_guid(const rti::core::Guid& the_virtual_guid);
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::Guid virtual_guid() const;

    /**
     * \dref_DataReaderProtocolQosPolicy_rtps_object_id
     */
    DataReaderProtocol& rtps_object_id(uint32_t the_rtps_object_id);
    /**
     * @brief Getter (see setter with the same name)
     */
    uint32_t rtps_object_id() const;

    /**
     * \dref_DataReaderProtocolQosPolicy_expects_inline_qos
     */
    DataReaderProtocol& expects_inline_qos(bool the_expects_inline_qos);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool expects_inline_qos() const;

    /**
     * \dref_DataReaderProtocolQosPolicy_disable_positive_acks
     */
    DataReaderProtocol& disable_positive_acks(bool the_disable_positive_acks);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_positive_acks() const;

    /**
     * \dref_DataReaderProtocolQosPolicy_propagate_dispose_of_unregistered_instances
     */
    DataReaderProtocol& propagate_dispose_of_unregistered_instances(
        bool the_propagate_dispose_of_unregistered_instances);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool propagate_dispose_of_unregistered_instances() const;

    /**
     * \dref_DataReaderProtocolQosPolicy_propagate_unregister_of_disposed_instances
     */
    DataReaderProtocol& propagate_unregister_of_disposed_instances(
        bool the_propagate_unregister_of_disposed_instances);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool propagate_unregister_of_disposed_instances() const;

    /**
     * \dref_DataReaderProtocolQosPolicy_rtps_reliable_reader
     */
    DataReaderProtocol& rtps_reliable_reader(
        const rti::core::RtpsReliableReaderProtocol& the_rtps_reliable_reader);
    /**
     * @brief Gets the reliable protocol settings by const reference (see setter)
     */
    const rti::core::RtpsReliableReaderProtocol& rtps_reliable_reader() const;
    /**
     * @brief Gets the reliable protocol setting by reference (see setter)
     */
    rti::core::RtpsReliableReaderProtocol& rtps_reliable_reader();

};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class AsynchronousPublisher
 * @ingroup DDSAsynchronousPublisherQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the mechanism to publish data using a separate
 * thread
 *
 * @details \dref_details_AsynchronousPublisherQosPolicy
 */
class OMG_DDS_API AsynchronousPublisher : public NativeValueType<AsynchronousPublisher> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(AsynchronousPublisher)

private:
    typedef NativeValueType<AsynchronousPublisher> Base;

public:
    /**
     * @brief Creates the default policy
     */
    AsynchronousPublisher() { }

    /**
     * \dref_AsynchronousPublisherQosPolicy_disable_asynchronous_write
     */
    AsynchronousPublisher& disable_asynchronous_write(
        bool the_disable_asynchronous_write);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_asynchronous_write() const;

    /**
     * \dref_AsynchronousPublisherQosPolicy_thread
     */
    AsynchronousPublisher& thread(const rti::core::ThreadSettings& the_thread);
    /**
     * @brief Getter (see setter with the same name)
     */
    const rti::core::ThreadSettings& thread() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::ThreadSettings& thread();

    /**
     * \dref_AsynchronousPublisherQosPolicy_disable_asynchronous_batch
     */
    AsynchronousPublisher& disable_asynchronous_batch(
        bool the_disable_asynchronous_batch);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_asynchronous_batch() const;

    /**
     * \dref_AsynchronousPublisherQosPolicy_asynchronous_batch_thread
     */
    AsynchronousPublisher& asynchronous_batch_thread(
        const rti::core::ThreadSettings& the_asynchronous_batch_thread);
    /**
     * @brief Getter (see setter with the same name)
     */
    const rti::core::ThreadSettings& asynchronous_batch_thread() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::ThreadSettings& asynchronous_batch_thread();

    /**
     * \dref_AsynchronousPublisherQosPolicy_disable_topic_query_publication
     */
    AsynchronousPublisher& disable_topic_query_publication(
        bool the_disable_topic_query_publication);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_topic_query_publication() const;

    /**
     * \dref_AsynchronousPublisherQosPolicy_topic_query_publication_thread
     */
    AsynchronousPublisher& topic_query_publication_thread(
        const rti::core::ThreadSettings& the_topic_query_publication_thread);
    /**
     * @brief Getter (see setter with the same name)
     */
    const rti::core::ThreadSettings& topic_query_publication_thread() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::ThreadSettings& topic_query_publication_thread();

    /**
     * @brief Returns a policy that enables asynchronous write and optionally
     * asynchronous batch flushing.
     *
     * It uses the default thread settings.
     *
     * For example:
     * \code
     * using namespace rti::core::policy;
     *
     * publisher_qos << AsynchronousPublisher::Enabled()
     * \endcode
     */
    static AsynchronousPublisher Enabled(bool enable_async_batch = false)
    {
        return AsynchronousPublisher()
            .disable_asynchronous_write(false)
            .disable_asynchronous_batch(!enable_async_batch);
    }

    /**
     * @brief Creates a policy that disables asynchronous writing
     */
    static AsynchronousPublisher Disabled()
    {
        return AsynchronousPublisher();
    }
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class Event
 * @ingroup DDSEventQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the thread in a DomainParticipant that
 * handles timed events.
 *
 * @details \dref_details_EventQosPolicy
 */
class OMG_DDS_API Event : public NativeValueType<Event> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Event)

private:
    typedef NativeValueType<Event> Base;

public:
    /**
     * @brief Creates the default policy
     */
    Event() { }

    /**
     * @brief Creates an instance with all the parameters set
     */
    Event(
        const rti::core::ThreadSettings& the_thread, 
        int32_t the_initial_count, 
        int32_t the_max_count); 

    /**
     * \dref_EventQosPolicy_thread
     */
    Event& thread(
        const rti::core::ThreadSettings& the_thread);
    /**
     * @brief Getter (see setter with the same name)
     */
    const rti::core::ThreadSettings& thread() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::ThreadSettings& thread();

    /**
     * \dref_EventQosPolicy_initial_count
     */
    Event& initial_count(int32_t the_initial_count);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_count() const;
    /**
     * \dref_EventQosPolicy_max_count
     */
    Event& max_count(int32_t the_max_count);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_count() const;

};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class Availability
 * @ingroup DDSAvailabilityQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures data availability in the context of Collaborative
 * DataWriters and Required Subscriptions
 *
 * @details \dref_details_AvailabilityQosPolicy
 */
class OMG_DDS_API Availability : public NativeValueType<Availability> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Availability)

private:
    typedef NativeValueType<Event> Base;

public:
    /**
     * @brief Creates the default policy
     */
    Availability() { }

    /**
     * @brief Creates a policy with all the paramters
     */
    Availability(
        bool the_enable_required_subscriptions, 
        const dds::core::Duration& the_data_waiting_time, 
        const dds::core::Duration& the_endpoint_waiting_time, 
        const rti::core::EndpointGroupSeq& the_required_enpoint_groups); 

    /**
     * \dref_AvailabilityQosPolicy_enable_required_subscriptions
     */
    Availability& enable_required_subscriptions(
        bool the_enable_required_subscriptions);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_required_subscriptions() const;

    /**
     * \dref_AvailabilityQosPolicy_max_data_availability_waiting_time
     */
    Availability& max_data_availability_waiting_time(
        const dds::core::Duration& the_data_waiting_time);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_data_availability_waiting_time() const;

    /**
     * \dref_AvailabilityQosPolicy_max_endpoint_availability_waiting_time
     */
    Availability& max_endpoint_availability_waiting_time(
        const dds::core::Duration& the_endpoint_waiting_time);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_endpoint_availability_waiting_time() const;

    /**
     * \dref_AvailabilityQosPolicy_required_matched_endpoint_groups
     */
    Availability& required_matched_endpoint_groups(
        const rti::core::EndpointGroupSeq& the_required_enpoint_groups);
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::EndpointGroupSeq required_matched_endpoint_groups() const;

};

// ----------------------------------------------------------------------------

class RtpsReliableWriterProtocol;

} // namespace policy


class RtpsReliableWriterProtocolAdapter {
public:
    typedef struct DDS_RtpsReliableWriterProtocol_t native_type;

    static void initialize(native_type& native_value)
    {
        static const DDS_RtpsReliableWriterProtocol_t default_value = 
            DDS_RTPS_RELIABLE_WRITER_PROTOCOL_DEFAULT;
        native_value = default_value;
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_RtpsReliableWriterProtocol_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_RtpsReliableWriterProtocol_equals(
            &first, &second) == DDS_BOOLEAN_TRUE;
    }
};

template <>
struct native_type_traits<policy::RtpsReliableWriterProtocol> {
    typedef RtpsReliableWriterProtocolAdapter adapter_type;
    typedef DDS_RtpsReliableWriterProtocol_t native_type;
};

namespace policy {

/**
 * @RTI_class_definition class RtpsReliableWriterProtocol
 * @ingroup DDSExtendedQosSupportModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures aspects of an RTPS reliable writer
 *
 * @details \dref_details_RtpsReliableWriterProtocol_t
 */
class OMG_DDS_API RtpsReliableWriterProtocol : 
    public NativeValueType<RtpsReliableWriterProtocol> {

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        RtpsReliableWriterProtocol)

    typedef NativeValueType<RtpsReliableWriterProtocol> Base;

    /**
     * @brief Creates an instance with the default settings
     */
    RtpsReliableWriterProtocol() {}

    RtpsReliableWriterProtocol(
        const DDS_RtpsReliableWriterProtocol_t& native_value)
        : Base(native_value)
    {
    }

    /**
     * \dref_RtpsReliableWriterProtocol_t_low_watermark
     */
    RtpsReliableWriterProtocol& low_watermark(int32_t the_low_watermark);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t low_watermark() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_high_watermark
     */
    RtpsReliableWriterProtocol& high_watermark(int32_t the_high_watermark);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t high_watermark() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_heartbeat_period
     */
    RtpsReliableWriterProtocol& heartbeat_period(
        const dds::core::Duration& the_heartbeat_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration heartbeat_period() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_fast_heartbeat_period
     */
    RtpsReliableWriterProtocol& fast_heartbeat_period(
        const dds::core::Duration& the_fast_heartbeat_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration fast_heartbeat_period() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_late_joiner_heartbeat_period
     */
    RtpsReliableWriterProtocol& late_joiner_heartbeat_period(
        const dds::core::Duration& the_late_joiner_heartbeat_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration late_joiner_heartbeat_period() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_virtual_heartbeat_period
     */
    RtpsReliableWriterProtocol& virtual_heartbeat_period(
        const dds::core::Duration& the_virtual_heartbeat_period);
    dds::core::Duration virtual_heartbeat_period();

    /**
     * \dref_RtpsReliableWriterProtocol_t_samples_per_virtual_heartbeat
     */
    RtpsReliableWriterProtocol& samples_per_virtual_heartbeat(
        int32_t the_samples_per_virtual_heartbeat);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t samples_per_virtual_heartbeat() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_max_heartbeat_retries
     */
    RtpsReliableWriterProtocol& max_heartbeat_retries(
        int32_t the_max_heartbeat_retries);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_heartbeat_retries() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_inactivate_nonprogressing_readers
     */
    RtpsReliableWriterProtocol& inactivate_nonprogressing_readers(
        bool the_inactivate_nonprogressing_readers);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool inactivate_nonprogressing_readers() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_heartbeats_per_max_samples
     */
    RtpsReliableWriterProtocol& heartbeats_per_max_samples(
        int32_t the_heartbeats_per_max_samples);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t heartbeats_per_max_samples() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_min_nack_response_delay
     */
    RtpsReliableWriterProtocol& min_nack_response_delay(
        const dds::core::Duration& the_min_nack_response_delay);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration min_nack_response_delay() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_max_nack_response_delay
     */
    RtpsReliableWriterProtocol& max_nack_response_delay(
        const dds::core::Duration& the_max_nack_response_delay);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_nack_response_delay() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_nack_suppression_duration
     */
    RtpsReliableWriterProtocol& nack_suppression_duration(
        const dds::core::Duration& the_nack_suppression_duration);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration nack_suppression_duration() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_max_bytes_per_nack_response
     */
    RtpsReliableWriterProtocol& max_bytes_per_nack_response(
        int32_t the_max_bytes_per_nack_response); 
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_bytes_per_nack_response() const; 

    /**
     * \dref_RtpsReliableWriterProtocol_t_disable_positive_acks_min_sample_keep_duration
     */
    RtpsReliableWriterProtocol& disable_positive_acks_min_sample_keep_duration(
        const dds::core::Duration& duration);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration disable_positive_acks_min_sample_keep_duration() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_disable_positive_acks_max_sample_keep_duration
     */
    RtpsReliableWriterProtocol& disable_positive_acks_max_sample_keep_duration(
        const dds::core::Duration& duration);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration disable_positive_acks_max_sample_keep_duration() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_disable_positive_acks_enable_adaptive_sample_keep_duration
     */
    RtpsReliableWriterProtocol& disable_positive_acks_enable_adaptive_sample_keep_duration(
        bool disable);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_positive_acks_enable_adaptive_sample_keep_duration() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_disable_positive_acks_decrease_sample_keep_duration_factor
     */
    RtpsReliableWriterProtocol& disable_positive_acks_decrease_sample_keep_duration_factor(
        int32_t factor);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t disable_positive_acks_decrease_sample_keep_duration_factor() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_disable_positive_acks_increase_sample_keep_duration_factor
     */
    RtpsReliableWriterProtocol& disable_positive_acks_increase_sample_keep_duration_factor(
        int32_t factor);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t disable_positive_acks_increase_sample_keep_duration_factor() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_min_send_window_size
     */
    RtpsReliableWriterProtocol& min_send_window_size(
        int32_t the_min_send_window_size);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t min_send_window_size() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_max_send_window_size
     */
    RtpsReliableWriterProtocol& max_send_window_size(
        int32_t the_max_send_window_size);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_send_window_size() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_send_window_update_period
     */
    RtpsReliableWriterProtocol& send_window_update_period(
        const dds::core::Duration& the_send_window_update_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration send_window_update_period() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_send_window_increase_factor
     */
    RtpsReliableWriterProtocol& send_window_increase_factor(
        int32_t the_send_window_increase_factor);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t send_window_increase_factor() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_send_window_decrease_factor
     */
    RtpsReliableWriterProtocol& send_window_decrease_factor(
        int32_t the_send_window_decrease_factor);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t send_window_decrease_factor() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_enable_multicast_periodic_heartbeat
     */
    RtpsReliableWriterProtocol& enable_multicast_periodic_heartbeat(
        bool the_enable_multicast_periodic_heartbeat);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_multicast_periodic_heartbeat() const;

    /**
     * \dref_RtpsReliableWriterProtocol_t_multicast_resend_threshold
     */
    RtpsReliableWriterProtocol& multicast_resend_threshold(
        int32_t the_multicast_resend_threshold); 
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t multicast_resend_threshold() const; 
};

/**
 * @RTI_class_definition class DataWriterProtocol
 * @ingroup DDSDataWriterProtocolQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures aspects of an the RTPS protocol related to
 * a dds::pub::DataWriter
 *
 * @details \dref_details_DataWriterProtocolQosPolicy
 */
class OMG_DDS_API DataWriterProtocol : public NativeValueType<DataWriterProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DataWriterProtocol)

private:
    typedef NativeValueType<DataWriterProtocol> Base;

public:
    /**
     * @brief Creates the default policy
     */
    DataWriterProtocol() { }

    /**
     * \dref_DataWriterProtocolQosPolicy_virtual_guid
     */
    DataWriterProtocol& virtual_guid(const rti::core::Guid& the_virtual_guid);
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::Guid virtual_guid() const;

    /**
     * \dref_DataWriterProtocolQosPolicy_rtps_object_id
     */
    DataWriterProtocol& rtps_object_id(uint32_t the_rtps_object_id);
    /**
     * @brief Getter (see setter with the same name)
     */
    uint32_t rtps_object_id() const;

    /**
     * \dref_DataWriterProtocolQosPolicy_push_on_write
     */
    DataWriterProtocol& push_on_write(bool the_push_on_write);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool push_on_write() const;

    /**
     * \dref_DataWriterProtocolQosPolicy_disable_positive_acks
     */
    DataWriterProtocol& disable_positive_acks(bool the_disable_positive_acks);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_positive_acks() const;

    /**
     * \dref_DataWriterProtocolQosPolicy_disable_inline_keyhash
     */
    DataWriterProtocol& disable_inline_keyhash(bool the_disable_inline_keyhash);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_inline_keyhash() const;

    /**
     * \dref_DataWriterProtocolQosPolicy_serialize_key_with_dispose
     */
    DataWriterProtocol& serialize_key_with_dispose(
        bool the_serialize_key_with_dispose);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool serialize_key_with_dispose() const;

    /**
     * \dref_DataWriterProtocolQosPolicy_propagate_app_ack_with_no_response
     */
    DataWriterProtocol& propagate_app_ack_with_no_response(
        bool the_propagate_app_ack_with_no_response);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool propagate_app_ack_with_no_response() const;

    /**
     * \dref_DataWriterProtocolQosPolicy_rtps_reliable_writer
     */
    DataWriterProtocol& rtps_reliable_writer(
        const RtpsReliableWriterProtocol& the_rtps_reliable_writer);
    /**
     * @brief Gets the reliable settings by const-reference (see setter)
     */
    const RtpsReliableWriterProtocol& rtps_reliable_writer() const;
    /**
     * @brief Gets the reliable settings by reference (see setter)
     */
    RtpsReliableWriterProtocol& rtps_reliable_writer();
};


// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class ExclusiveArea
 * @ingroup DDSExclusiveAreaQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures multi-threading and deadlock prevention
 *
 * @details \dref_details_ExclusiveAreaQosPolicy
 */
class OMG_DDS_API ExclusiveArea : public NativeValueType<ExclusiveArea> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ExclusiveArea)

private:
    typedef NativeValueType<ExclusiveArea> Base;

public:
    /**
     * @brief Creates the default policy
     */
    ExclusiveArea() { }

    /**
     * @brief Creates an instance specifying the use of shared or exclusive area
     *
     * See use_shared_exclusive_area().
     */
    explicit ExclusiveArea(bool the_use_shared_exclusive_area)
    {
        use_shared_exclusive_area(the_use_shared_exclusive_area);
    }

    /**
     * @brief Returns ExclusiveArea(true)
     */
    static ExclusiveArea SharedEA()
    {
        return ExclusiveArea(true);
    }

    /**
     * @brief Returns ExclusiveArea(false)
     */
    static ExclusiveArea ExclusiveEA() 
    {
       return ExclusiveArea();
    }

    /**
     * @brief Whether the dds::core::Entity is protected by its own exclusive
     * area or the shared one
     *
     * @details \dref_details_ExclusiveAreaQosPolicy_use_shared_exclusive_area
     */
    ExclusiveArea& use_shared_exclusive_area(
        bool the_use_shared_exclusive_area);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool use_shared_exclusive_area() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class ReceiverPool
 * @ingroup DDSReceiverPoolQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures threads that \ndds uses to receive and process
 * data from the transport modules (such as UDP)
 *
 * @details \dref_details_ReceiverPoolQosPolicy
 */
class OMG_DDS_API ReceiverPool : public NativeValueType<ReceiverPool> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ReceiverPool)

private:
    typedef NativeValueType<ReceiverPool> Base;

public:
    /**
     * @brief Indicates that the length will be automatically resolved
     */
    static OMG_DDS_API_CLASS_VARIABLE const int32_t LENGTH_AUTO;

    /**
     * @brief Creates the default policy
     */
    ReceiverPool() { }

    /**
     * @brief Creates an instance with the thread settings, buffer size and
     * buffer alignment configuration
     *
     * See individual setters.
     */
    ReceiverPool(
        const rti::core::ThreadSettings& the_thread, 
        int32_t the_buffer_size, 
        int32_t the_buffer_alignment);

    /**
     * @brief Configures the receiver pool thread(s)
     *
     * @details \dref_details_ReceiverPoolQosPolicy_thread
     */
    ReceiverPool& thread(const rti::core::ThreadSettings& the_thread);
    /**
     * @brief Getter (see setter with the same name)
     */
    const rti::core::ThreadSettings& thread() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::ThreadSettings& thread();

    /**
     * @brief Sets the length of the buffer used to store the incoming raw data
     *
     * @details \dref_details_ReceiverPoolQosPolicy_buffer_size
     */
    ReceiverPool& buffer_size(int32_t the_buffer_size);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t buffer_size() const;

    /**
     * @brief Sets the receive buffer alignment
     *
     * @details \dref_details_ReceiverPoolQosPolicy_buffer_size
     */
    ReceiverPool& buffer_alignment(int32_t the_buffer_alignment);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t buffer_alignment() const;
};

// ----------------------------------------------------------------------------

class BuiltinTopicReaderResourceLimits;

} // namespace policy

template <>
struct native_type_traits<rti::core::policy::BuiltinTopicReaderResourceLimits> {
    typedef PODNativeAdapter<DDS_BuiltinTopicReaderResourceLimits_t> adapter_type;
    typedef DDS_BuiltinTopicReaderResourceLimits_t native_type;
};

namespace policy {

/**
 * @RTI_class_definition class BuiltinTopicReaderResourceLimits
 * @ingroup DDSDiscoveryConfigQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures several resource management aspects of
 * the built-in topic DataReaders
 *
 * @details \dref_details_BuiltinTopicReaderResourceLimits_t
 *
 */
class OMG_DDS_API BuiltinTopicReaderResourceLimits : 
    public NativeValueType<BuiltinTopicReaderResourceLimits> {

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        BuiltinTopicReaderResourceLimits)

    typedef NativeValueType<BuiltinTopicReaderResourceLimits> Base;

    /**
     * @brief Creates an instance with the default settings
     */
    BuiltinTopicReaderResourceLimits() {}

    BuiltinTopicReaderResourceLimits(
        const DDS_BuiltinTopicReaderResourceLimits_t& native_value)
        : Base(native_value)
    {
    }

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_initial_samples
     */
    BuiltinTopicReaderResourceLimits& initial_samples(
        int32_t the_initial_samples);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_samples() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_max_samples
     */
    BuiltinTopicReaderResourceLimits& max_samples(int32_t the_max_samples);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_samples() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_initial_infos
     */
    BuiltinTopicReaderResourceLimits& initial_infos(int32_t the_initial_infos);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_infos() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_max_infos
     */
    BuiltinTopicReaderResourceLimits& max_infos(int32_t the_max_infos);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_infos() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_initial_outstanding_reads
     */
    BuiltinTopicReaderResourceLimits& initial_outstanding_reads(
        int32_t the_initial_outstanding_reads);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_outstanding_reads() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_max_outstanding_reads
     */
    BuiltinTopicReaderResourceLimits& max_outstanding_reads(
        int32_t the_max_outstanding_reads);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_outstanding_reads() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_max_samples_per_read
     */
    BuiltinTopicReaderResourceLimits& max_samples_per_read(
        int32_t the_max_samples_per_read);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_samples_per_read() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_disable_fragmentation_support
     */
    BuiltinTopicReaderResourceLimits& disable_fragmentation_support(
        bool the_disable_fragmentation_support);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool disable_fragmentation_support() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_max_fragmented_samples
     */
    BuiltinTopicReaderResourceLimits& max_fragmented_samples(
        int32_t the_max_fragmented_samples);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_fragmented_samples() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_initial_fragmented_samples
     */
    BuiltinTopicReaderResourceLimits& initial_fragmented_samples(
        int32_t the_initial_fragmented_samples);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_fragmented_samples() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_max_fragmented_samples_per_remote_writer
     */
    BuiltinTopicReaderResourceLimits& max_fragmented_samples_per_remote_writer(
        int32_t the_max_fragmented_samples_per_remote_writer);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_fragmented_samples_per_remote_writer() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_max_fragments_per_sample
     */
    BuiltinTopicReaderResourceLimits& max_fragments_per_sample(
        int32_t the_max_fragments_per_sample);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t max_fragments_per_sample() const;

    /**
     * \dref_BuiltinTopicReaderResourceLimits_t_dynamically_allocate_fragmented_samples
     */
    BuiltinTopicReaderResourceLimits& dynamically_allocate_fragmented_samples(
        bool the_dynamically_allocate_fragmented_samples);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool dynamically_allocate_fragmented_samples() const;
};

} } } // namespace rti::core::policy

namespace dds { namespace core { namespace policy {

typedef detail::WriterDataLifecycle WriterDataLifecycle;

} } } // namespace dds::core::policy

namespace rti { namespace core { namespace policy {

/**
 * @RTI_class_definition class DiscoveryConfig
 * @ingroup DDSDiscoveryConfigQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the discovery mechanism
 *
 * @details \dref_details_DiscoveryConfigQosPolicy
 */
class OMG_DDS_API DiscoveryConfig : public NativeValueType<DiscoveryConfig> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DiscoveryConfig)

private:
    typedef NativeValueType<DiscoveryConfig> Base;

public:
    /**
     * @brief Creates the default policy
     */
    DiscoveryConfig() { }

    /**
     * \dref_DiscoveryConfigQosPolicy_participant_liveliness_lease_duration
     */
    DiscoveryConfig& participant_liveliness_lease_duration(
        const dds::core::Duration& the_participant_liveliness_lease_duration);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration participant_liveliness_lease_duration() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_participant_liveliness_assert_period
     */
    DiscoveryConfig& participant_liveliness_assert_period(
        const dds::core::Duration& the_participant_liveliness_assert_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration participant_liveliness_assert_period() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_remote_participant_purge_kind
     */
    DiscoveryConfig& remote_participant_purge_kind(
        RemoteParticipantPurgeKind the_remote_participant_purge_kind);
    /**
     * @brief Getter (see setter with the same name)
     */
    RemoteParticipantPurgeKind remote_participant_purge_kind() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_max_liveliness_loss_detection_period
     */
    DiscoveryConfig& max_liveliness_loss_detection_period(
        const dds::core::Duration& the_max_liveliness_loss_detection_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_liveliness_loss_detection_period() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_initial_participant_announcements
     */
    DiscoveryConfig& initial_participant_announcements(
        int32_t the_initial_participant_announcements);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t initial_participant_announcements() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_min_initial_participant_announcement_period
     */
    DiscoveryConfig& min_initial_participant_announcement_period(
        const dds::core::Duration& the_min_initial_participant_announcement_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration min_initial_participant_announcement_period() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_max_initial_participant_announcement_period
     */
    DiscoveryConfig& max_initial_participant_announcement_period(
        const dds::core::Duration& the_max_initial_participant_announcement_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_initial_participant_announcement_period() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_participant_reader_resource_limits
     */
    DiscoveryConfig& participant_reader_resource_limits(
        const BuiltinTopicReaderResourceLimits& the_participant_reader_resource_limits);
    /**
     * @brief Getter (see setter with the same name)
     */
    const BuiltinTopicReaderResourceLimits& participant_reader_resource_limits() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    BuiltinTopicReaderResourceLimits& participant_reader_resource_limits();

    /**
     * \dref_DiscoveryConfigQosPolicy_publication_reader
     */
    DiscoveryConfig& publication_reader(
        const RtpsReliableReaderProtocol& the_publication_reader);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableReaderProtocol& publication_reader() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableReaderProtocol& publication_reader();

    /**
     * \dref_DiscoveryConfigQosPolicy_publication_reader_resource_limits
     */
    DiscoveryConfig& publication_reader_resource_limits(
        const BuiltinTopicReaderResourceLimits& the_publication_reader_resource_limits);
    /**
     * @brief Getter (see setter with the same name)
     */
    const BuiltinTopicReaderResourceLimits& publication_reader_resource_limits() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    BuiltinTopicReaderResourceLimits& publication_reader_resource_limits();

    /**
     * \dref_DiscoveryConfigQosPolicy_subscription_reader
     */
    DiscoveryConfig& subscription_reader(
        const RtpsReliableReaderProtocol& the_subscription_reader);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableReaderProtocol& subscription_reader() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableReaderProtocol& subscription_reader();

    /**
     * \dref_DiscoveryConfigQosPolicy_subscription_reader_resource_limits
     */
    DiscoveryConfig& subscription_reader_resource_limits(
        const BuiltinTopicReaderResourceLimits& the_subscription_reader_resource_limits);
    /**
     * @brief Getter (see setter with the same name)
     */
    const BuiltinTopicReaderResourceLimits& subscription_reader_resource_limits() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    BuiltinTopicReaderResourceLimits& subscription_reader_resource_limits();

    /**
     * \dref_DiscoveryConfigQosPolicy_publication_writer
     */
    DiscoveryConfig& publication_writer(
        const RtpsReliableWriterProtocol& the_publication_writer);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableWriterProtocol& publication_writer() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableWriterProtocol& publication_writer();

    /**
     * \dref_DiscoveryConfigQosPolicy_publication_writer_data_lifecycle
     */
    DiscoveryConfig& publication_writer_data_lifecycle(
        const dds::core::policy::WriterDataLifecycle& the_publication_writer_data_lifecycle);
    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::policy::WriterDataLifecycle& publication_writer_data_lifecycle() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::WriterDataLifecycle& publication_writer_data_lifecycle();

    /**
     * \dref_DiscoveryConfigQosPolicy_subscription_writer
     */
    DiscoveryConfig& subscription_writer(
        const RtpsReliableWriterProtocol& the_subscription_writer);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableWriterProtocol& subscription_writer() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableWriterProtocol& subscription_writer();

    /**
     * \dref_DiscoveryConfigQosPolicy_subscription_writer_data_lifecycle
     */
    DiscoveryConfig& subscription_writer_data_lifecycle(
        const dds::core::policy::WriterDataLifecycle& the_subscription_writer_data_lifecycle);
    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::policy::WriterDataLifecycle& subscription_writer_data_lifecycle() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::WriterDataLifecycle& subscription_writer_data_lifecycle();

    /**
     * \dref_DiscoveryConfigQosPolicy_builtin_discovery_plugins
     */
    DiscoveryConfig& builtin_discovery_plugins(
        const DiscoveryConfigBuiltinPluginKindMask& the_builtin_discovery_plugins);
    /**
     * @brief Getter (see setter with the same name)
     */
    DiscoveryConfigBuiltinPluginKindMask builtin_discovery_plugins() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_participant_message_reader_reliability_kind
     */
    DiscoveryConfig& participant_message_reader_reliability_kind(
         dds::core::policy::ReliabilityKind the_participant_message_reader_reliability_kind);
    dds::core::policy::ReliabilityKind
    /**
     * @brief Getter (see setter with the same name)
     */
    participant_message_reader_reliability_kind() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_participant_message_reader
     */
    DiscoveryConfig& participant_message_reader(
        const RtpsReliableReaderProtocol& the_participant_message_reader);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableReaderProtocol& participant_message_reader() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableReaderProtocol& participant_message_reader();

    /**
     * \dref_DiscoveryConfigQosPolicy_participant_message_writer
     */
    DiscoveryConfig& participant_message_writer(
        const RtpsReliableWriterProtocol& the_participant_message_writer);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableWriterProtocol& participant_message_writer() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableWriterProtocol& participant_message_writer();

    /**
     * \dref_DiscoveryConfigQosPolicy_publication_writer_publish_mode
     */
    DiscoveryConfig& publication_writer_publish_mode(
        const PublishMode& the_publication_writer_publish_mode);
    /**
     * @brief Getter (see setter with the same name)
     */
    const PublishMode& publication_writer_publish_mode() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    PublishMode& publication_writer_publish_mode();

    /**
     * \dref_DiscoveryConfigQosPolicy_subscription_writer_publish_mode
     */
    DiscoveryConfig& subscription_writer_publish_mode(
        const PublishMode& the_subscription_writer_publish_mode);
    /**
     * @brief Getter (see setter with the same name)
     */
    const PublishMode& subscription_writer_publish_mode() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    PublishMode& subscription_writer_publish_mode();

    /**
     * \dref_DiscoveryConfigQosPolicy_asynchronous_publisher
     */
    DiscoveryConfig& asynchronous_publisher(
        const AsynchronousPublisher& the_asynchronous_publisher);
    /**
     * @brief Getter (see setter with the same name)
     */
    const AsynchronousPublisher& asynchronous_publisher() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    AsynchronousPublisher& asynchronous_publisher();

    /**
     * \dref_DiscoveryConfigQosPolicy_default_domain_announcement_period
     */
    DiscoveryConfig& default_domain_announcement_period(
        const dds::core::Duration& the_default_domain_announcement_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration default_domain_announcement_period() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_ignore_default_domain_announcements
     */
    DiscoveryConfig& ignore_default_domain_announcements(
        bool the_ignore_default_domain_announcements);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool ignore_default_domain_announcements() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_service_request_writer
     */
    DiscoveryConfig& service_request_writer(
        const RtpsReliableWriterProtocol& the_service_request_writer);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableWriterProtocol& service_request_writer() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableWriterProtocol& service_request_writer();

    /**
     * \dref_DiscoveryConfigQosPolicy_service_request_writer_data_lifecycle
     */
    DiscoveryConfig& service_request_writer_data_lifecycle(
        const dds::core::policy::WriterDataLifecycle& lifecycle);
    /**
     * @brief Getter (see setter with the same name)
     */
    const dds::core::policy::WriterDataLifecycle& 
        service_request_writer_data_lifecycle() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::policy::WriterDataLifecycle& 
        service_request_writer_data_lifecycle();

    /**
     * \dref_DiscoveryConfigQosPolicy_service_request_writer_publish_mode
     */
    DiscoveryConfig& service_request_writer_publish_mode(
        const PublishMode& the_service_request_writer_publish_mode);
    /**
     * @brief Getter (see setter with the same name)
     */
    const PublishMode& service_request_writer_publish_mode() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    PublishMode& service_request_writer_publish_mode();

    /**
     * \dref_DiscoveryConfigQosPolicy_publication_reader
     */
    DiscoveryConfig& service_request_reader(
        const RtpsReliableReaderProtocol& the_service_request_reader);
    /**
     * @brief Getter (see setter with the same name)
     */
    const RtpsReliableReaderProtocol& service_request_reader() const;
    /**
     * @brief Getter (see setter with the same name)
     */
    RtpsReliableReaderProtocol& service_request_reader();

    /**
     * \dref_DiscoveryConfigQosPolicy_locator_reachability_assert_period
     */
    DiscoveryConfig& locator_reachability_assert_period(
        const dds::core::Duration& the_locator_reachability_assert_period);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration locator_reachability_assert_period() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_locator_reachability_lease_duration
     */
    DiscoveryConfig& locator_reachability_lease_duration(
            const dds::core::Duration& the_locator_reachability_lease_duration);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration locator_reachability_lease_duration() const;

    /**
     * \dref_DiscoveryConfigQosPolicy_locator_reachability_change_detection_period
     */
    DiscoveryConfig& locator_reachability_change_detection_period(
            const dds::core::Duration& the_locator_reachability_change_detection_period);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration locator_reachability_change_detection_period() const;

};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class TypeSupport
 * @ingroup DDSTypeSupportQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Allows attaching application-specific information to
 * a dds::pub::DataWriter or dds::sub::DataReader that is passed to the
 * serilization and deserialization routines.
 *
 * @details \dref_details_TypeSupportQosPolicy
 */
class OMG_DDS_API TypeSupport : public NativeValueType<TypeSupport> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TypeSupport)

private:
    typedef NativeValueType<TypeSupport> Base;

public:
    /**
     * @brief Creates the default policy
     */
    TypeSupport() { }

    /**
     * \dref_TypeSupportQosPolicy_plugin_data
     */
    TypeSupport& plugin_data(void* the_plugin_data);
    /**
     * @brief Getter (see setter with the same name)
     */
    void* plugin_data();

    /**
     * \dref_TypeSupportQosPolicy_cdr_padding_kind
     */
    TypeSupport& cdr_padding_kind(CdrPaddingKind the_cdr_padding_kind);
    /**
     * @brief Getter (see setter with the same name)
     */
    CdrPaddingKind cdr_padding_kind() const;
};

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class TransportMulticast
 * @ingroup DDSTransportMulticastQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Specifies the multicast address on which a
 * dds::sub::DataReader wants to receive its data and other settings.
 *
 * @details \dref_details_TransportMulticastQosPolicy
 */
class OMG_DDS_API TransportMulticast : public NativeValueType<TransportMulticast> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportMulticast)

private:
    typedef NativeValueType<TransportMulticast> Base;

public:

    /**
     * @brief Creates the default policy
     */
    TransportMulticast() { }

    /**
     * @brief Creates an instance with the speicfied multicast settings
     *
     * See individual setters.
     */
    TransportMulticast(
        const TransportMulticastSettingsSeq& the_value, 
        TransportMulticastKind the_kind);

    /**
     * \dref_TransportMulticastQosPolicy_value
     */
    TransportMulticast& settings(
        const TransportMulticastSettingsSeq& the_settings);
    /**
     * @brief Getter (see setter with the same name)
     */
    TransportMulticastSettingsSeq settings() const;

    /**
     * \dref_TransportMulticastQosPolicy_kind
     */
    TransportMulticast& kind(TransportMulticastKind the_kind);
    /**
     * @brief Getter (see setter with the same name)
     */
    TransportMulticastKind kind() const;
};

// ----------------------------------------------------------------------------
class TransportMulticastMappingFunction;
class MulticastMapping;

} // namespace policy


class TransportMulticastMappingFunctionAdapter {
public:
    typedef struct DDS_TransportMulticastMappingFunction_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_TransportMulticastMappingFunction_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_TransportMulticastMappingFunction_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        if (DDS_TransportMulticastMappingFunction_t_copy(&destination, &source) == 
            NULL) {
            throw std::bad_alloc();
        }
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_TransportMulticastMappingFunction_t_is_equal(
            &first, &second) == RTI_TRUE;
    }
};

template <>
struct native_type_traits<policy::TransportMulticastMappingFunction> {
    typedef TransportMulticastMappingFunctionAdapter adapter_type;
    typedef DDS_TransportMulticastMappingFunction_t native_type;
};

class MulticastMappingAdapter {
public:
    typedef struct DDS_TransportMulticastMapping_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_TransportMulticastMapping_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_TransportMulticastMapping_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        if (DDS_TransportMulticastMapping_t_copy(&destination, &source) == 
            NULL) {
            throw std::bad_alloc();
        }
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_TransportMulticastMapping_t_is_equal(
            &first, &second) == RTI_TRUE;
    }
};

template <>
struct native_type_traits<policy::MulticastMapping> {
    typedef MulticastMappingAdapter adapter_type;
    typedef DDS_TransportMulticastMapping_t native_type;
};

namespace policy {

// -------- TransportMulticastMappingFunction --------

class OMG_DDS_API TransportMulticastMappingFunction : 
    public NativeValueType<TransportMulticastMappingFunction> {

    typedef NativeValueType<TransportMulticastMappingFunction> Base;
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportMulticastMappingFunction)
public:
    TransportMulticastMappingFunction(
        const std::string& the_dll, 
        const std::string& the_function_name);

    TransportMulticastMappingFunction(
        const DDS_TransportMulticastMappingFunction_t& native_value)
      : Base(native_value)
    {
    }

public:
    TransportMulticastMappingFunction& dll(const std::string& the_dll);
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::optional_value<std::string> dll() const;

    TransportMulticastMappingFunction& function_name(
        const std::string& the_function_name);
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::optional_value<std::string> function_name() const;
};

// -------- MulticastMapping --------

class OMG_DDS_API MulticastMapping : public NativeValueType<MulticastMapping> {

    typedef NativeValueType<MulticastMapping> Base;
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(MulticastMapping)
public:

    MulticastMapping() {}

    MulticastMapping(
        const std::string& the_addresses, 
        const std::string& the_topic_expression, 
        const TransportMulticastMappingFunction& the_mapping_function);

    MulticastMapping(const DDS_TransportMulticastMapping_t& the_mapping)
      : Base(the_mapping)
    {
    }

public:
    MulticastMapping& addresses(const std::string& the_addresses);
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::optional_value<std::string> addresses() const;

    MulticastMapping& topic_expression(const std::string& the_topic_expression);
    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::optional_value<std::string> topic_expression() const;

    MulticastMapping& mapping_function(
        const TransportMulticastMappingFunction& the_mappings);
    /**
     * @brief Getter (see setter with the same name)
     */
    const TransportMulticastMappingFunction& mapping_function() const;
    TransportMulticastMappingFunction& mapping_function();
};

typedef std::vector<MulticastMapping> MulticastMappingSeq;

/**
 * @RTI_class_definition class TransportMulticastMapping
 *
 * \dref_TransportMulticastMappingQosPolicy
 */
class OMG_DDS_API TransportMulticastMapping : 
    public NativeValueType<TransportMulticastMapping> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportMulticastMapping)
    typedef NativeValueType<TransportMulticastMapping> Base;

    TransportMulticastMapping() { }
    TransportMulticastMapping(const MulticastMappingSeq& the_mappings);

    TransportMulticastMapping& mappings(
        const MulticastMappingSeq& the_mappings);
    /**
     * @brief Getter (see setter with the same name)
     */
    MulticastMappingSeq mappings() const;
};


// This Qos policy is not exposed in the API. This class is just a wrapper
// to provide constructor, destructor etc.
class OMG_DDS_API TransportEncapsulation :
    public NativeValueType<TransportEncapsulation> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportEncapsulation)
    TransportEncapsulation() {}
};

// This Qos policy is not exposed in the API. This class is just a wrapper
// to provide constructor, destructor etc.
class OMG_DDS_API Profile : public NativeValueType<Profile> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Profile)
    Profile() {}
};

// This Qos policy is not exposed in the API. This class is just a wrapper
// to provide constructor, destructor etc.
class OMG_DDS_API Logging : public NativeValueType<Logging> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Logging)
    Logging() {}
};

/*i
 * @RTI_class_definition class DomainParticipantProtocol
 *
 * \dref_DomainParticipantProtocolQosPolicy
 */
class OMG_DDS_API DomainParticipantProtocol
    : public NativeValueType<DomainParticipantProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(DomainParticipantProtocol)
    typedef NativeValueType<DomainParticipantProtocol> Base;

    DomainParticipantProtocol() {}

    /**
     * @brief Getter (see setter with the same name)
     */
    bool vendor_specific_entity() const;
    DomainParticipantProtocol& vendor_specific_entity(bool value);
};

/*i
 * @RTI_class_definition class TopicProtocol
 *
 * \dref_TopicProtocolQosPolicy
 */
class OMG_DDS_API TopicProtocol : public NativeValueType<TopicProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TopicProtocol)
    typedef NativeValueType<TopicProtocol> Base;

    TopicProtocol() {}

    /**
     * @brief Getter (see setter with the same name)
     */
    bool vendor_specific_entity() const;
    TopicProtocol& vendor_specific_entity(bool value);
};

/*i
 * @RTI_class_definition class TopicProtocol
 *
 * \dref_SubscriberProtocolQosPolicy
 */
class OMG_DDS_API SubscriberProtocol
    : public NativeValueType<SubscriberProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SubscriberProtocol)
    typedef NativeValueType<SubscriberProtocol> Base;

    SubscriberProtocol() {}

    /**
     * @brief Getter (see setter with the same name)
     */
    bool vendor_specific_entity() const;
    SubscriberProtocol& vendor_specific_entity(bool value);
};

/*i
 * @RTI_class_definition class PublisherProtocol
 *
 * \dref_PublisherProtocolQosPolicy
 */
class OMG_DDS_API PublisherProtocol : public NativeValueType<PublisherProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(PublisherProtocol)
    typedef NativeValueType<PublisherProtocol> Base;

    PublisherProtocol() {}

    /**
     * @brief Getter (see setter with the same name)
     */
    bool vendor_specific_entity() const;
    PublisherProtocol& vendor_specific_entity(bool value);
};

/**
 * @RTI_class_definition class TopicQueryDispatch
 * @ingroup DDSTopicQueryDispatchQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the ability of a \idref_DataWriter to publish
 * samples in response to a \idref_TopicQuery
 *
 * @details \dref_details_TopicQueryDispatchQosPolicy
 */
class OMG_DDS_API TopicQueryDispatch : public NativeValueType<TopicQueryDispatch> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TopicQueryDispatch)

private:
    typedef NativeValueType<TopicQueryDispatch> Base;

public:
    /**
     * @brief Creates the default policy
     */
    TopicQueryDispatch() {}

    /**
     * @brief Creates a policy with the provided values for 
     * enable, publication_period and samples_per_period 
     */
    TopicQueryDispatch(
        bool the_enable, 
        const dds::core::Duration& the_publication_period, 
        int32_t the_samples_per_period)
    {
        enable(the_enable);
        publication_period(the_publication_period);
        samples_per_period(the_samples_per_period);
    }

    /**
     * \dref_TopicQueryDispatchQosPolicy_enable
     */
    TopicQueryDispatch& enable(bool the_enable);
    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable() const;

    /**
     * \dref_TopicQueryDispatchQosPolicy_publication_period
     */
    TopicQueryDispatch& publication_period(
        const dds::core::Duration& the_publication_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration publication_period() const;

    /**
     * \dref_TopicQueryDispatchQosPolicy_samples_per_period
     */
    TopicQueryDispatch& samples_per_period(int32_t the_samples_per_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t samples_per_period() const;

    static TopicQueryDispatch Enabled()
    {
        return TopicQueryDispatch().enable(true);
    }

    static TopicQueryDispatch Disabled()
    {
        return TopicQueryDispatch().enable(false);
    }
};

} } } // namespace rti::core::policy

#endif // RTI_DDS_CORE_POLICY_HPP_
