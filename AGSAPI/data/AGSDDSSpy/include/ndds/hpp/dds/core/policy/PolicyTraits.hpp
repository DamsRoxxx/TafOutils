#ifndef OMG_DDS_CORE_POLICY_POLICY_TRAITS_HPP_
#define OMG_DDS_CORE_POLICY_POLICY_TRAITS_HPP_

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

// --- Macros: ----------------------------------------------------------------

#define OMG_DDS_POLICY_TRAITS(POLICY, ID) \
    template <> \
    class policy_id<POLICY> { \
    public: \
    static const dds::core::policy::QosPolicyId value = ID; \
}; \
template <> \
class OMG_DDS_API policy_name<POLICY> { \
public:\
static const std::string& name(); \
};

#define OMG_DDS_DEFINE_POLICY_TRAITS(POLICY, NAME) \
    const std::string& dds::core::policy::policy_name<POLICY>::name() { \
  static std::string the_name = #NAME; \
  return the_name; \
}


namespace dds { namespace core { namespace policy  {

// --- Policy-trait classes: --------------------------------------------------

/**
 * @defgroup DDSQosTraitsModule QoS Policy Traits
 * @ingroup DDSQosTypesModule
 * @brief The traits types policy_id and policy_name provide
 * information about a QoS policy
 */

/**
 * @ingroup DDSQosTraitsModule
 * @brief Obtains the policy ID
 *
 * @tparam A QoS policy from the namespaces dds::core::policy or rti::core::policy
 *
 * Specializations for each QoS policy provide the following constant:
 * \code
 * static const dds::core::policy::QosPolicyId value;
 * \endcode
 *
 */
template<typename Policy>
class policy_id {
};

/**
 * @ingroup DDSQosTraitsModule
 * @brief Obtains the policy name
 *
 * @tparam A QoS policy from the namespaces dds::core::policy or rti::core::policy
 *
 * Specializations for each QoS policy provide the following method:
 * \code
 * static const std::string& name();
 * \endcode
 *
 * For example:
 *
 * \code
 * using namespace dds::core::policy;
 *
 * std::cout << policy_name<Reliability>::name() << std::endl; // Prints "Reliability"
 * \endcode
 */
template<typename Policy>
class policy_name {
};

} } } // namespace dds::core::policy

#endif // OMG_DDS_CORE_POLICY_POLICY_TRAITS_HPP_
