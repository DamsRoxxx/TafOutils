#ifndef OMG_TDDS_CORE_POLICY_QOS_POLICY_COUNT_HPP_
#define OMG_TDDS_CORE_POLICY_QOS_POLICY_COUNT_HPP_

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

namespace dds { namespace core { namespace policy {

/**
 * @ingroup DDSQosTypesModule
 * @RTI_class_definition class QosPolicyCount
 * @headerfile dds/core/policy/QosPolicyCount.hpp
 *
 * @brief @st_value_type Holds a counter for a QosPolicyId
 */
template <typename D>
class TQosPolicyCount : public dds::core::Value<D> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TQosPolicyCount, D)

    /**
     * @brief Creates an instance with the policy ID and its counter
     */
    TQosPolicyCount(QosPolicyId the_policy_id, int32_t the_count)
        : dds::core::Value<D>(the_policy_id, the_count)
    {
    }

    TQosPolicyCount(const TQosPolicyCount& other)
        : dds::core::Value<D>(other)
    {

    }

    /*
     * Spec error: need this constructor.
     *
     * Parametric constructor for creating an qos policy count
     * from some other type. This method is intended for internal
     * usage.
     */
    template <typename ARG0>
    TQosPolicyCount(const ARG0& arg0) : dds::core::Value<D>(arg0)
    {
    }

public:
    /**
     * @brief Gets the policy ID
     */
    QosPolicyId policy_id() const
    {
        return this->delegate().policy_id();
    }

    /**
     * @brief Gets the counter
     */
    int32_t count() const
    {
        return this->delegate().count();
    }
};

} } }

#endif // !defined(OMG_TDDS_CORE_POLICY_QOS_POLICY_COUNT_HPP_)
