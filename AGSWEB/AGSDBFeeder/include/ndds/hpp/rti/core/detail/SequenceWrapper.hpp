/*
 Copyright (c) 2013, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_SEQUENCE_WRAPPER_HPP_
#define RTI_DDS_CORE_SEQUENCE_WRAPPER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Exception.hpp>

namespace rti { namespace core { namespace detail {

// A simple wrapper to help use an untyped data sequence as provided by a
// DDS_DataReader
template <typename T>
class ContiguousDataSequence {
public:
    typedef T DataType;

    ContiguousDataSequence()
        : data_buffer_(NULL), length_(0)
    {
    }

    ContiguousDataSequence(void ** data_buffer, size_t the_length)
        : data_buffer_(reinterpret_cast<DataType**>(data_buffer)),
          length_(the_length)
    {
    }

    DataType& operator[] (size_t i)
    {
        return *data_buffer_[i];
    }

    const DataType& operator[] (size_t i) const
    {
        return *data_buffer_[i];
    }

    size_t length() const
    {
        return length_;
    }

    DataType ** get_buffer()
    {
        return data_buffer_;
    }

    const DataType ** get_buffer() const
    {
        return data_buffer_;
    }

    void swap(ContiguousDataSequence& other)
    {
        std::swap(data_buffer_, other.data_buffer_);
        std::swap(length_, other.length_);
    }

private:
    DataType ** data_buffer_;
    size_t length_;
};

} } }
#endif /* RTI_DDS_CORE_SEQUENCE_WRAPPER_HPP_ */
