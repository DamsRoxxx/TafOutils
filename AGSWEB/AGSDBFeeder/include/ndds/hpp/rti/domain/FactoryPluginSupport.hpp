
/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,24oct14,eam Created
============================================================================= */

#ifndef RTI_DDS_DOMAIN_FACTORY_PLUGIN_SUPPORT_HPP_
#define RTI_DDS_DOMAIN_FACTORY_PLUGIN_SUPPORT_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_factory_plugin_impl.h"
#include <rti/core/ProxyTypeSupport.hpp>
#include <rti/core/Semaphore.hpp>

namespace rti { namespace domain { 

class OMG_DDS_API FactoryPluginSupport {
public:
    static OMG_DDS_API_CLASS_VARIABLE bool is_set; 

    static rti::core::Semaphore& mutex();

public:        
    
    static DDS_DomainParticipant * create_participant(
       DDS_DomainId_t domainId,
       const struct DDS_DomainParticipantQos * qos,
       const ListenerInfo listenerInfo,
       DDS_StatusMask mask);
    
    static DDS_ReturnCode_t delete_participant(
        DDS_DomainParticipant * cParticipant);
    
    static DDS_Publisher * create_publisher(
        DDS_DomainParticipant * cParticipant,
        const struct DDS_PublisherQos * qos,
        const ListenerInfo listenerInfo,
        DDS_StatusMask mask);
    
    static DDS_Publisher * get_implicit_publisher(
        DDS_DomainParticipant * participant);
    
    static DDS_Subscriber * create_subscriber(
        DDS_DomainParticipant * cParticipant,
        const struct DDS_SubscriberQos * qos,
        const ListenerInfo listenerInfo,
        DDS_StatusMask mask);
    
    static DDS_Subscriber * get_implicit_subscriber(
        DDS_DomainParticipant * participant);
    
    static DDS_Topic * create_topic(
        DDS_DomainParticipant * cParticipant,
        const char * topic_name,
        const char * type_name,
        const struct DDS_TopicQos* qos,
        const ListenerInfo listenerInfo,
        DDS_StatusMask mask);
    
    static DDS_TopicDescription * create_content_filtered_topic(
        DDS_DomainParticipant * participant,
        const char * name,
        DDS_Topic * related_topic,
        const char * filter_expression,
        const struct DDS_StringSeq * filter_parameters,
        const char * filter_name);
    
    static DDS_DataWriter * create_datawriter(
        DDS_Publisher * publisher,
        DDS_Topic * topic,
        const struct DDS_DataWriterQos * qos,
        const ListenerInfo listenerInfo,
        DDS_StatusMask mask);
    
    static DDS_DataReader * create_datareader(
        DDS_Subscriber * subscriber,
        DDS_TopicDescription * topicDescription,
        const struct DDS_DataReaderQos * qos,
        const ListenerInfo listenerInfo,
        DDS_StatusMask mask);
    
    static struct DDS_ProxyTypeSupport * create_dynamic_data_proxy_type_support(
        const DDS_TypeCode * typeCode,
        const struct DDS_DynamicDataTypeProperty_t * props);
    
    static struct DDS_ProxyTypeSupport * create_user_proxy_type_support(
        DDS_FactoryPluginUserTypeInfo userTypeInfo);

    static void create_factory_plugin_support(
        struct DDS_FactoryPluginSupport *plugin_support);
};

} } // namespace rti::domain

#endif //RTI_DDS_DOMAIN_FACTORY_PLUGIN_SUPPORT_HPP_
