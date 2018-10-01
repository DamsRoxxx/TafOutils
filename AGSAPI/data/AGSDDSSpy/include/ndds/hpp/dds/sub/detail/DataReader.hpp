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
#ifndef OMG_DDS_SUB_DETAIL_DATA_READER_HPP_
#define OMG_DDS_SUB_DETAIL_DATA_READER_HPP_

#include <rti/sub/SelectorImpl.hpp>
#include <dds/topic/Topic.hpp>
#include <rti/sub/DataReaderImpl.hpp>

namespace dds { namespace sub { namespace detail {

    using rti::sub::DataReaderImpl; // Implementation of the delegate

} } } // dds::sub::detail


namespace dds { namespace sub { namespace functors { namespace detail { 

    using rti::sub::functors::MaxSamplesManipulatorFunctor;
    using rti::sub::functors::ContentFilterManipulatorFunctor;
    using rti::sub::functors::ConditionManipulatorFunctor;
    using rti::sub::functors::StateFilterManipulatorFunctor;
    using rti::sub::functors::InstanceManipulatorFunctor;
    using rti::sub::functors::NextInstanceManipulatorFunctor;
} } } } // dds::sub::functors::detail


#endif /* OMG_TDDS_SUB_DETAIL_DATA_READER_HPP_ */
