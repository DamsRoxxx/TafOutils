#ifndef OMG_DDS_SUB_DATA_READER_LISTENER_HPP_
#define OMG_DDS_SUB_DATA_READER_LISTENER_HPP_

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

#include <dds/core/status/Status.hpp>

// Spec issue: missing fwd declaration of DataReader
// To avoid circular dependencies, it should be a forward declaration only.
#include <dds/sub/subfwd.hpp>

namespace dds { namespace sub {
  template <typename T>
  class DataReaderListener;

  template <typename T>
  class NoOpDataReaderListener;
} }

/**
 * @ingroup DDSReaderModule
 * @headerfile dds/sub/DataReaderListener.hpp
 *
 * @brief The Listener to notify status changes for a dds::sub::DataReader
 *
 * @details \dref_details_DataReaderListener
 *
 * @see NoOpDataReaderListener
 */
template<typename T>
class dds::sub::DataReaderListener {
public:
    virtual ~DataReaderListener()
    {
    }

    /**
     * @brief Handles the dds::core::status::RequestedDeadlineMissedStatus status
     *
     * @details \dref_details_DataReaderListener_on_requested_deadline_missed
     */
    virtual void on_requested_deadline_missed(
        DataReader<T>& reader,
        const dds::core::status::RequestedDeadlineMissedStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::RequestedIncompatibleQosStatus status
     *
     * @details \dref_details_DataReaderListener_on_requested_incompatible_qos
     */
    virtual void on_requested_incompatible_qos(
        DataReader<T>& reader,
        const dds::core::status::RequestedIncompatibleQosStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::SampleRejectedStatus status
     *
     * @details \dref_details_DataReaderListener_on_sample_rejected
     */
    virtual void on_sample_rejected(
        DataReader<T>& reader,
        const dds::core::status::SampleRejectedStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::LivelinessChangedStatus status
     *
     * @details \dref_details_DataReaderListener_on_liveliness_changed
     */
    virtual void on_liveliness_changed(
        DataReader<T>& reader,
        const dds::core::status::LivelinessChangedStatus& status) = 0;

    /**
     * @brief Called when one or more new data samples have been received.
     *
     * @details \dref_details_DataReaderListener_on_data_available
     */
    virtual void on_data_available(DataReader<T>& reader) = 0;

    /**
     * @brief Handles the dds::core::status::SubscriptionMatchedStatus status
     *
     * @details \dref_details_DataReaderListener_on_subscription_matched
     */
    virtual void on_subscription_matched(
        DataReader<T>& reader,
        const dds::core::status::SubscriptionMatchedStatus& status) = 0;

    /**
     * @brief Handles the dds::core::status::SampleLostStatus status
     *
     * @details \dref_details_DataReaderListener_on_sample_lost
     */
    virtual void on_sample_lost(
        DataReader<T>& reader,
        const dds::core::status::SampleLostStatus& status) = 0;
};

/**
 * @ingroup DDSReaderModule
 * @headerfile "dds/sub/DataReaderListener.hpp"
 * @brief A convenience implementation of DataReaderListener where all methods
 * are overridden to do nothing.
 *
 * Most of the types you can derive your listener from this class so you don't
 * have to implement the methods you don't need.
 */
template<typename T>
class dds::sub::NoOpDataReaderListener: public virtual DataReaderListener<T> {
public:
    virtual ~NoOpDataReaderListener()
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_requested_deadline_missed(
        DataReader<T>&,
        const dds::core::status::RequestedDeadlineMissedStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_requested_incompatible_qos(
        DataReader<T>&,
        const dds::core::status::RequestedIncompatibleQosStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_sample_rejected(
        DataReader<T>&,
        const dds::core::status::SampleRejectedStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_liveliness_changed(
        DataReader<T>&,
        const dds::core::status::LivelinessChangedStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_data_available(DataReader<T>&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_subscription_matched(
        DataReader<T>&,
        const dds::core::status::SubscriptionMatchedStatus&)
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_sample_lost(
        DataReader<T>&,
        const dds::core::status::SampleLostStatus&)
    {
    }
};

#endif /* OMG_DDS_SUB_DATA_READER_LISTENER_HPP_ */
