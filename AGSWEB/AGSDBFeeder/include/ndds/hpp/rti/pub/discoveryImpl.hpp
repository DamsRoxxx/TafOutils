/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,14mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_PUB_DISCOVERY_IMPL_HPP_
#define RTI_DDS_PUB_DISCOVERY_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/topic/BuiltinTopic.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/domain/domainfwd.hpp>
#include <rti/core/Locator.hpp>
#include <rti/pub/pubfwd.hpp>

namespace rti { namespace pub {

void ignore(
    dds::domain::DomainParticipant& participant,
    const dds::core::InstanceHandle& handle);

OMG_DDS_API
dds::core::InstanceHandleSeq matched_subscriptions(
    const UntypedDataWriter& writer);

OMG_DDS_API
dds::topic::SubscriptionBuiltinTopicData matched_subscription_data(
    const UntypedDataWriter& writer,
    const dds::core::InstanceHandle& handle);

// Extensions

OMG_DDS_API
dds::topic::ParticipantBuiltinTopicData matched_subscription_participant_data_impl(
    const UntypedDataWriter& writer,
    const dds::core::InstanceHandle& handle);

template <typename T>
dds::topic::ParticipantBuiltinTopicData matched_subscription_participant_data(
    const dds::pub::DataWriter<T>& writer,
    const dds::core::InstanceHandle& handle)
{
    return rti::pub::matched_subscription_participant_data_impl(
        *writer.delegate().get(), handle);
}

OMG_DDS_API
rti::core::LocatorSeq matched_subscriptions_locators_impl(
    const UntypedDataWriter& writer);

template<typename T>
rti::core::LocatorSeq matched_subscriptions_locators(
    const dds::pub::DataWriter<T>& writer)
{
    return rti::pub::matched_subscriptions_locators_impl(
        *writer.delegate().get());
}


} } // namespace rti::domain

#endif // RTI_DDS_PUB_DISCOVERY_IMPL_HPP_
