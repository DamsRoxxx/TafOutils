#ifndef OMG_DDS_TTOPIC_TOPIC_HPP_
#define OMG_DDS_TTOPIC_TOPIC_HPP_

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

#include <dds/core/types.hpp>
#include <dds/core/ref_traits.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/topic/qos/TopicQos.hpp>
#include <dds/topic/TopicDescription.hpp>
#include <dds/core/xtypes/DynamicType.hpp>


namespace dds { namespace topic {
  template <typename T, template <typename Q> class DELEGATE>
  class Topic;

  template <typename T>
  class TopicListener;
} }

/** 
 * @ingroup  DDSTopicEntityModule 
 * @RTI_class_definition template<typename T> class dds::topic::Topic : public dds::topic::TopicDescription
 * @headerfile dds/topic/Topic.hpp
 * 
 * @brief @st_ref_type Topic is the most basic description of the
 * data to be published and subscribed.
 *
 * @tparam T The type associated to this topic. It must be a type such that
 * \p dds::topic::is_topic_type<T>::value is true (see dds::topic::is_topic_type).
 * Valid types are \ref DDSTypesModule "IDL-generated types",
 * the \ref DDSBuiltInTypesModule "built-in types" and dds::core::xtypes::DynamicData.
 *
 * @details \dref_details_Topic
 */
template<typename T, template<typename Q> class DELEGATE>
class dds::topic::Topic: public dds::topic::TopicDescription<T, DELEGATE> {
public:
    typedef TopicListener<T> Listener;

public:

    OMG_DDS_REF_TYPE_T(Topic, TopicDescription, T, DELEGATE)

    ~Topic() {}
public:
    /**
     * @brief Creates a new topic.
     *  
     * This constructor behaves as \link Topic(const dds::domain::DomainParticipant&, const std::string&, const std::string&, const dds::topic::qos::TopicQos&, dds::topic::TopicListener<T>*, const dds::core::status::StatusMask&)
     * the most general one\endlink where the type name is automatically deduced
     * from dds::core::topic_type_name, it uses
     * \ref Entity_default_qos "the default TopicQos" and doesn't set a listener.
     *
     * @param the_participant The domain participant on which the topic will be defined.
     * @param topic_name The topic name.
     */
    Topic(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& topic_name)
        : TopicDescription<T, DELEGATE>(new DELEGATE<T>(the_participant, topic_name))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * @brief Creates a new topic.
     *  
     * This constructor behaves as \link Topic(const dds::domain::DomainParticipant&, const std::string&, const std::string&, const dds::topic::qos::TopicQos&, dds::topic::TopicListener<T>*, const dds::core::status::StatusMask&)
     * the most general one\endlink except that it uses
     * \ref Entity_default_qos "the default TopicQos" and doesn't set a listener.
     *
     * @param dp The domain participant on which the topic will be defined.
     * @param topic_name The topic name.
     * @param the_type_name The name to register the type with
     */
    Topic(
        const dds::domain::DomainParticipant& dp,
        const std::string& topic_name,
        const std::string& the_type_name)
        : TopicDescription<T, DELEGATE>(
            new DELEGATE<T>(dp, topic_name, the_type_name))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * @brief Creates a new Topic.
     *
     * This constructor behaves as \link Topic(const dds::domain::DomainParticipant&, const std::string&, const std::string&, const dds::topic::qos::TopicQos&, dds::topic::TopicListener<T>*, const dds::core::status::StatusMask&)
     * the most general one\endlink except that the type name is automatically
     * deduced from dds::core::topic_type_name
     */
    Topic(
        const dds::domain::DomainParticipant& dp,
        const std::string& topic_name,
        const dds::topic::qos::TopicQos& the_qos,
        dds::topic::TopicListener<T>* the_listener = NULL,
        const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all())
        : TopicDescription<T, DELEGATE>(
            new DELEGATE<T>(dp, topic_name, the_qos, the_listener, mask))
     {
        this->delegate()->remember_reference(this->delegate());
     }

    /**
     * @brief Create a new topic.
     *
     * @param participant The domain participant on which the topic will be defined.
     * @param topic_name The Topic name. Must not exceed 255 characters.
     * @param type_name The name given to the type \p T
     * @param the_qos The Qos settings for this Topic
     * @param the_listener the topic listener (default: NULL)
     * @param mask Changes of communication status to be invoked on the listener
     *        (default: all)
     *
     * @see \ref DDSQosTypesModule_usage for information on setting QoS before entity creation
     * @see \idref_TopicQos for rules on consistency among QoS
     * @see dds::core::QosProvider
     * @see dds::domain::DomainParticipant::default_topic_qos()
     * @see listener()
     */
    Topic(
        const dds::domain::DomainParticipant& participant,
        const std::string& topic_name,
        const std::string& type_name,
        const dds::topic::qos::TopicQos& the_qos,
        dds::topic::TopicListener<T>* the_listener = NULL,
        const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all())
        : TopicDescription<T, DELEGATE>(
            new DELEGATE<T>(participant, topic_name, type_name, the_qos, the_listener, mask))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    // Spec issue CPPPSM-18: need this constructor to make
    // polymorphic_cast work and creation from native entity
    Topic(DELEGATE_REF_T& delegate_ref)
        : TopicDescription<T, DELEGATE>(delegate_ref)
    {
        if (this->delegate()) {
            this->delegate()->remember_reference(this->delegate());
        }
    }

    // For internal use only
    Topic(dds::core::construct_from_native_tag_t, DELEGATE<T>* the_delegate)
        : TopicDescription<T, DELEGATE>(the_delegate)
    {
        this->delegate()->remember_reference(this->delegate());
    }

#if defined (OMG_DDS_X_TYPES_DYNANIC_TYPE_SUPPORT)
    /**
     * @brief Create a new topic with a dynamic type description. 
     *  
     * @see Topic(const dds::domain::DomainParticipant& the_participant,
        const std::string& topic_name,
        const dds::core::xtypes::DynamicType& type,
        const dds::topic::qos::TopicQos& qos,
        dds::topic::TopicListener<T>* listener,
        const dds::core::status::StatusMask& mask)
     */
    Topic(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& topic_name,
        const dds::core::xtypes::DynamicType& type)
        : TopicDescription<T, DELEGATE>(new DELEGATE<T>(the_participant, topic_name, type))
    {
        this->delegate()->remember_reference(this->delegate());
    }


    /**
     * @brief Create a new topic with a dynamic type description.
     *
     * Notice that in this case the data type \p T has to be DynamicData. Thus the
     * Topic type will be \p Topic<DynamicData>.
     *
     * The QoS will be set to dp.default_topic_qos().
     *
     * @param the_participant the domain participant on which the topic will be defined.
     * @param topic_name the topic's name.
     * @param type The DynamicType that describes the type for the DynamicData
     * samples of this topic.
     * @param the_qos The Qos settings for this Topic
     * @param the_listener the topic listener (default: NULL)
     * @param mask Changes of communication status to be invoked on the listener
     *        (default: all)
     *
     * @see dds::core::xtypes::DynamicData
     * @see rti::domain::register_type()
     */
    Topic(const dds::domain::DomainParticipant& the_participant,
        const std::string& topic_name,
        const dds::core::xtypes::DynamicType& type,
        const dds::topic::qos::TopicQos& the_qos,
        dds::topic::TopicListener<T>* the_listener = NULL,
        const dds::core::status::StatusMask& mask = dds::core::status::StatusMask::all())
            : TopicDescription<T, DELEGATE>(new DELEGATE<T>(
                the_participant, topic_name, type, the_qos, the_listener, mask))
    {
        this->delegate()->remember_reference(this->delegate());
    }

#endif // OMG_DDS_X_TYPES_DYNANIC_TYPE_SUPPORT

public:

    /**
     * @brief Sets the listener.
     *  
     * @param the_listener the topic listener
     * @param event_mask Changes of communication status to be invoked on the listener
     */
    void listener(
        Listener* the_listener,
        const ::dds::core::status::StatusMask& event_mask)
    {
        this->delegate()->listener(the_listener, event_mask);
    }

    /**
     * @brief Gets the listener
     * 
     * Returns the listener or NULL if there's no listener attached.
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }

    // Spec issue CPPPSM-217: return by value, not by reference
    /**
     * 
     * @brief Gets the current TopicQos for this Topic
     */
    dds::topic::qos::TopicQos qos() const
    {
        return this->delegate()->qos();
    }

    /**
     * @brief Sets the TopicQos setting for this Topic
     *
     * @param the_qos Set of policies to be applied to the Topic.
     * Immutable policies cannot be changed after this entity has been enabled.
     *
     * @throw dds::core::ImmutablePolicyError if \p the_qos contains a different
     * value for an immutable policy.
     * @throw dds::core::InconsistentPolicyError if some policies are inconsistent.
     *
     * @see dds::topic::qos::TopicQos for rules on consistency
     * among QoS policies
     * @see \ref Entity_set_qos
     * @see dds::domain::DomainParticipant::default_topic_qos()
     * @see dds::core::QosProvider::topic_qos()
     */
    void qos(const dds::topic::qos::TopicQos& the_qos)
    {
        this->delegate()->qos(the_qos);
    }

    // Spec issue CPPPSM-217: return by value, not by reference
    /**
     * @brief Retrieve the current InconsistentTopicStatus of this Topic.
     */
    dds::core::status::InconsistentTopicStatus inconsistent_topic_status() const
    {
        return this->delegate()->inconsistent_topic_status();
    }

};


#endif /* OMG_DDS_TTOPIC_TOPIC_HPP_ */
