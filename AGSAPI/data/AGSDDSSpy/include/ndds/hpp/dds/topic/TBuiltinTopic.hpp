#ifndef OMG_TDDS_TOPIC_BUILT_IN_TOPIC_HPP_
#define OMG_TDDS_TOPIC_BUILT_IN_TOPIC_HPP_

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
#include <dds/core/Value.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <dds/topic/BuiltinTopicKey.hpp>

namespace dds { namespace topic {
  template <typename D>
  class TParticipantBuiltinTopicData;

  template <typename D>
  class TTopicBuiltinTopicData;

  template <typename D>
  class TPublicationBuiltinTopicData;

  template <typename D>
  class TSubscriptionBuiltinTopicData;
} }

/** 
 *  @dref_ParticipantBuiltInTopicGroupDocs
 */

/** 
 * @ingroup DDSParticipantBuiltInTopicModule 
 * @headerfile dds/topic/BuiltinTopic.hpp
 * @RTI_class_definition class dds::topic::ParticipantBuiltinTopicData 
 * @brief Entry created when a dds::domain::DomainParticipant is discovered. 
 *
 */
template<typename D>
class dds::topic::TParticipantBuiltinTopicData: public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TParticipantBuiltinTopicData, D)

    // Spec Issue CPPPSM-231: without a user-provided default constructor clang
    // fails with 'default initialization
    // of an object of const type XXX requires a user-provided default 
    // constructor ()'

    /**
     * @brief Create a default ParticipantBuiltinTopicData
     */
    TParticipantBuiltinTopicData()
      : dds::core::Value<D>()
    {
    }

    /**
     * @brief Get the DCPS key to distinguish entries.
     * 
     * @return They key
     */
    const dds::topic::BuiltinTopicKey& key() const
    {
        return this->delegate().key();
    }

    /**
     * @brief Get the dds::core::policy::UserData policy of the 
     * corresponding dds::domain::DomainParticipant.
     *  
     * @return The UserData policy
     */
    const dds::core::policy::UserData& user_data() const
    {
        return this->delegate().user_data();
    }
};

/** 
 *  @dref_TopicBuiltInTopicGroupDocs
 */

/** 
 * @ingroup DDSTopicBuiltInTopicModule
 * @RTI_class_definition class dds::topic::TopicBuiltinTopicData
 * @headerfile dds/topic/BuiltinTopic.hpp
 *
 * @brief Entry created when a dds::topic::Topic object is discovered. 
 *  
 * @details @dref_Shared_topic_builtin_topic_data_description
 */
template<typename D>
class dds::topic::TTopicBuiltinTopicData: public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TTopicBuiltinTopicData, D)

    /**
     * @brief 
     */
    TTopicBuiltinTopicData()
      : dds::core::Value<D>()
    {
    }

    // Spec error CPPPSM-238: was missing suffixed const qualifier
    /**
     * @brief Get the DCPS key to distinguish entries.
     * 
     * @return The key
     */
    const dds::topic::BuiltinTopicKey& key() const
    {
        return this->delegate().key();
    }

    /**
     * @brief Get the name of the dds::topic::Topic
     * 
     * @return The topic's name
     */
    const dds::core::string& name() const
    {
        return this->delegate().name();
    }

    /**
     * @brief Get the name of the type attached to the dds::topic::Topic
     * 
     * @return The type's name
     */
    const dds::core::string& type_name() const
    {
        return this->delegate().type_name();
    }

    /**
     * @brief Get the dds::core::policy::Durability policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The Durability policy
     */
    const dds::core::policy::Durability& durability() const
    {
        return this->delegate().durability();
    }

/** @RTI_remove_lines 1 */
#ifdef OMG_DDS_PERSISTENCE_SUPPORT

    /**
     * @brief Get the dds::core::policy::DurabilityService policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The DurabilityService policy
     */
    const dds::core::policy::DurabilityService& durability_service() const
    {
        return this->delegate().durability_service();
    }

/** @RTI_remove_lines 1 */
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    /**
     * @brief Get the dds::core::policy::Deadline policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The Deadline policy
     */
    const dds::core::policy::Deadline& deadline() const
    {
        return this->delegate().deadline();
    }

    /**
     * @brief Get the dds::core::policy::LatencyBudget policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The LatencyBudget policy
     */
    const dds::core::policy::LatencyBudget& latency_budget() const
    {
        return this->delegate().latency_budget();
    }

    /**
     * @brief Get the dds::core::policy::Liveliness policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The Liveliness policy
     */
    const dds::core::policy::Liveliness& liveliness() const
    {
        return this->delegate().liveliness();
    }

    /**
     * @brief Get the dds::core::policy::Reliability policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The Reliability policy
     */
    const dds::core::policy::Reliability& reliability() const
    {
        return this->delegate().reliability();
    }

    /**
     * @brief Get the dds::core::policy::TransportPriority policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The TransportPriority policy
     */
    const dds::core::policy::TransportPriority& transport_priority() const
    {
        return this->delegate().transport_priority();
    }

    /**
     * @brief Get the dds::core::policy::Lifespan policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The Lifespan policy
     */
    const dds::core::policy::Lifespan& lifespan() const
    {
        return this->delegate().lifespan();
    }

    /**
     * @brief Get the dds::core::policy::DestinationOrder policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The DestinationOrder policy
     */
    const dds::core::policy::DestinationOrder& destination_order() const
    {
        return this->delegate().destination_order();
    }

    /**
     * @brief Get the dds::core::policy::History policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The History policy
     */
    const dds::core::policy::History& history() const
    {
        return this->delegate().history();
    }

    /**
     * @brief Get the dds::core::policy::ResourceLimits policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The ResourceLimits policy
     */
    const dds::core::policy::ResourceLimits& resource_limits() const
    {
        return this->delegate().resource_limits();
    }

    /**
     * @brief Get the dds::core::policy::Ownership policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The Ownership policy
     */
    const dds::core::policy::Ownership& ownership() const
    {
        return this->delegate().ownership();
    }

    /**
     * @brief Get the dds::core::policy::TopicData policy of the 
     * corresponding dds::topic::Topic
     * 
     * @return The TopicData policy
     */
    const dds::core::policy::TopicData& topic_data() const
    {
        return this->delegate().topic_data();
    }

};

/** 
 *  @dref_PublicationBuiltInTopicGroupDocs
 */

/** 
 * @ingroup DDSPublicationBuiltInTopicModule
 * @headerfile dds/topic/BuiltinTopic.hpp
 * @RTI_class_definition class dds::topic::PublicationBuiltinTopicData 
 *
 * @brief Entry created when a dds::pub::DataWriter is discovered in association 
 * with its dds::pub::Publisher. 
 *  
 * @details @dref_Shared_publication_builtin_topic_data_description
 */
template<typename D>
class dds::topic::TPublicationBuiltinTopicData: public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TPublicationBuiltinTopicData, D)

    /**
     * @brief Create a default PublicationBuiltinTopicData
     */
    TPublicationBuiltinTopicData()
      : dds::core::Value<D>()
    {
    }

    /**
     * @brief Get the DCPS key to distinguish entries
     * 
     * @return The key
     */
    const dds::topic::BuiltinTopicKey& key() const
    {
        return this->delegate().key();
    }

    /**
     * @brief Get the DCPS key of the dds::domain::DomainParticipant to which 
     * the dds::pub::DataWriter belongs
     * 
     * @return The DomainParticipant's key
     */
    const dds::topic::BuiltinTopicKey& participant_key() const
    {
        return this->delegate().participant_key();
    }

    /**
     * @brief Get the name of the related dds::topic::Topic.
     * 
     * @return The topic name
     */
    const dds::core::string& topic_name() const
    {
        return this->delegate().topic_name();
    }

    /**
     * @brief Get the name of the type attached to the dds::topic::Topic.
     * 
     * @return The type name
     */
    const dds::core::string& type_name() const
    {
        return this->delegate().type_name();
    }

    /**
     * @brief Get the dds::core::policy::Durability policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Durability policy
     */
    const dds::core::policy::Durability& durability() const
    {
        return this->delegate().durability();
    }

/** @RTI_remove_lines 1 */
#ifdef OMG_DDS_PERSISTENCE_SUPPORT
    /**
     * @brief Get the dds::core::policy::DurabilityService policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The DurabilityService policy
     */
    const dds::core::policy::DurabilityService& durability_service() const
    {
        return this->delegate().durability_service();
    }

/** @RTI_remove_lines 1 */
#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    /**
     * @brief Get the dds::core::policy::Deadline policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Deadline policy
     */
    const dds::core::policy::Deadline& deadline() const
    {
        return this->delegate().deadline();
    }

    /**
     * @brief Get the dds::core::policy::LatencyBudget policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The LatencyBudget policy
     */
    const dds::core::policy::LatencyBudget& latency_budget() const
    {
        return this->delegate().latency_budget();
    }

    /**
     * @brief Get the dds::core::policy::Liveliness policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Liveliness policy
     */
    const dds::core::policy::Liveliness& liveliness() const
    {
        return this->delegate().liveliness();
    }

    /**
     * @brief Get the dds::core::policy::Reliability policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Reliability policy
     */
    const dds::core::policy::Reliability& reliability() const
    {
        return this->delegate().reliability();
    }

    /**
     * @brief Get the dds::core::policy::Lifespan policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Lifespan policy
     */
    const dds::core::policy::Lifespan& lifespan() const
    {
        return this->delegate().lifespan();
    }

    /**
     * @brief Get the dds::core::policy::UserData policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The UserData policy
     */
    const dds::core::policy::UserData& user_data() const
    {
        return this->delegate().user_data();
    }

    /**
     * @brief Get the dds::core::policy::Ownership policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Ownership policy
     */
    const dds::core::policy::Ownership& ownership() const
    {
        return this->delegate().ownership();
    }

/** @RTI_remove_lines 1 */
#ifdef OMG_DDS_OWNERSHIP_SUPPORT
    /**
     * @brief Get the dds::core::policy::OwnershipStrength policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The OwnershipStrength policy
     */
    const dds::core::policy::OwnershipStrength& ownership_strength() const
    {
        return this->delegate().ownership_strength();
    }
/** @RTI_remove_lines 1 */
#endif  // OMG_DDS_OWNERSHIP_SUPPORT

    /**
     * @brief Get the dds::core::policy::DestinationOrder policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The DestinationOrder policy
     */
    const dds::core::policy::DestinationOrder& destination_order() const
    {
        return this->delegate().destination_order();
    }

    /**
     * @brief Get the dds::core::policy::Presentation policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Presentation policy
     */
    const dds::core::policy::Presentation& presentation() const
    {
        return this->delegate().presentation();
    }

    /**
     * @brief Get the dds::core::policy::Partition policy of the 
     * corresponding dds::pub::DataWriter
     * 
     * @return The Partition policy
     */
    const dds::core::policy::Partition& partition() const
    {
        return this->delegate().partition();
    }

    /**
     * @brief Get the dds::core::policy::TopicData policy of the related 
     * dds::topic::Topic
     * 
     * @return The TopicData policy
     */
    const dds::core::policy::TopicData& topic_data() const
    {
        return this->delegate().topic_data();
    }

    /**
     * @brief Get the dds::core::policy::GroupData policy of the 
     * dds::pub::Publisher to which the dds::pub::DataWriter belongs
     * 
     * @return The GroupData policy
     */
    const dds::core::policy::GroupData& group_data() const
    {
        return this->delegate().group_data();
    }

};

/** 
 *  @dref_SubscriptionBuiltInTopicGroupDocs
 */

/** 
 * @ingroup DDSSubscriptionBuiltInTopicModule
 * @RTI_class_definition class dds::topic::SubscriptionBuiltinTopicData 
 * @headerfile dds/topic/BuiltinTopic.hpp
 *
 * @brief Entry created when a dds::sub::DataReader is discovered in 
 * association with its dds::sub::Subscriber. 
 *  
 * @details @dref_Shared_subscription_builtin_topic_data_description
 */
template<typename D>
class dds::topic::TSubscriptionBuiltinTopicData: public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TSubscriptionBuiltinTopicData, D)

    /**
     * @brief Create a default SubscriptionBuiltinTopicData
     */
    TSubscriptionBuiltinTopicData()
      : dds::core::Value<D>()
    {
    }

    /**
     * @brief Get the DCPS key to distinguish entries
     * 
     * @return The key
     */
    const dds::topic::BuiltinTopicKey& key() const
    {
        return this->delegate().key();
    }

    /**
     * @brief Get the DCPS key of the dds::domain::DomainParticipant to which 
     * the dds::sub::DataReader belongs.
     * 
     * @return The DomainParticipant's key
     */
    const dds::topic::BuiltinTopicKey& participant_key() const
    {
        return this->delegate().participant_key();
    }

    /**
     * @brief Get the name of the related dds::topic::Topic.
     * 
     * @return The topic name
     */
    const dds::core::string& topic_name() const
    {
        return this->delegate().topic_name();
    }

    /**
     * @brief Get the name of the type attached to the dds::topic::Topic.
     * 
     * @return The type name
     */
    const dds::core::string& type_name() const
    {
        return this->delegate().type_name();
    }

    /**
     * @brief Get the dds::core::policy::Durability policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The Durability policy
     */
    const dds::core::policy::Durability& durability() const
    {
        return this->delegate().durability();
    }

    /**
     * @brief Get the dds::core::policy::Deadline policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The Deadline policy
     */
    const dds::core::policy::Deadline& deadline() const
    {
        return this->delegate().deadline();
    }

    /**
     * @brief Get the dds::core::policy::LatencyBudget policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The LatencyBudget policy
     */
    const dds::core::policy::LatencyBudget& latency_budget() const
    {
        return this->delegate().latency_budget();
    }

    /**
     * @brief Get the dds::core::policy::Liveliness policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The Liveliness policy
     */
    const dds::core::policy::Liveliness& liveliness() const
    {
        return this->delegate().liveliness();
    }

    /**
     * @brief Get the dds::core::policy::Reliability policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The Reliability policy
     */
    const dds::core::policy::Reliability& reliability() const
    {
        return this->delegate().reliability();
    }

    /**
     * @brief Get the dds::core::policy::Ownership policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The Ownership policy
     */
    const dds::core::policy::Ownership& ownership() const
    {
        return this->delegate().ownership();
    }

    /**
     * @brief Get the dds::core::policy::DestinationOrder policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The DestinationOrder policy
     */
    const dds::core::policy::DestinationOrder& destination_order() const
    {
        return this->delegate().destination_order();
    }

    /**
     * @brief Get the dds::core::policy::UserData policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The UserData policy
     */
    const dds::core::policy::UserData& user_data() const
    {
        return this->delegate().user_data();
    }

    /**
     * @brief Get the dds::core::policy::TimeBasedFilter policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The TimeBasedFilter policy
     */
    const dds::core::policy::TimeBasedFilter& time_based_filter() const
    {
        return this->delegate().time_based_filter();
    }

    /**
     * @brief Get the dds::core::policy::Presentation policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The Presentation policy
     */
    const dds::core::policy::Presentation& presentation() const
    {
        return this->delegate().presentation();
    }

    /**
     * @brief Get the dds::core::policy::TopicData policy of the 
     * corresponding dds::sub::DataReader
     * 
     * @return The TopicData policy
     */
    const dds::core::policy::Partition& partition() const
    {
        return this->delegate().partition();
    }

    /**
     * @brief Get the dds::core::policy::TopicData policy of the related 
     * dds::topic::Topic
     * 
     * @return The TopicData policy
     */
    const dds::core::policy::TopicData& topic_data() const
    {
        return this->delegate().topic_data();
    }

    /**
     * @brief Get the dds::core::policy::GroupData policy of the 
     * dds::sub::Subscriber to which the dds::sub::DataReader belongs
     * 
     * @return The GroupData policy
     */
    const dds::core::policy::GroupData& group_data() const
    {
        return this->delegate().group_data();
    }

};

#endif /* OMG_TDDS_TOPIC_BUILT_IN_TOPIC_HPP_ */
