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

#ifndef RTI_DDS_PUB_DETAIL_DATAWRITER_LISTENER_FORWARDER_HPP_
#define RTI_DDS_PUB_DETAIL_DATAWRITER_LISTENER_FORWARDER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/pub/Publisher.hpp>
#include <dds/pub/DataWriterListener.hpp>
#include <dds/pub/PublisherListener.hpp>
#include <rti/core/detail/NativeEntity.hpp> // for create_from_native_entity
#include <rti/pub/AcknowledgmentInfo.hpp>

namespace rti { namespace pub { namespace detail {

template <typename T>
DDS_DataWriterListener create_native_listener(
    dds::pub::DataWriterListener<T> * listener);

// This class is templatized to reuse the same code for DataWriters and
// Publishers
template <typename WRITER, typename LISTENER>
class DataWriterListenerForwarder {
protected:

    // --- Friend functions: --------------------------------------------------

    template <typename T>
    friend DDS_DataWriterListener create_native_listener(
        dds::pub::DataWriterListener<T> * listener);

    // --- Native listener callbacks: -----------------------------------------

    static void offered_deadline_missed_forward(
        void * listener_data,
        DDS_DataWriter * native_writer,
        const struct DDS_OfferedDeadlineMissedStatus* native_status)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(native_status != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::OfferedDeadlineMissedStatus status;
            status.delegate() = *native_status;
            listener->on_offered_deadline_missed(writer, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "offered_deadline_missed", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void liveliness_lost_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const struct DDS_LivelinessLostStatus* native_status)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(native_status != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::LivelinessLostStatus status;
            status.delegate() = *native_status;
            listener->on_liveliness_lost(writer, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "liveliness_lost", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void offered_incompatible_qos_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const struct DDS_OfferedIncompatibleQosStatus* native_status)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(native_status != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::OfferedIncompatibleQosStatus status;
            status.delegate() = *native_status;
            listener->on_offered_incompatible_qos(writer, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "offered_incompatible_qos", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void publication_matched_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const struct DDS_PublicationMatchedStatus* native_status)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(native_status != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::PublicationMatchedStatus status;
            status.delegate() = *native_status;
            listener->on_publication_matched(writer, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_publication_matched", 
                &RTI_LOG_ANY_FAILURE_s, 
                ex.what());
        } catch (...) {
        }
    }

    static void reliable_writer_cache_changed_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const struct DDS_ReliableWriterCacheChangedStatus* native_status)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(native_status != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            listener->on_reliable_writer_cache_changed(
                writer,
                rti::core::status::ReliableWriterCacheChangedStatus(*native_status));
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_reliable_writer_cache_changed", 
                &RTI_LOG_ANY_FAILURE_s, 
                ex.what());
        } catch (...) {
        }
    }

    static void reliable_reader_activity_changed_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const struct DDS_ReliableReaderActivityChangedStatus* native_status)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(native_status != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            listener->on_reliable_reader_activity_changed(
                writer,
                rti::core::status::ReliableReaderActivityChangedStatus(*native_status));
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_reliable_reader_activity_changed", 
                &RTI_LOG_ANY_FAILURE_s, 
                ex.what());
        } catch (...) {
        }
    }

    static void instance_replaced_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const DDS_InstanceHandle_t *handle)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(handle != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            listener->on_instance_replaced(
                writer,
                dds::core::InstanceHandle(*handle));
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_instance_replaced", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void application_acknowledgment_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const DDS_AcknowledgmentInfo * ack_info)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(ack_info != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            listener->on_application_acknowledgment(writer, *ack_info);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_application_acknowledgment", 
                &RTI_LOG_ANY_FAILURE_s, 
                ex.what());
        } catch (...) {
        }
    }

    static void service_request_accepted_forward(
        void* listener_data,
        DDS_DataWriter * native_writer,
        const struct DDS_ServiceRequestAcceptedStatus * native_status)
    {
        using namespace dds::pub;

        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            RTI_CHECK_PRECONDITION(native_status != NULL);
            WRITER writer = rti::core::detail::get_from_native_entity<WRITER>(
                native_writer);
            if (writer == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            listener->on_service_request_accepted(
                writer, 
                rti::core::status::ServiceRequestAcceptedStatus(*native_status));
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_service_request_accepted",
                &RTI_LOG_ANY_FAILURE_s, 
                ex.what());
        } catch (...) {
        }
    }
};

template <typename T>
DDS_DataWriterListener create_native_listener(
    dds::pub::DataWriterListener<T> * listener)
{
    typedef dds::pub::DataWriter<T> writer_type;
    typedef dds::pub::DataWriterListener<T> listener_type;
    typedef DataWriterListenerForwarder<writer_type, listener_type>
        forwarder_type;

    DDS_DataWriterListener native_listener;

    native_listener.on_offered_deadline_missed =
        forwarder_type::offered_deadline_missed_forward;
    native_listener.on_liveliness_lost =
        forwarder_type::liveliness_lost_forward;
    native_listener.on_offered_incompatible_qos =
        forwarder_type::offered_incompatible_qos_forward;
    native_listener.on_publication_matched =
        forwarder_type::publication_matched_forward;
    native_listener.on_reliable_writer_cache_changed =
        forwarder_type::reliable_writer_cache_changed_forward;
    native_listener.on_reliable_reader_activity_changed =
        forwarder_type::reliable_reader_activity_changed_forward;
    native_listener.on_instance_replaced =
        forwarder_type::instance_replaced_forward;
    native_listener.on_application_acknowledgment =
        forwarder_type::application_acknowledgment_forward;
    native_listener.on_service_request_accepted =
        forwarder_type::service_request_accepted_forward;

    native_listener.as_listener.listener_data = listener;

    return native_listener;
}


} } } // namespace rti::pub::detail

#endif // RTI_DDS_PUB_DETAIL_DATAWRITER_LISTENER_FORWARDER_HPP_
