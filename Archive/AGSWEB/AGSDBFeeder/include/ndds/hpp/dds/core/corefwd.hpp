#ifndef OMG_DDS_CORE_CORE_FWD_HPP_
#define OMG_DDS_CORE_CORE_FWD_HPP_

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

#include <dds/core/detail/corefwd.hpp>

namespace dds { namespace core {


namespace detail {

}

using dds::core::detail::optional;

typedef dds::core::detail::Entity Entity;
typedef dds::core::detail::BytesTopicType BytesTopicType;
typedef dds::core::detail::StringTopicType StringTopicType;
typedef dds::core::detail::KeyedStringTopicType KeyedStringTopicType;
typedef dds::core::detail::KeyedBytesTopicType KeyedBytesTopicType;

class Duration;

template <typename DELEGATE>
class TEntityQos;

namespace cond {
    typedef dds::core::cond::detail::Condition Condition;
}

namespace xtypes {

typedef detail::DynamicType DynamicType;
typedef detail::StructType StructType;
typedef detail::EnumType EnumType;
typedef detail::UnionType UnionType;
typedef detail::Member Member;
typedef detail::UnionMember UnionMember;
typedef detail::EnumMember EnumMember;

typedef detail::DynamicData DynamicData;

} // namespace xtypes

} }

#endif /* OMG_DDS_CORE_CORE_FWD_HPP_ */
