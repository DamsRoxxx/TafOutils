/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,18mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_DETAIL_DATAREADER_LISTENER_FORWARDER_HPP_
#define RTI_DDS_SUB_DETAIL_DATAREADER_LISTENER_FORWARDER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/DataReaderListener.hpp>
#include <dds/sub/SubscriberListener.hpp>
#include <rti/core/detail/NativeEntity.hpp>

namespace rti { namespace sub { namespace detail {

template <typename READER, typename LISTENER>
class DataReaderListenerForwarder;

template <typename T>
DDS_DataReaderListener create_native_listener(
    dds::sub::DataReaderListener<T> * listener)
{
    typedef dds::sub::DataReader<T> reader_type;
    typedef dds::sub::DataReaderListener<T> listener_type;
    typedef DataReaderListenerForwarder<reader_type, listener_type>
        forwarder_type;

    DDS_DataReaderListener native_listener;

    native_listener.on_requested_deadline_missed =
        forwarder_type::requested_deadline_missed_forward;
    native_listener.on_requested_incompatible_qos =
        forwarder_type::requested_incompatible_qos_forward;
    native_listener.on_sample_rejected =
        forwarder_type::sample_rejected_forward;
    native_listener.on_liveliness_changed =
        forwarder_type::liveliness_changed_forward;
    native_listener.on_data_available =
        forwarder_type::data_available_forward;
    native_listener.on_subscription_matched =
        forwarder_type::subscription_matched_forward;
    native_listener.on_sample_lost =
        forwarder_type::sample_lost_forward;

    native_listener.as_listener.listener_data = listener;

    return native_listener;
}

// This class is templatized to reuse the same code for DataReaders and
// Subscribers
template <typename READER, typename LISTENER>
class DataReaderListenerForwarder {
private:

    // --- Friend functions: --------------------------------------------------

    template <typename T>
    friend DDS_DataReaderListener create_native_listener(
        dds::sub::DataReaderListener<T> * listener);
    friend DDS_SubscriberListener create_native_listener(
        dds::sub::SubscriberListener * listener);

    // --- Native listener callbacks: -----------------------------------------

    static void requested_deadline_missed_forward(
        void * listener_data,
        DDS_DataReader * native_reader,
        const struct DDS_RequestedDeadlineMissedStatus* native_status)
    {
        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            READER reader = rti::core::detail::get_from_native_entity<READER>(
                native_reader);
            if (reader == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::RequestedDeadlineMissedStatus status;
            status.delegate() = *native_status;
            listener->on_requested_deadline_missed(reader, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_requested_deadline_missed", 
                &RTI_LOG_ANY_FAILURE_s, 
                ex.what());
        } catch (...) {
        }
    }

    static void requested_incompatible_qos_forward(
        void* listener_data,
        DDS_DataReader * native_reader,
        const struct DDS_RequestedIncompatibleQosStatus * native_status)
    {
        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            READER reader = rti::core::detail::get_from_native_entity<READER>(
                native_reader);
            if (reader == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::RequestedIncompatibleQosStatus status;
            status.delegate() = *native_status;
            listener->on_requested_incompatible_qos(reader, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_requested_incompatible_qos", 
                &RTI_LOG_ANY_FAILURE_s, 
                ex.what());
        } catch (...) {
        }
    }

    static void sample_rejected_forward(
        void* listener_data,
        DDS_DataReader * native_reader,
        const struct DDS_SampleRejectedStatus * native_status)
    {
        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            READER reader = rti::core::detail::get_from_native_entity<READER>(
                native_reader);
            if (reader == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::SampleRejectedStatus status;
            status.delegate() = *native_status;
            listener->on_sample_rejected(reader, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_sample_rejected", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void liveliness_changed_forward(
        void* listener_data,
        DDS_DataReader * native_reader,
        const struct DDS_LivelinessChangedStatus* native_status)
    {
        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            READER reader = rti::core::detail::get_from_native_entity<READER>(
                native_reader);
            if (reader == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::LivelinessChangedStatus status;
            status.delegate() = *native_status;
            listener->on_liveliness_changed(reader, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_liveliness_changed", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void data_available_forward(
        void* listener_data,
        DDS_DataReader * native_reader)
    {
        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            READER reader = rti::core::detail::get_from_native_entity<READER>(
                native_reader);
            if (reader == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            listener->on_data_available(reader);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_data_available", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void subscription_matched_forward(
        void* listener_data,
        DDS_DataReader * native_reader,
        const struct DDS_SubscriptionMatchedStatus* native_status)
    {
        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            READER reader = rti::core::detail::get_from_native_entity<READER>(
                native_reader);
            if (reader == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::SubscriptionMatchedStatus status;
            status.delegate() = *native_status;
            listener->on_subscription_matched(reader, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_subscription_matched", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }

    static void sample_lost_forward(
        void* listener_data,
        DDS_DataReader * native_reader,
        const struct DDS_SampleLostStatus* native_status)
    {
        try {
            LISTENER * listener = static_cast<LISTENER *>(listener_data);

            RTI_CHECK_PRECONDITION(listener != NULL);
            READER reader = rti::core::detail::get_from_native_entity<READER>(
                native_reader);
            if (reader == dds::core::null) {
                return; // Don't call listener for entities that don't exist in C++
            }

            dds::core::status::SampleLostStatus status;
            status.delegate() = *native_status;
            listener->on_sample_lost(reader, status);
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "on_sample_lost", &RTI_LOG_ANY_FAILURE_s, ex.what());
        } catch (...) {
        }
    }
};


} } } // namespace rti::sub::detail

#endif // RTI_DDS_SUB_DETAIL_DATAREADER_LISTENER_FORWARDER_HPP_
