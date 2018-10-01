#ifndef OMG_TDDS_CORE_QOS_ENTITY_QOS_HPP_
#define OMG_TDDS_CORE_QOS_ENTITY_QOS_HPP_

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

namespace dds {
  namespace core {
    template <typename DELEGATE>
    class TEntityQos;
  }
}

/** 
 *  @brief Acts as a container for Qos policies allowing to set
 * and retrieve all the policies of an entity as a unit. 
 */
template <typename DELEGATE>
class dds::core::TEntityQos : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TEntityQos, DELEGATE)

    TEntityQos() { }

    template<typename Policy>
    const Policy& policy() const
    {
        return this->delegate().template policy<Policy>();
    }

    template<typename Policy>
    Policy& policy()
    {
        return this->delegate().template policy<Policy>();
    }

    //!RTI_doc_block[EntityQosCopy]
    /**
     * @brief Sets a policy
     *
     * @see policy()
     * @see \ref DDSQosModule_set_qos
     */
    template<typename Policy>
    TEntityQos& policy(const Policy& p)
    {
        policy<Policy>() = p;
        return *this;
    }
    
    /**
     * @brief Sets a policy
     *
     * @see policy()
     * @see \ref DDSQosModule_set_qos
     */
    template<typename Policy>
    TEntityQos& operator <<(const Policy& p)
    {
        // set policy from p
        return policy(p);
    }

    /**
     * @brief Copies the values of a policy
     *
     * @param p The destination where to copy the current value of the Policy
     *
     * @see policy()
     * @see \ref DDSQosModule_set_qos
     */
    template<typename Policy>
    const TEntityQos& operator >>(Policy& p) const
    {
        // copy policy into p
        p = policy<Policy>();
        return *this;
    }
    //!RTI_doc_block[EntityQosCopy]

    template<typename T>
    TEntityQos<DELEGATE>& operator =(const TEntityQos<T>& other)
    {
        this->delegate() = other;
        return *this;
    }
};

#endif // OMG_TDDS_CORE_QOS_ENTITY_QOS_HPP_
