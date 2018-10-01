/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.7a,03mar14,eam Created
============================================================================= */

#ifndef RTI_DDS_CORE_QOS_PROVIDER_HPP_
#define RTI_DDS_CORE_QOS_PROVIDER_HPP_

#include "dds_c/dds_c_xml.h"
#include "dds_c/dds_c_xml_impl.h"

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>

#include <dds/core/corefwd.hpp>

#include <dds/domain/qos/DomainParticipantQos.hpp>
#include <dds/pub/qos/PublisherQos.hpp>
#include <dds/pub/qos/DataWriterQos.hpp>
#include <dds/sub/qos/SubscriberQos.hpp>
#include <dds/sub/qos/DataReaderQos.hpp>
#include <dds/topic/qos/TopicQos.hpp>

#include <rti/core/QosProviderParams.hpp>

#include <rti/core/OptionalValue.hpp>
#include <rti/core/Exception.hpp>
#include <rti/core/LockGuard.hpp>
#include <rti/domain/DomainParticipantConfigParams.hpp>
#include <rti/domain/FactoryPluginSupport.hpp>

namespace rti { namespace core {

namespace detail {

inline const char * empty_string_to_NULL(const std::string& my_string) {
    return (my_string.length() == 0 ? NULL : my_string.c_str());
}

// For the DefaultQosProvider, it uses the DPF lock; for any user-created
// QosProvider it uses a new semaphore and takes ownership of it.
class QosProviderMutex {
public:
    // Leaves the semaphore set to NULL, meaning that the DPF lock will be used.
    // QosProviderResourceManager will create a new semaphore if needed.
    QosProviderMutex() : native_semaphore_(NULL)
    {
    }

    ~QosProviderMutex();

    void take();
    void give();

    RTIOsapiSemaphore *native_semaphore_;
};

// Manage the QosProvider Resources -------------------------------------------
class QosProviderResourceManager {
public:
    QosProviderResourceManager(bool default_provider = false);

    ~QosProviderResourceManager();

    DDS_QosProvider* get() const;
    QosProviderMutex& mutex() const
    {
        return mutex_;
    }

    void finalize_provider();

private:
    DDS_QosProvider *native_provider_;
    mutable QosProviderMutex mutex_;
    bool default_provider_;
};

}

/**
 * @relatesalso dds::core::QosProvider
 * @brief Special value to select the default QoS profile
 */
extern OMG_DDS_API_VARIABLE const char* USE_DDS_DEFAULT_QOS_PROFILE; 

/** @RTI_class_definition NA */
class OMG_DDS_API QosProviderImpl {
public: 
    typedef dds::core::smart_ptr_traits<QosProviderImpl>::ref_type
        ref_type;
    typedef dds::core::smart_ptr_traits<QosProviderImpl>::weak_ref_type
        weak_ref_type;

public:
    QosProviderImpl(const std::string& uri, const std::string& profile);

    QosProviderImpl(const std::string& uri);

    QosProviderImpl(const char* uri);

    QosProviderImpl(const rti::core::QosProviderParams& params);

    QosProviderImpl(
        const rti::core::QosProviderParams& params, bool default_provider);

    ~QosProviderImpl();

public: 
    static ref_type Default();
    static void reset_default();

    void reset_provider();

    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Get the rti::core::QosProviderParams for the default
     * QosProvider
     * 
     * @return rti::core::QosProviderParams 
     */
    static rti::core::QosProviderParams default_provider_params();

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the rti::core::QosProviderParams for the
     * default QosProvider
     * 
     * @param params The QosProviderParams to set
     */
    static void default_provider_params(
        const rti::core::QosProviderParams& params);

    // Getters
    dds::domain::qos::DomainParticipantQos participant_qos() const;
    dds::domain::qos::DomainParticipantQos participant_qos(
        const std::string& id) const;

    dds::topic::qos::TopicQos topic_qos() const;
    dds::topic::qos::TopicQos topic_qos(const std::string& id) const;

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the dds::topic::qos::TopicQos that this
     * QosProvider is currently associated with. 
     * 
     *  The TopicQos will be found based on the given profile name and 
     * topic name.   
     * 
     * @param id The profile to look for the TopicQos in
     * @param topic_name The topic name associated with profile to set
     * 
     * @return dds::topic::qos::TopicQos The TopicQos that is located 
     * in the profile specified by id 
     */
    dds::topic::qos::TopicQos topic_qos_w_topic_name(
       const std::string& id, const std::string& topic_name) const; // Extension

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the dds::topic::qos::TopicQos that this
     * QosProvider is currently associated with. 
     * 
     *  The TopicQos will be found based on the given topic name and 
     * must be located in the current default profile associated with the 
     * QosProvider.  
     * 
     * @param topic_name The topic name associated with profile to set
     * 
     * @return dds::topic::qos::TopicQos The TopicQos that is located 
     * in the profile specified by id 
     */
    dds::topic::qos::TopicQos topic_qos_w_topic_name(
       const std::string& topic_name) const; // Extension

    dds::sub::qos::SubscriberQos subscriber_qos() const;
    dds::sub::qos::SubscriberQos subscriber_qos(const std::string& id) const;

    dds::sub::qos::DataReaderQos datareader_qos() const;
    dds::sub::qos::DataReaderQos datareader_qos(const std::string& id) const;

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the dds::sub::qos::DataReaderQos that this
     * QosProvider is currently associated with. 
     * 
     *  The DataReaderQos will be found based on the given profile 
     * name and topic name.   
     * 
     * @param id The profile to look for the DataReaderQos in
     * @param topic_name The topic name associated with profile to set
     * 
     * @return dds::sub::qos::DataReaderQos The DataReaderQos that is located 
     * in the profile specified by id 
     */
    dds::sub::qos::DataReaderQos datareader_qos_w_topic_name(
       const std::string& id, const std::string& topic_name) const;

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the dds::sub::qos::DataReaderQos that this
     * QosProvider is currently associated with. 
     * 
     *  The DataReaderQos will be found based on the given topic name 
     * and must be located in the current default profile associated with the 
     * QosProvider.  
     * 
     * @param topic_name The topic name associated with profile to set
     * 
     * @return dds::sub::qos::DataReaderQos The DataReaderQos that is located 
     * in the profile specified by id 
     */
    dds::sub::qos::DataReaderQos datareader_qos_w_topic_name(
       const std::string& topic_name) const;

    dds::pub::qos::PublisherQos publisher_qos() const;
    dds::pub::qos::PublisherQos publisher_qos(const std::string& id) const;

    dds::pub::qos::DataWriterQos datawriter_qos() const;
    dds::pub::qos::DataWriterQos datawriter_qos(const std::string& id) const;

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the dds::pub::qos::DataWriterQos that this
     * QosProvider is currently associated with. 
     * 
     * The DataWriterQos will be found based on the given profile 
     * name and topic name.   
     * 
     * @param id The profile to look for the DataWriterQos in
     * @param topic_name The topic name associated with profile to set
     * 
     * @return dds::pub::qos::DataWriterQos The DataWriterQos that is located 
     * in the profile specified by id 
     */
    dds::pub::qos::DataWriterQos datawriter_qos_w_topic_name(
       const std::string& id, const std::string& topic_name) const;

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the dds::pub::qos::DataWriterQos that this
     * QosProvider is currently associated with. 
     * 
     *  The DataWriterQos will be found based on the given topic name 
     * and  must be located in the current default profile associated with the 
     * QosProvider.  
     * 
     * @param topic_name The topic name associated with profile to set
     * 
     * @return dds::pub::qos::DataWriterQos The DataWriterQos that is located 
     * in the profile specified by id 
     */
    dds::pub::qos::DataWriterQos datawriter_qos_w_topic_name(
       const std::string& topic_name) const;

public:
    // --- RTI extensions: ----------------------------------------------------
    // Getters
    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Get the default library associated with this
     * QosProvider. 
     *  
     *  There may not be a default library set. The default library is 
     * the library that is checked in when setting the default profile if no 
     * library name is explicitly given. The default library is configurable.   
     * 
     * @return rti::core::optional_value<std::string> The default library. 
     */
    rti::core::optional_value<std::string> default_library() const;

    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Get the default profile associated with this
     * QosProvider. 
     *  
     *  There may not be a default profile set.  
     * @return rti::core::optional_value<std::string> The default profile. 
     */
    rti::core::optional_value<std::string> default_profile() const;

    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Get the default profile library associated with this
     * QosProvider. 
     *  
     * There may not be a default profile library set. The default 
     * profile library is the library in which the default profile resides and 
     * is not necessarily the same library as the one returned from 
     * default_library(). The default profile library is not configurable.
     * 
     * @return rti::core::optional_value<std::string> The default profile library. 
     */
    rti::core::optional_value<std::string> default_profile_library() const;

    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Get a list of the QoS profile libraries loaded by this
     * QosProvider.
     * 
     * @return dds::core::StringSeq A list of the currently loaded QoS profile 
     * libraries.  
     */
    dds::core::StringSeq qos_profile_libraries() const;

    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Get a list of the QoS profiles located in the default
     * library of this QosProvider. 
     * 
     * @return dds::core::StringSeq A list of profiles.
     */
    dds::core::StringSeq qos_profiles(const std::string& library_name) const;

    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Check if the profiles are loaded by this QosProvider
     * 
     * @return bool false if the profiles are not loaded, true otherwise.
     */
    bool profiles_loaded() const;

    /** 
     * @memberof dds::core::QosProvider 
     * @brief @extension Load a type
     *
     * @param type_library_name The name of the library that contains the type
     * @param type_name The name of the type
     *
     * This function loads a type from its XML definition.
     *
     * @see \ref DDSXTypesExampleModule_dynamic_type_creation_xml "Example".
     *
     */
    const dds::core::xtypes::DynamicType& type(
        const std::string& type_library_name,
        const std::string& type_name) const;

    /**
     * @memberof dds::core::QosProvider
     * @brief @extension Get a list of the type libraries loaded by this
     * QosProvider.
     *
     * @return A list of the currently loaded type libraries.
     */
    dds::core::StringSeq type_libraries() const;

    /**
     * @memberof dds::core::QosProvider
     * @brief @extension Get the QosProvider params for this QosProvider.
     *
     * @return rti::core::QosProviderParams The QosProviderParams for this
     * QosProvider.
     */
    rti::core::QosProviderParams provider_params() const;

    // Setters
    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the default library for this QosProvider.
     * 
     * @param library_name The library to set as the default or
     * rti::core::USE_DDS_DEFAULT_QOS_PROFILE to unset the default library and
     * use the system default.
     */
    void default_library(const std::string& library_name);

    /**
     * @memberof dds::core::QosProvider 
     * @brief @extension Set the default profile for this QosProvider.
     *  
     * The profile must be located in the current default library 
     * unless the library is also specified in the name.  
     *  
     * @param profile_name The profile to set as the default or
     * rti::core::USE_DDS_DEFAULT_QOS_PROFILE to unset the default profile and
     * use the system default.
     */
    void default_profile(const std::string& profile_name);

    /** 
     * @memberof dds::core::QosProvider  
     * @brief @extension Set the rti::core::QosProviderParams for this
     * QosProvider.
     * 
     * @param provider_params The QosProviderParams to set.
     */
    void provider_params(const rti::core::QosProviderParams& provider_params);

    // Loading
    /** 
     * @memberof dds::core::QosProvider  
     * @brief @extension Load the XML QoS profiles.
     * 
     * The XML QoS profiles are loaded implicitly after the first
     * dds::domain::DomainParticipant is created or explicitly, after a call 
     * to this function. 
     * This method has the same effect as reload_profiles().
     */
    void load_profiles();

    /**
     * @memberof dds::core::QosProvider  
     * @brief @extension Reload the XML QoS profiles.
     * 
     * The XML QoS profiles are loaded implicitly after the first
     * DomainParticipant is created or explicitly, after a call to this
     * function. 
     * This method has the same effect as load_profiles().
     */
    void reload_profiles();

    /**
     * @memberof dds::core::QosProvider  
     * @brief @extension Unload the XML QoS profiles.
     * 
     * The resources associated with the XML QoS profiles are freed. 
     * Any reference to the profiles after calling this function will fail 
     * with an Exception.
     */
    void unload_profiles();

    /**
     * @memberof dds::core::QosProvider  
     * @brief @extension Creates a dds::domain::DomainParticipant given its 
     * configuration name from a description provided in an XML configuration 
     * file that has been loaded by this QosProvider.
     *  
     * \dref_details_DomainParticipantFactory_create_participant_from_config
     *  
     * @param config_name Name of the participant configuration in the XML file.
     * @param params input parameters that allow changing some properties of 
     * the configuration referred to by \p config_name. Specifically, \p params
     * allows overriding the domain ID, participant name, and entities 
     * QoS specified in the XML configuration. 
     *  
     * @see XMLAppCreationExampleModule 
     */
    dds::domain::DomainParticipant 
    create_participant_from_config(
        const std::string& config_name, 
        const rti::domain::DomainParticipantConfigParams& params = 
            rti::domain::DomainParticipantConfigParams());

private: 

    void init(const std::string& uri, const rti::core::QosProviderParams& provider_params);

    static std::pair<std::string, std::string>
        split_profile_name(const std::string &profile);

private:
    detail::QosProviderResourceManager native_provider_;
/** @RTI_remove_lines 1 */
};

// DefaultQosProvider ---------------------------------------------------------
class DefaultQosProvider {
public:
    typedef dds::core::smart_ptr_traits<QosProviderImpl>::ref_type ref_type;

    static ref_type& get_instance();
    static void reset_instance();

    // Anywhere this is called should be protected with the 
    // DefaultQosProvider's mutex
    static void finalize();
    static Semaphore& mutex();
    static void params(const QosProviderParams& params);
    static QosProviderParams params();

private:
    static ref_type& get_instance(const rti::core::QosProviderParams& params);

    static ref_type instance_;
};

} } // namespace rti::core

#endif // RTI_DDS_CORE_QOS_PROVIDER_HPP_

