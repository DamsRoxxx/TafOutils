/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,12feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_PUB_PUBLISHER_HPP_
#define RTI_DDS_PUB_PUBLISHER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/pub/qos/PublisherQos.hpp>
#include <dds/pub/qos/DataWriterQos.hpp>
#include <rti/core/Entity.hpp>

#include "ndds/ndds_c.h"

namespace rti { namespace pub {

/**
 * @RTI_class_definition NA
 */
class OMG_DDS_API PublisherImpl : public rti::core::Entity {
public:

    PublisherImpl(const dds::domain::DomainParticipant& participant);

    PublisherImpl(
        const dds::domain::DomainParticipant& participant,
        const dds::pub::qos::PublisherQos& qos,
        dds::pub::PublisherListener* listener = NULL,
        const dds::core::status::StatusMask& mask = dds::core::status::StatusMask::all());

    // For internal use
    PublisherImpl(DDS_Publisher * native_object);

    ~PublisherImpl();

    void listener(
        dds::pub::PublisherListener * the_listener,
        const ::dds::core::status::StatusMask& event_mask);
    dds::pub::PublisherListener * listener() const;


    const dds::pub::qos::PublisherQos qos() const;
    void qos(const dds::pub::qos::PublisherQos& the_qos);

    dds::pub::qos::DataWriterQos default_writer_qos();
    PublisherImpl& default_writer_qos(const dds::pub::qos::DataWriterQos& qos);

    void wait_for_acknowledgments(const dds::core::Duration& max_wait);

    // Extension
    /**
     * @memberof dds::pub::Publisher
     *
     * \dref_Publisher_wait_for_asynchronous_publishing
     */
    void wait_for_asynchronous_publishing(const dds::core::Duration& max_wait);

    const dds::domain::DomainParticipant& participant() const;

    void close_contained_entities();

    // --- From Entity: -------------------------------------------------------
    void close();

    // --- For internal use: --------------------------------------------------
    DDS_Publisher * native_publisher()
    {
        return (DDS_Publisher *) native_entity();
    }

    const DDS_Publisher * native_publisher() const
    {
        return (const DDS_Publisher *) native_entity();
    }

private:
    dds::domain::DomainParticipant participant_;
};

} }

#endif // RTI_DDS_PUB_PUBLISHER_HPP_
