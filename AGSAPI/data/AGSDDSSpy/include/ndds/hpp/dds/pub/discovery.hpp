#ifndef OMG_DDS_PUB_DISCOVERY_HPP_
#define OMG_DDS_PUB_DISCOVERY_HPP_

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

// Spec error: this file was missing all includes
#include <rti/pub/discoveryImpl.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/topic/BuiltinTopic.hpp>

namespace dds { namespace pub {

/**
 * @relatesalso dds::pub::DataWriter
 * @headerfile dds/pub/discovery.hpp
 *
 * @brief Instructs \ndds to locally ignore a publication. 
 *  
 * \dref_details_DomainParticipant_ignore_publication 
 */
// Spec error: participant was const but shouldn't
OMG_DDS_API
void ignore(
    dds::domain::DomainParticipant& participant,
    const dds::core::InstanceHandle& handle);

/**
 * @relatesalso dds::pub::DataWriter
 * @headerfile dds/pub/discovery.hpp
 *
 * @brief Instructs \ndds to locally ignore several publications.
 *
 * @tparam FwdIterator A forward iterator whose value type is
 * dds::core::InstanceHandle
 *  
 * @see ignore(dds::domain::DomainParticipant&, const dds::core::InstanceHandle&);
 */
template<typename FwdIterator>
void ignore(
    dds::domain::DomainParticipant& participant,
    FwdIterator begin,
    FwdIterator end)
{
    for (; begin != end; ++begin) {
        ignore(participant, *begin);
    }
}

/**
 * @relatesalso dds::pub::DataWriter
 * @headerfile dds/pub/discovery.hpp
 *
 * @brief Retrieve the list of subscriptions currently associated with a
 * dds::pub::DataWriter
 *
 * @details \dref_details_DataWriter_get_matched_subscriptions
 */
template<typename T>
dds::core::InstanceHandleSeq matched_subscriptions(
    const dds::pub::DataWriter<T>& writer)
{
    return rti::pub::matched_subscriptions(*writer.delegate().get());
}

/**
 * @relatesalso dds::pub::DataWriter
 * @headerfile dds/pub/discovery.hpp
 *
 * @brief Retrieve the list of subscriptions currently associated with a
 * dds::pub::DataWriter.
 *
 * This operation is similar to matched_subscriptions(const dds::pub::DataWriter<T>&)
 * but it copies the instance handles into an iterator range.
 *
 * @tparam FwdIterator A forward iterator whose value type is
 * dds::core::InstanceHandle
 */
template<typename T, typename FwdIterator>
FwdIterator matched_subscriptions(
    const dds::pub::DataWriter<T>& writer,
    FwdIterator begin,
    FwdIterator end)
{
    dds::core::InstanceHandleSeq subscriptions = matched_subscriptions(writer);

    for (dds::core::InstanceHandleSeq::const_iterator it = subscriptions.begin();
        begin != end && it != subscriptions.end();
        ++begin, ++it) {

        *begin = *it;
    }

    return begin;
}

/**
 * @relatesalso dds::pub::DataWriter
 * @headerfile dds/pub/discovery.hpp
 *
 * @brief Retrieves information on a subscription that is currently associated
 * with a dds::pub::DataWriter
 *
 * @details \dref_details_DataWriter_get_matched_subscription_data
 */
template<typename T>
const dds::topic::SubscriptionBuiltinTopicData matched_subscription_data(
    const dds::pub::DataWriter<T>& writer,
    const dds::core::InstanceHandle& subscription_handle)
{
    return rti::pub::matched_subscription_data(
        *writer.delegate().get(), subscription_handle);
}

} } // namespace dds::pub

#endif // OMG_DDS_PUB_DISCOVERY_HPP_
