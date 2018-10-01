/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_CONTENT_FILTERED_TOPIC_IMPL_HPP_
#define RTI_DDS_TOPIC_CONTENT_FILTERED_TOPIC_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_domain.h"

#include <dds/topic/Topic.hpp>
#include <dds/topic/Filter.hpp>
#include <rti/core/detail/NativeConversion.hpp>
#include <rti/core/detail/NativeSequence.hpp>

namespace rti { namespace topic {

namespace detail {

template <typename T>
TopicCreationResult create_native_cft(
    const dds::topic::Topic<T>& topic,
    const std::string& name,
    const dds::topic::Filter& filter)
{
    using rti::core::detail::NativeSequenceAdapter;

    DDS_StringSeq native_params = DDS_SEQUENCE_INITIALIZER;
    NativeSequenceAdapter<char *> seq_adapter(native_params); // RAII
    rti::core::native_conversions::to_native(
        native_params, filter->parameters());

    DDS_ContentFilteredTopic * native_cft = NULL;

    if (filter->name() == "") {
        // Not a custom filter
        native_cft =
            DDS_DomainParticipant_create_contentfilteredtopic(
                const_cast<DDS_DomainParticipant*>(
                    topic.participant()->native_participant()), // CPPPSM
                name.c_str(),
                const_cast<DDS_Topic*>(topic->native_topic()),
                filter.expression().c_str(),
                &native_params);
    } else {
        // A custom filter is being used
        native_cft = 
            DDS_DomainParticipant_create_contentfilteredtopic_with_filter(
               const_cast<DDS_DomainParticipant*>(
                  topic.participant()->native_participant()), // CPPPSM
               name.c_str(),
               const_cast<DDS_Topic*>(topic->native_topic()),
               filter.expression().c_str(),
               &native_params, 
               filter->name().c_str());
    }
    rti::core::check_create_entity(native_cft, "ContentFilteredTopic");

    // Return the information that the CFT base classes need
    return TopicCreationResult(
        EntityCreationResult(
            const_cast<DDS_Entity*>(topic->native_entity()), false),
        native_cft->_as_TopicDescription /* Workaround for CPPPSM-29 */);
}

} // namespace detail

/**
 * @RTI_class_definition NA
 */
template <typename T>
class ContentFilteredTopicImpl : public TopicDescriptionImpl<T> {
public:

    ContentFilteredTopicImpl(
        const dds::topic::Topic<T>& the_topic,
        const std::string& the_name,
        const dds::topic::Filter& the_filter)
        : UntypedTopicDescription(
            detail::create_native_cft(the_topic, the_name, the_filter),
            the_topic.participant(),
            the_name,
            the_topic.type_name()),
          topic_(the_topic)
    {
    }

    ContentFilteredTopicImpl(
        DDS_ContentFilteredTopic * native_cft,
        bool = false /* ignored */)
        : UntypedTopicDescription(
            DDS_Topic_as_entity(DDS_ContentFilteredTopic_get_related_topic(native_cft)),
            DDS_ContentFilteredTopic_as_topicdescription(native_cft)),
          topic_(
              rti::core::detail::create_from_native_entity<dds::topic::Topic<T> >(
                  DDS_ContentFilteredTopic_get_related_topic(native_cft)))
    {
    }

    virtual ~ContentFilteredTopicImpl()
    {
        try {
            this->close();
        } catch (const std::exception& ex) {
            DDSLog_exception(
                "~ContentFilteredTopicImpl()", &RTI_LOG_ANY_FAILURE_s, ex.what());
        }
    }

public:

    std::string filter_expression() const
    {
        const char * expression = DDS_ContentFilteredTopic_get_filter_expression(
            const_cast<DDS_ContentFilteredTopic*>(
                this->native_content_filtered_topic()));
        rti::core::check_get_entity(expression, "get filter expression");

        return expression;
    }

    const dds::core::StringSeq filter_parameters() const
    {
        using rti::core::detail::NativeSequenceAdapter;

        DDS_StringSeq native_params = DDS_SEQUENCE_INITIALIZER;
        NativeSequenceAdapter<char *> seq_adapter(native_params); // RAII

        DDS_ReturnCode_t retcode = DDS_ContentFilteredTopic_get_expression_parameters(
            const_cast<DDS_ContentFilteredTopic*>(
                this->native_content_filtered_topic()), &native_params);
        rti::core::check_return_code(retcode, "get filter parameters");

        return rti::core::native_conversions::from_native<
            std::string, DDS_StringSeq>(native_params);
    }

    template<typename FwdIterator>
    void filter_parameters(const FwdIterator& begin, const FwdIterator& end)
    {
        using rti::core::detail::NativeSequenceAdapter;

        dds::core::StringSeq tmp_params (begin, end);

        DDS_StringSeq native_params = DDS_SEQUENCE_INITIALIZER;
        NativeSequenceAdapter<char *> seq_adapter(native_params); // RAII
        rti::core::native_conversions::to_native(native_params, tmp_params);

        DDS_ReturnCode_t retcode =
            DDS_ContentFilteredTopic_set_expression_parameters(
                this->native_content_filtered_topic(), &native_params);
        rti::core::check_return_code(retcode, "set filter parameters");
    }

    const dds::topic::Topic<T>& topic() const
    {
        return topic_;
    }

    // --- From TopicDescription: ---------------------------------------------

    void close()
    {
        if (!this->closed()) {
            this->reserved_data(NULL);

            if (!this->created_from_c()) {
                DDS_ReturnCode_t retcode =
                    DDS_DomainParticipant_delete_contentfilteredtopic(
                        this->participant()->native_participant(),
                        native_content_filtered_topic());
                rti::core::check_return_code(
                    retcode, "failed to delete DDS_ContentFilteredTopic");
            }

            this->forget_participant();
            TopicDescriptionImpl<T>::close();
        }
    }

    // --- Extensions: --------------------------------------------------------

    /**
     * @memberof dds::topic::ContentFilteredTopic
     * @brief @extension Modifies the filter
     *
     * @param the_filter Contains the new filter expression and parameters. The
     * filter name is immutable: if filter->name() is different it will be
     * ignored.
     *
     * @details @dref_details_ContentFilteredTopic_set_expression
     */
    void filter(const dds::topic::Filter& the_filter)
    {
        using rti::core::detail::NativeSequenceAdapter;

        DDS_StringSeq native_params = DDS_SEQUENCE_INITIALIZER;
        NativeSequenceAdapter<char *> seq_adapter(native_params); // RAII
        rti::core::native_conversions::to_native(
                native_params, the_filter->parameters());

        DDS_ReturnCode_t retcode =
        DDS_ContentFilteredTopic_set_expression(
                native_content_filtered_topic(),
                the_filter.expression().c_str(),
                &native_params);
        rti::core::check_return_code(retcode, "failed to change filter");
    }

    /**
     * @memberof dds::topic::ContentFilteredTopic
     * @brief @extension Appends a term to a parameter
     * @details @dref_details_ContentFilteredTopic_append_to_expression_parameter
     */
    void append_to_expression_parameter(int32_t index, const std::string& val)
    {
        DDS_ReturnCode_t retcode =
            DDS_ContentFilteredTopic_append_to_expression_parameter(
                native_content_filtered_topic(), index, val.c_str());
        rti::core::check_return_code(retcode, "append_to_expression_parameter failed");
    }

    /**
     * @memberof dds::topic::ContentFilteredTopic
     * @brief @extension Removes a term from a parameter
     * @details @dref_details_ContentFilteredTopic_remove_from_expression_parameter
     */
    void remove_from_expression_parameter(int32_t index, const std::string& val)
    {
        DDS_ReturnCode_t retcode =
            DDS_ContentFilteredTopic_remove_from_expression_parameter(
                native_content_filtered_topic(), index, val.c_str());
        rti::core::check_return_code(retcode, "remove_from_expression_parameter failed");
    }

public:
    // --- For internal use: --------------------------------------------------

    DDS_ContentFilteredTopic * native_content_filtered_topic()
    {
        return DDS_ContentFilteredTopic_narrow(
            this->native_topic_description());
    }

    const DDS_ContentFilteredTopic * native_content_filtered_topic() const
    {
        return DDS_ContentFilteredTopic_narrow(
            const_cast<DDS_TopicDescription *>(this->native_topic_description()));
    }

private:
    dds::topic::Topic<T> topic_;
};

} } // namespace rti::topic

namespace rti { namespace core { namespace detail {

template <typename T>
struct get_ptr_from_native_entity<rti::topic::ContentFilteredTopicImpl<T>, DDS_ContentFilteredTopic> {

    typedef rti::core::Entity::weak_ref_type EntityWeakRef;
    typedef rti::core::Entity::ref_type EntityRef;
    typedef typename dds::core::smart_ptr_traits<rti::topic::ContentFilteredTopicImpl<T> >::ref_type
        ContentFilteredTopicRef;

    static ContentFilteredTopicRef do_it(DDS_ContentFilteredTopic * native_cft)
    {
        // First get the weak reference we store as reserved data in the native
        // entity
        EntityWeakRef ** weak_ref = static_cast<EntityWeakRef**>(
            DDS_TopicDescription_get_user_objectI(
                DDS_ContentFilteredTopic_as_topicdescription(native_cft)));

        if (weak_ref == NULL || *weak_ref == NULL) {
            // If the weak reference doesn't exist it's because someone else
            // created this entity natively, bypassing the C++ API. An example is
            // the XML application-creation. We return an empty reference.
            return ContentFilteredTopicRef();
        }

        // Locking a weak reference creates a strong reference
        EntityRef entity_ref = (*weak_ref)->lock();
        if (!entity_ref) {
            // The weak reference has expired
            return ContentFilteredTopicRef();
        }

        // Downcast from rti::core::Entity to the actual class,
        // ContentFilteredTopicImpl
        ContentFilteredTopicRef cft_ref =
            rtiboost::dynamic_pointer_cast<rti::topic::ContentFilteredTopicImpl<T> >(
                entity_ref);
        if (!cft_ref) {
            throw dds::core::InvalidDowncastError(
                "Internal downcast error to ContentFilteredTopic");
        }

        return cft_ref;
    }
};

} } } // namespace rti::core::detail

#endif // RTI_DDS_TOPIC_CONTENT_FILTERED_TOPIC_IMPL_HPP_
