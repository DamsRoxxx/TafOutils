/* $Id$

(c) Copyright, Real-Time Innovations, 2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,29feb16,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_CDR_SERIALIZATION_HPP_
#define RTI_DDS_TOPIC_CDR_SERIALIZATION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#ifndef RTI_NO_CDR_TEMPLATES

#include <vector>
#include <string>

#include "cdr/cdr_stream.h"
#include "dds_c/dds_c_topic.h"

#include <dds/core/SafeEnumeration.hpp>
#include <dds/core/String.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/array.hpp>
#include <rti/topic/TopicTraits.hpp>

#include <rti/core/Pointer.hpp>

#include <rti/topic/cdr/cdrfwd.hpp>
#include <rti/topic/cdr/SerializationHelpers.hpp>
#include <rti/topic/cdr/PrimitiveTypes.hpp>
#include <rti/topic/cdr/SequenceSerialization.hpp>

/*
 * Serialization and deserialization utilities for type-plugin generated code
 */

namespace rti { namespace topic { namespace cdr {

inline unsigned int calculate_serialized_size(
        const std::string& str,
        unsigned int current_alignment)
{
    return RTICdrType_getStringSerializedSize(current_alignment, str.c_str());
}

#ifndef RTI_NO_STD_WSTRING
inline unsigned int calculate_serialized_size(
        const std::wstring& str,
        unsigned int current_alignment)
{
    return RTICdrType_get4ByteMaxSizeSerialized(current_alignment)
            + static_cast<unsigned int>(str.size()) * RTI_CDR_WCHAR_SIZE
            + RTI_CDR_WCHAR_SIZE;
}
#endif

// --- external

template <typename T>
bool serialize(
        struct RTICdrStream *me,
        const dds::core::external<T>& p,
        RTICdrUnsignedLong max_length)
{
    if (!p) {
        return false;
    }
    return serialize(me, *p, max_length);
}

template <typename T>
bool deserialize(
        struct RTICdrStream *me,
        dds::core::external<T>& p,
        RTICdrUnsignedLong max_length)
{
    if (!p) {
        dds::core::detail::make_shared<T>(p);
    }
    return deserialize(me, *p, max_length);
}

template <typename T>
unsigned int calculate_serialized_size(
        const dds::core::external<T>& p,
        unsigned int current_alignment)
{
    if (!p) {
        return 0;
    }

    return calculate_serialized_size(*p, current_alignment);
}


} } } // namespace rti::topic::cdr

#endif // RTI_NO_STD_WSTRING

#endif // RTI_DDS_TOPIC_CDR_SERIALIZATION_HPP_
