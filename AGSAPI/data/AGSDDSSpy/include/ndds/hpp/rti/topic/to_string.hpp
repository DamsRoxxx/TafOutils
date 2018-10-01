/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
5.20,08aug14,ajm CODEGENII-303 Adding impl_type trait
5.20,16jun14,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_TOSTRING_HPP_
#define RTI_DDS_TOPIC_TOSTRING_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <ostream>

#include <dds/topic/TopicTraits.hpp>
#include <dds/core/xtypes/DynamicData.hpp>
#include <rti/topic/PrintFormat.hpp>

namespace rti { namespace topic {

/**
 * @ingroup DDSTopicTraitsModule
 *
 * @brief Prints a data sample to an output stream
 *
 * @tparam TopicType A valid topic-type. Valid types are \ref DDSTypesModule "IDL-generated types" 
 * that were generated with typecodes enabled, the
 * \ref DDSBuiltInTypesModule "built-in types" and dds::core::xtypes::DynamicData.
 *
 * @param out The output stream to print to
 * @param sample The sample to print to the output stream
 * @param print_format Properties describing the format with
 *                     which to print the sample. For example, a
 *                     sample may be printed in a default
 *                     format, JSON format or XML format. 
 */
template <typename TopicType>
std::ostream& to_string(
        std::ostream& out,
        const TopicType& sample,
        const PrintFormatProperty& print_format = PrintFormatProperty::Default())
{
    OMG_DDS_STATIC_ASSERT(
        (dds::topic::is_topic_type<TopicType>::value),
        "Type TopicType must be a DDS topic type");

    return rti::core::xtypes::to_string(
            out,
            rti::core::xtypes::convert(sample),
            print_format);

}

/**
 * @ingroup DDSTopicTraitsModule
 *
 * @brief Tranforms a data sample into a human-readable string
 *        format
 *
 * @tparam TopicType A valid topic-type. Valid types are \ref DDSTypesModule "IDL-generated types" 
 * that were generated with typecodes enabled, the \ref DDSBuiltInTypesModule "built-in types"
 * and dds::core::xtypes::DynamicData.
 *
 * @param sample The sample to get the string representation of
 * @param print_format Properties describing the format with
 *                     which to print the sample. For example, a
 *                     sample may be printed in a default
 *                     format, JSON format or XML format. 
 */
template <typename TopicType>
std::string to_string(
        const TopicType& sample,
        const PrintFormatProperty& print_format = PrintFormatProperty::Default())
{
    OMG_DDS_STATIC_ASSERT(
        (dds::topic::is_topic_type<TopicType>::value),
        "Type TopicType must be a DDS topic type");

    return rti::core::xtypes::to_string(
            rti::core::xtypes::convert(sample),
            print_format);
}

inline std::ostream& to_string(
        std::ostream& out,
        const dds::core::xtypes::DynamicData& sample,
        const PrintFormatProperty& print_format = PrintFormatProperty::Default())
{
    return rti::core::xtypes::to_string(out, sample, print_format);
}

inline std::string to_string(
        const dds::core::xtypes::DynamicData& sample,
        const PrintFormatProperty& print_format = PrintFormatProperty::Default())
{
    return rti::core::xtypes::to_string(sample, print_format);
}

} } // namespace rti::topic

#endif // RTI_DDS_TOPIC_TOSTRING_HPP_
