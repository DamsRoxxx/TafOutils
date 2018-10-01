#ifndef OMG_DDS_SUB_DETAIL_SUB_FWD_HPP_
#define OMG_DDS_SUB_DETAIL_SUB_FWD_HPP_

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

#include <dds/core/corefwd.hpp>
#include <rti/sub/subfwd.hpp>

namespace dds { namespace sub {

template <typename DELEGATE>
class TSubscriber;

namespace detail {

typedef dds::sub::TSubscriber<rti::sub::SubscriberImpl> Subscriber;

using rti::sub::DataReaderImpl;

using rti::sub::SampleImpl;


}   // namespace detail

namespace qos { namespace detail {

typedef dds::core::TEntityQos<rti::sub::qos::DataReaderQosImpl> DataReaderQos;
typedef dds::core::TEntityQos<rti::sub::qos::SubscriberQosImpl> SubscriberQos;

} }

namespace cond {

template <typename DELEGATE>
class TReadCondition;

template <typename DELEGATE>
class TQueryCondition;

namespace detail {

    typedef dds::sub::cond::TReadCondition<rti::sub::cond::ReadConditionImpl>
        ReadCondition;
    typedef dds::sub::cond::TQueryCondition<rti::sub::cond::QueryConditionImpl>
        QueryCondition;

} // namespace detail

} // namespace cond::detail

} } // namespace dds::sub

#endif // OMG_DDS_SUB_DETAIL_SUB_FWD_HPP_
