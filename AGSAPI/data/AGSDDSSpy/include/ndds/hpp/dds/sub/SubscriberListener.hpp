#ifndef OMG_DDS_SUB_SUBSCRIBER_LISTENER_HPP_
#define OMG_DDS_SUB_SUBSCRIBER_LISTENER_HPP_

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

#include <dds/sub/AnyDataReaderListener.hpp>
#include <dds/sub/subfwd.hpp>

namespace dds { namespace sub {

/**
 * @ingroup DDSSubscriberModule
 * @headerfile dds/sub/SubscriberListener.hpp
 *
 * @brief The listener to notify status changes for a dds::sub::Subscriber
 *
 * A SubscriberListener contains exactly the same methods as a
 * AnyDataReaderListener, since it can receive status changes from any of
 * its contained DataReaders.
 *
 * @details \dref_details_SubscriberListener
 *
 * @see NoOpSubscriberListener
 */
class SubscriberListener: public virtual AnyDataReaderListener {
public:
    virtual ~SubscriberListener()
    {
    }

    virtual void on_data_on_readers(Subscriber& sub) = 0;
};

class NoOpSubscriberListener :
    public virtual SubscriberListener,
    public virtual NoOpAnyDataReaderListener {
public:
    virtual ~NoOpSubscriberListener()
    {
    }

    virtual void on_data_on_readers(Subscriber&)
    {
    }

    // Re-define these listeners here to avoid warnings of inheritance via dominance
    virtual void on_requested_deadline_missed(
        AnyDataReader&,
        const dds::core::status::RequestedDeadlineMissedStatus&)
    {
    }

    virtual void on_requested_incompatible_qos(
        AnyDataReader&,
        const dds::core::status::RequestedIncompatibleQosStatus&)
    {
    }

    virtual void on_sample_rejected(
        AnyDataReader&,
        const dds::core::status::SampleRejectedStatus&)
    {
    }

    virtual void on_liveliness_changed(
        AnyDataReader&,
        const dds::core::status::LivelinessChangedStatus&)
    {
    }

    virtual void on_data_available(AnyDataReader&)
    {
    }

    virtual void on_subscription_matched(
        AnyDataReader&,
        const dds::core::status::SubscriptionMatchedStatus&)
    {
    }

    virtual void on_sample_lost(
        AnyDataReader&,
        const dds::core::status::SampleLostStatus&)
    {
    }
};

} } // namespace dds::sub

#endif /* OMG_DDS_SUB_SUBSCRIBER_LISTENER_HPP_ */
