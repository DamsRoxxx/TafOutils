#ifndef OMG_DDS_SUB_SUB_FWD_HPP_
#define OMG_DDS_SUB_SUB_FWD_HPP_

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

#include <dds/core/detail/conformance.hpp>
#include <dds/sub/detail/subfwd.hpp>

namespace dds { namespace sub {

class AnyDataReader;

class AnyDataReaderListener;

template <typename T,
          template <typename Q> class DELEGATE = dds::sub::detail::DataReaderImpl>
class DataReader;

template <typename T>
class DataReaderListener;

class NoOpAnyDataReaderListener;

template <typename T>
class NoOpDataReaderListener;

class NoOpSubscriberListener;

template <typename T>
class ReaderQuery;


template <
    typename T,
    template <typename Q> class DELEGATE = detail::SampleImpl>
class Sample;

typedef dds::sub::detail::Subscriber Subscriber;

class SubscriberListener;

namespace cond {
    typedef dds::sub::cond::detail::ReadCondition ReadCondition;
#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
    typedef dds::sub::cond::detail::QueryCondition QueryCondition;
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
}

namespace qos {
    typedef dds::sub::qos::detail::DataReaderQos DataReaderQos;
    typedef dds::sub::qos::detail::SubscriberQos SubscriberQos;
}

namespace status {
    class ReaderState;
    class DataState;
}

} }

#endif /* OMG_DDS_SUB_SUB_FWD_HPP_ */
