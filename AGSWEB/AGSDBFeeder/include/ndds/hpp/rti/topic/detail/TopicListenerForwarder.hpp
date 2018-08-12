/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,12feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_DETAIL_TOPIC_LISTENER_FORWARDER_HPP_
#define RTI_DDS_TOPIC_DETAIL_TOPIC_LISTENER_FORWARDER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/topic/TopicListener.hpp>

namespace rti { namespace topic { namespace detail {

template <typename TOPIC, typename LISTENER>
class TopicListenerForwarder;

template <typename T>
DDS_TopicListener create_native_listener(
    dds::topic::TopicListener<T> * listener)
{
    DDS_TopicListener native_listener;

    typedef dds::topic::Topic<T> Topic;
    typedef dds::topic::TopicListener<T> Listener;
    typedef TopicListenerForwarder<Topic, Listener> ListenerForwarder;

    native_listener.on_inconsistent_topic =
        ListenerForwarder::inconsistent_topic_forward;

    native_listener.as_listener.listener_data = listener;

    return native_listener;
}

// This class is templatized to reuse the same code for Topics and
// Publishers
template <typename TOPIC, typename LISTENER>
class TopicListenerForwarder {
protected:
    typedef TOPIC Topic;
    typedef LISTENER Listener;

    // --- Friend functions: --------------------------------------------------

    template <typename U>
    friend DDS_TopicListener create_native_listener(
        dds::topic::TopicListener<U> * listener);

    // --- Native listener callbacks: -----------------------------------------

    static void inconsistent_topic_forward(
        void * listener_data,
        DDS_Topic * native_topic,
        const struct DDS_InconsistentTopicStatus* native_status)
    {
        try {
            using namespace dds::topic;

            Listener * listener = static_cast<Listener *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            TOPIC topic = rti::core::detail::create_from_native_entity<TOPIC>(
                native_topic);
            if (topic == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::InconsistentTopicStatus status;
            status.delegate() = *native_status;
            listener->on_inconsistent_topic(topic, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_inconsistent_topic", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }
};

} } } // namespace rti::topic::detail

#endif // RTI_DDS_TOPIC_DETAIL_TOPIC_LISTENER_FORWARDER_HPP_
