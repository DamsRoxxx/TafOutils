#ifndef OMG_DDS_PUB_PUBLISHER_LISTENER_HPP_
#define OMG_DDS_PUB_PUBLISHER_LISTENER_HPP_

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

#include <dds/pub/AnyDataWriterListener.hpp>

namespace dds {
  namespace pub {
    class PublisherListener;
    class NoOpPublisherListener;
  }
}

/**
 * @ingroup DDSPublisherModule
 * @headerfile dds/pub/PublisherListener.hpp
 *
 * @brief The listener to notify status changes for a dds::pub::Publisher
 *
 * A PublisherListener contains exactly the same methods as a
 * AnyDataWriterListener, since it can receive status changes from any of
 * its contained DataWriters.
 *
 * @details \dref_details_PublisherListener
 *
 * @see NoOpPublisherListener
 */
class dds::pub::PublisherListener :
    public virtual dds::pub::AnyDataWriterListener {
public:
    virtual ~PublisherListener()
    {
    }
};

class dds::pub::NoOpPublisherListener :
    public virtual dds::pub::PublisherListener,
    public virtual dds::pub::NoOpAnyDataWriterListener {
public:
    virtual ~NoOpPublisherListener()
    {
    }

    // Re-define these listeners here to avoid warnings of inheritance 
    // via dominance
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

    // Extensions
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



#endif /* OMG_DDS_PUB_PUBLISHER_LISTENER_HPP_ */
