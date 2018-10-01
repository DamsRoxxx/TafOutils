/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
-------------------- 
1.0a,20jan15,eam Created
============================================================================= */

#ifndef RTI_DDS_SUB_ACK_RESPONSE_DATA_HPP_
#define RTI_DDS_SUB_ACK_RESPONSE_DATA_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"
#include <dds/core/types.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace sub {

extern OMG_DDS_API_VARIABLE const uint8_t DUMMY_END;

class AckResponseData;

class AckResponseDataAdapter {
public:
    typedef DDS_AckResponseData_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_AckResponseData_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_AckResponseData_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        if (DDS_AckResponseData_t_copy(&destination, &source) == NULL){
            throw std::bad_alloc();
        }
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_AckResponseData_equals(&first, &second) == DDS_BOOLEAN_TRUE;
    } 
};

} // namespace sub

namespace core {

template<>
struct native_type_traits<rti::sub::AckResponseData> {
    typedef rti::sub::AckResponseDataAdapter adapter_type;
    typedef rti::sub::AckResponseDataAdapter::native_type native_type;
};

} // namespace core

namespace sub {

/**
 * @RTI_class_definition class AckResponseData
 * @ingroup DDSAckResponseDataModule
 * @headerfile rti/sub/AckResponseData.hpp
 * @brief @extension Data payload associated to an application-level acknowledgment
 *
 * When a \idref_DataReader explicitly acknowledges samples with
 * \idref_DataReader_acknowledge_sample or \idref_DataReader_acknowledge_all,
 * it may specify opaque data to send as payload in the acknowledgment message
 * sent to the \idref_DataWriter.
 */
class OMG_DDS_API AckResponseData : public rti::core::NativeValueType<AckResponseData> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(AckResponseData)

private:
    typedef rti::core::NativeValueType<AckResponseData> Base;

public:

    /**
     * @brief Creates an empty sequence of bytes
     */
    AckResponseData() : Base()
    {
    }

    AckResponseData(const DDS_AckResponseData_t& native_value) 
      : Base(native_value)
    {
    }

    /**
     * @brief Creates an instance by copying a sequence of bytes
     */
    explicit AckResponseData(const dds::core::ByteSeq& sequence)
    {
        value(sequence.begin(), sequence.end());
    }

    AckResponseData(const uint8_t* value_begin, const uint8_t* value_end);

public:
    template <typename OCTET_ITER>
    AckResponseData& value(OCTET_ITER the_begin, OCTET_ITER the_end)
    {
        value_impl(
            the_begin,
            the_end,
            typename std::iterator_traits<OCTET_ITER>::iterator_category());

        return *this;
    }

    /**
     * @brief Gets the sequence of bytes
     */
    dds::core::ByteSeq value() const
    {
        return dds::core::ByteSeq(begin(), end());
    }

    /**
     * @brief Sets the sequence of bytes
     */
    dds::core::ByteSeq& value(dds::core::ByteSeq& dst) const;

    /**
     * @brief Provides access to the beginning of the sequence of bytes
     */
    const uint8_t* begin() const;

    /**
     * @brief Gets the end of the sequence
     */
    const uint8_t* end() const;

private:
    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::random_access_iterator_tag)
    {
        // Knowing the size of the range [begin, end) allows for an optimized
        // implementation.
        resize(the_end - the_begin);
        std::copy(
            the_begin, the_end, DDS_OctetSeq_get_contiguous_buffer(&native().value));
    }

    template <typename OCTET_ITER>
    void value_impl(
        OCTET_ITER the_begin, OCTET_ITER the_end, std::input_iterator_tag)
    {
        // Generic, less-efficient implementation for iterators that don't
        // support calculating the length of a range
        int sequence_index = 0;
        for (OCTET_ITER it = the_begin; it != the_end; ++it) {
            resize(sequence_index + 1);
            *DDS_OctetSeq_get_reference(&native().value, sequence_index) = *it;
            sequence_index++;
        }
    }

    void resize(size_t length);
    size_t length() const;

};

} } // namespace rti::sub

#endif // RTI_DDS_SUB_ACK_RESPONSE_DATA_HPP_
