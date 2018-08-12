#ifndef OMG_TDDS_PUB_PUBLISHER_HPP_
#define OMG_TDDS_PUB_PUBLISHER_HPP_

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
#include <dds/core/TEntity.hpp>
#include <dds/pub/qos/DataWriterQos.hpp>
#include <dds/pub/qos/PublisherQos.hpp>
#include <dds/domain/DomainParticipant.hpp>

namespace dds { namespace pub {
  template <typename DELEGATE>
  class TPublisher;

  class PublisherListener;
} }

/** 
 * @ingroup DDSPublisherModule 
 * @RTI_class_definition class dds::pub::Publisher : public dds::core::Entity
 * @headerfile dds/pub/Publisher.hpp
 *  
 * @brief @st_ref_type A publisher is the object responsible for the actual
 * dissemination of publications.
 *  
 * @details \dref_details_Publisher
 *
 * @see dds::pub::SuspendedPublication
 * @see \ref DDSPublisherExampleModule
 * @see \ref DDSEntityExampleModuleForCpp2
 */
template <typename DELEGATE>
class dds::pub::TPublisher : public dds::core::TEntity<DELEGATE> {
public:
  typedef dds::pub::PublisherListener Listener;

public:
    //Spec error: was OMG_DDS_REF_TYPE unlike, TDomainParticipant
    // which is OMG_DDS_BASIC_REF_TYPE. That would make expressions like the
    // following not compile: Publisher p = ...; p = dds::core::null
    OMG_DDS_BASIC_REF_TYPE(TPublisher, dds::core::TEntity, DELEGATE)


    /**
    * @brief Create a Publisher
    *
    * It uses default qos::PublisherQos and no listener.
    *
    * @param the_participant The DomainParticipant where this Publisher will be created
    */
    explicit TPublisher(const dds::domain::DomainParticipant& the_participant)
        : dds::core::TEntity<DELEGATE>(new DELEGATE(the_participant))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
    * @brief Create a <code>Publisher</code> with the desired QoS 
    * policies and attaches to it the specified PublisherListener. 
    *  
    * @pre The specified QoS policies must be consistent, or the operation will fail
    *
    * @param the_participant The DomainParticipant where this Publisher will be created
    * @param the_qos The PublisherQos
    * @param the_listener The PublisherListener
    * @param mask Changes of communication status to be invoked on the listener.
    *  
    * @throw dds::core::Error If there is any error creating the Publisher
    */
    TPublisher(
        const dds::domain::DomainParticipant& the_participant,
        const dds::pub::qos::PublisherQos& the_qos,
        dds::pub::PublisherListener* the_listener = NULL,
        const dds::core::status::StatusMask& mask = dds::core::status::StatusMask::all())
        : dds::core::TEntity<DELEGATE>(new DELEGATE(the_participant, the_qos, the_listener, mask))
    {
        this->delegate()->remember_reference(this->delegate());
    }


    // Spec issue: need this constructor
    TPublisher(dds::core::construct_from_native_tag_t, DELEGATE* the_delegate)
        : dds::core::TEntity<DELEGATE>(the_delegate)
    {
        this->delegate()->remember_reference(this->delegate());
    }

    ~TPublisher()
    {
    }

    // ------------------------------------------------------------------------

    /**
     * @brief Gets the PublisherQos
     */
    const dds::pub::qos::PublisherQos qos() const
    {
        return this->delegate()->qos();
    }

    /**
     * @brief Set the PublisherQos.
     *
     * @details \dref_details_Publisher_set_qos
     */
    void qos(const dds::pub::qos::PublisherQos& the_qos)
    {
        this->delegate()->qos(the_qos);
    }

    /**
     * @brief Sets the PublisherQos
     */
    TPublisher& operator <<(const dds::pub::qos::PublisherQos& the_qos)
    {
        qos(the_qos);
        return *this;
    }

    /**
     * @brief Gets the PublisherQos
     */
    TPublisher& operator >>(dds::pub::qos::PublisherQos& the_qos)
    {
        the_qos = qos();
        return *this;
    }

    /**
     * @brief Sets the default DataWriterQos
     */
    TPublisher& default_datawriter_qos(const dds::pub::qos::DataWriterQos& dwqos)
    {
        this->delegate()->default_writer_qos(dwqos);
        return *this;
    }

    /**
     * @brief Gets the default DataWriterQos
     *
     * The retrieved DataWriterQos will match the set of values specified on
     * the last call to default_datawriter_qos(const dds::pub::qos::DataWriterQos&).
     * If the application never called that function, the default value comes
     * from the dds::domain::DomainParticipant.
     */
    dds::pub::qos::DataWriterQos default_datawriter_qos() const
    {
        return this->delegate()->default_writer_qos();
    }

    // ------------------------------------------------------------------------

    /**
     * @brief Sets the Publisher listener
     *
     * @details \dref_details_Publisher_set_listener 
     *  
     * @param plistener the topic listener
     * @param event_mask Changes of communication status to be invoked on the listener
     */
    void listener(
        Listener* plistener,
        const dds::core::status::StatusMask& event_mask)
    {
        this->delegate()->listener(plistener, event_mask);
    }

    /**
     * @brief Returns the listener currently associated with this Publisher.
     *
     * If there's no listener it returns NULL.
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }

    // ------------------------------------------------------------------------

    /**
     * @brief Blocks the calling thread until all data written by this Publisher's
     * reliable DataWriters is acknowledged, or until timeout expires.
     *
     * @details \dref_details_Publisher_wait_for_acknowledgments
     */
    void wait_for_acknowledgments(const dds::core::Duration& max_wait)
    {
        this->delegate()->wait_for_acknowledgments(max_wait);
    }

    // ------------------------------------------------------------------------

    // Spec error: should not return const DomainParticipant
    /**
     * @brief Gets the DomainParticipant to which this Publisher belongs
     */
    const dds::domain::DomainParticipant& participant() const
    {
        return this->delegate()->participant();
    }

};


#endif /* OMG_TDDS_PUB_PUBLISHER_HPP_ */
