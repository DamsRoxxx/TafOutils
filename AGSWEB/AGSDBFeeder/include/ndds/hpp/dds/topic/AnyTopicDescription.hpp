#ifndef OMG_DDS_TOPIC_ANY_TOPIC_DESCRIPTION_HPP_
#define OMG_DDS_TOPIC_ANY_TOPIC_DESCRIPTION_HPP_

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
#include <dds/topic/detail/AnyTopicDescription.hpp>


namespace dds { namespace topic {

class AnyTopicDescription {
public:
    template<typename T>
    AnyTopicDescription(
        const dds::topic::TopicDescription<T>& topic_description)
        : holder_(topic_description)
    {
    }

public:
    // Spec issue CPPPSM-217: changed to return by value
    dds::domain::DomainParticipant domain_participant() const
    {
        return holder_->domain_participant();
    }

    // Spec issue CPPPSM-217: changed to return by value
    std::string name() const
    {
        return holder_->name();
    }

    // Spec issue CPPPSM-217: changed to return by value
    std::string type_name() const
    {
        return holder_->type_name();
    }

public:
    AnyTopicDescription& swap(AnyTopicDescription& rhs)
    {
        std::swap(holder_, rhs.holder_);
        return *this;
    }

    template<typename T>
    AnyTopicDescription& operator =(const dds::topic::Topic<T>& topic)
    {
        *this = AnyTopicDescription(topic);
        return *this;
    }

    AnyTopicDescription& operator =(const AnyTopicDescription& other)
    {
        holder_ = other.holder_;
        return *this;
    }

public:
    // Spec issue CPPPSM-217: changed to return by value
    template<typename T>
    dds::topic::TopicDescription<T> get()
    {
        detail::TDHolder<T> * actual_holder =
            dynamic_cast<detail::TDHolder<T> *>(holder_.get());
        if (actual_holder == 0) {
            throw dds::core::InvalidDowncastError(
                "invalid cast to typed TopicDescription");
        }

        return actual_holder->get();
    }

public:
    const detail::TDHolderBase* operator->() const
    {
        return holder_.get();
    }

    detail::TDHolderBase* operator->()
    {
        return holder_.get();
    }

protected:
    dds::core::smart_ptr_traits<detail::TDHolderBase>::ref_type holder_;
};

}}

#endif /* OMG_DDS_TOPIC_ANY_TOPIC_DESCRIPTION_HPP_ */
