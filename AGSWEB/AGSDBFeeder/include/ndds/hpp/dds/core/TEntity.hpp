#ifndef OMG_TDDS_CORE_ENTITY_HPP_
#define OMG_TDDS_CORE_ENTITY_HPP_

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

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Reference.hpp>
#include <dds/core/status/Status.hpp>

namespace dds { namespace core {

/** 
 * @ingroup DDSInfrastructureModule 
 * @RTI_class_definition class Entity 
 * @headerfile dds/core/Entity.hpp
 *
 * @brief @st_ref_type This is the abstract base class for all the DDS objects that
 * support QoS policies, a listener and a status condition. 
 *
 * @see \ref a_st_ref_type "Reference types" for operations that all reference
 * types provide.
 * @see \ref DDSEntityExampleModuleForCpp2
 *
 * @details \dref_details_Entity
 */
template <typename DELEGATE>
class TEntity : public Reference<DELEGATE> {
public:
    OMG_DDS_REF_TYPE(TEntity, dds::core::Reference, DELEGATE)

protected:
    // Spec error CPPPSM-168: need this constructor
    explicit TEntity(const DELEGATE_REF_T& ref)
        : dds::core::Reference<DELEGATE>(ref)
    {
    }

public:
    ~TEntity() { }


    /**
     * @brief Enables this entity (if it was created disabled)
     *
     * @details \dref_details_Entity_enable
     */
    void enable()
    {
        this->delegate()->enable();
    }

    /**
     * @brief Retrieves the list of communication statuses that are triggered.
     *
     * @details \dref_details_Entity_get_status_changes
     */
    const dds::core::status::StatusMask status_changes()
    {
        return this->delegate()->status_changes();
    }

    /**
     * @brief Get the instance handle that represents this entity
     *
     * @details \dref_details_Entity_get_instance_handle
     */
    const dds::core::InstanceHandle instance_handle() const
    {
        return this->delegate()->instance_handle();
    }


    /**
     * @brief Forces the destruction of this entity.
     *
     * @mtsafety_delete
     *
     * @see \ref a_st_ref_type "Reference types"
     */
    void close()
    {
        this->delegate()->close();
    }

    /**
     * @brief Disables the automatic destruction of this entity
     *
     * @see \ref a_st_ref_type "Reference types"
     */
    void retain()
    {
        this->delegate()->retain();
    }
};

// Internal tag type to disambiguate some
// internal constructors in subclasses of Entity
struct construct_from_native_tag_t {};

} } // namespace dds::core

#ifdef DOXYGEN_DOCUMENTATION_ONLY
 /**
  * @ingroup DDSEntityModule
  * @headerfile dds/dds.hpp
  * @brief Entity listeners
  *
  * @note This type doesn't exist in the API, it just represents the concept
  * that all subclasses of dds::core::Entity have an associated listener type.
  * The actual listener types are:
  * \li dds::domain::DomainParticipantListener
  * \li dds::topic::TopicListener
  * \li dds::sub::SubscriberListener
  * \li dds::pub::PublisherListener
  * \li dds::sub::DataReaderListener
  * \li dds::pub::DataWriterListener
  *
  * \dref_details_Listener
  */
class Listener {};
#endif

#endif /* OMG_TDDS_CORE_ENTITY_HPP_ */

