/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_SAMPLE_IDENTITY_HPP_
#define RTI_DDS_CORE_SAMPLE_IDENTITY_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <rti/core/NativeValueType.hpp>
#include <rti/core/detail/NativeConversion.hpp>

#include <rti/core/Guid.hpp>
#include <rti/core/SequenceNumber.hpp>

namespace rti { namespace core {

class SampleIdentityAdapter {
public:
    typedef struct DDS_SampleIdentity_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_SampleIdentity_t_initialize(&native_value);
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_SampleIdentity_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_SampleIdentity_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

class SampleIdentity;

template <>
struct native_type_traits<SampleIdentity> {
    typedef rti::core::SampleIdentityAdapter adapter_type;
    typedef DDS_SampleIdentity_t native_type;
};

/** 
 * @ingroup DDSInfrastructureModule 
 * @RTI_class_definition class SampleIdentity 
 * @headerfile SampleIdentity.hpp "rti/core/SampleIdentity.hpp"
 *  
 * @brief @extension @st_value_type A SampleIdentity defines a pair
 * (Virtual Writer Guid, SequenceNumber) that uniquely identifies a sample 
 * within a DDS domain and a Topic.
 */
class SampleIdentity : public NativeValueType<SampleIdentity> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SampleIdentity)

    typedef NativeValueType<SampleIdentity> Base;

    /**
     * @brief Create a default SampleIdentity object
     */
    SampleIdentity()
    {
    }

    /**
     * @brief Create a SampleIdentity with the provided Guid and 
     * SequenceNumber 
     * 
     * @param the_writer_guid The Guid to create the SampleIdentity with
     * @param the_sequence_number The SequenceNumber to create the SampleIdentity 
     * with 
     */
    SampleIdentity(
        const Guid& the_writer_guid,
        const SequenceNumber& the_sequence_number)
    {
        writer_guid() = the_writer_guid;
        sequence_number() = the_sequence_number;
    }

    SampleIdentity(const struct DDS_SampleIdentity_t &native_sample_identity) 
      : Base(native_sample_identity)
    {
    }

    /**
     * @brief Get the 16-byte identifier identifying the virtual Guid.  
     */
    const Guid& writer_guid() const
    {
        return rti::core::native_conversions::cast_from_native<Guid>(
            native().writer_guid);
    }

    /**
     * @brief Get the 16-byte identifier identifying the virtual Guid.  
     */
    Guid& writer_guid()
    {
        return rti::core::native_conversions::cast_from_native<Guid>(
            native().writer_guid);
    }

    /**
     * @brief Get the monotonically increasing 64-bit SequenceNumber that identifies 
     * the sample in the data source.
     */
    const SequenceNumber& sequence_number() const
    {
        return rti::core::native_conversions::cast_from_native<SequenceNumber>(
            native().sequence_number);
    }

    /**
     * @brief Get the monotonically increasing 64-bit SequenceNumber that identifies 
     * the sample in the data source.
     */
    SequenceNumber& sequence_number()
    {
        return rti::core::native_conversions::cast_from_native<SequenceNumber>(
            native().sequence_number);
    }

    /**
     * @brief Special value to indicate that \ndds will automatically assign
     * the identity of a sample.
     */
    static SampleIdentity automatic()
    {
        return SampleIdentity(DDS_AUTO_SAMPLE_IDENTITY);
    }

    /**
     * @brief An invalid or unknown sample identity.
     */
    static SampleIdentity unknown()
    {
        return SampleIdentity(DDS_UNKNOWN_SAMPLE_IDENTITY);
    }
};

/**
 * @relates rti::core::SampleIdentity
 *
 * @brief Prints a SampleIdentity to an output stream
 */
inline std::ostream& operator<<(std::ostream& out, const SampleIdentity& sid)
{
    out << "[Guid: " << sid.writer_guid()
        << ", SN: " << sid.sequence_number() << "]";
    return out;
}

} } // namespace rti::core

#endif // RTI_DDS_CORE_SAMPLE_IDENTITY_HPP_
