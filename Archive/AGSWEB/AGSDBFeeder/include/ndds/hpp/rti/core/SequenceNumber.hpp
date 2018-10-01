/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_SEQUENCE_NUMBER_HPP_
#define RTI_DDS_CORE_SEQUENCE_NUMBER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure_impl.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

class SequenceNumberAdapter {
public:
    typedef struct DDS_SequenceNumber_t native_type;

    static void initialize(native_type& native_value)
    {
        native_value = DDS_SEQUENCE_NUMBER_UNKNOWN;
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        destination = source;
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_SequenceNumber_compare(&first, &second) == 0;
    }
};

class SequenceNumber;

template <>
struct native_type_traits<SequenceNumber> {
    typedef rti::core::SequenceNumberAdapter adapter_type;
    typedef DDS_SequenceNumber_t native_type;
};

/** 
 * @ingroup DDSInfrastructureModule 
 * @RTI_class_definition class SequenceNumber 
 * @headerfile rti/core/SequenceNumber.hpp
 *  
 * @brief @extension @st_value_type A class representing the DDS 64-bit 
 * Sequence Number
 */
class OMG_DDS_API SequenceNumber : public NativeValueType<SequenceNumber> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SequenceNumber)

    typedef NativeValueType<SequenceNumber> Base;

    // Special values
    /**
     * @brief Create a SequenceNumber representing 0
     */
    static SequenceNumber zero()
    {
        return DDS_SEQUENCE_NUMBER_ZERO;
    }

    /**
     * @brief Create a SequenceNumber representing the 
     * unknown SequenceNumber value
     */
    static SequenceNumber unknown()
    {
        return DDS_SEQUENCE_NUMBER_UNKNOWN;
    }

    /**
     * @brief Create a SequenceNumber representing the highest, most positive 
     * value for the sequence number 
     */
    static SequenceNumber maximum()
    {
        return DDS_SEQUENCE_NUMBER_MAX;
    }

    /**
     * @brief Create a SequenceNumber that will cause the value to be internally 
     * determined by @ndds 
     *
     * @see rti::core::WriteParams::replace_auto()
     */
    static SequenceNumber automatic()
    {
        return DDS_AUTO_SEQUENCE_NUMBER;
    }

    /**
     * @brief Create a default SequenceNumber, equal to unknown()
     */
    SequenceNumber()
    {
    }

    /**
     * @brief Create a SequenceNumber with the provided high and low values 
     * @param high_value The value for the most significant part of the sequence number.   
     * @param low_value The value for the least significant part of the sequence number.   
     */
    SequenceNumber(int32_t high_value, uint32_t low_value)
    {
        high(high_value);
        low(low_value);
    }

    /**
     * @brief Creates a SequenceNumber from an int64_t
     */
    /*implicit*/ SequenceNumber(int64_t the_value)
    {
        value(the_value);
    }

    SequenceNumber(const DDS_SequenceNumber_t &native_sequence_number)
        : Base(native_sequence_number)
    {
    }

    /**
     * @brief Get the value of the most significant part of the sequence number.
     */
    int32_t high() const
    {
        return native().high;
    }

    /**
     * @brief Set the value of the most significant part of the sequence number.
     */
    SequenceNumber& high(int32_t the_value)
    {
        native().high = the_value;
        return *this;
    }

    /**
     * @brief Get the value of the most significant part of the sequence number.
     */
    uint32_t low() const
    {
        return native().low;
    }

    /**
     * @brief Set the value of the least significant part of the sequence number.
     */
    SequenceNumber& low(uint32_t the_value)
    {
        native().low = the_value;
        return *this;
    }

    /**
     * @brief Get the value of the sequence number
     */
    long long value() const;

    /**
     * @brief Set the value of the sequence number
     */
    void value(long long value);
    
    /**
     * @brief Add two SequenceNumbers
     */
    SequenceNumber operator+(const SequenceNumber& other) const;

    /**
     * @brief Subtract one SequenceNumber from another
     */
    SequenceNumber operator-(const SequenceNumber& other) const;

    /**
     * @brief Compound assignment operator, assigning the result of the 
     * addition to the current SequenceNumber object 
     */
    SequenceNumber& operator+=(const SequenceNumber& other);

    /**
     * @brief Compound assignment operator, assigning the result of the 
     * subtraction to the current SequenceNumber object 
     */
    SequenceNumber& operator-=(const SequenceNumber& other);

    /**
     * @brief Pre-increment the value of the SequenceNumber by 1
     */
    SequenceNumber operator++();
    /**
     * @brief Post-increment the value of the SequenceNumber by 1
     */
    SequenceNumber operator++(int);

    /**
     * @brief Pre-decrement the value of the SequenceNumber by 1
     */
    SequenceNumber operator--();

    /**
     * @brief Post-decrement the value of the SequenceNumber by 1
     */
    SequenceNumber operator--(int);

    /**
     * @brief Compare two SequenceNumbers for a less-than relationship
     */
    bool operator<(const SequenceNumber& other) const;
    /**
     * @brief Compare two SequenceNumbers for a less-than-or-equal relationship
     */
    bool operator<=(const SequenceNumber& other) const;
    /**
     * @brief Compare two SequenceNumbers for a greater-than relationship
     */
    bool operator>(const SequenceNumber& other) const;
    /**
     * @brief Compare two SequenceNumbers for a greater-than-or-equal relationship
     */
    bool operator>=(const SequenceNumber& other) const;
};


/**
 * @relates rti::core::SequenceNumber
 *
 * @brief Prints a SequenceNumber to an output stream
 */
inline std::ostream& operator<<(std::ostream& out, const SequenceNumber& sn)
{
    out << sn.value();
    return out;
}

} } // namespace rti::core

#endif // RTI_DDS_CORE_SEQUENCE_NUMBER_HPP_
