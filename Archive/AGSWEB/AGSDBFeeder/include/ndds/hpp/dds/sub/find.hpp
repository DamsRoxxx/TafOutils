#ifndef OMG_DDS_SUB_FIND_HPP_
#define OMG_DDS_SUB_FIND_HPP_

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

#include <string>
#include <vector>


// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/sub/detail/find.hpp>


namespace dds { namespace sub {

// Spec issue CPPPSM-219: was returning a const reference, but this
// assumes that the DomainParticipant is storing the subscriber 
/** 
 * @relatesalso Subscriber 
 * @brief Access the built-in Subscriber
 * \dref_details_DomainParticipant_get_builtin_subscriber 
 * @param dp The DomainParticipant that the built-in subscriber belongs to.
 */
OMG_DDS_API
dds::sub::Subscriber builtin_subscriber(
    const dds::domain::DomainParticipant& dp);

template<typename READER, typename FwdIterator>
uint32_t find(
    const dds::sub::Subscriber& sub,
    const std::string& topic_name,
    FwdIterator begin,
    uint32_t max_size);

template<typename READER, typename BinIterator>
uint32_t find(
    const dds::sub::Subscriber& sub,
    const std::string& topic_name,
    BinIterator begin);

template<typename READER, typename T, typename FwdIterator>
uint32_t find(
    const dds::sub::Subscriber& sub,
    const dds::topic::TopicDescription<T>& topic_description,
    FwdIterator begin,
    uint32_t max_size);

template<typename READER, typename T, typename BinIterator>
uint32_t find(
    const dds::sub::Subscriber& sub,
    const dds::topic::TopicDescription<T>& topic_description,
    BinIterator begin);

template<typename READER, typename FwdIterator>
uint32_t find(
    const dds::sub::Subscriber& sub,
    const dds::sub::status::DataState& rs,
    FwdIterator begin,
    uint32_t max_size);

template<typename READER, typename BinIterator>
uint32_t find(
    const dds::sub::Subscriber& sub,
    const dds::sub::status::DataState& rs,
    BinIterator begin);

} }

#endif /* OMG_DDS_SUB_FIND_HPP_ */
