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

#ifndef RTI_DDS_TOPIC_CDR_SEQUENCE_SERIALIZATION_HPP_
#define RTI_DDS_TOPIC_CDR_SEQUENCE_SERIALIZATION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#ifndef RTI_NO_CDR_TEMPLATES

#include <rti/core/Exception.hpp>
#include <rti/topic/cdr/cdrfwd.hpp>
#include <rti/topic/cdr/PrimitiveTypes.hpp>

/*
 * Sequence and array serialization functions for the type-plugin generated code
 */

namespace rti { namespace topic { namespace cdr {

// prepare_vector resizes to the length of the sequence about to be deserialized
// in stream

template <typename T, size_t N>
bool prepare_vector(
        struct RTICdrStream *stream,
        rti::core::bounded_sequence<T, N>& v,
        RTICdrUnsignedLong)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    uint32_t size;
    if (!RTICdrStream_deserializeUnsignedLong(stream, &size)) {
        return false;
    }

    // reset_sample default-initializes, so we can use this function instead of
    // the less-efficient resize().
    v.resize_uninitialized(size);

    return true;
}

template <typename T>
bool prepare_vector(
        struct RTICdrStream *stream,
        std::vector<T>& v,
        RTICdrUnsignedLong max_length)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    uint32_t size;
    if (!RTICdrStream_deserializeUnsignedLong(stream, &size)) {
        return false;
    }

    if (size > max_length) {
        log_exceed_seq_max_length_error(size, max_length);
        return false;
    }

    v.resize(size);

    return true;
}

template <typename T, size_t N>
bool prepare_vector(
        struct RTICdrStream *,
        dds::core::array<T, N>&,
        RTICdrUnsignedLong)
{
    // arrays don't need any resizing
    return true;
}


//
// --- Arrays of srings
//

template <typename ElementType, size_t N>
bool serialize(
        struct RTICdrStream *me,
        const dds::core::array<ElementType, N>& container,
        RTICdrUnsignedLong max_str_length)
{
    return serialize_string_container(me, container, max_str_length);
}

template <typename ElementType, size_t N>
bool deserialize(
        struct RTICdrStream *me,
        dds::core::array<ElementType, N>& container,
        RTICdrUnsignedLong max_str_length)
{
    return deserialize_string_container(me, container, max_str_length);
}

template <typename ElementType, size_t N>
unsigned int calculate_serialized_size(
        const dds::core::array<ElementType, N>& container,
        unsigned int current_alignment)
{
    return calculate_container_serialized_size(container, current_alignment);
}

template <typename ContainerType>
bool serialize_string_container(
        struct RTICdrStream *me,
        const ContainerType& container,
        RTICdrUnsignedLong max_str_length)
{
    size_t length = container.size();
    for (size_t i = 0; i < length; i++) {
        if (!serialize(me, container[i], max_str_length)) {
            return false;
        }
    }

    return true;
}


template <typename ContainerType>
bool serialize_string_container(
        struct RTICdrStream *me,
        const ContainerType& container,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length)
{
    size_t length = container.size();

    if (length > max_length) {
        log_exceed_seq_max_length_error(
                static_cast<unsigned int>(length),
                max_length);
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        if (!serialize(me, container[i], max_length, max_str_length)) {
            return false;
        }
    }

    return true;
}

template <typename ContainerType>
bool deserialize_string_container(
        struct RTICdrStream *me,
        ContainerType& container,
        RTICdrUnsignedLong max_str_length)
{
    size_t length = container.size();
    for (size_t i = 0; i < length; i++) {
        if (!deserialize(me, container[i], max_str_length)) {
            return false;
        }
    }

    return true;
}

// serialize for sequences of strings (the function needs the extra parameter
// max_str_length).
template <size_t N, typename CharType>
bool serialize(
        struct RTICdrStream *me,
        const rti::core::bounded_sequence<std::basic_string<CharType>, N>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length)
{
    RTI_CHECK_PRECONDITION(me != NULL);
    RTI_CHECK_PRECONDITION(me->_currentPosition != NULL);
    RTI_CHECK_PRECONDITION(max_str_length > 0);

    uint32_t length = static_cast<uint32_t>(string_vector.size());

    if (length > max_length) {
        log_exceed_seq_max_length_error(length, max_length);
        return false;
    }

    if (!RTICdrStream_serializeUnsignedLong(me, &length)) {
        return false;
    }

    if (!serialize_string_container(me, string_vector, max_str_length)) {
        return false;
    }

    return true;
}

template <size_t N, typename CharType>
bool deserialize(
    struct RTICdrStream *me,
    rti::core::bounded_sequence<std::basic_string<CharType>, N>& v,
    RTICdrUnsignedLong max_length,
    RTICdrUnsignedLong max_str_length)
{
    RTI_CHECK_PRECONDITION(max_str_length > 0);

    if (!prepare_vector(me, v, max_length)) {
        return false;
    }

    if (!deserialize_string_container(me, v, max_str_length)) {
        return false;
    }

    return true;
}


//
// --- Sequences (vector or bounded_sequence) of primitive and aggregation types
//

template <typename ContainerType>
unsigned int calculate_container_serialized_size(
        const ContainerType& container,
        unsigned int current_alignment)
{
    typedef typename ContainerType::const_iterator iterator;

    unsigned int serialized_size = 0;
    for (iterator it = container.begin(); it != container.end(); ++it) {
        serialized_size += calculate_serialized_size(
                *it,
                current_alignment + serialized_size);
    }

    return serialized_size;
}

// Template selected when T is not primitive
template <typename T>
typename rtiboost::disable_if_c<is_primitive<T>::value, unsigned int>::type
calculate_serialized_size(
        const std::vector<T>& v,
        uint32_t current_alignment)
{
    uint32_t length_size = // size to serialize the sequence's length
            RTICdrType_get4ByteMaxSizeSerialized(current_alignment);
    return length_size + calculate_container_serialized_size(
            v,
            current_alignment + length_size);
}

// Template selected when T is primitive
template <typename T>
typename rtiboost::enable_if_c<is_primitive<T>::value, unsigned int>::type
calculate_serialized_size(
        const std::vector<T>& v,
        uint32_t current_alignment)
{
    return RTICdrType_getPrimitiveSequenceSerializedSize(
                current_alignment,
                static_cast<unsigned int>(v.size()),
                static_cast<RTICdrPrimitiveType>(primitive_type_traits<T>::cdr_type));
}

// deserialize vector of aggreation types with a deserialize_function
//
template <typename TopicType>
bool deserialize_vector(
        struct RTICdrStream *stream,
        std::vector<TopicType>& v,
        RTICdrUnsignedLong max_length,
        RTICdrStreamDeserializeFunction deserialize_function,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_data,
        void *endpoint_data,
        void *endpoint_plugin_qos)
{
    RTI_CHECK_PRECONDITION(deserialize_function != NULL);

    if (!prepare_vector(stream, v, max_length)) {
        return false;
    }

    size_t size = v.size();

    for (size_t i = 0; i < size; i++) {
        if (!deserialize_function(
                endpoint_data,
                &v[i],
                stream,
                deserialize_encapsulation,
                deserialize_data,
                endpoint_plugin_qos)) {
            return false;
        }
    }

    return true;
}

template <typename TopicType>
bool serialize_vector(
        struct RTICdrStream *stream,
        const std::vector<TopicType>& v,
        RTICdrUnsignedLong max_length,
        RTICdrStreamSerializeFunction serialize_function,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_data,
        void *endpoint_data,
        void *endpoint_plugin_qos)
{
    unsigned int size = static_cast<unsigned int>(v.size());
    return RTICdrStream_serializeNonPrimitiveSequence(
            stream,
            size > 0 ? &v[0] : NULL,
            size,
            max_length,
            sizeof(TopicType),
            serialize_function,
            serialize_encapsulation,
            encapsulation_id,
            serialize_data,
            endpoint_data,
            endpoint_plugin_qos) == RTI_TRUE;
}

template <typename TopicType>
unsigned int calculate_serialized_size(
        const std::vector<TopicType>& v,
        unsigned int current_alignment,
        RTICdrTypeGetSerializedSampleSizeFunction serialize_function,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        void *endpoint_data)
{
    unsigned int size = static_cast<unsigned int>(v.size());
    return RTICdrStream_getNonPrimitiveSequenceSerializedSize(
            current_alignment,
            size,
            sizeof(TopicType),
            serialize_function,
            include_encapsulation,
            encapsulation_id,
            size > 0 ? &v[0] : NULL,
            endpoint_data);
}

//
// --- Sequences of primitive types:
//
// The different templates in sequence_serialization_helper specialize for
// the different kinds of T.
//
// - When sizeof(T) == 1, the operation can be more efficient
// - When T is bool, a special implementation is needed
// - For the rest of primitive types
//
// The templates work for vector and bounded_sequence (template argument C)
//
namespace detail {

template <typename T, size_t N>
bool serialize_length(
        struct RTICdrStream *stream,
        const rti::core::bounded_sequence<T, N>& v,
        RTICdrUnsignedLong max_length)
{
    uint32_t length = static_cast<uint32_t>(v.size());

    if (length > max_length) {
        log_exceed_seq_max_length_error(length, max_length);
        return false;
    }

    if (!RTICdrStream_serializeUnsignedLong(stream, &length)) {
        return false;
    }

    return true;
}

template <typename T>
bool serialize_length(
        struct RTICdrStream *stream,
        const std::vector<T>& v,
        RTICdrUnsignedLong max_length)
{
    uint32_t length = static_cast<uint32_t>(v.size());

    if (length > max_length) {
        log_exceed_seq_max_length_error(length, max_length);
        return false;
    }

    if (!RTICdrStream_serializeUnsignedLong(stream, &length)) {
        return false;
    }

    return true;
}

template <typename T, size_t N>
bool serialize_length(
        struct RTICdrStream *,
        const dds::core::array<T, N>&,
        RTICdrUnsignedLong)
{
    // arrays don't serialize its length
    return true;
}

template <typename C>
static bool serialize_vector_general_case(
        struct RTICdrStream *me,
        const C& v,
        RTICdrUnsignedLong max_length)
{
    typedef typename C::value_type T;

    if (!serialize_length(me, v, max_length)) {
        return false;
    }

    uint32_t length = static_cast<uint32_t>(v.size());

    if (length == 0) {
        return true;
    }

    rti::topic::cdr::align<T>(me);

    if (me->_needByteSwap) {
        for (uint32_t i = 0; i < length; i++) {
            if (!rti::topic::cdr::serialize_fast(me, &v[i])) {
                return false;
            }
        }
    } else {
        RTIOsapiMemory_copy(me->_currentPosition, &v[0], sizeof(T) * length);
        me->_currentPosition += sizeof(T) * length;
    }
    return true;
}

template <typename C>
static bool deserialize_vector_general_case(
        struct RTICdrStream *me,
        C& v,
        RTICdrUnsignedLong max_length)
{
    typedef typename C::value_type T;

    if (!prepare_vector(me, v, max_length)) {
        return false;
    }
    size_t size = v.size();

    if (size == 0) {
        return true;
    }

    rti::topic::cdr::align<T>(me);

    if (me->_needByteSwap) {
        for (size_t i = 0; i < size; i++) {
            if (!rti::topic::cdr::deserialize_fast(me, &v[i])) {
                return false;
            }
        }
    } else {
        RTIOsapiMemory_copy(&v[0], me->_currentPosition, sizeof(T) * size);
        me->_currentPosition += sizeof(T) * size;
    }

    return true;
}

// We need sequence_serialization_helper because we need partial template
// specialization (standalone functions don't support it)
template <typename T>
struct sequence_serialization_helper {

    // For types of size > 1
    template <typename C>
    static
    typename rtiboost::enable_if_c<sizeof(typename C::value_type) != 1, bool>::type
    serialize(
            struct RTICdrStream *me,
            const C& v,
            RTICdrUnsignedLong max_length)
    {
        return serialize_vector_general_case(me, v, max_length);
    }

    // For types of size == 1 (char, octet) there is no need to align or swap order
    template <typename C>
    static
    typename rtiboost::enable_if_c<sizeof(typename C::value_type) == 1, bool>::type
    serialize(
            struct RTICdrStream *me,
            const C& v,
            RTICdrUnsignedLong max_length)
    {
        if (!serialize_length(me, v, max_length)) {
            return false;
        }

        uint32_t length = static_cast<uint32_t>(v.size());

        if (length == 0) {
            return true;
        }

        std::copy(v.begin(), v.end(), reinterpret_cast<T*>(me->_currentPosition));
        me->_currentPosition += length;
        return true;
    }

    // For types of size > 1
    template <typename C>
    static
    typename rtiboost::enable_if_c<sizeof(typename C::value_type) != 1, bool>::type
    deserialize(
            struct RTICdrStream *me,
            C& v,
            RTICdrUnsignedLong max_length)
    {
        return deserialize_vector_general_case(me, v, max_length);
    }

    // For types of size == 1 (char, octet) there is no need to align or swap order
    template <typename C>
    static
    typename rtiboost::enable_if_c<sizeof(typename C::value_type) == 1, bool>::type
    deserialize(
            struct RTICdrStream *me,
            C& v,
            RTICdrUnsignedLong max_length)
    {
        if (!prepare_vector(me, v, max_length)) {
            return false;
        }
        size_t size = v.size();

        if (size == 0) {
            return true;
        }

        T * pos = reinterpret_cast<T*>(me->_currentPosition);
        std::copy(pos, pos + size, v.begin());
        me->_currentPosition += size;

        return true;
    }
};

// We need a different implementation because vector<bool> doesn't behave
// as all other vector<T>.
template <>
struct sequence_serialization_helper<bool> {

    template <typename C>
    static bool serialize(
            struct RTICdrStream *me,
            const C& v,
            RTICdrUnsignedLong max_length)
    {
        if (!serialize_length(me, v, max_length)) {
            return false;
        }

        uint32_t length = static_cast<uint32_t>(v.size());

        if (length == 0) {
                    return true;
                }

        for (uint32_t i = 0; i < length; i++) {
            bool tmp_value = v[i];
            if (!rti::topic::cdr::serialize_fast(me, &tmp_value)) {
                return false;
            }
        }

        return true;
    }

    template <typename C>
    static bool deserialize(
            struct RTICdrStream *me,
            C& v,
            RTICdrUnsignedLong max_length)
    {
        if (!prepare_vector(me, v, max_length)) {
            return false;
        }

        size_t size = v.size();

        for (size_t i = 0; i < size; i++) {
            bool tmp_value;
            if (!rti::topic::cdr::deserialize_fast(me, &tmp_value)) {
                return false;
            }

            v[i] = tmp_value;
        }

        return true;
    }

};

// The general template should take care of LongDouble, but
// Visual Studio 2010 can't compile it. 
template <>
struct sequence_serialization_helper<rti::core::LongDouble> {

    template <typename C>
    static bool serialize(
            struct RTICdrStream *me,
            const C& v,
            RTICdrUnsignedLong max_length)
    {
        return serialize_vector_general_case(me, v, max_length);
    }

    template <typename C>
    static bool deserialize(
            struct RTICdrStream *me,
            C& v,
            RTICdrUnsignedLong max_length)
    {
        return deserialize_vector_general_case(me, v, max_length);
    }

};

// wchar_t requires a different (less-efficient) serialization when
// its size is not the same as DDS_Wchar (what goes on the wire)
template <>
struct sequence_serialization_helper<wchar_t> {

    // When sizeof(wchar_t) == sizeof(DDS_Wchar) we don't need any
    // special conversion
    template <typename C>
    static
    typename rtiboost::enable_if_c<
        sizeof(typename C::value_type) == sizeof(DDS_Wchar),
        bool>::type
    serialize(
            struct RTICdrStream *me,
            const C& v,
            RTICdrUnsignedLong max_length)
    {
        return serialize_vector_general_case(me, v, max_length);
    }

    // When sizeof(wchar_t) != sizeof(DDS_Wchar) we need to cast and serialize
    // element by element
    template <typename C>
    static
    typename rtiboost::enable_if_c<
        sizeof(typename C::value_type) != sizeof(DDS_Wchar),
        bool>::type
    serialize(
            struct RTICdrStream *me,
            const C& v,
            RTICdrUnsignedLong max_length)
    {
        typedef typename C::value_type T;

        if (!serialize_length(me, v, max_length)) {
            return false;
        }

        uint32_t length = static_cast<uint32_t>(v.size());

        if (length == 0) {
            return true;
        }

        rti::topic::cdr::align<T>(me);

        for (uint32_t i = 0; i < length; i++) {
            // serialize_fast knows what to do for wchar_t
            if (!rti::topic::cdr::serialize_fast(me, &v[i])) {
                return false;
            }
        }
        return true;
    }

    // When sizeof(wchar_t) == sizeof(DDS_Wchar) we don't need any
    // special conversion
    template <typename C>
    static
    typename rtiboost::enable_if_c<
        sizeof(typename C::value_type) == sizeof(DDS_Wchar),
        bool>::type
    deserialize(
            struct RTICdrStream *me,
            C& v,
            RTICdrUnsignedLong max_length)
    {
        return deserialize_vector_general_case(me, v, max_length);
    }

    // When sizeof(wchar_t) != sizeof(DDS_Wchar) we need to deserialize a
    // DDS_Wchar and then cast it to wchar_t, element by element
    template <typename C>
    static
    typename rtiboost::enable_if_c<
        sizeof(typename C::value_type) != sizeof(DDS_Wchar),
        bool>::type
    deserialize(
            struct RTICdrStream *me,
            C& v,
            RTICdrUnsignedLong max_length)
    {
        typedef typename C::value_type T;

        if (!prepare_vector(me, v, max_length)) {
            return false;
        }
        size_t size = v.size();

        if (size == 0) {
            return true;
        }

        rti::topic::cdr::align<T>(me);

        for (size_t i = 0; i < size; i++) {
            // deserialize_fast knows what to do for wchar_t
            if (!rti::topic::cdr::deserialize_fast(me, &v[i])) {
                return false;
            }
        }

        return true;
    }
};

} // namespace detail


template <typename T, size_t N>
bool serialize_vector(
        struct RTICdrStream *me,
        const rti::core::bounded_sequence<T, N>& v,
        RTICdrUnsignedLong max_length)
{
    return detail::sequence_serialization_helper<T>::serialize(
                me,
                v,
                max_length);
}


template <typename T, size_t N>
bool deserialize_vector(
        struct RTICdrStream *me,
        rti::core::bounded_sequence<T, N>& v,
        RTICdrUnsignedLong max_length)
{
    return detail::sequence_serialization_helper<T>::deserialize(
            me,
            v,
            max_length);
}

template <typename T>
bool serialize_vector(
        struct RTICdrStream *me,
        const std::vector<T>& v,
        RTICdrUnsignedLong max_length)
{
    return detail::sequence_serialization_helper<T>::serialize(
                me,
                v,
                max_length);
}

template <typename T>
inline bool deserialize_vector(
        struct RTICdrStream *me,
        std::vector<T>& v,
        RTICdrUnsignedLong max_length)
{
    return detail::sequence_serialization_helper<T>::deserialize(
                me,
                v,
                max_length);
}

template <typename T, size_t N>
bool serialize(
        struct RTICdrStream *me,
        const dds::core::array<T, N>& v)
{
    return detail::sequence_serialization_helper<T>::serialize(
                me,
                v,
                N);
}


template <typename T, size_t N>
bool deserialize(
        struct RTICdrStream *me,
        dds::core::array<T, N>& v)
{
    return detail::sequence_serialization_helper<T>::deserialize(
            me,
            v,
            N);
}

template <typename T, size_t N, size_t M>
bool serialize(
        struct RTICdrStream *me,
        const dds::core::array<dds::core::array<T, N>, M>& v)
{
    return serialize(
            me,
            reinterpret_cast<const dds::core::array<T, N * M>&>(v));
}

template <typename T, size_t N, size_t M>
bool deserialize(
        struct RTICdrStream *me,
        dds::core::array<dds::core::array<T, N>, M>& v)
{
    return deserialize(
            me,
            reinterpret_cast<dds::core::array<T, N * M>&>(v));
}


template <typename T, size_t N>
typename rtiboost::disable_if_c<is_primitive<T>::value, unsigned int>::type
calculate_serialized_size(
        const rti::core::bounded_sequence<T, N>& v,
        uint32_t current_alignment)
{

    uint32_t length_size = // size to serialize the sequence's length
            RTICdrType_get4ByteMaxSizeSerialized(current_alignment);
    return length_size + calculate_container_serialized_size(
            v,
            current_alignment + length_size);
}

template <typename T, size_t N>
typename rtiboost::enable_if_c<is_primitive<T>::value, unsigned int>::type
calculate_serialized_size(
        const rti::core::bounded_sequence<T, N>& v,
        uint32_t current_alignment)
{

    return RTICdrType_getPrimitiveSequenceSerializedSize(
                current_alignment,
                static_cast<unsigned int>(v.size()),
                static_cast<RTICdrPrimitiveType>(
                        primitive_type_traits<T>::cdr_type));
}

template <typename TopicType, size_t N>
bool deserialize_vector(
        struct RTICdrStream *stream,
        rti::core::bounded_sequence<TopicType, N>& v,
        RTICdrUnsignedLong max_length,
        RTICdrStreamDeserializeFunction deserialize_function,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_data,
        void *endpoint_data,
        void *endpoint_plugin_qos)
{
    RTI_CHECK_PRECONDITION(deserialize_function != NULL);

    if (!prepare_vector(stream, v, max_length)) {
        return false;
    }

    size_t size = v.size();

    for (size_t i = 0; i < size; i++) {
        if (!deserialize_function(
                endpoint_data,
                &v[i],
                stream,
                deserialize_encapsulation,
                deserialize_data,
                endpoint_plugin_qos)) {
            return false;
        }
    }

    return true;
}

template <typename TopicType, size_t N>
bool serialize_vector(
        struct RTICdrStream *stream,
        const rti::core::bounded_sequence<TopicType, N>& v,
        RTICdrUnsignedLong max_length,
        RTICdrStreamSerializeFunction serialize_function,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_data,
        void *endpoint_data,
        void *endpoint_plugin_qos)
{
    unsigned int size = static_cast<unsigned int>(v.size());
    return RTICdrStream_serializeNonPrimitiveSequence(
            stream,
            size > 0 ? &v[0] : NULL,
            size,
            max_length,
            sizeof(TopicType),
            serialize_function,
            serialize_encapsulation,
            encapsulation_id,
            serialize_data,
            endpoint_data,
            endpoint_plugin_qos) == RTI_TRUE;
}

template <typename TopicType, size_t N>
unsigned int calculate_serialized_size(
        const rti::core::bounded_sequence<TopicType, N>& v,
        unsigned int current_alignment,
        RTICdrTypeGetSerializedSampleSizeFunction serialize_function,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        void *endpoint_data)
{
    unsigned int size = static_cast<unsigned int>(v.size());
    return RTICdrStream_getNonPrimitiveSequenceSerializedSize(
            current_alignment,
            size,
            sizeof(TopicType),
            serialize_function,
            include_encapsulation,
            encapsulation_id,
            size > 0 ? &v[0] : NULL,
            endpoint_data);
}

//
// --- Arrays of pointers
//


// T is non-primitive type
template <typename T, size_t N>
bool serialize_pointer_array(
        struct RTICdrStream *stream,
        const dds::core::array<dds::core::external<T>, N>& v,
        RTICdrStreamSerializeFunction serializeFunction,
        RTIBool serializeEncapsulation,
        RTIEncapsulationId encapsulationId,
        RTIBool serializeSample,
        void *endpointData,
        void *endpointPluginQos)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);
    RTI_CHECK_PRECONDITION(serializeFunction != NULL);

    for (size_t i = 0; i < N; ++i) {
        if (!v[i]) {
            return false;
        }
        if (!serializeFunction(
                endpointData,
                v[i].get(),
                stream,
                serializeEncapsulation,
                encapsulationId,
                serializeSample,
                endpointPluginQos)) {
            return false;
        }
    }

    return true;
}

template <typename T, size_t N, size_t M>
bool serialize_pointer_array(
        struct RTICdrStream *stream,
        const dds::core::array<dds::core::array<T, M>, N>& v,
        RTICdrStreamSerializeFunction serializeFunction,
        RTIBool serializeEncapsulation,
        RTIEncapsulationId encapsulationId,
        RTIBool serializeSample,
        void *endpointData,
        void *endpointPluginQos)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    for (size_t i = 0; i < N; ++i) {
        if (!serialize_pointer_array(
                stream,
                v[i],
                serializeFunction,
                serializeEncapsulation,
                encapsulationId,
                serializeSample,
                endpointData,
                endpointPluginQos)) {
            return false;
        }
    }

    return true;
}

template <typename T, size_t N>
bool serialize_pointer_array(
        struct RTICdrStream *stream,
        const dds::core::array<dds::core::external<T>, N>& v)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    if (!align<T>(stream)) {
        return false;
    }

    if (!RTICdrStream_checkSize(stream, get_size<T>() * N)) {
        return false;
    }


    for (size_t i = 0; i < N; ++i) {
        if (!v[i]) {
            return false;
        }
        primitive_type_traits<T>::serialize(stream, v[i].get());
    }

    return true;
}

template <typename T, size_t N, size_t M>
bool serialize_pointer_array(
        struct RTICdrStream *stream,
        const dds::core::array<dds::core::array<T, M>, N>& v)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    for (size_t i = 0; i < N; ++i) {
        if (!serialize_pointer_array(stream, v[i])) {
            return false;
        }
    }

    return true;
}

template <typename T, size_t N>
bool deserialize_pointer_array(
        struct RTICdrStream *stream,
        dds::core::array<dds::core::external<T>, N>& v,
        RTICdrStreamDeserializeFunction deserializeFunction,
        RTIEncapsulationId encapsulationId,
        RTIBool deserializeSample,
        void *endpointData,
        void *endpointPluginQos)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);
    RTI_CHECK_PRECONDITION(deserializeFunction != NULL);

    for (size_t i = 0; i < N; ++i) {
        if (!v[i]) {
            return false;
        }
        if (!deserializeFunction(
                endpointData,
                v[i].get(),
                stream,
                encapsulationId,
                deserializeSample,
                endpointPluginQos)) {
            return false;
        }
    }

    return true;
}


template <typename T, size_t N, size_t M>
bool deserialize_pointer_array(
        struct RTICdrStream *stream,
        dds::core::array<dds::core::array<T, M>, N>& v,
        RTICdrStreamDeserializeFunction deserializeFunction,
        RTIEncapsulationId encapsulationId,
        RTIBool deserializeSample,
        void *endpointData,
        void *endpointPluginQos)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    for (size_t i = 0; i < N; ++i) {
        if (!deserialize_pointer_array(
                stream,
                v[i],
                deserializeFunction,
                encapsulationId,
                deserializeSample,
                endpointData,
                endpointPluginQos)) {
            return false;
        }
    }

    return true;
}

template <typename T, size_t N>
bool deserialize_pointer_array(
        struct RTICdrStream *stream,
        dds::core::array<dds::core::external<T>, N>& v)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    if (!align<T>(stream)) {
        return false;
    }

    if (!RTICdrStream_checkSize(stream, get_size<T>() * N)) {
        return false;
    }


    for (size_t i = 0; i < N; ++i) {
        if (!v[i]) {
            return false;
        }
        primitive_type_traits<T>::deserialize(stream, v[i].get());
    }

    return true;
}

template <typename T, size_t N, size_t M>
bool deserialize_pointer_array(
        struct RTICdrStream *stream,
        dds::core::array<dds::core::array<T, M>, N>& v)
{
    RTI_CHECK_PRECONDITION(stream != NULL);
    RTI_CHECK_PRECONDITION(stream->_currentPosition != NULL);

    for (size_t i = 0; i < N; ++i) {
        if (!deserialize_pointer_array(stream, v[i])) {
            return false;
        }
    }

    return true;
}

} } } // namespace rti::topic::cdr


#endif // RTI_NO_CDR_TEMPLATES

#endif // RTI_DDS_TOPIC_CDR_SEQUENCE_SERIALIZATION_HPP_
