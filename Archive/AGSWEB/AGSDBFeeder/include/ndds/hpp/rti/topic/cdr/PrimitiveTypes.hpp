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

#ifndef RTI_DDS_TOPIC_CDR_PRIMITIVETYPES_HPP_
#define RTI_DDS_TOPIC_CDR_PRIMITIVETYPES_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "cdr/cdr_stream.h"

#include <dds/core/detail/inttypes.hpp>
#include <rti/core/LongDouble.hpp>

namespace rti { namespace topic { namespace cdr {

template <typename T>
struct primitive_type_traits {};


#define RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        TYPE,\
        CDR_ENUM,\
        CDR_TYPE,\
        SERIALIZE_MACRO)\
template <>\
struct primitive_type_traits<TYPE> {\
    enum { cdr_type = CDR_ENUM };\
    static bool serialize(RTICdrStream *stream, const TYPE* v)\
    {\
        return RTICdrStream_ ## SERIALIZE_MACRO(stream, (CDR_TYPE *) v); \
    }\
    static bool deserialize(RTICdrStream *stream, TYPE* v)\
    {\
        return RTICdrStream_de ## SERIALIZE_MACRO(stream, (CDR_TYPE *) v);\
    }\
    static bool serialize_fast(RTICdrStream *stream, const TYPE* v)\
    {\
        RTICdrStream_ ## SERIALIZE_MACRO ## Fast(stream, (CDR_TYPE *) v); return true;\
    }\
    static bool deserialize_fast(RTICdrStream *stream, TYPE* v)\
    {\
        RTICdrStream_de ## SERIALIZE_MACRO ## Fast(stream, (CDR_TYPE *) v); return true;\
    }\
}

RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        char, RTI_CDR_CHAR_TYPE, RTICdr1Byte, serialize1Byte);
RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        uint8_t, RTI_CDR_OCTET_TYPE, RTICdr1Byte, serialize1Byte);

RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        int16_t, RTI_CDR_SHORT_TYPE, RTICdr2Byte, serialize2Byte);
RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        uint16_t, RTI_CDR_UNSIGNED_SHORT_TYPE, RTICdr2Byte, serialize2Byte);

RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        int32_t, RTI_CDR_LONG_TYPE, RTICdr4Byte, serialize4Byte);
RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        uint32_t, RTI_CDR_UNSIGNED_LONG_TYPE, RTICdr4Byte, serialize4Byte);

RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        float, RTI_CDR_FLOAT_TYPE, RTICdr4Byte, serialize4Byte);

RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        rti::core::int64, RTI_CDR_LONG_LONG_TYPE, RTICdr8Byte, serialize8Byte);
RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        rti::core::uint64, RTI_CDR_UNSIGNED_LONG_LONG_TYPE, RTICdr8Byte, serialize8Byte);

RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        rti::core::LongDouble, RTI_CDR_LONG_DOUBLE_TYPE, RTICdr16Byte, serialize16Byte);

RTI_TOPIC_CDR_SPECIALIZE_PRIMITIVE_TYPE_TRAITS(\
        double, RTI_CDR_DOUBLE_TYPE, RTICdrDouble, serializeDouble);


// --- bool:

// When sizeof(bool) != sizeof(DDS_Boolean) (very few platforms)
template <size_t SizeOfBool>
struct bool_serialization_impl {
    static bool serialize(RTICdrStream *stream, const bool *v)
    {
        DDS_Boolean tmp = *v;
        return RTICdrStream_serializeBoolean(stream, &tmp);
    }
    static bool deserialize(RTICdrStream *stream, bool *v)
    {
        DDS_Boolean tmp;
        if (!RTICdrStream_deserializeBoolean(stream, &tmp)) {
            return false;
        }

        *v = tmp ? true : false;
        return true;
    }
};

// When sizeof(bool) == sizeof(DDS_Boolean) (most platforms)
template <>
struct bool_serialization_impl<sizeof(DDS_Boolean)> {
    static bool serialize(RTICdrStream *stream, const bool *v)
    {
        RTICdrStream_serializeBooleanFast(stream, (DDS_Boolean *) v);
        return true;
    }

    static bool deserialize(RTICdrStream *stream, bool *v)
    {
        RTICdrStream_deserializeBooleanFast(stream, (DDS_Boolean *) v);
        return true;
    }
};

template <>
struct primitive_type_traits<bool> {
    enum { cdr_type = RTI_CDR_BOOLEAN_TYPE };
    static bool serialize(RTICdrStream *stream, const bool *v)
    {
        return bool_serialization_impl<sizeof(bool)>::serialize(stream, v);
    }
    static bool deserialize(RTICdrStream *stream, bool *v)
    {
        return bool_serialization_impl<sizeof(bool)>::deserialize(stream, v);
    }
    static bool serialize_fast(RTICdrStream *stream, const bool *v)
    {
        return bool_serialization_impl<sizeof(bool)>::serialize(stream, v);
    }
    static bool deserialize_fast(RTICdrStream *stream, bool *v)
    {
        return bool_serialization_impl<sizeof(bool)>::deserialize(stream, v);
    }
};

// --- wchar_t

// When sizeof(wchar_t) != sizeof(DDS_Wchar)
template <size_t SizeOfWchar>
struct wchar_serialization_impl {
    static bool serialize(RTICdrStream *stream, const wchar_t *v)
    {
        DDS_Wchar tmp = static_cast<DDS_Wchar>(*v);
        return RTICdrStream_serializeWchar(stream, &tmp);
    }
    static bool deserialize(RTICdrStream *stream, wchar_t *v)
    {
        DDS_Wchar tmp;
        if (!RTICdrStream_deserializeWchar(stream, &tmp)) {
            return false;
        }

        *v = static_cast<wchar_t>(tmp);
        return true;
    }
};

// When sizeof(wchar_t) == sizeof(DDS_Wchar)
template <>
struct wchar_serialization_impl<sizeof(DDS_Wchar)> {
    static bool serialize(RTICdrStream *stream, const wchar_t *v)
    {
        RTICdrStream_serializeWchar(stream, reinterpret_cast<const DDS_Wchar*>(v));
        return true;
    }

    static bool deserialize(RTICdrStream *stream, wchar_t *v)
    {
        RTICdrStream_deserializeWchar(
                stream,
                reinterpret_cast<const DDS_Wchar*>(v));
        return true;
    }
};

template <>
struct primitive_type_traits<wchar_t> {
    enum { cdr_type = RTI_CDR_WCHAR_TYPE };
    static bool serialize(RTICdrStream *stream, const wchar_t *v)
    {
        return wchar_serialization_impl<sizeof(wchar_t)>::serialize(stream, v);
    }
    static bool deserialize(RTICdrStream *stream, wchar_t *v)
    {
        return wchar_serialization_impl<sizeof(wchar_t)>::deserialize(stream, v);
    }
    static bool serialize_fast(RTICdrStream *stream, const wchar_t *v)
    {
        return wchar_serialization_impl<sizeof(wchar_t)>::serialize(stream, v);
    }
    static bool deserialize_fast(RTICdrStream *stream, wchar_t *v)
    {
        return wchar_serialization_impl<sizeof(wchar_t)>::deserialize(stream, v);
    }
};

template <typename T>
struct is_primitive : rtiboost::is_arithmetic<T> {
};

template <>
struct is_primitive<rti::core::LongDouble> : rtiboost::true_type {
};

template <typename T>
typename rtiboost::enable_if_c<is_primitive<T>::value, bool>::type
serialize(RTICdrStream *stream, const T *v)
{
    return primitive_type_traits<T>::serialize(stream, v);
}

template <typename T>
typename rtiboost::enable_if_c<is_primitive<T>::value, bool>::type
deserialize(RTICdrStream *stream, T *v)
{
    return primitive_type_traits<T>::deserialize(stream, v);
}

template <typename T>
typename rtiboost::enable_if_c<is_primitive<T>::value, bool>::type
serialize_fast(RTICdrStream *stream, const T *v)
{
    return primitive_type_traits<T>::serialize_fast(stream, v);
}

template <typename T>
typename rtiboost::enable_if_c<is_primitive<T>::value, bool>::type
deserialize_fast(RTICdrStream *stream, T *v)
{
    return primitive_type_traits<T>::deserialize_fast(stream, v);
}


template <typename T>
bool align(RTICdrStream *stream)
{
    int alignment = RTICdrType_getPrimitiveTypeAlignment(
            static_cast<RTICdrPrimitiveType>(primitive_type_traits<T>::cdr_type));
    if (!RTICdrStream_align(stream, alignment)) {
        return false;
    }

    return true;
}

template <typename T>
unsigned int get_size()
{
    return RTICdrType_getPrimitiveTypeSize(static_cast<RTICdrPrimitiveType>(
            primitive_type_traits<T>::cdr_type));
}

} } } // namespace rti::topic::cdr

#endif // RTI_DDS_TOPIC_CDR_PRIMITIVETYPES_HPP_
