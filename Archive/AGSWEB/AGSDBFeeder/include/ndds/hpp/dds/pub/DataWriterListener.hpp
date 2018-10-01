#ifndef OMG_DDS_PUB_DATA_WRITER_LISTENER_HPP_
#define OMG_DDS_PUB_DATA_WRITER_LISTENER_HPP_

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
#include <dds/pub/pubfwd.hpp>

namespace dds { namespace pub {

/**
 * @ingroup DDSWriterModule
 * @headerfile dds/pub/DataWriterListener.hpp
 *
 * @brief The Listener to notify status changes for a dds::pub::DataWriter
 *
 * @details \dref_details_DataWriterListener
 *
 * @see NoOpDataWriterListener
 */
template<typename T>
class DataWriterListener {
public:
    virtual ~DataWriterListener()
    {
    }

public:
    /**
     * @brief Handles the dds::core::status::OfferedDeadlineMissedStatus status
     *
     * @details \dref_details_DataWriterListener_on_offered_deadline_missed
     */
    virtual void on_offered_deadline_missed(
        dds::pub::DataWriter<T>& writer,
        const dds::core::status::OfferedDeadlineMissedStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::OfferedIncompatibleQosStatus status
     *
     * @details \dref_details_DataWriterListener_on_offered_incompatible_qos
     */
    virtual void on_offered_incompatible_qos(
        dds::pub::DataWriter<T>& writer,
        const dds::core::status::OfferedIncompatibleQosStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::LivelinessLostStatus status
     *
     * @details \dref_details_DataWriterListener_on_liveliness_lost
     */
    virtual void on_liveliness_lost(
        dds::pub::DataWriter<T>& writer,
        const dds::core::status::LivelinessLostStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::PublicationMatchedStatus status
     *
     * @details \dref_details_DataWriterListener_on_publication_matched
     */
    virtual void on_publication_matched(
        dds::pub::DataWriter<T>& writer,
        const dds::core::status::PublicationMatchedStatus& status) = 0;

    // --- Extensions: --------------------------------------------------------

    /**
     * @brief @extension Handles the dds::core::status::ReliableWriterCacheChangedStatus status
     *
     * @details \dref_details_DataWriterListener_on_reliable_writer_cache_changed
     */
    virtual void on_reliable_writer_cache_changed(
        dds::pub::DataWriter<T>& writer,
        const rti::core::status::ReliableWriterCacheChangedStatus& status) = 0;

    /**
     * @brief @extension Handles the dds::core::status::ReliableReaderActivityChangedStatus status
     *
     * @details \dref_details_DataWriterListener_on_reliable_reader_activity_changed
     */
    virtual void on_reliable_reader_activity_changed(
        dds::pub::DataWriter<T>& writer,
        const rti::core::status::ReliableReaderActivityChangedStatus& status) = 0;

    /**
     * @brief @extension Notifies when an instance is replaced in DataWriter queue.
     *
     * @details \dref_details_DataWriterListener_on_instance_replaced
     */
    virtual void on_instance_replaced(
        dds::pub::DataWriter<T>& writer,
        const dds::core::InstanceHandle& handle) = 0;

    /**
     * @brief @extension Called when a sample is application-acknowledged.
     *
     * @details \dref_details_DataWriterListener_on_application_acknowledgment 
     * @param  writer \st_out Locally created DataWriter that triggers the 
     *         listener callback
     * @param acknowledgment_info \st_out rti::pub::AcknowledgmentInfo of the acknowledged sample 
     */
    virtual void on_application_acknowledgment(
        dds::pub::DataWriter<T>& writer,
        const rti::pub::AcknowledgmentInfo& acknowledgment_info) = 0;

    /**
     * @brief @extension Called when a sample that has been received on a the 
     * built-in service channel is intended for the DataWriter that has 
     * installed this listener 
     *
     * @details \dref_details_DataWriterListener_on_service_request_accepted
     */
    virtual void on_service_request_accepted(
        dds::pub::DataWriter<T>& writer,
        const rti::core::status::ServiceRequestAcceptedStatus& status) = 0;
};

/**
 * @ingroup DDSWriterModule
 * @headerfile "dds/pub/DataWriterListener.hpp"
 * @brief A convenience implementation of DataWriterListener where all methods
 * are overridden to do nothing.
 *
 * Most of the types you can derive your listener from this class so you don't
 * have to implement the methods you don't need.
 */
template<typename T>
class NoOpDataWriterListener: public virtual DataWriterListener<T> {
public:
    virtual ~NoOpDataWriterListener()
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_offered_deadline_missed(
        dds::pub::DataWriter<T>&,
        const dds::core::status::OfferedDeadlineMissedStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_offered_incompatible_qos(
        dds::pub::DataWriter<T>&,
        const dds::core::status::OfferedIncompatibleQosStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_liveliness_lost(
        dds::pub::DataWriter<T>&,
        const dds::core::status::LivelinessLostStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_publication_matched(
        dds::pub::DataWriter<T>&,
        const dds::core::status::PublicationMatchedStatus&)
    {
    }

    // --- Extensions: --------------------------------------------------------

    /**
     * @brief @extension No-op
     */
    virtual void on_reliable_writer_cache_changed(
        dds::pub::DataWriter<T>&,
        const rti::core::status::ReliableWriterCacheChangedStatus&)
    {
    }

    /**
     * @brief @extension No-op
     */
    virtual void on_reliable_reader_activity_changed(
        dds::pub::DataWriter<T>&,
        const rti::core::status::ReliableReaderActivityChangedStatus&)
    {
    }

    /**
     * @brief @extension No-op
     */
    virtual void on_instance_replaced(
        dds::pub::DataWriter<T>&,
        const dds::core::InstanceHandle&)
    {
    }

    /**
     * @brief @extension No-op
     */
    virtual void on_application_acknowledgment(
        dds::pub::DataWriter<T>&,
        const rti::pub::AcknowledgmentInfo&)
    {
    }

    /**
     * @brief @extension No-op
     */
    virtual void on_service_request_accepted(
        dds::pub::DataWriter<T>&,
        const rti::core::status::ServiceRequestAcceptedStatus&)
    {
    }
};

} } // namespace dds::pub

#endif // OMG_DDS_PUB_DATA_WRITER_LISTENER_HPP_
