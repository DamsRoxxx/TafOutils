#ifndef OMG_DDS_CORE_DETAIL_BUILTIN_TOPIC_TYPES_HPP_
#define OMG_DDS_CORE_DETAIL_BUILTIN_TOPIC_TYPES_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/BuiltinTopicTypesImpl.hpp>

#if defined (OMG_DDS_X_TYPES_BUILTIN_TOPIC_TYPES_SUPPORT)
namespace dds { namespace core { namespace detail {

typedef TBytesTopicType<rti::core::BytesTopicTypeImpl> BytesTopicType;
typedef TStringTopicType<rti::core::StringTopicTypeImpl> StringTopicType;
typedef TKeyedBytesTopicType<rti::core::KeyedBytesTopicTypeImpl> KeyedBytesTopicType;
typedef TKeyedStringTopicType<rti::core::KeyedStringTopicTypeImpl> KeyedStringTopicType;

template <typename T>
struct OMG_DDS_API builtin_topic_type_support {

    static void initialize_sample(T& )
    {

    }

    static void register_type(
            dds::domain::DomainParticipant&,
            const std::string& type_name)
    {
        if (type_name != dds::topic::topic_type_name<T>::value()) {
            throw dds::core::InvalidArgumentError(
                "can't register BuiltinType with a different type name");
        }
    }

    static std::vector<char>& to_cdr_buffer(
            std::vector<char>& buffer,
            const T& sample)
    {
        return rti::core::detail::to_cdr_buffer(buffer, sample.delegate());
    }

    static void from_cdr_buffer(
            T& sample,
            const std::vector<char>& buffer)
    {
        return rti::core::detail::from_cdr_buffer(sample.delegate(), buffer);
    }

    static const rti::topic::TypePluginKind::type type_plugin_kind =
            rti::topic::TypePluginKind::NON_STL;
};

} // namespace detail

inline std::ostream& operator << (std::ostream& out,const StringTopicType& sample)
{
    out << sample.delegate();
    out << sample.data() << "\n";
    return out;
}

inline std::ostream& operator << (
    std::ostream& out, const KeyedStringTopicType& sample)
{
    out << sample.delegate();
    out << "key: " << sample.key() << "\n";
    out << "value: " << sample.value() << "\n";
    return out;
}

inline std::ostream& operator << (std::ostream& out, const BytesTopicType& sample)
{
    out << sample.delegate();
    out << "data: {";
    if (sample.data().size() > 0) {
        std::copy(sample->begin(), sample->end() - 1, std::ostream_iterator<int>(out, ", "));
        std::copy(sample->end() - 1, sample->end(), std::ostream_iterator<int>(out, ""));
    }
    out << "}";
    return out;
}

inline std::ostream& operator << (std::ostream& out, const KeyedBytesTopicType& sample)
{
    out << sample.delegate();
    out << "key: " << sample.key() << std::endl;
    out << "value: {";
    if (sample.value().size() > 0) {
        std::copy(sample->begin(), sample->end() - 1, std::ostream_iterator<int>(out, ", "));
        std::copy(sample->end() - 1, sample->end(), std::ostream_iterator<int>(out, ""));
    }
    out << "}";
    return out;
}

} }

namespace dds { namespace topic {

template<>
struct OMG_DDS_API topic_type_support<dds::core::StringTopicType> :
    public dds::core::detail::builtin_topic_type_support<
        dds::core::StringTopicType> {

};

template<>
struct OMG_DDS_API topic_type_support<dds::core::KeyedStringTopicType> :
    public dds::core::detail::builtin_topic_type_support<
        dds::core::KeyedStringTopicType> {

};

template<>
struct OMG_DDS_API topic_type_support<dds::core::BytesTopicType> :
    public dds::core::detail::builtin_topic_type_support<
        dds::core::BytesTopicType> {

};

template<>
struct OMG_DDS_API topic_type_support<dds::core::KeyedBytesTopicType> :
    dds::core::detail::builtin_topic_type_support<
        dds::core::KeyedBytesTopicType> {

};

} } // namespace dds::topic

#endif

#endif // OMG_DDS_CORE_DETAIL_BUILTIN_TOPIC_TYPES_HPP_
