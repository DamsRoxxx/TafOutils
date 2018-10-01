/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_SAMPLE_IMPL_HPP_
#define RTI_DDS_SUB_SAMPLE_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/SampleInfo.hpp>
#include <rti/sub/subfwd.hpp>

#include "ndds/ndds_c.h"

namespace rti { namespace sub {

template<typename T>
class SampleImpl {
public:
    typedef T DataType;
    typedef dds::sub::SampleInfo InfoType;

    /**
     * Create a sample with invalid data.
     */
    SampleImpl()
    {
        // The default value for is_valid is False, so 
        // nothing to be done here
    }

    SampleImpl(const DataType& the_data, const dds::sub::SampleInfo& the_info)
        : data_(the_data), 
          info_(the_info)
    {}

    SampleImpl(const LoanedSample<DataType>& sample_ref)
        : data_(sample_ref.data()),
          info_(sample_ref.info())
    {
    }

    SampleImpl(const SampleImpl& other)
        : data_(other.data()), 
          info_(other.info())
    {
    }

    const DataType& data() const
    {
        return data_;
    }

    void data(const DataType& the_data)
    {
        data_ = the_data;
    }

    const dds::sub::SampleInfo& info() const
    {
        return info_;
    }

    void info(const dds::sub::SampleInfo& the_info)
    {
        info_ = the_info;
    }

    SampleImpl & operator=(const LoanedSample<DataType>& sample_ref)
    {
        SampleImpl(sample_ref).swap(*this);
        return *this;
    }

    void swap(SampleImpl & other) throw()
    {
        using std::swap;

        swap(data_, other.data_);
        swap(info_, other.info_);
    }

private:
    DataType data_; 
    InfoType info_;

};

} } // namespace rti::sub

#endif // RTI_DDS_SUB_SAMPLE_IMPL_HPP_
