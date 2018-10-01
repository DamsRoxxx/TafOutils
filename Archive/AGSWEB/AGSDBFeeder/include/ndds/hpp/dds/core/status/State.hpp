#ifndef OMG_DDS_CORE_STATUS_STATE_HPP_
#define OMG_DDS_CORE_STATUS_STATE_HPP_

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

#include <bitset>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_subscription.h"
#include <dds/core/types.hpp>

namespace dds { namespace core { namespace status {

/**
 * @ingroup DDSReaderModule
 * @brief Reasons why a sample was rejected
 *
 * @see dds::core::status::SampleRejectedStatus::last_reason()
 */
class SampleRejectedState: public std::bitset<OMG_DDS_STATE_BIT_COUNT > {
public:
    typedef std::bitset<OMG_DDS_STATE_BIT_COUNT > MaskType;

    /**
     * @brief Creates not_lost()
     */
    SampleRejectedState()
    {
    }

    /**
     * @brief Create from a bitset
     */
    SampleRejectedState(const MaskType& src) : MaskType(src)
    {
    }

    /** \dref_SampleRejectedStatusKind_NOT_REJECTED */
    static const SampleRejectedState not_rejected()
    {
        return SampleRejectedState(DDS_NOT_REJECTED);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_SAMPLES_LIMIT */
    static const SampleRejectedState rejected_by_samples_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_SAMPLES_LIMIT);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_INSTANCES_LIMIT */
    static const SampleRejectedState rejected_by_instances_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_INSTANCE_LIMIT);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT */
    static const SampleRejectedState rejected_by_samples_per_instance_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT);
    }

    //
    // Extensions (added to standard header, issue ID:  CPPPSM-291)
    //

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_REMOTE_WRITERS_LIMIT */
    static const SampleRejectedState rejected_by_remote_writers_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_REMOTE_WRITERS_LIMIT);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_REMOTE_WRITERS_PER_INSTANCE_LIMIT */
    static const SampleRejectedState rejected_by_remote_writers_per_instance_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_REMOTE_WRITERS_PER_INSTANCE_LIMIT);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_SAMPLES_PER_REMOTE_WRITER_LIMIT */
    static const SampleRejectedState rejected_by_samples_per_remote_writer_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_SAMPLES_PER_REMOTE_WRITER_LIMIT);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_VIRTUAL_WRITERS_LIMIT */
    static const SampleRejectedState rejected_by_virtual_writers_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_VIRTUAL_WRITERS_LIMIT);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_REMOTE_WRITERS_PER_SAMPLE_LIMIT */
    static const SampleRejectedState rejected_by_remote_writers_per_sample_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_REMOTE_WRITERS_PER_SAMPLE_LIMIT);
    }

    /** \dref_SampleRejectedStatusKind_REJECTED_BY_REMOTE_WRITER_SAMPLES_PER_VIRTUAL_QUEUE_LIMIT */
    static const SampleRejectedState rejected_by_remote_writers_per_virtual_queue_limit()
    {
        return SampleRejectedState(DDS_REJECTED_BY_REMOTE_WRITER_SAMPLES_PER_VIRTUAL_QUEUE_LIMIT);
    }

private:
    // @TODO
    // -- This Ctor should be fixed as currently there is this 
    // -- cast only to avoid an error when compiling with the  MS vC++ compiler
    SampleRejectedState(uint32_t s) :
        MaskType((uint64_t) s)
    {
    }

};

inline void swap(SampleRejectedState& left, SampleRejectedState& right)
    OMG_NOEXCEPT_IF(noexcept(
        swap(
            static_cast<SampleRejectedState::MaskType&>(left),
            static_cast<SampleRejectedState::MaskType&>(right))))
{
    swap(
        static_cast<SampleRejectedState::MaskType&>(left),
        static_cast<SampleRejectedState::MaskType&>(right));
}

// StatusMask create_status_mask(uint64_t);
/**
 * @ingroup DDSStatusTypesModule
 * @brief A std::bitset (list) of statuses.
 *  
 * @dref_details_StatusMask
 *  
 * @see \ref DDSEntityExampleModule_listener
 */
class StatusMask : public std::bitset<OMG_DDS_STATUS_COUNT > {
public:
    /**
     * @brief The base class, a std::bitset.
     */
    typedef std::bitset<OMG_DDS_STATUS_COUNT > MaskType;

public:
    /**
     * @brief Creates StatusMask::none()
     */
    StatusMask()
    {
    }

    /**
     * @brief Creates a StatusMask from the bits in a uint64_t value.
     */
    explicit StatusMask(uint64_t mask) :
        std::bitset<OMG_DDS_STATUS_COUNT >(mask)
    {
    }

    /**
     * @brief Creates a StatusMask from a bitset
     */
    // Spec error CPPPSM-158: need this constructor
    StatusMask(const MaskType& mask) : MaskType(mask)
    {
    }

    /**
     * @brief All the bits are set
     */
    static const StatusMask all()
    {
        return StatusMask(DDS_STATUS_MASK_ALL);
    }

    /**
     * @brief No bits are set
     */
    static const StatusMask none()
    {
        return StatusMask(DDS_STATUS_MASK_NONE);
    }

    /**
     * @brief Another topic exists with the same name but different
     * characteristics.
     *
     * @details \dref_details_StatusKind_INCONSISTENT_TOPIC_STATUS
     */
    static const StatusMask inconsistent_topic()
    {
        return StatusMask(DDS_INCONSISTENT_TOPIC_STATUS);
    }

    /**
     * @brief The deadline that the dds::pub::DataWriter has committed through
     * its dds::core::policy::Deadline was not respected for a specific instance.
     *
     * @details \dref_details_StatusKind_OFFERED_DEADLINE_MISSED_STATUS
     */
    static const StatusMask offered_deadline_missed()
    {
        return StatusMask(DDS_OFFERED_DEADLINE_MISSED_STATUS);
    }

    /**
     * @brief The deadline that the dds::sub::DataReader was expecting through
     * its dds::core::policy::Deadline was not respected for a specific instance.
     *
     * @details \dref_details_StatusKind_REQUESTED_DEADLINE_MISSED_STATUS
     */
    static const StatusMask requested_deadline_missed()
    {
        return StatusMask(DDS_REQUESTED_DEADLINE_MISSED_STATUS);
    }

    /**
     * @brief A QosPolicy value was incompatible with what was requested.
     *
     * @details \dref_details_StatusKind_OFFERED_INCOMPATIBLE_QOS_STATUS
     */
    static const StatusMask offered_incompatible_qos()
    {
        return StatusMask(DDS_OFFERED_INCOMPATIBLE_QOS_STATUS);
    }

    /**
     * @brief A QosPolicy value was incompatible with what is offered.
     *
     * @details \dref_details_StatusKind_REQUESTED_INCOMPATIBLE_QOS_STATUS
     */
    static const StatusMask requested_incompatible_qos()
    {
        return StatusMask(DDS_REQUESTED_INCOMPATIBLE_QOS_STATUS);
    }

    /**
     * @brief A sample has been lost (i.e. was never received).
     *
     * @details \dref_details_StatusKind_SAMPLE_LOST_STATUS
     */
    static const StatusMask sample_lost()
    {
        return StatusMask(DDS_SAMPLE_LOST_STATUS);
    }

    /**
     * @brief A (received) sample has been rejected.
     *
     * @details \dref_details_StatusKind_SAMPLE_REJECTED_STATUS
     */
    static const StatusMask sample_rejected()
    {
        return StatusMask(DDS_SAMPLE_REJECTED_STATUS);
    }

    /**
     * @brief New data is available
     *
     * @details \dref_details_StatusKind_DATA_ON_READERS_STATUS
     */
    static const StatusMask data_on_readers()
    {
        return StatusMask(DDS_DATA_ON_READERS_STATUS);
    }

    /**
     * @brief One or more new data samples have been received.
     *
     * @details \dref_details_StatusKind_DATA_AVAILABLE_STATUS
     */
    static const StatusMask data_available()
    {
        return StatusMask(DDS_DATA_AVAILABLE_STATUS);
    }

    /**
     * @brief The liveliness that the dds::pub::DataWriter has committed to
     * through its dds::core::policy::Liveliness policy was not respected, thus
     * dds::sub::DataReader entities will consider the writer as no longer alive
     *
     * @details \dref_details_StatusKind_LIVELINESS_LOST_STATUS
     */
    static const StatusMask liveliness_lost()
    {
        return StatusMask(DDS_LIVELINESS_LOST_STATUS);
    }

    /**
     * @brief The liveliness of one or more dds::pub::DataWriter that were writing
     * instances read through the dds::sub::DataReader has changed. Some
     * dds::pub::DataWriter have become alive or not_alive.
     *
     * @details \dref_details_StatusKind_LIVELINESS_CHANGED_STATUS
     */
    static const StatusMask liveliness_changed()
    {
        return StatusMask(DDS_LIVELINESS_CHANGED_STATUS);
    }

    /**
     * @brief The dds::pub::DataWriter has found dds::sub::DataReader that matches
     * the dds::topic::Topic and has compatible QoS.
     *
     * @details \dref_details_StatusKind_PUBLICATION_MATCHED_STATUS
     */
    static const StatusMask publication_matched()
    {
        return StatusMask(DDS_PUBLICATION_MATCHED_STATUS);
    }

    /**
     * @brief The dds::sub::DataReader has found dds::pub::DataWriter that
     * matches the dds::topic::Topic and has compatible QoS.
     *
     * @details \dref_details_StatusKind_SUBSCRIPTION_MATCHED_STATUS
     */
    static const StatusMask subscription_matched()
    {
        return StatusMask(DDS_SUBSCRIPTION_MATCHED_STATUS);
    }

    //
    // Extensions (added to standard header, issue ID:  CPPPSM-291)
    //

    /**
     * @brief @extension The number of unacknowledged samples in a reliable
     * writer's cache has changed such that it has reached a pre-defined
     * trigger point.
     *
     * @details \dref_details_StatusKind_RELIABLE_WRITER_CACHE_CHANGED_STATUS
     */
    static const StatusMask reliable_writer_cache_changed()
    {
        return StatusMask(DDS_RELIABLE_WRITER_CACHE_CHANGED_STATUS);
    }

    /**
     * @brief @extension One or more reliable readers has become active or
     * inactive.
     *
     * @details \dref_details_StatusKind_RELIABLE_READER_ACTIVITY_CHANGED_STATUS
     */
    static const StatusMask reliable_reader_activity_changed()
    {
        return StatusMask(DDS_RELIABLE_READER_ACTIVITY_CHANGED_STATUS);
    }

    /**
     * @brief @extension The status of the writer's cache.
     *
     * @details \dref_details_StatusKind_DATA_WRITER_CACHE_STATUS
     */
    static const StatusMask datawriter_cache()
    {
        return StatusMask(DDS_DATA_WRITER_CACHE_STATUS);
    }

    /**
     * @brief @extension The status of a writer's internal protocol related metrics
     *
     * @details \dref_details_StatusKind_DATA_WRITER_PROTOCOL_STATUS
     */
    static const StatusMask datawriter_protocol()
    {
        return StatusMask(DDS_DATA_WRITER_PROTOCOL_STATUS);
    }

    /**
     * @brief @extension The status of the reader's cache.
     *
     * @details \dref_details_StatusKind_DATA_READER_CACHE_STATUS
     */
    static const StatusMask datareader_cache()
    {
        return StatusMask(DDS_DATA_READER_CACHE_STATUS);
    }

    /**
     * @brief @extension The status of a reader's internal protocol related metrics
     *
     * @details \dref_details_StatusKind_DATA_READER_PROTOCOL_STATUS
     */
    static const StatusMask datareader_protocol()
    {
        return StatusMask(DDS_DATA_READER_PROTOCOL_STATUS);
    }

    /**
     * @brief @extension A dds::pub::DataWriter has received an application-level
     * acknowledgment for a sample
     *
     * @details \dref_details_StatusKind_DATA_WRITER_APPLICATION_ACKNOWLEDGMENT_STATUS
     */
    static const StatusMask datawriter_application_acknowledgment()
    {
        return StatusMask(DDS_DATA_WRITER_APPLICATION_ACKNOWLEDGMENT_STATUS);
    }

    /**
     * @brief @extension A dds::pub::DataWriter instance has been replaced
     *
     * @details \dref_StatusKind_DATA_WRITER_INSTANCE_REPLACED_STATUS
     */
    static const StatusMask datawriter_instance_replaced()
    {
        return StatusMask(DDS_DATA_WRITER_INSTANCE_REPLACED_STATUS);
    }

    /**
     * @brief @extension A service request has been received for a 
     * dds::pub::DataWriter 
     *
     * @details \dref_details_StatusKind_SERVICE_REQUEST_ACCEPTED_STATUS
     */
    static const StatusMask service_request_accepted()
    {
        return StatusMask(DDS_SERVICE_REQUEST_ACCEPTED_STATUS);
    }

};

inline void swap(StatusMask& left, StatusMask& right)
    OMG_NOEXCEPT_IF(noexcept(
        swap(
            static_cast<StatusMask::MaskType&>(left),
            static_cast<StatusMask::MaskType&>(right))))
{
    swap(
        static_cast<StatusMask::MaskType&>(left),
        static_cast<StatusMask::MaskType&>(right));
}

} } } // namespace dds / core / status


#endif // OMG_DDS_CORE_STATUS_STATE_HPP_
