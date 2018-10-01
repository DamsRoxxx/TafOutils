#ifndef OMG_DDS_CORE_STATUS_STATUS_HPP_
#define OMG_DDS_CORE_STATUS_STATUS_HPP_

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

#include <dds/core/status/detail/Status.hpp>
#include <dds/core/status/State.hpp>

namespace dds { namespace core { namespace status {

typedef dds::core::status::detail::InconsistentTopicStatus
    InconsistentTopicStatus;

typedef dds::core::status::detail::OfferedDeadlineMissedStatus
    OfferedDeadlineMissedStatus;

typedef dds::core::status::detail::RequestedDeadlineMissedStatus
    RequestedDeadlineMissedStatus;

typedef dds::core::status::detail::OfferedIncompatibleQosStatus
    OfferedIncompatibleQosStatus;

typedef dds::core::status::detail::RequestedIncompatibleQosStatus
    RequestedIncompatibleQosStatus;

typedef dds::core::status::detail::SampleLostStatus
    SampleLostStatus;

typedef dds::core::status::detail::SampleRejectedStatus
    SampleRejectedStatus;

class DataOnReadersStatus {
    // empty -- defined to allow specialization of get_status<>
};

class DataAvailableStatus {
    // empty -- defined to allow specialization of get_status<>
};

typedef dds::core::status::detail::LivelinessLostStatus
    LivelinessLostStatus;

typedef dds::core::status::detail::LivelinessChangedStatus
    LivelinessChangedStatus;

typedef dds::core::status::detail::PublicationMatchedStatus
    PublicationMatchedStatus;

typedef dds::core::status::detail::SubscriptionMatchedStatus
    SubscriptionMatchedStatus;

// --- get_status ------------------------------------------------------------

/**
 * @relatesalso StatusMask
 * @brief Obtains the StatusMask mask associated to a status class.
 *
 * For example:
 *
 * \code
 * using namespace dds::core::status;
 *
 * StatusMask mask = get_status<PublicationMatchedStatus>();
 * assert(mask == StatusMask::publication_matched());
 * \endcode
 *
 */
template <typename STATUS>
StatusMask get_status();

template <>
inline StatusMask get_status<InconsistentTopicStatus>()
{
    return StatusMask::inconsistent_topic();
}

template <>
inline StatusMask get_status<OfferedDeadlineMissedStatus>()
{
    return StatusMask::offered_deadline_missed();
}

template <>
inline StatusMask get_status<RequestedDeadlineMissedStatus>()
{
    return StatusMask::requested_deadline_missed();
}

template <>
inline StatusMask get_status<OfferedIncompatibleQosStatus>()
{
    return StatusMask::offered_incompatible_qos();
}

template <>
inline StatusMask get_status<RequestedIncompatibleQosStatus>()
{
    return StatusMask::requested_incompatible_qos();
}

template <>
inline StatusMask get_status<SampleLostStatus>()
{
    return StatusMask::sample_lost();
}

template <>
inline StatusMask get_status<SampleRejectedStatus>()
{
    return StatusMask::sample_rejected();
}


template <>
inline StatusMask get_status<DataOnReadersStatus>()
{
    return StatusMask::data_on_readers();
}

template <>
inline StatusMask get_status<DataAvailableStatus>()
{
    return StatusMask::data_available();
}

template <>
inline StatusMask get_status<LivelinessLostStatus>()
{
    return StatusMask::liveliness_lost();
}

template <>
inline StatusMask get_status<LivelinessChangedStatus>()
{
    return StatusMask::liveliness_changed();
}

template <>
inline StatusMask get_status<PublicationMatchedStatus>()
{
    return StatusMask::publication_matched();
}

template <>
inline StatusMask get_status<SubscriptionMatchedStatus>()
{
    return StatusMask::subscription_matched();
}

} } }

#endif /* OMG_DDS_CORE_STATUS_STATUS_HPP_ */
