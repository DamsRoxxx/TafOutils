#ifndef OMG_DDS_TOPIC_ANY_TOPIC_HPP_
#define OMG_DDS_TOPIC_ANY_TOPIC_HPP_

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

#include <dds/core/Exception.hpp>
#include <dds/core/ref_traits.hpp>
#include <dds/topic/detail/AnyTopic.hpp>
#include <dds/topic/TopicDescription.hpp>

namespace dds {  namespace topic {

/**
 * @ingroup DDSTopicModule
 * @headerfile "dds/pub/AnyDataWriter.hpp"
 *
 * @brief @st_ref_type This class provides an non-template holder for
 * representing a Topic of any type
 *
 * This class is useful for code that uses Topics of different types. It
 * provides access to type-independent Topic functions.
 *
 * An AnyTopic is always created from a typed Topic, increasing its
 * reference count. The member function get() allows getting the typed Topic
 * back.
 */
class AnyTopic {
public:

    // CPPPSM-197
    typedef detail::THolderBase DELEGATE_T;
    typedef dds::core::smart_ptr_traits<DELEGATE_T>::ref_type DELEGATE_REF_T;

    // Spec issue: this constructor was missing
    AnyTopic(dds::core::null_type)
    {
    }

    /**
     * @brief Create an AnyTopic that represents a generic, untyped Topic
     *
     * @tparam T The type of the Topic that this AnyTopic is
     * being created from
     * @param topic The typed Topic that this AnyTopic will represent
     */
    template <typename T>
    AnyTopic(const dds::topic::Topic<T>& topic)
        : holder_(topic.delegate())
    {
    }

    // Spec issue: need this constructor
    // For internal use only
    AnyTopic(
        dds::core::smart_ptr_traits<detail::THolderBase>::ref_type holder)
        : holder_(holder)
    {
    }

    // Spec issue CPPPSM-217: changed to return by value
    /**
     * @brief Gets the DomainParticipant this topic belongs to
     */
    dds::domain::DomainParticipant domain_participant() const
    {
        return holder_->participant();
    }

    // Spec issue CPPPSM-217: changed to return by value
    /**
     * @brief Gets the InconsistentTopicStatus of this topic
     */
    dds::core::status::InconsistentTopicStatus inconsistent_topic_status()
    {
        return holder_->inconsistent_topic_status();
    }

    // Spec issue CPPPSM-217: changed to return by value
    /**
     * @brief Get the TopicQos
     */
    dds::topic::qos::TopicQos qos() const
    {
        return holder_->qos();
    }

    /**
     * @brief Sets the TopicQos
     */
    void qos(const dds::topic::qos::TopicQos& the_qos)
    {
        holder_->qos(the_qos);
    }

    // Spec issue: missing name() and type_name() methods
    /**
     * @brief Gets the topic name
     */
    std::string name() const
    {
        return holder_->name();
    }

    /**
     * @brief Gets the type name
     */
    std::string type_name() const
    {
        return holder_->type_name();
    }

    /**
     * @brief Closes the Topic
     *
     * @see Topic::close()
     */
    void close()
    {
        holder_->close();
    }

    /**
     * @brief Gets the typed Topic from this AnyTopic
     *
     * @tparam T The type of the Topic to extract
     *
     * @return The typed Topic that this AnyTopic
     * represents
     *
     * @throw dds::core::InvalidDowncastError If this AnyTopic
     * doesn't represent a Topic<T>.
     */
    template <typename T>
    Topic<T> get()
    {
        typename Topic<T>::DELEGATE_REF_T typed_holder =
            rtiboost::dynamic_pointer_cast<typename Topic<T>::DELEGATE_T>(
                holder_);
        if (typed_holder == NULL) {
            throw dds::core::InvalidDowncastError(
                "Invalid cast to typed Topic");
        }

        return Topic<T>(typed_holder);
    }

    AnyTopic& swap(AnyTopic& rhs)
    {
        std::swap(holder_, rhs.holder_);
        return *this;
    }

    bool operator==(const AnyTopic& other) const
    {
        return holder_ == other.holder_;
    }

    bool operator!=(const AnyTopic& other) const
    {
        return holder_ != other.holder_;
    }

    // CPPPSM-197
    bool operator==(dds::core::null_type) const
    {
        return (holder_.get() == 0);
    }

    // CPPPSM-197
    bool operator!=(dds::core::null_type) const
    {
        return !(holder_.get() == 0);
    }

    const detail::THolderBase* operator->() const
    {
        return holder_.get();
    }

    detail::THolderBase* operator->()
    {
        return holder_.get();
    }

private:
    dds::core::smart_ptr_traits<detail::THolderBase>::ref_type holder_;
};

/**
 * @relatesalso AnyTopic
 * @brief Same as AnyTopic::get()
 */
template <typename T>
Topic<T> get(const AnyTopic& any_topic)
{
    return any_topic.get<T>();
}

} } // namespace dds::topic

#endif /* OMG_DDS_TOPIC_ANY_TOPIC_HPP_ */
