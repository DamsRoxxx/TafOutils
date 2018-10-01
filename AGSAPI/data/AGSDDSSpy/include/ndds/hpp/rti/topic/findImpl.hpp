/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,12feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_FIND_IMPL_HPP_
#define RTI_DDS_TOPIC_FIND_IMPL_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_topic.h"

#include <dds/topic/Topic.hpp>
#include <rti/core/detail/NativeEntity.hpp>
#include <rti/topic/CustomFilter.hpp>

namespace rti { namespace topic { namespace detail {

template<typename TOPIC>
class topic_find {

};

template<typename T>
class topic_find<dds::topic::TopicDescription<T> > {
public:
    typedef dds::topic::TopicDescription<T> TopicDescription;

    static TopicDescription find(
        const dds::domain::DomainParticipant& participant,
        const std::string& topic_name)
    {

        DDS_TopicDescription * native_topic_description =
            DDS_DomainParticipant_lookup_topicdescription(
                (DDS_DomainParticipant *) participant->native_participant(),
                topic_name.c_str());

        if (native_topic_description == NULL) {
            return dds::core::null;
        }

        // Return a C++ object from the existing native object
        return create_topic_description_from_native<T>(native_topic_description);
    }
};

template<typename T>
class topic_find<dds::topic::Topic<T> > {
public:
    typedef dds::topic::Topic<T> Topic;

    static Topic find(
        const dds::domain::DomainParticipant& participant,
        const std::string& topic_name)
    {

        DDS_TopicDescription * native_topic_description =
            DDS_DomainParticipant_lookup_topicdescription(
                (DDS_DomainParticipant *) participant->native_participant(),
                topic_name.c_str());

        if (native_topic_description == NULL) {
            return dds::core::null;
        }

        DDS_Topic * native_topic = DDS_Topic_narrow(native_topic_description);
        if (native_topic == NULL) {
            throw dds::core::InvalidDowncastError(
                "TopicDescription '" + topic_name + "' is not a Topic");
        }

        // Return a C++ object from the existing native object
        return rti::core::detail::create_from_native_entity<Topic, DDS_Topic>(
            native_topic);
    }
};

template<typename T>
class topic_find<dds::topic::ContentFilteredTopic<T> > {
public:
    typedef dds::topic::ContentFilteredTopic<T> Topic;

    static Topic find(
        const dds::domain::DomainParticipant& participant,
        const std::string& topic_name)
    {

        DDS_TopicDescription * native_topic_description =
            DDS_DomainParticipant_lookup_topicdescription(
                (DDS_DomainParticipant *) participant->native_participant(),
                topic_name.c_str());

        if (native_topic_description == NULL) {
            return dds::core::null;
        }

        DDS_ContentFilteredTopic * native_topic =
            DDS_ContentFilteredTopic_narrow(native_topic_description);
        if (native_topic == NULL) {
            throw dds::core::InvalidDowncastError(
                "TopicDescription '" + topic_name + "' is not a ContentFilteredTopic");
        }

        // Return a C++ object from the existing native object
        return rti::core::detail::create_from_native_entity<Topic, DDS_ContentFilteredTopic>(
            native_topic);
    }
};

} // namespace detail


template <typename AnyTopicBackInsertIterator>
uint32_t find_topics_impl(
    rti::domain::DomainParticipantImpl& participant,
    AnyTopicBackInsertIterator begin,
    bool create_new = true)
{
    DDS_TopicSeq native_topics = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_Topic> topics_adapter(
        native_topics);

    DDS_ReturnCode_t retcode = DDS_DomainParticipant_get_topics(
        participant.native_participant(), &native_topics);
    rti::core::check_return_code(retcode, "get native topics");

    rti::core::detail::create_from_native_entity<
        dds::topic::AnyTopic,
        DDS_Topic,
        AnyTopicBackInsertIterator>(begin, topics_adapter, create_new);

    return topics_adapter.size();
}

/**
 * @relatesalso dds::topic::Topic
 *
 * @brief @extension Retrieve all the dds::topic::Topic created from this
 * dds::domain::DomainParticipant
 *
 * @tparam AnyTopicBackInsertIterator Type of the back-inserting iterator
 * passed into this function
 * @param participant The dds::domain::DomainParticipant the Topics belong to
 * @param begin A back-inserting iterator to the position in the destination
 * container to insert the found Topics into
 *
 * @return The number of found Topics
 */
template <typename AnyTopicBackInsertIterator>
uint32_t find_topics(
    dds::domain::DomainParticipant participant,
    AnyTopicBackInsertIterator begin)
{
    return find_topics_impl(*participant.delegate(), begin);
}



/**
 * @relatesalso dds::topic::Topic
 *
 * @brief @extension Retrieve all the dds::topic::Topic created from this
 * dds::domain::DomainParticipant
 *
 * @tparam AnyTopicForwardIterator Type of the forward iterator passed into
 * this function
 * @param participant The dds::domain::DomainParticipant the Topics belong to
 * @param begin A forward iterator to the position in the destination container
 * to insert the found Topics in
 * @param max_size The maximum number of Topics to return
 *
 * @return The number of found Topics
 */
template <typename AnyTopicForwardIterator>
uint32_t find_topics(
    dds::domain::DomainParticipant participant,
    AnyTopicForwardIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_TopicSeq native_topics = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_Topic> topics_adapter(
        native_topics);

    DDS_ReturnCode_t retcode = DDS_DomainParticipant_get_topics(
        participant->native_participant(), &native_topics);
    rti::core::check_return_code(retcode, "get native topics");

    rti::core::detail::create_from_native_entity<
        dds::topic::AnyTopic,
        DDS_Topic,
        AnyTopicForwardIterator>(begin, max_size, topics_adapter);

    return (max_size < topics_adapter.size() ?
            max_size : topics_adapter.size());
}


/** 
 * @ingroup DDSCustomContentFilterModule 
 * @brief Lookup a content filter previously registered with 
 * dds::domain::DomainParticipant::register_contentfilter
 *  
 * You cannot lookup the @ndds built-in content filters. 
 *  
 * @tparam T The user-defined content filter type that the CustomFilter was 
 * created with  
 * @param participant The dds::domain::DomainParticipant that the content filter 
 * is registered with.  
 * @param filter_name Name of the filter to lookup.
 * 
 * @return The found rti::topic::CustomFilter or dds::core::null if it is 
 * not found 
 */
template<typename T>
CustomFilter<T> find_content_filter(
   const dds::domain::DomainParticipant& participant, 
   const std::string& filter_name)
{
    // You can't lookup the builtin filters
    if (is_builtin_filter(filter_name)) {
        return dds::core::null;
    }

    void *filter_data = DDS_DomainParticipant_lookup_contentfilter(
       const_cast<DDS_DomainParticipant *>(
          participant->native_participant()), 
       filter_name.c_str());
    if (filter_data == NULL) {
        return dds::core::null;
    }

    // filter_data is a weak reference to a FilterHolderImpl
    FilterHolder fh = create_filter_holder_from_filter_data(filter_data);
    return rtiboost::dynamic_pointer_cast<T>(fh.custom_filter().delegate());
}

/**
 * @brief @extension Lookup the names of up to max_size number of the custom content
 * filters registered to a dds::domain::DomainParticipant 
 *  
 * The names of the @ndds built-in content filters will not be 
 * returned as part of the list.
 * 
 * @tparam FwdIterator A forwward iterator whose value type is
 * \p std::string (or convertible to)
 * @param participant The dds::domain::DomainParticipant that the content 
 * filters are registered with 
 * @param begin A forward iterator to the position in the destination 
 * container to insert the names of the found content filters into 
 * @param max_size The maximum number of filters to lookup 
 * 
 * @return The number of found content filters
 */
template<typename FwdIterator>
uint32_t find_registered_content_filters(
   const dds::domain::DomainParticipant& participant, 
   FwdIterator begin,
   uint32_t max_size)
{
    struct DDS_StringSeq filter_names = DDS_SEQUENCE_INITIALIZER;

    // Wrap filter_names so that it is finalized
    rti::core::detail::NativeSequenceAdapter<char *> seqWrapper(filter_names);

    DDS_ReturnCode_t retCode = 
        DDS_DomainParticipant_get_registered_contentfilters(
           const_cast<DDS_DomainParticipant *>(
              participant->native_participant()), &filter_names);
    rti::core::check_return_code(retCode, "get_registered_contentfilters");

    uint32_t samples_to_copy =
        max_size < (uint32_t) DDS_StringSeq_get_length(&filter_names) ?
        max_size : (uint32_t) DDS_StringSeq_get_length(&filter_names);
    for (uint32_t i = 0; i < samples_to_copy; i++) {
        const char* name = *DDS_StringSeq_get_reference(&filter_names, i);

        // Don't copy out the builtin filters
        if (!rti::topic::is_builtin_filter(name)) {
            *begin = name;
            begin++;
        }
    }

    return samples_to_copy;
}

// We need this one so that we can call this from the dtor of the
// DomainParticipantImpl
template<typename BinIterator>
uint32_t find_registered_content_filters(
   const rti::domain::DomainParticipantImpl& participant, 
   BinIterator begin)
{
    struct DDS_StringSeq filter_names = DDS_SEQUENCE_INITIALIZER;

    // Wrap filter_names so that it is finalized
    rti::core::detail::NativeSequenceAdapter<char *> seqWrapper(filter_names);

    DDS_ReturnCode_t retCode = 
        DDS_DomainParticipant_get_registered_contentfilters(
           const_cast<DDS_DomainParticipant *>(
              participant.native_participant()), &filter_names);
    rti::core::check_return_code(retCode, "get_registered_contentfilters");

    for (int32_t i = 0; i < DDS_StringSeq_get_length(&filter_names); i++) {
        const char* name = *DDS_StringSeq_get_reference(&filter_names, i);

        // Don't copy out the builtin filters
        if (!rti::topic::is_builtin_filter(name)) {
            *begin = name;
            begin++;
        }
    }

    return DDS_StringSeq_get_length(&filter_names);
}

/** 
 * @relatesalso dds::topic::ContentFilteredTopic
 *  
 * @brief Lookup the names of all of the custom content filters registered to a 
 * dds::domain::DomainParticipant 
 *  
 * The names of the @ndds built-in content filters will not be 
 * returned as part of the list.
 *  
 * @tparam BinIterator A back-inserting iterator whose value type is
 * \p std::string (or convertible to)
 * @param participant The dds::domain::DomainParticipant that the content 
 * filters are registered with 
 * @param begin A back-inserting iterator to the position in the destination 
 * container to insert the the names of the found content filters into
 * 
 * @return The number of found content filters
 */
template<typename BinIterator>
uint32_t find_registered_content_filters(
   const dds::domain::DomainParticipant& participant, 
   BinIterator begin)
{
    return find_registered_content_filters(participant.delegate(), begin);
}

} } // namespace rti::topic::



#endif // RTI_DDS_TOPIC_FIND_IMPL_HPP_
