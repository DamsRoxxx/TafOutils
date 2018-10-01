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

#ifndef RTI_DDS_TOPIC_TOPIC_HPP_
#define RTI_DDS_TOPIC_TOPIC_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_builtin_impl.h"

#include <dds/core/BuiltinTopicTypes.hpp>
#include <dds/core/corefwd.hpp>
#include <dds/topic/qos/TopicQos.hpp>
#include <dds/topic/TopicTraits.hpp>
#include <dds/topic/TopicListener.hpp>

#include <rti/topic/TopicDescriptionImpl.hpp>
#include <rti/core/Exception.hpp>
#include <rti/topic/detail/TopicListenerForwarder.hpp>
#include <rti/domain/PluginSupport.hpp>


namespace rti { namespace topic {

class OMG_DDS_API UntypedTopic : public virtual UntypedTopicDescription {
protected:
    ~UntypedTopic();

public:
    const dds::topic::qos::TopicQos qos() const;
    void qos(const dds::topic::qos::TopicQos& the_qos);

    dds::core::status::InconsistentTopicStatus inconsistent_topic_status() const;

    // From Entity
    void close(); // override

    // From TopicDescription
    //
    // 'using' is to avoid partially-overridden warning:
    using UntypedTopicDescription::reserved_data;
    virtual void reserved_data(void * ptr);

public: // but for internal use

    DDS_Topic * native_topic()
    {
        return DDS_Topic_narrow_from_entity(this->native_entity());
    }

    const DDS_Topic * native_topic() const
    {
        return DDS_Topic_narrow_from_entity(
            (DDS_Entity *) this->native_entity());
    }
};

// ----------------------------------------------------------------------------

namespace detail {

OMG_DDS_API
TopicCreationResult create_native_topic_untyped(
    const dds::domain::DomainParticipant& participant,
    const std::string& name,
    const std::string& type_name,
    const dds::topic::qos::TopicQos * qos,
    DDS_TopicListener* listener,
    const dds::core::status::StatusMask& mask);

// Returns native writer and boolean indicating if it needs to be enabled
template <typename T>
TopicCreationResult create_native_topic(
    const dds::domain::DomainParticipant& participant,
    const std::string& name,
    const std::string& type_name = dds::topic::topic_type_name<T>::value(),
    const dds::topic::qos::TopicQos * qos = NULL,
    dds::topic::TopicListener<T>* listener = NULL,
    const dds::core::status::StatusMask& mask =
        dds::core::status::StatusMask::all())
{
    DDS_TopicListener native_listener;
    if (listener != NULL) {
        native_listener = create_native_listener<T>(listener);
    }

    // const_cast due to issue CPPPSM-178
    dds::topic::topic_type_support<T>::register_type(
        const_cast<dds::domain::DomainParticipant&>(participant), type_name);

    return create_native_topic_untyped(
        participant, name, type_name, qos, listener ? &native_listener : NULL, mask);
}

// Returns native writer and boolean indicating if it needs to be enabled
OMG_DDS_API
TopicCreationResult create_native_dynamic_data_topic(
    const dds::domain::DomainParticipant& participant,
    const std::string& name,
    const dds::core::xtypes::DynamicType& type,
    const dds::topic::qos::TopicQos * qos = NULL,
    dds::topic::TopicListener<dds::core::xtypes::DynamicData>* listener = NULL,
    const dds::core::status::StatusMask& mask =
        dds::core::status::StatusMask::all());

} // namespace detail

template <typename T>
class OMG_DDS_API TopicImpl : public TopicDescriptionImpl<T>, public UntypedTopic {
public:
    typedef dds::topic::topic_type_support<T> topic_type_support;
    typedef dds::topic::TopicListener<T> Listener;

    TopicImpl(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& the_name)
        : UntypedTopicDescription(
            detail::create_native_topic<T>(
                the_participant, the_name, dds::topic::topic_type_name<T>::value()),
            the_participant,
            the_name,
            dds::topic::topic_type_name<T>::value())
    {
        // T must be a valid registered DDS type
        OMG_DDS_STATIC_ASSERT(
            (dds::topic::is_topic_type<T>::value),
            "Type T must be a DDS topic type");
    }

    TopicImpl(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& the_name,
        const std::string& the_type_name)
        : UntypedTopicDescription(
            detail::create_native_topic<T>(the_participant, the_name, the_type_name),
            the_participant,
            the_name,
            the_type_name)
    {
        // T must be a valid registered DDS type
        OMG_DDS_STATIC_ASSERT(
            (dds::topic::is_topic_type<T>::value),
            "Type T must be a DDS topic type");
    }

    TopicImpl(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& topic_name,
        const dds::topic::qos::TopicQos& the_qos,
        dds::topic::TopicListener<T>* the_listener,
        const dds::core::status::StatusMask& mask)
        : UntypedTopicDescription(
            detail::create_native_topic<T>(
                the_participant,
                topic_name,
                dds::topic::topic_type_name<T>::value(),
                &the_qos,
                the_listener,
                mask),
            the_participant,
            topic_name,
            dds::topic::topic_type_name<T>::value())
    {
        // T must be a valid registered DDS type
        OMG_DDS_STATIC_ASSERT(
            (dds::topic::is_topic_type<T>::value),
            "Type T must be a DDS topic type");

        if (the_listener != NULL) {
            retain_for_listener();
        }
    }

    TopicImpl(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& the_name,
        const std::string& the_type_name,
        const dds::topic::qos::TopicQos& the_qos,
        dds::topic::TopicListener<T>* the_listener,
        const dds::core::status::StatusMask& mask)
        : UntypedTopicDescription(
            detail::create_native_topic<T>(
                the_participant, the_name, the_type_name, &the_qos, the_listener, mask),
            the_participant,
            the_name,
            the_type_name)
    {
        // T must be a valid registered DDS type
        OMG_DDS_STATIC_ASSERT(
            (dds::topic::is_topic_type<T>::value),
            "Type T must be a DDS topic type");

        if (the_listener != NULL) {
            retain_for_listener();
        }
    }

    TopicImpl(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& the_name,
        const dds::core::xtypes::DynamicType& type)
        : UntypedTopicDescription(
            detail::create_native_dynamic_data_topic(the_participant, the_name, type),
            the_participant,
            the_name,
            rti::core::xtypes::type_name(type))
    {
        // T must be DynamicData
        OMG_DDS_STATIC_ASSERT(
            (dds::core::is_same<T, dds::core::xtypes::DynamicData>::value),
            "Type T must be DynamicData when creating a Topic with a DynamicType");
    }

    TopicImpl(
        const dds::domain::DomainParticipant& the_participant,
        const std::string& the_name,
        const dds::core::xtypes::DynamicType& type,
        const dds::topic::qos::TopicQos& the_qos,
        dds::topic::TopicListener<T>* the_listener,
        const dds::core::status::StatusMask& mask)
        : UntypedTopicDescription(
            detail::create_native_dynamic_data_topic(
                the_participant, the_name, type, &the_qos, the_listener, mask),
            the_participant,
            the_name,
            rti::core::xtypes::type_name(type))
    {
        // T must be DynamicData
        OMG_DDS_STATIC_ASSERT(
            (dds::core::is_same<T, dds::core::xtypes::DynamicData>::value),
            "Type T must be DynamicData when creating a Topic with a DynamicType");

        if (the_listener != NULL) {
            retain_for_listener();
        }
    }

    // for internal use
    TopicImpl(DDS_Topic * the_native_topic)
        : UntypedTopicDescription(
            DDS_Topic_as_entity(the_native_topic),
            DDS_Topic_as_topicdescription(the_native_topic))
    {
    }

    ~TopicImpl()
    {
        try {
            this->close();
        } catch (const std::exception& ex) {
            DDSLog_exception("~TopicImpl()", &RTI_LOG_ANY_FAILURE_s, ex.what());
        }
    }


    void listener(
        Listener* the_listener,
        const ::dds::core::status::StatusMask& mask)
    {
        if (the_listener == NULL) {
            DDS_Topic_set_listener(native_topic(), NULL, DDS_STATUS_MASK_NONE);
            this->unretain_for_listener();
        } else {
            DDS_TopicListener native_listener =
                detail::create_native_listener(the_listener);
            DDS_ReturnCode_t retcode = DDS_Topic_set_listener(
                native_topic(), &native_listener, mask.to_ulong());
            rti::core::check_return_code(retcode, "failed to set listener");

            this->retain_for_listener();
        }
    }

    Listener * listener() const
    {
        DDS_TopicListener native_listener =
            DDS_Topic_get_listener((DDS_Topic *) native_topic());

        return static_cast<Listener*>(
            native_listener.as_listener.listener_data);
    }

    // Defined here in order to avoid the 'inherits via dominance' warning
    void close() 
    {
        UntypedTopic::close();
    }

    // To avoid partially-overridden warning
    using UntypedTopic::reserved_data;
    void reserved_data(void * ptr)
    {
        // Redefined to avoid inheritance-via-dominance warning
        UntypedTopic::reserved_data(ptr);
    }

};

} } // namespace rti::topic

namespace dds { namespace topic {

/** 
 * @ingroup DDSParticipantBuiltInTopicModule
 * @brief Participant builtin topic name 
 *  
 * Topic name of the builtin dds::sub::DataReader for the 
 * dds::topic::ParticipantBuiltinTopicData type 
 */
OMG_DDS_API std::string participant_topic_name();

/** 
 * @ingroup DDSTopicBuiltInTopicModule
 * @brief Topic topic name 
 *  
 * Topic name of the builtin dds::sub::DataReader for the 
 * dds::topic::TopicBuiltinTopicData type 
 */
OMG_DDS_API std::string topic_topic_name();

/** 
 * @ingroup DDSPublicationBuiltInTopicModule
 * @brief  Publication topic name 
 *  
 * Topic name of the builtin dds::sub::DataReader for the 
 * dds::topic::PublicationBuiltinTopicData type 
 */
OMG_DDS_API std::string publication_topic_name();

/** 
 * @ingroup DDSSubscriptionBuiltInTopicModule
 * @brief Subscription topic name 
 *  
 * Topic name of the builtin dds::sub::DataReader for the 
 * dds::topic::SubscriptionBuiltinTopicData type 
 */
OMG_DDS_API std::string subscription_topic_name();

} }  // namespace dds::topic

namespace rti { namespace topic {

// Helper function to check if a topic name is one of the builtin topics
OMG_DDS_API
bool is_builtin_topic(const std::string &topic_name);

OMG_DDS_API std::string virtual_subscription_topic_name();

/**
 * @ingroup DDSServiceRequestBuiltInTopicModule
 * @brief ServiceRequest built-in topic name
 *
 * Topic name of the builtin dds::sub::DataReader for the
 * rti::topic::ServiceRequest type
 */
OMG_DDS_API std::string service_request_topic_name();

} }  // namespace rti::topic

#endif // RTI_DDS_TOPIC_TOPIC_HPP_
