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

#ifndef RTI_DDS_TOPIC_CDR_HPP_
#define RTI_DDS_TOPIC_CDR_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_topic.h"

#include <rti/topic/TopicTraits.hpp>

/**
 * @defgroup DDSTopicCdrModule Topic-type serialization and deserialization
 * @ingroup DDSTopicTraitsModule
 * @brief Provides functions to serialize and deserialize user data types to
 * and from CDR format.
 *
 * DDS serializes topic-types into bytes in CDR format to transmit them between
 * DataWriters and DataReaders. The functions rti::topic::to_cdr() and
 * rti::topic::from_cdr() expose this functionality so applications can take
 * advantage of this capability.
 *
 */

namespace rti { namespace topic {

/**
 * @ingroup DDSTopicCdrModule
 *
 * @brief Deserializes a sample from a buffer of bytes in CDR format
 *
 * @pre sample must have been created by a previous call to from_cdr_buffer()
 * or default-constructed and then initialized with
 * \p dds::topic::topic_type_support<TopicType>::initialize_sample(). This
 * precondition doesn't apply if \p TopicType is \p dds::core::xtypes::DynamicData
 *
 * This function does the same as from_cdr_buffer() but it doesn't create
 * a new sample. When deserializing multiple samples this operation will be
 * more efficient.
 *
 * @tparam TopicType A valid topic-type. Valid types are \ref DDSTypesModule "IDL-generated types",
 * the \ref DDSBuiltInTypesModule "built-in types" and dds::core::xtypes::DynamicData.
 *
 * @param sample The destination (see precondition)
 * @param buffer The CDR buffer to deserialize
 */
template <typename TopicType>
void from_cdr_buffer_no_alloc(
    TopicType& sample, const std::vector<char>& buffer)
{
    dds::topic::topic_type_support<TopicType>::from_cdr_buffer(sample, buffer);
}

namespace detail {

template <typename TopicType>
typename rtiboost::enable_if_c<
    dds::topic::topic_type_support<TopicType>::type_plugin_kind
        == rti::topic::TypePluginKind::NON_STL, void>::type
    initialize_sample_impl(TopicType& sample)
{
    // Non-STL plugin has a initialize function
    dds::topic::topic_type_support<TopicType>::initialize_sample(sample);
}

template <typename TopicType>
typename rtiboost::enable_if_c<
    dds::topic::topic_type_support<TopicType>::type_plugin_kind
        == rti::topic::TypePluginKind::STL, void>::type
    initialize_sample_impl(TopicType&)
{
    // STL plugin doesn't need a explicit initialize function
}

} // namespace detail

/**
 * @ingroup DDSTopicCdrModule
 *
 * @brief Creates a sample by deserializing a buffer of bytes in CDR format
 *
 * @tparam TopicType A valid topic-type. Valid types are \ref DDSTypesModule "IDL-generated types",
 * the \ref DDSBuiltInTypesModule "built-in types" and dds::core::xtypes::DynamicData.
 *
 * @param buffer The CDR buffer to desrialize
 * @return The deserialized sample
 *
 * @see from_cdr_buffer_no_alloc()
 */
template <typename TopicType>
TopicType from_cdr_buffer(const std::vector<char>& buffer)
{
    TopicType sample;
    // depending of the kind of type plugin that supports TopicType, 
    // initialize or not:
    detail::initialize_sample_impl(sample);
    from_cdr_buffer_no_alloc(sample, buffer);
    return sample;
}

/**
 * @ingroup DDSTopicCdrModule
 *
 * @brief Serializes a sample into a buffer of octets in CDR format
 *
 * @tparam TopicType A valid topic-type. Valid types are \ref DDSTypesModule "IDL-generated types",
 * the \ref DDSBuiltInTypesModule "built-in types" and dds::core::xtypes::DynamicData.
 *
 * @param buffer The destination buffer. It will be resized to fit the serialized
 * sample
 * @param sample The sample to serialize
 *
 */
template <typename TopicType>
std::vector<char>& to_cdr_buffer(
    std::vector<char>& buffer,
    const TopicType& sample)
{
    return dds::topic::topic_type_support<TopicType>::to_cdr_buffer(
        buffer, sample);
}


} } // namespace rti::topic



#endif // RTI_DDS_TOPIC_CDR_HPP_
