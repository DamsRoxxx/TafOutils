#ifndef OMG_DDS_T_TOPIC_CONTENT_FILTERED_TOPIC_HPP_
#define OMG_DDS_T_TOPIC_CONTENT_FILTERED_TOPIC_HPP_

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

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/detail/conformance.hpp>
#include <dds/core/types.hpp>
#include <dds/topic/Topic.hpp>
#include <dds/topic/Filter.hpp>

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

namespace dds {
  namespace topic {
    template <typename T, template <typename Q> class DELEGATE>
    class ContentFilteredTopic;
  }
}


/** 
 * @ingroup DDSTopicEntityModule
 * @RTI_class_definition template<typename T> class dds::topic::ContentFilteredTopic : public dds::topic::TopicDescription
 * @headerfile dds/topic/ContentFilteredTopic.hpp
 *  
 * @brief @st_ref_type Specialization of TopicDescription that allows for
 * content-based subscriptions.
 *
 * @details \dref_details_ContentFilteredTopic
 *
 * @tparam T The topic-type
 *
 * @see \ref NDDSFilterExampleModule_content_filtered_topic
 */
template<typename T, template<typename Q> class DELEGATE>
class dds::topic::ContentFilteredTopic: public TopicDescription<T, DELEGATE> {
public:
OMG_DDS_REF_TYPE_T(ContentFilteredTopic, TopicDescription, T, DELEGATE)

public:
    /**
     * @brief Creates a ContentFilteredTopic to perform content-based subscriptions
     *
     * The ContentFilteredTopic only relates to samples published under that Topic,
     * filtered according to their content. The filtering is done by means of
     * evaluating a logical expression that involves the values of some of the
     * data-fields in the sample. The logical expression derived from the
     * Filter arguments.
     *
     * \ref DDSQueryAndFilterSyntaxModule describes the syntax of
     * filter_expression and expression_parameters.
     *
     * @pre The application is not allowed to create two ContentFilteredTopic
     * objects with the same topic name attached to the same DomainParticipant.
     * If the application attempts this, this function will fail and throw
     * dds::core::Error.
     *
     * By default this function will create a content filter using
     * the built-in SQL filter which implements a superset of the DDS specification.
     * This filter requires that all IDL types have been compiled with DynamicType
     * (also known as TypeCode). If this precondition is not met, this operation
     * return throws dds::core::Error. Do not use rtiddsgen's -notypecode option
     * if you want to use the built-in SQL filter.
     *
     * To use a different filter, set Filter::name().
     *
     * @param the_topic The Topic to be filtered
     * @param the_name Name for the new content filtered topic, must not exceed
     *             255 characters.
     * @param filter The filter to apply, which includes the filter name (by default
     * SQL), the filter expression and the expression parameters.
     *
     */
    ContentFilteredTopic(
        const Topic<T>& the_topic,
        const std::string& the_name,
        const dds::topic::Filter& filter)
        : TopicDescription<T, DELEGATE>(new DELEGATE<T>(the_topic, the_name, filter))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    ContentFilteredTopic(DELEGATE_REF_T& delegate_ref)
        : TopicDescription<T, DELEGATE>(delegate_ref)
    {
        if (this->delegate()) {
            this->delegate()->remember_reference(this->delegate());
        }
    }

    // For internal use only
    ContentFilteredTopic(dds::core::construct_from_native_tag_t, DELEGATE<T>* the_delegate)
        : TopicDescription<T, DELEGATE>(the_delegate)
    {
        this->delegate()->remember_reference(this->delegate());
    }

    virtual ~ContentFilteredTopic() { }

public:

    // Spec issue CPPPSM-217: return by value, not by reference
    /**
     * @brief Gets the filter expression.
     */
    std::string filter_expression() const
    {
        return this->delegate()->filter_expression();
    }

    /**
     * @brief Gets the filter expression parameters.
     */
    const dds::core::StringSeq filter_parameters() const
    {
        return this->delegate()->filter_parameters();
    }

    /**
     * @brief Modifies the filter parameters
     *
     * @tparam FwdIterator A forward iterator whose value type is std::string
     * (or convertible to std::string)
     *
     * 
     * @param begin The beginning of the range
     * @param end The end of the range (can't contain more than 100 elements)
     */
    template<typename FwdIterator>
    void filter_parameters(const FwdIterator& begin, const FwdIterator& end)
    {
        this->delegate()->filter_parameters(begin, end);
    }

    /**
     * @brief Gets the related topic.
     */
    const dds::topic::Topic<T>& topic() const
    {
        return this->delegate()->topic();
    }
};

#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT


#endif // OMG_DDS_T_TOPIC_CONTENT_FILTERED_TOPIC_HPP_
