#ifndef OMG_DDS_TOPIC_TOPIC_FWD_HPP_
#define OMG_DDS_TOPIC_TOPIC_FWD_HPP_

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

#include <dds/core/detail/conformance.hpp>
#include <dds/topic/detail/topicfwd.hpp>

namespace dds { namespace topic {

class AnyTopic;
class AnyTopicDescription;
class AnyTopicListener;

//typedef TBuiltinTopicKey<detail::BuiltinTopicKeyImpl> BuiltinTopicKey;

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
template <typename T,
          template <typename Q> class DELEGATE = detail::ContentFilteredTopicImpl>
class ContentFilteredTopic;
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

template <typename T>
struct is_topic_type;

#ifdef OMG_DDS_MULTI_TOPIC_SUPPORT
template <typename T,
          template <typename Q> class DELEGATE = detail::MultiTopic>
class MultiTopic;
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

class NoOpAnyTopicListener;

typedef dds::topic::detail::ParticipantBuiltinTopicData ParticipantBuiltinTopicData;
typedef dds::topic::detail::TopicBuiltinTopicData TopicBuiltinTopicData;
typedef dds::topic::detail::PublicationBuiltinTopicData PublicationBuiltinTopicData;
typedef dds::topic::detail::SubscriptionBuiltinTopicData SubscriptionBuiltinTopicData;

typedef dds::topic::detail::Filter Filter;

template <typename T,
          template <typename Q> class DELEGATE = detail::TopicImpl>
class Topic;


template <typename T,
          template <typename Q> class DELEGATE = detail::TopicDescriptionImpl>
class TopicDescription;

template <typename T>
class TopicInstance;

template <typename T>
class TopicListener;

template <typename T>
struct topic_type_support;

/*
namespace qos {
    typedef qos::detail::TopicQos TopicQos;
}
*/

} }

#endif /* OMG_DDS_TOPIC_TOPIC_FWD_HPP_ */
