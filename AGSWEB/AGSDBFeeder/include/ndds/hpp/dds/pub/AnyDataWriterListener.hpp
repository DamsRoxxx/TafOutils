#ifndef OMG_DDS_PUB_ANY_DATA_WRITER_LISTENER_HPP_
#define OMG_DDS_PUB_ANY_DATA_WRITER_LISTENER_HPP_

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

#include <dds/core/status/Status.hpp>
#include <rti/pub/AcknowledgmentInfo.hpp>

namespace dds { namespace pub {
  class AnyDataWriter;
  class AnyDataWriterListener;
  class NoOpAnyDataWriterListener;
} }

/**
 * @ingroup DDSWriterModule
 * @headerfile dds/pub/AnyDataWriterListener.hpp
 *
 * @brief The listener to notify status changes for a dds::pub::DataWriter of
 * a generic type.
 *
 * This class is only intended to act as the base of PublisherListener.
 *
 * @see DataWriterListener
 * @see PublisherListener
 */
class dds::pub::AnyDataWriterListener {
public:
    virtual ~AnyDataWriterListener()
    {
    }

    /**
     * @brief Handles the dds::core::status::OfferedDeadlineMissedStatus status
     */
    virtual void on_offered_deadline_missed(
        dds::pub::AnyDataWriter& writer,
        const ::dds::core::status::OfferedDeadlineMissedStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::OfferedIncompatibleQosStatus status
     */
    virtual void on_offered_incompatible_qos(
        dds::pub::AnyDataWriter& writer,
        const ::dds::core::status::OfferedIncompatibleQosStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::LivelinessLostStatus status
     */
    virtual void on_liveliness_lost(
        dds::pub::AnyDataWriter& writer,
        const ::dds::core::status::LivelinessLostStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::PublicationMatchedStatus status
     */
    virtual void on_publication_matched(
        dds::pub::AnyDataWriter& writer,
        const ::dds::core::status::PublicationMatchedStatus& status) = 0;

    // --- Extensions: --------------------------------------------------------

    /**
     * @brief @extension Handles the dds::core::status::ReliableWriterCacheChangedStatus status
     */
    virtual void on_reliable_writer_cache_changed(
        dds::pub::AnyDataWriter& writer,
        const rti::core::status::ReliableWriterCacheChangedStatus& status) = 0;

    /**
     * @brief @extension Handles the dds::core::status::ReliableReaderActivityChangedStatus status
     */
    virtual void on_reliable_reader_activity_changed(
        dds::pub::AnyDataWriter& writer,
        const rti::core::status::ReliableReaderActivityChangedStatus& status) = 0;

    /**
     * @brief @extension Notifies when an instance is replaced in DataWriter queue.
     */
    virtual void on_instance_replaced(
        dds::pub::AnyDataWriter& writer,
        const dds::core::InstanceHandle& handle) = 0;

    /**
     * @brief @extension Called when a sample is application-acknowledged.
     */
    virtual void on_application_acknowledgment(
        dds::pub::AnyDataWriter& writer,
        const rti::pub::AcknowledgmentInfo& acknowledgment_info) = 0;

    /**
     * @brief @extension Called when a sample that has been received on a the 
     * built-in service channel is intended for the DataWriter that has 
     * installed this listener 
     */
    virtual void on_service_request_accepted(
        dds::pub::AnyDataWriter& writer,
        const rti::core::status::ServiceRequestAcceptedStatus& status) = 0;
};

class dds::pub::NoOpAnyDataWriterListener:
    public virtual dds::pub::AnyDataWriterListener {
public:
    virtual ~NoOpAnyDataWriterListener()
    {
    }

public:
    virtual void on_offered_deadline_missed(
        dds::pub::AnyDataWriter&,
        const ::dds::core::status::OfferedDeadlineMissedStatus&)
    {
    }

    virtual void on_offered_incompatible_qos(
        dds::pub::AnyDataWriter&,
        const ::dds::core::status::OfferedIncompatibleQosStatus&)
    {
    }

    virtual void on_liveliness_lost(
        dds::pub::AnyDataWriter&,
        const ::dds::core::status::LivelinessLostStatus&)
    {
    }

    virtual void on_publication_matched(
        dds::pub::AnyDataWriter&,
        const ::dds::core::status::PublicationMatchedStatus&)
    {
    }

    // --- Extensions: --------------------------------------------------------

    virtual void on_reliable_writer_cache_changed(
        dds::pub::AnyDataWriter&,
        const rti::core::status::ReliableWriterCacheChangedStatus&)
    {
    }

    virtual void on_reliable_reader_activity_changed(
        dds::pub::AnyDataWriter&,
        const rti::core::status::ReliableReaderActivityChangedStatus&)
    {
    }

    virtual void on_instance_replaced(
        dds::pub::AnyDataWriter&,
        const dds::core::InstanceHandle&)
    {
    }

    virtual void on_application_acknowledgment(
        dds::pub::AnyDataWriter&,
        const rti::pub::AcknowledgmentInfo&)
    {
    }

    virtual void on_service_request_accepted(
        dds::pub::AnyDataWriter&,
        const rti::core::status::ServiceRequestAcceptedStatus&)
    {
    }
};


#endif /* OMG_DDS_PUB_ANY_DATA_WRITER_LISTENER_HPP_ */
