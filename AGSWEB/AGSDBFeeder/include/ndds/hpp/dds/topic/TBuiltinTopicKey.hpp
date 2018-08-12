#ifndef OMG_DDS_TOPIC_TBUILTIN_TOPIC_KEY_HPP_
#define OMG_DDS_TOPIC_TBUILTIN_TOPIC_KEY_HPP_

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

#include <dds/core/Value.hpp>

namespace dds { namespace topic {
  template <typename D>
  class TBuiltinTopicKey;
} }

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @RTI_class_definition class dds::topic::BuiltinTopicKey
 * @headerfile dds/topic/BuiltinTopicKey.hpp
 * @brief The key of the built-in topics
 *
 * @details \dref_details_BuiltinTopicKey_t
 */
template<typename D>
class dds::topic::TBuiltinTopicKey: public ::dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TBuiltinTopicKey, D)

    typedef typename D::VALUE_T VALUE_T;

    // Spec Issue CPPPSM-231: default constructor required
    /**
     * @brief Creates a key whose value() are all zeros
     */
    TBuiltinTopicKey() : dds::core::Value<D>()
    {
    }

    VALUE_T value() const
    {
        return this->delegate().value();
    }

  #ifdef DOXYGEN_DOCUMENTATION_ONLY
    /**
     * @brief Returns a copy of the four integers that represent the key
     */
    std::vector<uint32_t> value() const;
  #endif
};

#endif /* OMG_DDS_TOPIC_TBUILTIN_TOPIC_KEY_HPP_ */
