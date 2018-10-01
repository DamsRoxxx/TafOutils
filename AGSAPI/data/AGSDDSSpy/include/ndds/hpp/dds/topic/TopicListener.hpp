#ifndef OMG_DDS_TOPIC_TOPIC_LISTENER_HPP_
#define OMG_DDS_TOPIC_TOPIC_LISTENER_HPP_

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

#include <dds/topic/topicfwd.hpp>
#include <dds/core/status/Status.hpp>

namespace dds { namespace topic {

/**
 * @ingroup DDSTopicModule
 * @headerfile dds/topic/TopicListener.hpp
 *
 * @brief The listener to notify status changes for a dds::topic::Topic
 *
 * @details \dref_details_TopicListener
 *
 * @see NoOpTopicListener
 */
template<typename T>
class TopicListener {
public:
    virtual ~TopicListener()
    {
    }

    /**
     * @brief Handles the dds::core::status::InconsistentTopicStatus status
     *
     * @details \dref_details_TopicListener_on_inconsistent_topic
     */
    virtual void on_inconsistent_topic(
        Topic<T>& topic,
        const dds::core::status::InconsistentTopicStatus& status) = 0;
};

/**
 * @ingroup DDSTopicModule
 * @headerfile dds/topic/TopicListener.hpp
 *
 * @brief A convenience implementation of TopicListener where all methods
 * are overridden to do nothing.
 */
template<typename T>
class NoOpTopicListener: public virtual TopicListener<T> {
public:
    virtual ~NoOpTopicListener()
    {
    }

    /**
     * @brief No-op
     */
    virtual void on_inconsistent_topic(
        Topic<T>&,
        const dds::core::status::InconsistentTopicStatus&)
    {
    }
};

} }

#endif /* OMG_DDS_TOPIC_TOPIC_LISTENER_HPP_ */
