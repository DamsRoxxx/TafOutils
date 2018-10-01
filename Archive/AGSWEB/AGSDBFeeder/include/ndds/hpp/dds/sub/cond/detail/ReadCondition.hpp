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
#ifndef OMG_DDS_SUB_DETAIL_READ_CONDITION_HPP_
#define OMG_DDS_SUB_DETAIL_READ_CONDITION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/cond/TReadCondition.hpp>
#include <rti/sub/cond/ReadConditionImpl.hpp>

namespace dds { namespace sub { namespace cond { namespace detail {

typedef dds::sub::cond::TReadCondition<rti::sub::cond::ReadConditionImpl>
    ReadCondition;

} } } }

namespace rti { namespace sub { namespace cond {

/**
 * @relates dds::sub::cond::ReadCondition
 *
 * @brief @extension Creates a ReadCondition with the extended DataStateEx.
 *
 * (Note: this function is in the rti::sub::cond namespace)
 *
 * The usual way to create a dds::sub::cond::ReadCondition is the constructor
 * that receives a dds::sub::status::DataState. This extension function allows
 * using rti::sub::status::DataStateEx, which includes additional
 * state masks.
 */
inline dds::sub::cond::detail::ReadCondition create_read_condition_ex(
    const dds::sub::AnyDataReader& reader,
    const ::rti::sub::status::DataStateEx& status)
{
    dds::sub::cond::detail::ReadCondition condition(
        new rti::sub::cond::ReadConditionImpl(reader, status));
    condition.delegate()->remember_reference(condition.delegate());
    return condition;
}

/**
 * @relates dds::sub::cond::ReadCondition
 *
 * @brief @extension Creates a ReadCondition with the extended DataStateEx and
 * a handler.
 *
 * (Note: this function is in the rti::sub::cond namespace)
 *
 * The usual way to create a dds::sub::cond::ReadCondition is the constructor
 * that receives a dds::sub::status::DataState. This extension function allows
 * using rti::sub::status::DataStateEx, which includes additional
 * state masks.
 */
template <typename Functor>
dds::sub::cond::detail::ReadCondition create_read_condition_ex(
    const dds::sub::AnyDataReader& reader,
    const ::rti::sub::status::DataStateEx& status,
    const Functor& handler)
{
    dds::sub::cond::detail::ReadCondition condition(
        new rti::sub::cond::ReadConditionImpl(reader, status, handler));
    condition.delegate()->remember_reference(condition.delegate());
    return condition;
}

} } } // rti::sub::cond

#endif // OMG_DDS_SUB_DETAIL_READ_CONDITION_HPP_
