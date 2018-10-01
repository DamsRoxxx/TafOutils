#ifndef OMG_DDS_DOMAIN_DOMAINPARTICIPANT_LISTENER_HPP_
#define OMG_DDS_DOMAIN_DOMAINPARTICIPANT_LISTENER_HPP_

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

#include <dds/pub/PublisherListener.hpp>
#include <dds/sub/SubscriberListener.hpp>
#include <dds/topic/AnyTopicListener.hpp>

namespace dds { namespace domain {

/**
 * @brief The listener class for DomainParticipants 
 */
class DomainParticipantListener :
    public virtual dds::pub::PublisherListener,
    public virtual dds::sub::SubscriberListener,
    public virtual dds::topic::AnyTopicListener {
public:
    virtual ~DomainParticipantListener()
    {
    }
};

class NoOpDomainParticipantListener :
    public virtual DomainParticipantListener,
    public virtual dds::pub::NoOpPublisherListener,
    public virtual dds::sub::NoOpSubscriberListener,
    public virtual dds::topic::NoOpAnyTopicListener {
public:
    virtual ~NoOpDomainParticipantListener()
    {
    }

    // Re-define these listeners here to avoid warnings of inheritance via dominance

    // Publication listeners
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

    // Extension Publication listeners
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

    // Subscription listeners
    virtual void on_data_on_readers(dds::sub::Subscriber&)
    {
    }

    virtual void on_requested_deadline_missed(
        dds::sub::AnyDataReader&,
        const dds::core::status::RequestedDeadlineMissedStatus&)
    {
    }

    virtual void on_requested_incompatible_qos(
        dds::sub::AnyDataReader&,
        const dds::core::status::RequestedIncompatibleQosStatus&)
    {
    }

    virtual void on_sample_rejected(
        dds::sub::AnyDataReader&,
        const dds::core::status::SampleRejectedStatus&)
    {
    }

    virtual void on_liveliness_changed(
        dds::sub::AnyDataReader&,
        const dds::core::status::LivelinessChangedStatus&)
    {
    }

    virtual void on_data_available(dds::sub::AnyDataReader&)
    {
    }

    virtual void on_subscription_matched(
        dds::sub::AnyDataReader&,
        const dds::core::status::SubscriptionMatchedStatus&)
    {
    }

    virtual void on_sample_lost(
        dds::sub::AnyDataReader&,
        const dds::core::status::SampleLostStatus&)
    {
    }

    // Topic Listeners
    virtual void on_inconsistent_topic(
        dds::topic::AnyTopic&,
        const dds::core::status::InconsistentTopicStatus&)
    {
    }
};

} } // namespace dds::domain

#endif /* OMG_DDS_DOMAIN_DOMAINPARTICIPANT_LISTENER_HPP_ */
