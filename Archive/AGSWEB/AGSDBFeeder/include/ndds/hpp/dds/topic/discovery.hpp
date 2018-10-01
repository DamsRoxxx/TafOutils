#ifndef OMG_DDS_TOPIC_DISCOVER_HPP_
#define OMG_DDS_TOPIC_DISCOVER_HPP_

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

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/domain/DomainParticipant.hpp>
#include <rti/topic/discoveryImpl.hpp>

// Spec Issue CPPPSM-218: API changes in this file
namespace dds { namespace topic {


  // Spec error: made max_size signed because LENGTH_UNLIMITED is -1
  /**
   * @relatesalso dds::topic::Topic
   *
   * @brief Retrieves the topics discovered in a DomainParticipant
   *
   * @tparam FwdIterator A forward iterator whose value type is
   * dds::core::InstanceHandle
   *
   * @param participant The DomainParticipant where to look up the discovered
   * topics
   * @param begin The beginning of the range where to insert the InstanceHandles
   * that correspond to the discovered topics
   * @param max_size The maximum number of topics to insert or
   * dds::core::LENGTH_UNLIMITED
   */
  template <typename FwdIterator>
  int32_t discover_any_topic(
     const dds::domain::DomainParticipant& participant, 
     FwdIterator begin, int32_t max_size);

  /**
   * @relatesalso dds::topic::Topic
   * @brief Retrieves the topics discovered in a DomainParticipant
   *
   * This is equivalent to discover_any_topic(participant, begin, dds::core::LENGTH_UNLIMITED)
   */
  template <typename BinIterator>
  int32_t discover_any_topic(
     const dds::domain::DomainParticipant& participant, 
     BinIterator begin)
  {
      return discover_any_topic(
         participant, begin, dds::core::LENGTH_UNLIMITED);
  }

  // Spec error: missing a way to retrieve information with a specific instance
  // handle(s)--no way to link the data with the handle to ignore it
  /**
   * @relatesalso dds::topic::Topic
   *
   * @brief Gets the information about a discovered topic
   *
   * @details \dref_DomainParticipant_get_discovered_topic_data
   */
  OMG_DDS_API
  dds::topic::TopicBuiltinTopicData discover_topic_data(
     const dds::domain::DomainParticipant& participant, 
     const dds::core::InstanceHandle& topic_handle);

  /**
   * @relatesalso dds::topic::Topic
   *
   * @brief Gets the information about several topics
   */
  template <typename FwdIterator>
  int32_t discover_topic_data(
     const dds::domain::DomainParticipant& participant, 
     FwdIterator begin,
     const dds::core::InstanceHandleSeq& handles);

  /**
   * @relatesalso dds::topic::Topic
   *
   * @brief Gets the information about all topics
   *
   * @tparam A forward iterator whose value type is
   * dds::topic::TopicBuiltinTopicData
   *
   * @param participant The DomainParticipant where to look up all the topics
   * @param begin The beginning of a range where to copy the topic data
   * @param max_size The maximum number of items to copy or
   * dds::core::LENGTH_UNLIMITED
   */
  template <typename FwdIterator>
  int32_t discover_topic_data(
     const dds::domain::DomainParticipant& participant, 
     FwdIterator begin, int32_t max_size);

  /**
   * @relatesalso dds::topic::Topic
   *
   * @brief Gets the information about all topics
   */
  template <typename BinIterator>
  int32_t discover_topic_data(
     const dds::domain::DomainParticipant& participant, 
     BinIterator begin)
  {
      return discover_topic_data(
         participant, begin, dds::core::LENGTH_UNLIMITED);
  }

  // Spec error: participant was const
  // Spec error: missing export decl

  /**
   * @relatesalso dds::topic::Topic
   *
   * @brief Instructs a DomainParticipant to ignore a topic
   *
   * @details \dref_DomainParticipant_ignore_topic
   */
  OMG_DDS_API
  void ignore(
      dds::domain::DomainParticipant& participant,
      const dds::core::InstanceHandle& handle);

  /**
   * @relatesalso dds::topic::Topic
   *
   * @brief Ignores a range of topics
   *
   * @see ignore(dds::domain::DomainParticipant&,const dds::core::InstanceHandle&)
   */
  template <typename FwdIterator>
  void ignore(
      dds::domain::DomainParticipant& participant,
      FwdIterator begin,
      FwdIterator end)
  {
      for (; begin != end; ++begin) {
          ignore(participant, *begin);
      }
  }

} }

#endif /* OMG_DDS_TOPIC_DISCOVER_HPP_ */
