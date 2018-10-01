#ifndef OMG_DDS_TOPIC_FIND_HPP_
#define OMG_DDS_TOPIC_FIND_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Inc.
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

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/topic/detail/find.hpp>

namespace dds { namespace topic {

/**
 * @relatesalso dds::topic::Topic
 * @brief Looks up a Topic from a DomainParticipant
 *
 * @tparam TOPIC The topic, for example \p dds::topic::Topic<Foo>.
 * @param participant The DomainParticipant that contains the Topic
 * @param topic_name The topic name
 * @return A reference to an existing Topic in this participant or an empty
 * reference (i.e. equals to dds::core::null) if it doesn't exist.
 *
 * @throw dds::core::InvalidDowncastError If the concrete type of the topic
 * description identified by \p topic_name is not \p TOPIC.
 *
 * The participant doesn't need to be enabled. The returned topic may be
 * enabled or disabled.
 *
 * @warning This function currently only supports looking up a Topic, not
 * a TopicDescription, ContentFilteredTopic or AnyTopic.
 */
template<typename TOPIC>
TOPIC find(
    const dds::domain::DomainParticipant& participant,
    const std::string& topic_name)
{
    return rti::topic::detail::topic_find<TOPIC>::find(participant, topic_name);
}

} }

#endif /* OMG_DDS_TOPIC_FIND_HPP_ */
