#ifndef OMG_DDS_SUB_DETAIL_QUERY_CONDITION_HPP_
#define OMG_DDS_SUB_DETAIL_QUERY_CONDITION_HPP_

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
#include <dds/sub/cond/TQueryCondition.hpp>
#include <rti/sub/cond/QueryConditionImpl.hpp>

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

namespace dds { namespace sub { namespace cond { namespace detail {

typedef dds::sub::cond::TQueryCondition<rti::sub::cond::QueryConditionImpl>
    QueryCondition;

} } } }

namespace rti { namespace sub { namespace cond {

/**
 * @ingroup DDSQueryConditionModule
 *
 * @brief @extension Creates a QueryCondition with the extended DataStateEx.
 *
 * (Note: this function is in the rti::sub::cond namespace)
 *
 * The usual way to create a dds::sub::cond::QueryCondition is the constructor
 * that receives a dds::sub::status::DataState. This extension function allows
 * using rti::sub::status::DataStateEx, which includes additional
 * state masks.
 */
inline dds::sub::cond::detail::QueryCondition create_query_condition_ex(
    const dds::sub::Query& query,
    const ::rti::sub::status::DataStateEx& status)
{
    dds::sub::cond::detail::QueryCondition condition(
        new rti::sub::cond::QueryConditionImpl(query, status));
    condition.delegate()->remember_reference(condition.delegate());
    return condition;
}

/**
 * @ingroup DDSQueryConditionModule
 *
 * @brief @extension Creates a QueryCondition with the extended DataStateEx and
 * a handler.
 *
 * (Note: this function is in the rti::sub::cond namespace)
 *
 * The usual way to create a dds::sub::cond::QueryCondition is the constructor
 * that receives a dds::sub::status::DataState. This extension function allows
 * using rti::sub::status::DataStateEx, which includes additional
 * state masks.
 */
template <typename Functor>
dds::sub::cond::detail::QueryCondition create_query_condition_ex(
    const dds::sub::Query& query,
    const ::rti::sub::status::DataStateEx& status,
    const Functor& handler)
{
    dds::sub::cond::detail::QueryCondition condition(
        new rti::sub::cond::QueryConditionImpl(query, status, handler));
    condition.delegate()->remember_reference(condition.delegate());
    return condition;
}

} } } // rti::sub::cond

#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

#endif /* OMG_DDS_SUB_DETAIL_QUERY_CONDITION_HPP_ */
