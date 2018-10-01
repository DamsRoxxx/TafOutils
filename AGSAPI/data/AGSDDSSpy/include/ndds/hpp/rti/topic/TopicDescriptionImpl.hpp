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

#ifndef RTI_DDS_TOPIC_TOPIC_DESCRIPTION_HPP_
#define RTI_DDS_TOPIC_TOPIC_DESCRIPTION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/domain/domainfwd.hpp>
#include <rti/core/Entity.hpp>
#include <rti/core/detail/NativeEntity.hpp>

#include "ndds/ndds_c.h"

namespace rti { namespace topic {

namespace detail {

// Contains a DDS_Topic (as Entity) and a boolean indicating whether to enable
typedef std::pair<DDS_Entity*, bool> EntityCreationResult;

// Adds a pointer to the topic as topic description
typedef std::pair<EntityCreationResult, DDS_TopicDescription*> TopicCreationResult;

}

class OMG_DDS_API UntypedTopicDescription : public rti::core::Entity {
public:
    const dds::domain::DomainParticipant& participant() const;
    dds::domain::DomainParticipant& participant();
    const std::string& name() const;
    const std::string& type_name() const;

    DDS_TopicDescription * native_topic_description()
    {
        assert_not_closed();
        return native_topic_description_;
    }

    const DDS_TopicDescription * native_topic_description() const
    {
        assert_not_closed();
        return native_topic_description_;
    }


    virtual void close(); /* override */
    bool closed() const; /* override */
    virtual void reserved_data(void * ptr); /* override */
    void * reserved_data(); /* override */

protected:
    UntypedTopicDescription();

    UntypedTopicDescription(
        const detail::TopicCreationResult& created_topic,
        const dds::domain::DomainParticipant& participant,
        const std::string& name,
        const std::string& type_name);

    UntypedTopicDescription(
        DDS_Entity * native_entity,
        DDS_TopicDescription * native_topic_description);

    virtual ~UntypedTopicDescription();

    void native_topic_description(
        DDS_Entity * entity,
        DDS_TopicDescription * topic_description);

    void forget_participant();


protected:
    DDS_TopicDescription * native_topic_description_;
    dds::domain::DomainParticipant participant_;
    std::string name_;
    std::string type_name_;
};

template<typename T>
class TopicDescriptionImpl : public virtual UntypedTopicDescription {
protected:
    TopicDescriptionImpl()
    {
    }
};

template <typename T>
dds::topic::TopicDescription<T> create_topic_description_from_native(
    DDS_TopicDescription * native_topic_description)
{
    using rti::core::detail::create_from_native_entity;

    DDS_Topic * as_topic = DDS_Topic_narrow(native_topic_description);
    if (as_topic != NULL) {
        return create_from_native_entity<dds::topic::Topic<T> >(as_topic);
    }

    DDS_ContentFilteredTopic * as_cft =
        DDS_ContentFilteredTopic_narrow(native_topic_description);
    if (as_cft != NULL) {
        return create_from_native_entity<dds::topic::ContentFilteredTopic<T> >(as_cft);
    }

    throw dds::core::PreconditionNotMetError(
        "Native TopicDescription is not a Topic nor a ContentFilteredTopic");
}

} }

#endif // RTI_DDS_TOPIC_TOPIC_DESCRIPTION_HPP_
