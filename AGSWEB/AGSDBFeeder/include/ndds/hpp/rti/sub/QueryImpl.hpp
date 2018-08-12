/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,01apr14,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_QUERY_IMPL_HPP_
#define RTI_DDS_SUB_QUERY_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/sub/AnyDataReader.hpp>
#include <rti/topic/FilterImpl.hpp>

namespace rti { namespace sub {

class QueryImpl : public rti::topic::FilterImpl {
public:

    template<typename T>
    QueryImpl(
        const dds::sub::DataReader<T>& dr, const std::string& query_expression)
        : FilterImpl(query_expression),
          reader_ (dr)
    {
    }

    template<typename T, typename FWIterator>
    QueryImpl(
        const dds::sub::DataReader<T>& dr,
        const std::string& query_expression,
        const FWIterator& params_begin, const FWIterator& params_end)
        : FilterImpl(query_expression, params_begin, params_end),
          reader_ (dr)
    {
    }

    const dds::sub::AnyDataReader& data_reader() const
    {
        return reader_;
    }

private:
    dds::sub::AnyDataReader reader_;
};

} } // namespace rti::sub

#endif // RTI_DDS_SUB_QUERY_IMPL_HPP_
