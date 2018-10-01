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

#ifndef RTI_DDS_TOPIC_CDR_CDRFWD_HPP_
#define RTI_DDS_TOPIC_CDR_CDRFWD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#ifndef RTI_NO_STD_WSTRING

#include <vector>
#include <string>

#include "cdr/cdr_stream.h"
#include "dds_c/dds_c_topic.h"

#include <dds/core/String.hpp>
#include <dds/core/array.hpp>
#include <rti/topic/TopicTraits.hpp>

#include <rti/core/Pointer.hpp>

/*
 * Serialization and deserialization utilities for type-plugin generated code
 */

namespace rti { namespace topic { namespace cdr {

OMG_DDS_API
void log_exceed_seq_max_length_error(
        unsigned int actual_length,
        unsigned int max_length);

// --- pointers

template <typename T>
bool serialize(
        struct RTICdrStream *me,
        const dds::core::external<T>& p,
        RTICdrUnsignedLong max_length);

template <typename T>
bool deserialize(
        struct RTICdrStream *me,
        dds::core::external<T>& p,
        RTICdrUnsignedLong max_length);

template <typename T>
unsigned int calculate_serialized_size(
        const dds::core::external<T>& p,
        unsigned int current_alignment);


// --- strings

OMG_DDS_API
bool deserialize(RTICdrStream * stream, std::string& out, uint32_t max_length);

OMG_DDS_API
bool serialize(
        struct RTICdrStream *me,
        const std::string& str,
        RTICdrUnsignedLong max_length);

unsigned int calculate_serialized_size(
        const std::string& str,
        unsigned int current_alignment);

#ifndef RTI_NO_STD_WSTRING
unsigned int calculate_serialized_size(
        const std::wstring& str,
        unsigned int current_alignment);

OMG_DDS_API
bool serialize(
        struct RTICdrStream *me,
        const std::wstring& str,
        RTICdrUnsignedLong max_length);

OMG_DDS_API
bool deserialize(
        struct RTICdrStream *me,
        std::wstring& str,
        RTICdrUnsignedLong max_length);
#endif

template <typename ContainerType>
bool serialize_string_container(
        struct RTICdrStream *me,
        const ContainerType& container,
        RTICdrUnsignedLong max_str_length);

template <typename ContainerType>
bool serialize_string_container(
        struct RTICdrStream *me,
        const ContainerType& container,
        RTICdrUnsignedLong max_element_length,
        RTICdrUnsignedLong max_str_length);

template <typename ContainerType>
bool deserialize_string_container(
        struct RTICdrStream *me,
        ContainerType& container,
        RTICdrUnsignedLong max_str_length);

// --- Vector

template <typename ContainerType>
unsigned int calculate_container_serialized_size(
        const ContainerType& container,
        unsigned int current_alignment);

OMG_DDS_API
bool serialize(
        struct RTICdrStream *me,
        const std::vector<std::string>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length);


OMG_DDS_API
bool deserialize(
        struct RTICdrStream *me,
        std::vector<std::string>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length);


#ifndef RTI_NO_STD_WSTRING
OMG_DDS_API
bool serialize(
        struct RTICdrStream *me,
        const std::vector<std::wstring>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length);


OMG_DDS_API
bool deserialize(
        struct RTICdrStream *me,
        std::vector<std::wstring>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length);
#endif

template <typename T>
bool serialize(
        struct RTICdrStream *me,
        const std::vector<std::string>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length);

template <typename T>
bool deserialize_vector(
        struct RTICdrStream *me,
        std::vector<T>& v,
        RTICdrUnsignedLong max_length);

template <typename TopicType>
bool deserialize_vector(
        struct RTICdrStream *stream,
        std::vector<TopicType>& v,
        RTICdrUnsignedLong max_length,
        RTICdrStreamDeserializeFunction deserialize_function,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_data,
        void *endpoint_data,
        void *endpoint_plugin_qos);

template <typename T>
bool serialize_vector(
        struct RTICdrStream *me,
        const std::vector<T>& v,
        RTICdrUnsignedLong max_length);

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
        void *endpoint_plugin_qos);

template <typename TopicType>
unsigned int calculate_serialized_size(
        const std::vector<TopicType>& v,
        unsigned int current_alignment,
        RTICdrTypeGetSerializedSampleSizeFunction serialize_function,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        void *endpoint_data);

// --- bounded_sequence

template <size_t N, typename CharType>
bool serialize(
        struct RTICdrStream *me,
        const rti::core::bounded_sequence<std::basic_string<CharType>, N>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length);


template <size_t N, typename CharType>
bool deserialize(
        struct RTICdrStream *me,
        rti::core::bounded_sequence<std::basic_string<CharType>, N>& string_vector,
        RTICdrUnsignedLong max_length,
        RTICdrUnsignedLong max_str_length);


template <typename T, size_t N>
bool deserialize_vector(
        struct RTICdrStream *me,
        rti::core::bounded_sequence<T, N>& v,
        RTICdrUnsignedLong max_length);

template <typename TopicType, size_t N>
bool deserialize_vector(
        struct RTICdrStream *stream,
        rti::core::bounded_sequence<TopicType, N>& v,
        RTICdrUnsignedLong max_length,
        RTICdrStreamDeserializeFunction deserialize_function,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_data,
        void *endpoint_data,
        void *endpoint_plugin_qos);

template <typename T, size_t N>
bool serialize_vector(
        struct RTICdrStream *me,
        const rti::core::bounded_sequence<T, N>& v,
        RTICdrUnsignedLong max_length);

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
        void *endpoint_plugin_qos);

template <typename TopicType, size_t N>
unsigned int calculate_serialized_size(
        const rti::core::bounded_sequence<TopicType, N>& v,
        unsigned int current_alignment,
        RTICdrTypeGetSerializedSampleSizeFunction serialize_function,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        void *endpoint_data);


} } } // namespace rti::topic::cdr

#endif // RTI_NO_STD_WSTRING

#endif // RTI_DDS_TOPIC_CDR_CDRFWD_HPP_
