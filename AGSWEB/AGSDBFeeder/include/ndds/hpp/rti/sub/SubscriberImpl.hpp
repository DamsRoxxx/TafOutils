/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,15mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_SUBSCRIBER_HPP_
#define RTI_DDS_SUB_SUBSCRIBER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/ref_traits.hpp>
#include <dds/domain/domainfwd.hpp>
#include <dds/sub/subfwd.hpp>

#include <rti/core/Entity.hpp>

#include "ndds/ndds_c.h"

namespace rti { namespace sub {

class OMG_DDS_API SubscriberImpl : public rti::core::Entity {
public:

    SubscriberImpl(const dds::domain::DomainParticipant& participant);

    SubscriberImpl(
        const dds::domain::DomainParticipant& participant,
        const dds::sub::qos::SubscriberQos& qos,
        dds::sub::SubscriberListener* listener = NULL,
        const dds::core::status::StatusMask& mask = dds::core::status::StatusMask::all());

    // For internal use
    SubscriberImpl(DDS_Subscriber * native_object);

    ~SubscriberImpl();

    void notify_datareaders();

    void listener(
        dds::sub::SubscriberListener * the_listener,
        const ::dds::core::status::StatusMask& event_mask);
    dds::sub::SubscriberListener * listener() const;


    const dds::sub::qos::SubscriberQos qos() const;
    void qos(const dds::sub::qos::SubscriberQos& the_qos);

    dds::sub::qos::DataReaderQos default_datareader_qos();
    SubscriberImpl& default_datareader_qos(const dds::sub::qos::DataReaderQos& qos);

    const dds::domain::DomainParticipant& participant() const;

    void close_contained_entities();

    // --- From Entity: -------------------------------------------------------
    void close();

    // --- For internal use: --------------------------------------------------
    DDS_Subscriber * native_subscriber()
    {
        return (DDS_Subscriber *) native_entity();
    }

    const DDS_Subscriber * native_subscriber() const
    {
        return (const DDS_Subscriber *) native_entity();
    }

private:
    dds::domain::DomainParticipant participant_;
};

} }

#endif // RTI_DDS_SUB_SUBSCRIBER_HPP_
