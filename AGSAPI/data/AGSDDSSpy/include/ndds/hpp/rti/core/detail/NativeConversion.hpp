/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,22jan13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_NATIVE_CONVERSION_HPP_
#define RTI_DDS_CORE_NATIVE_CONVERSION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <rti/core/NativeValueType.hpp> // native_type_traits<>
#include <dds/core/Duration.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/core/Time.hpp>
#include <dds/core/vector.hpp>

namespace rti { namespace core { namespace native_conversions {

// Duration
inline void to_native(
    DDS_Duration_t& destination, const dds::core::Duration& source)
{
    destination.sec = source.sec();
    destination.nanosec = source.nanosec();
}

inline dds::core::Duration from_native(const DDS_Duration_t& source)
{
    return dds::core::Duration(source.sec, source.nanosec);
}

// Time
inline void to_native(
   DDS_Time_t& destination, const dds::core::Time& source)
{
    destination.sec = source.sec();
    destination.nanosec = source.nanosec();
}

inline dds::core::Time from_native(const DDS_Time_t& source)
{
    return dds::core::Time(source.sec, source.nanosec);
}

inline dds::core::InstanceHandle from_native_handle(
        const DDS_InstanceHandle_t& source)
{
    return dds::core::InstanceHandle(source);
}

inline dds::core::InstanceHandleSeq from_native_handle_seq(
        const DDS_InstanceHandleSeq& native_seq)
{
    dds::core::InstanceHandleSeq seq(native_seq._length, dds::core::InstanceHandle::nil());
    std::transform(
            native_seq._contiguous_buffer,
            native_seq._contiguous_buffer + native_seq._length,
            seq.begin(),
            from_native_handle);

    return seq;
}

// string => char * (making a copy)
OMG_DDS_API
void to_native(char *& destination, const std::string& source);

// vector<string> => StringSeq
OMG_DDS_API
void to_native(DDS_StringSeq& destination, const dds::core::StringSeq& source);

// Generic conversion from native sequence TSeq to vector<T>. It requires
// that T can be implicitly constructed from TSeq's element type.
template <typename T, typename TSeq>
std::vector<T> from_native(const TSeq& native_sequence)
{
    return std::vector<T>(
        native_sequence._contiguous_buffer,
        native_sequence._contiguous_buffer + native_sequence._length);
}

template <>
inline std::vector<dds::core::InstanceHandle >
from_native<dds::core::InstanceHandle, DDS_InstanceHandleSeq>(
        const DDS_InstanceHandleSeq& native_sequence)
{
    return from_native_handle_seq(native_sequence);
}

// Generic conversion to native sequence NativeSeq from TSeq.
template<typename T, typename TSeq, typename NativeSeq>
void to_native(const TSeq& the_sequence, NativeSeq& old_native_seq)
{
    using namespace rti::core::native_conversions;

    // This "magic" cast works because all the types involved have the same
    // memory layout as the C type
    dds::core::vector<T>& native_seq =
        reinterpret_cast<dds::core::vector<T>&>(old_native_seq);

    native_seq.resize(the_sequence.size());
    std::copy(the_sequence.begin(), the_sequence.end(), native_seq.begin());
}

// Generic conversion to native sequence NativeSeq from TSeq for types that 
// don't have a default ctor
template<typename T, typename TSeq, typename NativeSeq>
void to_native(
    const TSeq& the_sequence, NativeSeq& old_native_seq, const T& value)
{
    using namespace rti::core::native_conversions;

    // This "magic" cast works because all the types involved have the same
    // memory layout as the C type
    dds::core::vector<T>& native_seq =
        reinterpret_cast<dds::core::vector<T>&>(old_native_seq);

    native_seq.resize(the_sequence.size(), value);
    std::copy(the_sequence.begin(), the_sequence.end(), native_seq.begin());
}

} } } // namespace rti::core::native_conversions

#endif // RTI_DDS_CORE_NATIVE_CONVERSION_HPP_

