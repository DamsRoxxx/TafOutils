/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20mar14,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_COND_QUERY_CONDITION_HPP_
#define RTI_DDS_SUB_COND_QUERY_CONDITION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/corefwd.hpp>
#include <dds/sub/Query.hpp>
#include <rti/sub/cond/ReadConditionImpl.hpp>

namespace rti { namespace sub { namespace cond {

namespace detail {

OMG_DDS_API
DDS_ReadCondition * create_native_query_condition(
    const dds::sub::AnyDataReader& reader,
    const dds::sub::Query& query,
    const dds::sub::status::DataState& status);

OMG_DDS_API
DDS_ReadCondition * create_native_query_condition(
    const dds::sub::AnyDataReader& reader,
    const dds::sub::Query& query,
    const rti::sub::status::DataStateEx& status);

} // namespace detail

/** @RTI_class_definition NA */
class OMG_DDS_API QueryConditionImpl : public ::rti::sub::cond::ReadConditionImpl {
public:

    typedef dds::sub::Query::iterator iterator;
    typedef dds::sub::Query::const_iterator const_iterator;

    QueryConditionImpl(
        const dds::sub::Query& query,
        const dds::sub::status::DataState& status);


    template <typename Functor>
    QueryConditionImpl(
        const dds::sub::Query& query,
        const dds::sub::status::DataState& status,
        const Functor& the_handler)
        : ReadConditionImpl (
            detail::create_native_query_condition(query.data_reader(), query, status),
            query.data_reader(),
            the_handler)
    {
    }

    QueryConditionImpl(
        const dds::sub::Query& query,
        const rti::sub::status::DataStateEx& status);


    template <typename Functor>
    QueryConditionImpl(
        const dds::sub::Query& query,
        const rti::sub::status::DataStateEx& status,
        const Functor& the_handler)
        : ReadConditionImpl (
            detail::create_native_query_condition(query.data_reader(), query, status),
            query.data_reader(),
            the_handler)
    {
    }

    ~QueryConditionImpl();

    std::string expression() const;

    template<typename FWIterator>
    void parameters(const FWIterator& begin, const FWIterator& end)
    {
        parameters(dds::core::StringSeq(begin, end));
    }

    // Extension
    /** 
     * @memberof dds::sub::cond::QueryCondition 
     * @brief @extension Set the parameters 
     */ 
    void parameters(const dds::core::StringSeq& parameters);

    uint32_t parameters_length() const;

    dds::core::StringSeq parameters() const;
/** @RTI_remove_lines 1 */
};

} } } // namespace rti::sub::cond

#endif // RTI_DDS_SUB_COND_QUERY_CONDITION_HPP_

