#ifndef RTI_CORE_FWD_HPP_
#define RTI_CORE_FWD_HPP_

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

#include <vector>

#include <dds/core/ref_traits.hpp>

#include <dds/core/detail/conformance.hpp>
#include <rti/core/policy/policyfwd.hpp>

namespace rti { namespace core {

namespace cond {
    class Condition;
    class StatusCondition;
    class GuardCondition;
    class WaitSetImpl;
    class AsyncWaitSet;
    class AsyncWaitSetListener;
}

class Entity;
class InstanceHandle;
class KeyedBytesTopicTypeImpl;
class BytesTopicTypeImpl;
class StringTopicTypeImpl;
class KeyedStringTopicTypeImpl;

template <typename T>
class optional;

namespace status {
    class InconsistentTopicStatus;
    class LivelinessChangedStatus;
    class LivelinessLostStatus;
    class OfferedDeadlineMissedStatus;
    class OfferedIncompatibleQosStatus;
    class PublicationMatchedStatus;
    class RequestedDeadlineMissedStatus;
    class RequestedIncompatibleQosStatus;
    class SampleLostStatus;
    class SampleRejectedStatus;
    class SubscriptionMatchedStatus;
} // namespace status

namespace xtypes {

class DynamicTypeImpl;
class StructTypeImpl;
class EnumTypeImpl;
class UnionTypeImpl;
class MemberImpl;
class UnionMember;
class EnumMemberImpl;
class DynamicDataImpl;

template <typename TopicType>
TopicType convert(const DynamicDataImpl& sample);

template <typename TopicType>
DynamicDataImpl convert(const TopicType& sample);

OMG_DDS_API
std::string type_name(const DynamicTypeImpl& type);

} // namespace xtypes

} } // namespace rti::core

#endif // RTI_CORE_FWD_HPP_
