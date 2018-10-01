/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,13feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_STATUS_STATUS_HPP_
#define RTI_DDS_CORE_STATUS_STATUS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/InstanceHandle.hpp>
#include <dds/core/status/State.hpp>
#include <dds/core/Time.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/status/StatusAdapter.hpp>
#include <rti/core/SequenceNumber.hpp>
#include <rti/core/ServiceRequestId.hpp>

namespace rti { namespace core { namespace status {

class OMG_DDS_API InconsistentTopicStatus :
    public rti::core::NativeValueType<InconsistentTopicStatus> {

private:
    typedef rti::core::NativeValueType<InconsistentTopicStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        InconsistentTopicStatus)

    InconsistentTopicStatus() { }
    
    InconsistentTopicStatus(const DDS_InconsistentTopicStatus& src)
        : Base(src)
    {
    }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }
};

/**
 * @ingroup DDSReaderModule
 * @brief @extension Reasons why a sample was lost
 *
 * @see dds::core::status::SampleLostStatus::last_reason()
 */
class OMG_DDS_API SampleLostState : public std::bitset<OMG_DDS_STATE_BIT_COUNT > {
public:
    typedef std::bitset<OMG_DDS_STATE_BIT_COUNT > MaskType;

    /**
     * @brief Creates not_lost()
     */
    SampleLostState()
    {
    }

    /**
     * @brief Create from a bitset
     */
    SampleLostState(const MaskType& src) : MaskType(src)
    {
    }

    /** \dref_SampleLostStatusKind_NOT_LOST */
    static const SampleLostState not_lost()
    {
        return SampleLostState(DDS_NOT_LOST);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_WRITER */
    static const SampleLostState lost_by_writer()
    {
        return SampleLostState(DDS_LOST_BY_WRITER);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_INSTANCES_LIMIT */
    static const SampleLostState lost_by_instances_limit()
    {
        return SampleLostState(DDS_LOST_BY_INSTANCES_LIMIT);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_REMOTE_WRITERS_PER_INSTANCE_LIMIT */
    static const SampleLostState lost_by_remote_writers_per_instance_limit()
    {
        return SampleLostState(DDS_LOST_BY_REMOTE_WRITERS_PER_INSTANCE_LIMIT);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_INCOMPLETE_COHERENT_SET */
    static const SampleLostState lost_by_incomplete_coherent_set()
    {
        return SampleLostState(DDS_LOST_BY_INCOMPLETE_COHERENT_SET);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_LARGE_COHERENT_SET */
    static const SampleLostState lost_by_large_coherent_set()
    {
        return SampleLostState(DDS_LOST_BY_LARGE_COHERENT_SET);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_SAMPLES_PER_REMOTE_WRITER_LIMIT */
    static const SampleLostState lost_by_samples_per_remote_writer_limit()
    {
        return SampleLostState(DDS_LOST_BY_SAMPLES_PER_REMOTE_WRITER_LIMIT);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_VIRTUAL_WRITERS_LIMIT */
    static const SampleLostState lost_by_virtual_writers_limit()
    {
        return SampleLostState(DDS_LOST_BY_VIRTUAL_WRITERS_LIMIT);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_REMOTE_WRITERS_PER_SAMPLE_LIMIT */
    static const SampleLostState lost_by_remote_writers_per_sample_limit()
    {
        return SampleLostState(DDS_LOST_BY_REMOTE_WRITERS_PER_SAMPLE_LIMIT);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_AVAILABILITY_WAITING_TIME */
    static const SampleLostState lost_by_availability_waiting_time()
    {
        return SampleLostState(DDS_LOST_BY_AVAILABILITY_WAITING_TIME);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_REMOTE_WRITER_SAMPLES_PER_VIRTUAL_QUEUE_LIMIT */
    static const SampleLostState lost_by_remote_writers_per_virtual_queue_limit()
    {
        return SampleLostState(DDS_LOST_BY_REMOTE_WRITER_SAMPLES_PER_VIRTUAL_QUEUE_LIMIT);
    }

    /** \dref_SampleLostStatusKind_LOST_BY_OUT_OF_MEMORY */
    static const SampleLostState lost_by_out_of_memory()
    {
        return SampleLostState(DDS_LOST_BY_OUT_OF_MEMORY);
    }

private:
    SampleLostState(uint32_t s)
        : MaskType((uint64_t) s) // cast to avoid error with Visual Studio
    {
    }

};

/**
 * @RTI_class_definition NA
 */
class OMG_DDS_API SampleLostStatus : public rti::core::NativeValueType<SampleLostStatus> {
public:
    typedef rti::core::NativeValueType<SampleLostStatus> Base;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SampleLostStatus)
    SampleLostStatus() { }
    SampleLostStatus(const DDS_SampleLostStatus& src) : Base(src) { }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    /**
     * @memberof dds::core::status::SampleLostStatus
     *
     * \dref_PublicationMatchedStatus_current_count_peak
     */
    rti::core::status::SampleLostState last_reason() const
    {
        return SampleLostState(
            SampleLostState::MaskType(native().last_reason));
    }
/** @RTI_remove_lines 1 */
};

class OMG_DDS_API SampleRejectedStatus :
    public rti::core::NativeValueType<SampleRejectedStatus> {

private:
    typedef rti::core::NativeValueType<SampleRejectedStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        SampleRejectedStatus)

    SampleRejectedStatus() { }

    SampleRejectedStatus(const DDS_SampleRejectedStatus& src) : Base(src) { }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    dds::core::status::SampleRejectedState last_reason() const
    {
        using dds::core::status::SampleRejectedState;

        return SampleRejectedState(
            SampleRejectedState::MaskType(native().last_reason));
    }

    const dds::core::InstanceHandle last_instance_handle() const
    {
        return dds::core::InstanceHandle(native().last_instance_handle);
    }
};


class OMG_DDS_API LivelinessLostStatus :
    public rti::core::NativeValueType<LivelinessLostStatus> {

private:
    typedef rti::core::NativeValueType<LivelinessLostStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        LivelinessLostStatus)

    LivelinessLostStatus() { }

    LivelinessLostStatus(const DDS_LivelinessLostStatus& src)
        : Base(src)
    {
    }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }
};

class OMG_DDS_API LivelinessChangedStatus :
    public rti::core::NativeValueType<LivelinessChangedStatus> {

private:
    typedef rti::core::NativeValueType<LivelinessChangedStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        LivelinessChangedStatus)

    LivelinessChangedStatus() { }

    LivelinessChangedStatus(const DDS_LivelinessChangedStatus& src)
        : Base(src)
    {
    }

public:

    int32_t alive_count() const
    {
        return native().alive_count;
    }

    int32_t not_alive_count() const
    {
        return native().not_alive_count;
    }

    int32_t alive_count_change() const
    {
        return native().alive_count_change;
    }

    int32_t not_alive_count_change() const
    {
        return native().not_alive_count_change;
    }

    const dds::core::InstanceHandle last_publication_handle() const
    {
        return dds::core::InstanceHandle(native().last_publication_handle);
    }
};

class OMG_DDS_API OfferedDeadlineMissedStatus :
    public rti::core::NativeValueType<OfferedDeadlineMissedStatus> {

private:
    typedef rti::core::NativeValueType<OfferedDeadlineMissedStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        OfferedDeadlineMissedStatus)

    OfferedDeadlineMissedStatus() { }

    OfferedDeadlineMissedStatus(const DDS_OfferedDeadlineMissedStatus& src)
        : Base(src)
    {
    }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    const dds::core::InstanceHandle last_instance_handle() const
    {
        return dds::core::InstanceHandle(native().last_instance_handle);
    }
};

class OMG_DDS_API RequestedDeadlineMissedStatus :
    public rti::core::NativeValueType<RequestedDeadlineMissedStatus> {

private:
    typedef rti::core::NativeValueType<RequestedDeadlineMissedStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        RequestedDeadlineMissedStatus)

    RequestedDeadlineMissedStatus() { }

    RequestedDeadlineMissedStatus(const DDS_RequestedDeadlineMissedStatus& src)
        : Base(src)
    {
    }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    const dds::core::InstanceHandle last_instance_handle() const
    {
        return dds::core::InstanceHandle(native().last_instance_handle);
    }
};


class OMG_DDS_API OfferedIncompatibleQosStatus :
    public rti::core::NativeValueType<OfferedIncompatibleQosStatus> {

private:
    typedef rti::core::NativeValueType<OfferedIncompatibleQosStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        OfferedIncompatibleQosStatus)

    OfferedIncompatibleQosStatus() { }

    OfferedIncompatibleQosStatus(const DDS_OfferedIncompatibleQosStatus& src)
        : Base(src)
    {
    }

    // The operator== from Base doesn't work in this case because 'policies'
    // is a sequence, so this class is not a POD
    bool operator==(const OfferedIncompatibleQosStatus& other) const
    {
        return total_count() == other.total_count()
            && total_count_change() == other.total_count_change()
            && last_policy_id() == other.last_policy_id()
            && policies() == other.policies();
    }

public  :
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    dds::core::policy::QosPolicyId last_policy_id() const
    {
        return native().last_policy_id;
    }

    const dds::core::policy::QosPolicyCountSeq policies() const
    {
        return rti::core::native_conversions::sequence_to_vector<
            dds::core::policy::QosPolicyCount>(native().policies);
    }
};

class OMG_DDS_API RequestedIncompatibleQosStatus :
    public rti::core::NativeValueType<RequestedIncompatibleQosStatus> {

private:
    typedef rti::core::NativeValueType<RequestedIncompatibleQosStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        RequestedIncompatibleQosStatus)
    
    RequestedIncompatibleQosStatus() {}
    
    RequestedIncompatibleQosStatus(
        const DDS_RequestedIncompatibleQosStatus& src)
        : Base(src)
    {
    }

    // The operator== from Base doesn't work in this case because 'policies'
    // is a sequence, so this class is not a POD
    bool operator==(const RequestedIncompatibleQosStatus& other) const
    {
        return total_count() == other.total_count()
            && total_count_change() == other.total_count_change()
            && last_policy_id() == other.last_policy_id()
            && policies() == other.policies();
    }

public  :
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    dds::core::policy::QosPolicyId last_policy_id() const
    {
        return native().last_policy_id;
    }

    const dds::core::policy::QosPolicyCountSeq policies() const
    {
        return rti::core::native_conversions::sequence_to_vector<
            dds::core::policy::QosPolicyCount>(native().policies);
    }
};


/**
 * @RTI_class_definition NA
 */
class OMG_DDS_API PublicationMatchedStatus :
    public rti::core::NativeValueType<PublicationMatchedStatus> {

private:
    typedef rti::core::NativeValueType<PublicationMatchedStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        PublicationMatchedStatus)

    PublicationMatchedStatus() { }

    PublicationMatchedStatus(const DDS_PublicationMatchedStatus& src)
        : Base(src)
    {
    }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    int32_t current_count() const
    {
        return native().current_count;
    }

    int32_t current_count_change() const
    {
        return native().current_count_change;
    }

    const dds::core::InstanceHandle last_subscription_handle() const
    {
        return dds::core::InstanceHandle(native().last_subscription_handle);
    }

    // Extension

    /**
     * @memberof dds::core::status::PublicationMatchedStatus
     *
     * \dref_PublicationMatchedStatus_current_count_peak
     */
    int32_t current_count_peak() const
    {
        return native().current_count_peak;
    }

/** @RTI_remove_lines 1 */
};

/**
 * @RTI_class_definition NA
 */
class OMG_DDS_API SubscriptionMatchedStatus :
    public rti::core::NativeValueType<SubscriptionMatchedStatus> {

private:
    typedef rti::core::NativeValueType<SubscriptionMatchedStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        SubscriptionMatchedStatus)

    SubscriptionMatchedStatus() { }

    SubscriptionMatchedStatus(const DDS_SubscriptionMatchedStatus& src)
        : Base(src)
    {
    }

public:
    int32_t total_count() const
    {
        return native().total_count;
    }

    int32_t total_count_change() const
    {
        return native().total_count_change;
    }

    int32_t current_count() const
    {
        return native().current_count;
    }

    int32_t current_count_change() const
    {
        return native().current_count_change;
    }

    const dds::core::InstanceHandle last_publication_handle() const
    {
        return dds::core::InstanceHandle(native().last_publication_handle);
    }

    // Extension
    /**
     * @memberof dds::core::status::SubscriptionMatchedStatus
     *
     * \dref_PublicationMatchedStatus_current_count_peak
     */
    int32_t current_count_peak() const
    {
        return native().current_count_peak;
    }
/** @RTI_remove_lines 1 */
};

// --- Extensions: ------------------------------------------------------------

/**
 * @ingroup DDSStatusTypesModule
 *
 * @brief @extension @st_value_type Encapsulates an event count containing a total
 * count and an incremental count since the last time a status was read.
 *
 * @tparam IntegerType The integer type used to measure the event counts.
 */
template <typename IntegerType>
class EventCount : public std::pair<IntegerType, IntegerType> {
public:
    typedef std::pair<IntegerType, IntegerType> Base;
    typedef IntegerType value_type;

    EventCount() :Base(0, 0)
    {
    }

    EventCount(IntegerType the_total, IntegerType the_change) : Base(the_total, the_change)
    {
    }

    EventCount(const DDS_ReliableWriterCacheEventCount& value)
        : Base(value.total_count, value.total_count_change)
    {
    }

    /**
     * @brief The total count
     */
    IntegerType total() const
    {
        return Base::first;
    }

    /**
     * @brief The incremental count
     */
    IntegerType change() const
    {
        return Base::second;
    }
};

/**
 * @brief Event counts measured with 32-bit integers
 */
typedef EventCount<int32_t> EventCount32;

/**
 * @brief Event counts measured with 64-bit integers
 */
typedef EventCount<int64_t> EventCount64;

/**
 * @ingroup DDSStatusTypesModule
 * @brief @extension Information about the status
 * dds::core::status::StatusMask::datareader_cache()
 *
 * @details \dref_details_DataReaderCacheStatus
 */
class DataReaderCacheStatus :
    public rti::core::NativeValueType<DataReaderCacheStatus> {

private:
    typedef rti::core::NativeValueType<DataReaderCacheStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        DataReaderCacheStatus)

    DataReaderCacheStatus() { }

    DataReaderCacheStatus(const DDS_DataReaderCacheStatus& src)
        : Base(src)
    {
    }

public:
    /** \dref_DataReaderCacheStatus_sample_count */
    int64_t sample_count() const
    {
        return native().sample_count;
    }

    /** \dref_DataReaderCacheStatus_sample_count_peak */
    int64_t sample_count_peak() const
    {
        return native().sample_count_peak;
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @brief @extension Information about the status
 * dds::core::status::StatusMask::datareader_protocol()
 *
 * @details \dref_details_DataReaderProtocolStatus
 */
class OMG_DDS_API DataReaderProtocolStatus :
    public rti::core::NativeValueType<DataReaderProtocolStatus> {

public:
    typedef rti::core::NativeValueType<DataReaderProtocolStatus> Base;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        DataReaderProtocolStatus)

    DataReaderProtocolStatus() { }

    DataReaderProtocolStatus(const DDS_DataReaderProtocolStatus& src)
        : Base(src)
    {
    }

public:
    /** \dref_DataReaderProtocolStatus_received_sample_count
     */
    EventCount64 received_sample_count() const
    {
        return EventCount64(native().received_sample_count, native().received_sample_count_change);
    }
    /** \dref_DataReaderProtocolStatus_received_sample_bytes
     */
    EventCount64 received_sample_bytes() const
    {
        return EventCount64(native().received_sample_bytes, native().received_sample_bytes_change);
    }
    /** \dref_DataReaderProtocolStatus_duplicate_sample_count
     */
    EventCount64 duplicate_sample_count() const
    {
        return EventCount64(native().duplicate_sample_count, native().duplicate_sample_count_change);
    }
    /** \dref_DataReaderProtocolStatus_duplicate_sample_count
     */
    EventCount64 duplicate_sample_bytes() const
    {
        return EventCount64(native().duplicate_sample_bytes, native().duplicate_sample_bytes_change);
    }
    /*i \dref_DataReaderProtocolStatus_filtered_sample_count
     */
    EventCount64 filtered_sample_count() const
    {
        return EventCount64(native().filtered_sample_count, native().filtered_sample_count_change);
    }
    /*i \dref_DataReaderProtocolStatus_filtered_sample_bytes
     */
    EventCount64 filtered_sample_bytes() const
    {
        return EventCount64(native().filtered_sample_bytes, native().filtered_sample_bytes_change);
    }

    /** \dref_DataReaderProtocolStatus_received_heartbeat_count
     */
    EventCount64 received_heartbeat_count() const
    {
        return EventCount64(native().received_heartbeat_count, native().received_heartbeat_count_change);
    }
    /** \dref_DataReaderProtocolStatus_received_heartbeat_bytes
     */
    EventCount64 received_heartbeat_bytes() const
    {
        return EventCount64(native().received_heartbeat_bytes, native().received_heartbeat_bytes_change);
    }
    /** \dref_DataReaderProtocolStatus_sent_ack_count
     */
    EventCount64 sent_ack_count() const
    {
        return EventCount64(native().sent_ack_count, native().sent_ack_count_change);
    }
    /** \dref_DataReaderProtocolStatus_sent_ack_bytes
     */
    EventCount64 sent_ack_bytes() const
    {
        return EventCount64(native().sent_ack_bytes, native().sent_ack_bytes_change);
    }
    /** \dref_DataReaderProtocolStatus_sent_nack_count
     */
    EventCount64 sent_nack_count() const
    {
        return EventCount64(native().sent_nack_count, native().sent_nack_count_change);
    }
    /** \dref_DataReaderProtocolStatus_sent_nack_bytes
     */
    EventCount64 sent_nack_bytes() const
    {
        return EventCount64(native().sent_nack_bytes, native().sent_nack_bytes_change);
    }
    /** \dref_DataReaderProtocolStatus_received_gap_count
     */
    EventCount64 received_gap_count() const
    {
        return EventCount64(native().received_gap_count, native().received_gap_count_change);
    }
    /** \dref_DataReaderProtocolStatus_received_gap_bytes
     */
    EventCount64 received_gap_bytes() const
    {
        return EventCount64(native().received_gap_bytes, native().received_gap_bytes_change);
    }
    /** \dref_DataReaderProtocolStatus_rejected_sample_count
     */
    EventCount64 rejected_sample_count() const
    {
        return EventCount64(native().rejected_sample_count, native().rejected_sample_count_change);
    }
    /** \dref_DataReaderProtocolStatus_first_available_sample_sequence_number
     */
    rti::core::SequenceNumber first_available_sample_sequence_number() const
    {
        return native().first_available_sample_sequence_number;
    }
    /** \dref_DataReaderProtocolStatus_last_available_sample_sequence_number
     */
    rti::core::SequenceNumber last_available_sample_sequence_number() const
    {
        return native().last_available_sample_sequence_number;
    }
    /** \dref_DataReaderProtocolStatus_last_committed_sample_sequence_number
     */
    rti::core::SequenceNumber last_committed_sample_sequence_number() const
    {
        return native().last_committed_sample_sequence_number;
    }
    /** \dref_DataReaderProtocolStatus_uncommitted_sample_count
     */
    int32_t uncommitted_sample_count() const
    {
        return native().uncommitted_sample_count;
    }

    bool operator==(const DataReaderProtocolStatus& other) const;
    bool operator!=(const DataReaderProtocolStatus& other) const
    {
        return !(*this == other);
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @brief @extension Information about the status
 * dds::core::status::StatusMask::datawriter_cache()
 *
 * @details \dref_details_DataWriterCacheStatus
 */
class OMG_DDS_API DataWriterCacheStatus :
    public rti::core::NativeValueType<DataWriterCacheStatus> {

private:
    typedef rti::core::NativeValueType<DataWriterCacheStatus> Base;

public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        DataWriterCacheStatus)

    DataWriterCacheStatus() { }

    DataWriterCacheStatus(const DDS_DataWriterCacheStatus& src)
        : Base(src)
    {
    }

public:
    /** \dref_DataWriterCacheStatus_sample_count */
    int64_t sample_count() const
    {
        return native().sample_count;
    }

    /** \dref_DataWriterCacheStatus_sample_count_peak */
    int64_t sample_count_peak() const
    {
        return native().sample_count_peak;
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @brief @extension Information about the status
 * dds::core::status::StatusMask::reliable_writer_cache_changed()
 *
 * @details \dref_details_ReliableWriterCacheChangedStatus
 */
class OMG_DDS_API ReliableWriterCacheChangedStatus :
    public rti::core::NativeValueType<ReliableWriterCacheChangedStatus> {

public:
    typedef rti::core::NativeValueType<ReliableWriterCacheChangedStatus> Base;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        ReliableWriterCacheChangedStatus)

    ReliableWriterCacheChangedStatus() { }

    ReliableWriterCacheChangedStatus(const DDS_ReliableWriterCacheChangedStatus& src)
        : Base(src)
    {
    }

    /** \dref_ReliableWriterCacheChangedStatus_empty_reliable_writer_cache
     */
    EventCount32 empty_reliable_writer_cache() const
    {
        return native().empty_reliable_writer_cache;
    }

    /** \dref_ReliableWriterCacheChangedStatus_full_reliable_writer_cache
     */
    EventCount32 full_reliable_writer_cache() const
    {
        return native().full_reliable_writer_cache;
    }

    /** \dref_ReliableWriterCacheChangedStatus_low_watermark_reliable_writer_cache
     */
    EventCount32 low_watermark_reliable_writer_cache() const
    {
        return native().low_watermark_reliable_writer_cache;
    }

    /** \dref_ReliableWriterCacheChangedStatus_high_watermark_reliable_writer_cache
     */
    EventCount32 high_watermark_reliable_writer_cache() const
    {
        return native().high_watermark_reliable_writer_cache;
    }

    /** \dref_ReliableWriterCacheChangedStatus_unacknowledged_sample_count
     */
    int32_t unacknowledged_sample_count() const
    {
        return native().unacknowledged_sample_count;
    }

    /** \dref_ReliableWriterCacheChangedStatus_unacknowledged_sample_count_peak
     */
    int32_t unacknowledged_sample_count_peak() const
    {
        return native().unacknowledged_sample_count_peak;
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @brief @extension Information about the status
 * dds::core::status::StatusMask::reliable_reader_activity_changed()
 *
 * @details \dref_details_ReliableReaderActivityChangedStatus
 */
class OMG_DDS_API ReliableReaderActivityChangedStatus :
    public rti::core::NativeValueType<ReliableReaderActivityChangedStatus> {

public:
    typedef rti::core::NativeValueType<ReliableReaderActivityChangedStatus> Base;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        ReliableReaderActivityChangedStatus)

    ReliableReaderActivityChangedStatus() { }

    ReliableReaderActivityChangedStatus(const DDS_ReliableReaderActivityChangedStatus& src)
        : Base(src)
    {
    }

public:
    /** \dref_ReliableReaderActivityChangedStatus_active_count */
    EventCount32 active_count() const
    {
        return EventCount32(native().active_count, native().active_count_change);
    }

    /** \dref_ReliableReaderActivityChangedStatus_inactive_count */
    EventCount32 inactive_count() const
    {
        return EventCount32(native().inactive_count, native().inactive_count_change);
    }

    /** \dref_ReliableReaderActivityChangedStatus_last_instance_handle */
    dds::core::InstanceHandle last_instance_handle() const
    {
        return dds::core::InstanceHandle(native().last_instance_handle);
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @brief @extension Information about the status
 * dds::core::status::StatusMask::datawriter_protocol()
 *
 * @details \dref_details_DataWriterProtocolStatus
 */
class OMG_DDS_API DataWriterProtocolStatus :
    public rti::core::NativeValueType<DataWriterProtocolStatus> {

public:
    typedef rti::core::NativeValueType<DataWriterProtocolStatus> Base;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        DataWriterProtocolStatus)

    DataWriterProtocolStatus() { }

    DataWriterProtocolStatus(const DDS_DataWriterProtocolStatus& src)
        : Base(src)
    {
    }

public:
    /** \dref_DataWriterProtocolStatus_pushed_sample_count
     */
    EventCount64 pushed_sample_count() const
    {
        return EventCount64(native().pushed_sample_count, native().pushed_sample_count_change);
    }
    /** \dref_DataWriterProtocolStatus_pushed_sample_bytes
     */
    EventCount64 pushed_sample_bytes() const
    {
        return EventCount64(native().pushed_sample_bytes, native().pushed_sample_bytes_change);
    }

    // CORE-5953: not exposed
    EventCount64 filtered_sample_count() const
    {
        return EventCount64(native().filtered_sample_count, native().filtered_sample_count_change);
    }

    // CORE-5953: not exposed
    EventCount64 filtered_sample_bytes() const
    {
        return EventCount64(native().filtered_sample_bytes, native().filtered_sample_bytes_change);
    }
    /** \dref_DataWriterProtocolStatus_sent_heartbeat_count
     */
    EventCount64 sent_heartbeat_count() const
    {
        return EventCount64(native().sent_heartbeat_count, native().sent_heartbeat_count_change);
    }
    /** \dref_DataWriterProtocolStatus_sent_heartbeat_bytes
     */
    EventCount64 sent_heartbeat_bytes() const
    {
        return EventCount64(native().sent_heartbeat_bytes, native().sent_heartbeat_bytes_change);
    }
    /** \dref_DataWriterProtocolStatus_pulled_sample_count
     */
    EventCount64 pulled_sample_count() const
    {
        return EventCount64(native().pulled_sample_count, native().pulled_sample_count_change);
    }
    /** \dref_DataWriterProtocolStatus_pulled_sample_bytes
     */
    EventCount64 pulled_sample_bytes() const
    {
        return EventCount64(native().pulled_sample_bytes, native().pulled_sample_bytes_change);
    }
    /** \dref_DataWriterProtocolStatus_received_ack_count
     */
    EventCount64 received_ack_count() const
    {
        return EventCount64(native().received_ack_count, native().received_ack_count_change);
    }
    /** \dref_DataWriterProtocolStatus_received_ack_bytes
     */
    EventCount64 received_ack_bytes() const
    {
        return EventCount64(native().received_ack_bytes, native().received_ack_bytes_change);
    }
    /** \dref_DataWriterProtocolStatus_received_nack_count
     */
    EventCount64 received_nack_count() const
    {
        return EventCount64(native().received_nack_count, native().received_nack_count_change);
    }
    /** \dref_DataWriterProtocolStatus_received_nack_bytes
     */
    EventCount64 received_nack_bytes() const
    {
        return EventCount64(native().received_nack_bytes, native().received_nack_bytes_change);
    }
    /** \dref_DataWriterProtocolStatus_sent_gap_count
     */
    EventCount64 sent_gap_count() const
    {
        return EventCount64(native().sent_gap_count, native().sent_gap_count_change);
    }
    /** \dref_DataWriterProtocolStatus_sent_gap_bytes
     */
    EventCount64 sent_gap_bytes() const
    {
        return EventCount64(native().sent_gap_bytes, native().sent_gap_bytes_change);
    }
    /** \dref_DataWriterProtocolStatus_rejected_sample_count
     */
    EventCount64 rejected_sample_count() const
    {
        return EventCount64(native().rejected_sample_count, native().rejected_sample_count_change);
    }

    /** \dref_DataWriterProtocolStatus_send_window_size
     */
    int32_t send_window_size() const
    {
        return native().send_window_size;
    }

    /** \dref_DataWriterProtocolStatus_first_available_sample_sequence_number
     */
    rti::core::SequenceNumber first_available_sample_sequence_number() const
    {
        return native().first_available_sample_sequence_number;
    }
    /** \dref_DataWriterProtocolStatus_last_available_sample_sequence_number
     */
    rti::core::SequenceNumber last_available_sample_sequence_number() const
    {
        return native().last_available_sample_sequence_number;
    }
    /** \dref_DataWriterProtocolStatus_first_unacknowledged_sample_sequence_number
     */
    rti::core::SequenceNumber first_unacknowledged_sample_sequence_number() const
    {
        return native().first_unacknowledged_sample_sequence_number;
    }
    /** \dref_DataWriterProtocolStatus_first_available_sample_virtual_sequence_number
     */
    rti::core::SequenceNumber first_available_sample_virtual_sequence_number() const
    {
        return native().first_available_sample_virtual_sequence_number;
    }
    /** \dref_DataWriterProtocolStatus_last_available_sample_virtual_sequence_number
     */
    rti::core::SequenceNumber last_available_sample_virtual_sequence_number() const
    {
        return native().last_available_sample_virtual_sequence_number;
    }
    /** \dref_DataWriterProtocolStatus_first_unacknowledged_sample_virtual_sequence_number
     */
    rti::core::SequenceNumber first_unacknowledged_sample_virtual_sequence_number() const
    {
        return native().first_unacknowledged_sample_virtual_sequence_number;
    }
    /** \dref_DataWriterProtocolStatus_first_unacknowledged_sample_subscription_handle
     */
    dds::core::InstanceHandle first_unacknowledged_sample_subscription_handle() const
    {
        return dds::core::InstanceHandle(
                native().first_unacknowledged_sample_subscription_handle);
    }
    /** \dref_DataWriterProtocolStatus_first_unelapsed_keep_duration_sample_sequence_number
     */
    rti::core::SequenceNumber first_unelapsed_keep_duration_sample_sequence_number() const
    {
        return native().first_unelapsed_keep_duration_sample_sequence_number;
    }
};

/**
 * @ingroup DDSStatusTypesModule
 *
 * @details \dref_details_DomainParticipantProtocolStatus
 */
class OMG_DDS_API DomainParticipantProtocolStatus :
    public rti::core::NativeValueType<DomainParticipantProtocolStatus> {

public:
    typedef rti::core::NativeValueType<DomainParticipantProtocolStatus> Base;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
            DomainParticipantProtocolStatus)

    DomainParticipantProtocolStatus() { }

    DomainParticipantProtocolStatus(const DDS_DomainParticipantProtocolStatus& src)
        : Base(src)
    {
    }

public:
    /** \dref_DomainParticipantProtocolStatus_corrupted_rtps_message_count
     */
    int64_t corrupted_rtps_message_count() const
    {
        return native().corrupted_rtps_message_count;
    }

    /** \dref_DomainParticipantProtocolStatus_corrupted_rtps_message_count_change
     */
    int64_t corrupted_rtps_message_count_change() const
    {
        return native().corrupted_rtps_message_count_change;
    }

    /** \dref_DomainParticipantProtocolStatus_last_corrupted_message_timestamp
     */
    dds::core::Time last_corrupted_message_timestamp() const
    {
        return dds::core::Time(
                native().last_corrupted_message_timestamp.sec,
                native().last_corrupted_message_timestamp.nanosec);
    }
};

/**
 * @ingroup DDSStatusTypesModule
 * @brief @extension Information about the status
 * dds::core::status::StatusMask::service_request_accepted()
 *
 * @details \dref_details_ServiceRequestAcceptedStatus
 */
class OMG_DDS_API ServiceRequestAcceptedStatus :
    public rti::core::NativeValueType<ServiceRequestAcceptedStatus> {

public:
    typedef rti::core::NativeValueType<ServiceRequestAcceptedStatus> Base;

    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        ServiceRequestAcceptedStatus)

    ServiceRequestAcceptedStatus() { }

    ServiceRequestAcceptedStatus(const DDS_ServiceRequestAcceptedStatus& src)
        : Base(src)
    {
    }

public:
    /** \dref_ServiceRequestAcceptedStatus_total_count
     */
    EventCount32 total_count() const
    {
        return EventCount32(native().total_count, native().total_count_change);
    }

    /** \dref_ServiceRequestAcceptedStatus_current_count
     */
    EventCount32 current_count() const
    {
        return EventCount32(native().current_count, native().current_count_change);
    }

    /** \dref_ServiceRequestAcceptedStatus_last_request_handle
     */
    dds::core::InstanceHandle last_request_handle() const
    {
        return dds::core::InstanceHandle(native().last_request_handle);
    }

    /** \dref_ServiceRequestAcceptedStatus_service_id
     */
    rti::core::ServiceRequestId service_id() const
    {
        return (rti::core::ServiceRequestId::type)native().service_id;
    }
};

} } } // namespace rti::core::status

namespace dds { namespace core { namespace status {

// Specializations of get_status:
template <typename STATUS>
StatusMask get_status();

template <>
inline StatusMask get_status<rti::core::status::ReliableWriterCacheChangedStatus>()
{
    return StatusMask::reliable_writer_cache_changed();
}

template <>
inline StatusMask get_status<rti::core::status::ReliableReaderActivityChangedStatus>()
{
    return StatusMask::reliable_reader_activity_changed();
}

template <>
inline StatusMask get_status<rti::core::status::DataWriterCacheStatus>()
{
    return StatusMask::datawriter_cache();
}

template <>
inline StatusMask get_status<rti::core::status::DataWriterProtocolStatus>()
{
    return StatusMask::datawriter_protocol();
}

template <>
inline StatusMask get_status<rti::core::status::DataReaderCacheStatus>()
{
    return StatusMask::datareader_cache();
}

template <>
inline StatusMask get_status<rti::core::status::DataReaderProtocolStatus>()
{
    return StatusMask::datareader_protocol();
}

template <>
inline StatusMask get_status<rti::core::status::ServiceRequestAcceptedStatus>()
{
    return StatusMask::service_request_accepted();
}

} } } // namespace dds::core::status

#endif // RTI_DDS_CORE_STATUS_STATUS_HPP_

