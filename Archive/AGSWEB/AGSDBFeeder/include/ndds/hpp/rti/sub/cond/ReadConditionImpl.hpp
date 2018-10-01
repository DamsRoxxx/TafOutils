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

#ifndef RTI_DDS_SUB_COND_READ_CONDITION_HPP_
#define RTI_DDS_SUB_COND_READ_CONDITION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/corefwd.hpp>
#include <dds/sub/subfwd.hpp>
#include <dds/sub/AnyDataReader.hpp>
#include <dds/sub/status/DataState.hpp>
#include <rti/sub/status/DataStateEx.hpp>

#include <rti/core/cond/ConditionImpl.hpp>

namespace rti { namespace sub { namespace cond {

namespace detail {

OMG_DDS_API
DDS_Condition * create_native_read_condition(
    const dds::sub::AnyDataReader& reader,
    const dds::sub::status::DataState& status);

OMG_DDS_API
DDS_Condition * create_native_read_condition(
    const dds::sub::AnyDataReader& reader,
    const rti::sub::status::DataStateEx& status);

} // namespace detail

class OMG_DDS_API ReadConditionImpl : public rti::core::cond::Condition {
public:

    ReadConditionImpl(
        const dds::sub::AnyDataReader& dr,
        const dds::sub::status::DataState& status);

    template <typename Functor>
    ReadConditionImpl(
        const dds::sub::AnyDataReader& reader,
        const dds::sub::status::DataState& status,
        const Functor& the_handler)
        : Condition (
            detail::create_native_read_condition(reader, status), the_handler),
          reader_ (reader)
    {
    }

    ReadConditionImpl(
        const dds::sub::AnyDataReader& dr,
        const rti::sub::status::DataStateEx& status);

    template <typename Functor>
    ReadConditionImpl(
        const dds::sub::AnyDataReader& reader,
        const rti::sub::status::DataStateEx& status,
        const Functor& the_handler)
        : Condition (
            detail::create_native_read_condition(reader, status), the_handler),
          reader_ (reader)
    {
    }

    virtual ~ReadConditionImpl();

    dds::sub::status::DataState state_filter() const;

    rti::sub::status::DataStateEx state_filter_ex() const;

    const dds::sub::AnyDataReader& data_reader() const;

    void close();
    bool closed() const;
protected:
    ReadConditionImpl(
        DDS_ReadCondition * native_condition,
        const dds::sub::AnyDataReader& reader);

    template <typename Functor>
    ReadConditionImpl(
        DDS_ReadCondition * the_native_condition,
        const dds::sub::AnyDataReader& reader,
        const Functor& the_handler)
        : Condition (DDS_ReadCondition_as_condition(the_native_condition), the_handler),
          reader_ (reader)
    {
    }

private:
    dds::sub::AnyDataReader reader_;
};

} } } // namespace rti::sub::cond


#endif // RTI_DDS_SUB_COND_READ_CONDITION_HPP_

