#ifndef OMG_DDS_TOPIC_TOPIC_INSTANCE_HPP_
#define OMG_DDS_TOPIC_TOPIC_INSTANCE_HPP_

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

#include <dds/core/InstanceHandle.hpp>

namespace dds { namespace topic {
  template <typename T>
  class TopicInstance;
} }

/** 
 * @ingroup DDSTopicEntityModule 
 * @brief Encapsulates a sample and its associated instance handle.
 *  
 * @tparam The type of the sample that the TopicInstance is encapsulating. 
 *
 * @see dds::pub::DataWriter::write(const dds::topic::TopicInstance<T>&)
 *
 */
template <typename T>
class dds::topic::TopicInstance {
public:

    /**
     * @brief Create a null TopicInstance
     *
     * The sample is default constructed and the instance handle is
     * equal to dds::core::null.
     */
    TopicInstance() : h_(dds::core::null) { }

    /**
     * @brief Create a TopicInstance with an InstanceHandle
     * 
     * The sample is default constructed and the instance handle is copied
     * from \p handle.
     */
    TopicInstance(const ::dds::core::InstanceHandle& the_handle) : h_(the_handle) { }

    /**
     * @brief Create a TopicInstance with a data sample and an InstanceHandle
     */
    TopicInstance(
        const ::dds::core::InstanceHandle& the_handle,
        const T& the_sample)
        : h_(the_handle), sample_(the_sample)
    {
    }

    /**
     * @brief Obtains the InstanceHandle
     */
    operator dds::core::InstanceHandle() const
    {
        return handle();
    }

    /**
     * @brief Obtains the InstahnceHandle
     */
    dds::core::InstanceHandle handle() const
    {
        return h_;
    }

    /**
     * @brief Sets the InstanceHandle
     */
    void handle(const ::dds::core::InstanceHandle& the_handle)
    {
        h_ = the_handle;
    }

    /**
     * @brief Gets the sample by const reference
     */
    const T& sample() const
    {
        return sample_;
    }

    /**
     * @brief Gets the sample by reference
     */
    T& sample()
    {
        return sample_;
    }

    /**
     * @brief Assigns the data sample
     *
     * @param the_sample The data sample to copy into this TopicInstance
     */
    void sample(const T& the_sample)
    {
        sample_ = the_sample;
    }

private:
    dds::core::InstanceHandle h_;
    T sample_;
};

#endif // OMG_DDS_TOPIC_TOPIC_INSTANCE_HPP_

