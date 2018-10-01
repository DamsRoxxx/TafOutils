#ifndef OMG_TDDS_SUB_SUBSCRIBER_HPP_
#define OMG_TDDS_SUB_SUBSCRIBER_HPP_

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

#include <dds/core/TEntity.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/sub/qos/DataReaderQos.hpp>

namespace dds { namespace sub {
  template <typename DELEGATE>
  class TSubscriber;

  class SubscriberListener;
} }

/** 
 * @ingroup DDSSubscriberModule 
 *  
 * @RTI_class_definition class dds::sub::Subscriber : public dds::core::Entity
 * @headerfile Subscriber.hpp "dds/sub/Subscriber.hpp"
 *  
 * @brief @st_ref_type A subscriber is the object responsible for actually 
 * receiving data from a subscription.
 * 
 * @details \dref_details_Subscriber
 *  
 * @see \ref DDSEntityExampleModuleForCpp2
 */
template<typename DELEGATE>
class dds::sub::TSubscriber : public dds::core::TEntity<DELEGATE> {
public:
    typedef dds::sub::SubscriberListener Listener;

public:
    OMG_DDS_BASIC_REF_TYPE(TSubscriber, dds::core::TEntity, DELEGATE)

    /**
     * @brief Create a Subscriber attached to the given 
     * DomainParticipant.
     *  
     * The subscriber QoS will be set to participant.default_subscriber_qos()
     *
     * @param the_participant the DomainParticipant that will own this subscriber.
     */
    explicit TSubscriber(const ::dds::domain::DomainParticipant& the_participant)
        : dds::core::TEntity<DELEGATE>(new DELEGATE(the_participant))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * @brief Create a Subscriber attached to the given DomainParticipant.
     *
     * @param dp The DomainParticipant that will own this subscriber.
     * @param the_qos The qos::SubscriberQos
     * @param the_listener The subscriber listener.
     * @param mask The listener event mask.
     */
    TSubscriber(
        const ::dds::domain::DomainParticipant& dp,
        const dds::sub::qos::SubscriberQos& the_qos,
        dds::sub::SubscriberListener* the_listener = NULL,
        const dds::core::status::StatusMask& mask =
            dds::core::status::StatusMask::all())
        : dds::core::TEntity<DELEGATE>(new DELEGATE(dp, the_qos, the_listener, mask))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    // For internal use only
    TSubscriber(dds::core::construct_from_native_tag_t, DELEGATE* the_delegate)
        : dds::core::TEntity<DELEGATE>(the_delegate)
    {
        this->delegate()->remember_reference(this->delegate());
    }

public:
    ~TSubscriber()
    {
    }

public:
    /**
     * @brief This operation invokes the operation on_data_available on the
     * DataReaderListener objects attached to contained DataReader
     * entities with a DATA_AVAILABLE status that is 
     * considered changed as described in \ref Status_changes_read. 
     *  
     * \dref_details_Subscriber_notify_datareaders 
     */
    void notify_datareaders()
    {
        this->delegate()->notify_datareaders();
    }

    /**
     * @brief Attach a listener to this Subscriber
     *
     * @param the_listener The listener
     * @param event_mask The event mask for the listener.
     */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask& event_mask)
    {
        this->delegate()->listener(the_listener, event_mask);
    }

    /**
     * @brief Get the Subscriber listener.
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }

    // Spec issue CPPPSM-217: return by value, not by reference
    /**
     * @brief Get the Subscriber QoS.
     */ 
    dds::sub::qos::SubscriberQos qos() const
    {
        return this->delegate()->qos();
    }

    /**
     * @brief Set the Subscriber QoS.
     * 
     * @param the_qos the new QoS.
     */
    void qos(const dds::sub::qos::SubscriberQos& the_qos)
    {
        this->delegate()->qos(the_qos);
    }

    /**
     * @brief Get the default DataReader QoS.
     * 
     * @return dds::sub::qos::DataReaderQos 
     */
    dds::sub::qos::DataReaderQos default_datareader_qos() const
    {
        return this->delegate()->default_datareader_qos();
    }

    /**
     * @brief Set the default DataReaderQoS.
     *  
     * @param the_qos The default DataReaderQoS.
     */
    TSubscriber& default_datareader_qos(const dds::sub::qos::DataReaderQos& the_qos)
    {
        this->delegate()->default_datareader_qos(the_qos);
        return *this;
    }

    /**
     * @brief Return the DomainParticipant that owns this Subscriber.
     * 
     * @return const dds::domain::DomainParticipant& The DomainParticipant that 
     * owns this subscriber 
     */
    const dds::domain::DomainParticipant& participant() const
    {
        return this->delegate()->participant();
    }
};


#endif /* OMG_TDDS_SUB_SUBSCRIBER_HPP_ */
