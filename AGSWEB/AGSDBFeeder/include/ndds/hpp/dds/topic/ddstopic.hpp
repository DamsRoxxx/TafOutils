#ifndef OMG_DDS_TOPIC_PACKAGE_INCLUDE_HPP_
#define OMG_DDS_TOPIC_PACKAGE_INCLUDE_HPP_

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

/////////////////////////////////////////////////////////////////////////////
// -- QoS Includes
#include <dds/topic/qos/TopicQos.hpp>

/////////////////////////////////////////////////////////////////////////////
// -- Topic Includes

#include <dds/topic/Filter.hpp>

#include <dds/topic/TopicInstance.hpp>

#include <dds/topic/TopicDescription.hpp>

#include <dds/topic/TopicTraits.hpp>

/*
 * Depends on:
 *  <dds/topic/qos/TopicQos.hpp>
 *  <dds/topic/TopicDescription.hpp>
 *  <dds/topic/TopicTraits.hpp>
 */
#include <dds/topic/Topic.hpp>

/*
 * Depends on:
 *  <dds/topic/Topic.hpp>
 */
#include <dds/topic/TopicListener.hpp>

#include <dds/topic/AnyTopic.hpp>

/*
 * Depends on:
 *  <dds/topic/TopicDescription.hpp>
 */
#include <dds/topic/AnyTopicDescription.hpp>

/*
 * Depends on:
 *  <dds/topic/AnyTopic.hpp>
 */
#include <dds/topic/AnyTopicListener.hpp>

/*
 * Depends on:
 *  <dds/topic/Filter.hpp>
 *  <dds/topic/Topic.hpp>
 */
#include <dds/topic/ContentFilteredTopic.hpp>

#include <dds/topic/BuiltinTopicKey.hpp>

/*
 * Depends on:
 *  <dds/topic/TopicTraits.hpp>
 *  <dds/topic/BuiltinTopicKey.hpp>
 */
#include <dds/topic/BuiltinTopic.hpp>

/*
 * Depends on:
 *  <dds/topic/TopicDescription.hpp>
 */
// #include <dds/topic/MultiTopic.hpp>

/*
 * Depends on:
 *  <dds/topic/Topic.hpp>
 */
#include <dds/topic/find.hpp>

/*
 * Depends on:
 *  <dds/topic/BuiltinTopic.hpp>
 */
#include <dds/topic/discovery.hpp>

// using namespace dds::topic::all will include all topic sub-namespaces
namespace dds {

/**
 * @brief Contains topic related classes and functions, the built-in topics
 * and topic traits used by IDL-generated types.
 */
namespace topic {

namespace all {

using namespace dds::topic;
using namespace dds::topic::qos;

} // namespace all

/**
 * @brief Contains TopicQos
 */
namespace qos {}

} // namespace topic

} // namespace dds

#endif /* OMG_DDS_TOPIC_PACKAGE_INCLUDE_HPP_ */
