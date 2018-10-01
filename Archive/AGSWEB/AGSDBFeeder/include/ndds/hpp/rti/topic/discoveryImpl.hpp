/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.7a,03jun14,eam Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_DISCOVERY_IMPL_HPP_
#define RTI_DDS_TOPIC_DISCOVERY_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/InstanceHandle.hpp>
#include <dds/domain/DomainParticipant.hpp>

namespace dds { namespace topic {

template <typename Iterator>
int32_t discover_any_topic(
    const dds::domain::DomainParticipant& participant, 
    Iterator begin, int32_t max_size)
{
    DDS_InstanceHandleSeq native_handles = DDS_SEQUENCE_INITIALIZER;
    rti::core::detail::NativeSequenceAdapter<DDS_InstanceHandle_t> handles(
       native_handles);

    DDS_ReturnCode_t retcode = DDS_DomainParticipant_get_discovered_topics(
         const_cast<DDS_DomainParticipant*>(
            participant->native_participant()), &native_handles);
    rti::core::check_return_code(retcode, "get discovered topics");

    int32_t length = DDS_InstanceHandleSeq_get_length(&native_handles);

    // Figure out how many to copy
    int32_t size =
        (max_size == dds::core::LENGTH_UNLIMITED || length < max_size) ? 
        length : max_size;

    std::transform(
            native_handles._contiguous_buffer,
            native_handles._contiguous_buffer + size,
            begin,
            rti::core::native_conversions::from_native_handle);

    return size;
}

OMG_DDS_API
dds::topic::TopicBuiltinTopicData
discover_topic_data(
     const dds::domain::DomainParticipant& participant, 
     const dds::core::InstanceHandle& handle);

template <typename Iterator>
int32_t discover_topic_data(
    const dds::domain::DomainParticipant& participant, 
    Iterator begin,
    const dds::core::InstanceHandleSeq& handles)
{
    int32_t returned_size = 0;
    for (dds::core::InstanceHandleSeq::const_iterator it = handles.begin();
          it != handles.end(); it++) {

        *begin++ = 
            discover_topic_data(participant, *it);
        returned_size++;
    }

    return returned_size;
}

template <typename Iterator>
int32_t discover_topic_data(
     const dds::domain::DomainParticipant& participant, 
     Iterator begin, int32_t max_size)
{
    using namespace dds::core;
    InstanceHandleSeq handles;

    // Get handles of all discovered topics
    // Don't pass in max_size, because handles to local topics that
    // we can get topic data about might be left off of the returned shortened list 
    std::back_insert_iterator<InstanceHandleSeq> handle_it(handles);
    int32_t discovered_topics  = 
        discover_any_topic(participant, handle_it, LENGTH_UNLIMITED);

    // How many to get data about
    int32_t max_topics = max_size == LENGTH_UNLIMITED ?
        discovered_topics : max_size;

    // Now retrieve data for each handle
    int32_t size = 0;
    for (InstanceHandleSeq::const_iterator it = handles.begin();
          it != handles.end() && size < max_topics; it++) {
        try {
            // Don't increment 'begin' inline, the solaris
            // compiler will increment begin even if an exception is thrown
            *begin = discover_topic_data(participant, *it);
            begin++;
            size++;
        } catch (UnsupportedError&) {
            // Don't do anything with UnsupportedError it means we tried to 
            // retrieve data about a remote topic
        }
    }

    return size;
}

} } // namespace dds::topic

#endif // RTI_DDS_TOPIC_DISCOVERY_IMPL_HPP_
