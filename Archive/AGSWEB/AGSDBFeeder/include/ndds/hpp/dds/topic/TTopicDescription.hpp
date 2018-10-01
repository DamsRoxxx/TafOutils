#ifndef OMG_DDS_T_TOPIC_TOPIC_DESCRIPTION_HPP_
#define OMG_DDS_T_TOPIC_TOPIC_DESCRIPTION_HPP_

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
#include <dds/topic/TopicTraits.hpp>

namespace dds { namespace topic {
  template <typename T,
  template <typename Q> class DELEGATE>
  class TopicDescription;
} }


/**
 * @ingroup DDSTopicEntityModule
 * @RTI_class_definition template<typename T> class dds::topic::TopicDescription : public dds::core::Entity
 * @headerfile dds/topic/TopicDescription.hpp
 *
 * @brief Abstract base class of Topic and ContentFilteredTopic
 *
 * @details \dref_details_TopicDescription
 *
 * @tparam T The topic-type
 */
template <typename T, template <typename Q> class DELEGATE>
class dds::topic::TopicDescription : public ::dds::core::TEntity< DELEGATE<T> > {
public:
  typedef T DataType;

public:
OMG_DDS_REF_TYPE(TopicDescription, ::dds::core::TEntity, DELEGATE<T>)

    TopicDescription(DELEGATE_REF_T& the_delegate)
        : dds::core::TEntity<DELEGATE<T> >(the_delegate)
    {
    }

public:
    virtual ~TopicDescription() { }

public:
    /**
     * @brief Gets the topic name
     */
    const std::string& name() const
    {
        return this->delegate()->name();
    }

    /**
     * @brief Gets the type name
     *
     * The type name defines a locally unique type for the publication or the
     * subscription.
     *
     * The association between the topic and the type name is
     * automatic through the template parameter \p T, via the trait
     * dds::topic::topic_type_name<T>::name(), that is given
     *
     * When \p T is rti::core::xtypes::DynamicData,
     * the type name is obtained by default from the rti::core::xtypes::DynamicType.
     */
    const std::string& type_name() const
    {
        return this->delegate()->type_name();
    }

    /**
     * @brief Gets the related dds::domain::DomainParticipant
     */
    const dds::domain::DomainParticipant& participant() const
    {
        return this->delegate()->participant();
    }

};


#endif /* OMG_DDS_T_TOPIC_TOPIC_DESCRIPTION_HPP_ */
