#ifndef OMG_DDS_CORE_QOS_TPROVIDER_HPP_
#define OMG_DDS_CORE_QOS_TPROVIDER_HPP_


/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Inc.
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

#include <dds/core/Reference.hpp>

#include <dds/domain/qos/DomainParticipantQos.hpp>

#include <dds/topic/qos/TopicQos.hpp>

#include <dds/sub/qos/SubscriberQos.hpp>
#include <dds/sub/qos/DataReaderQos.hpp>

#include <dds/pub/qos/PublisherQos.hpp>
#include <dds/pub/qos/DataWriterQos.hpp>

namespace dds {
  namespace core {
    template <typename DELEGATE>
    class TQosProvider;
  }
}

/**
 * @RTI_class_definition class dds::core::QosProvider
 * @ingroup NDDSXmlConfigurationModule
 * @headerfile dds/core/QosProvider.hpp
 *  
 * @brief @st_ref_type The QosProvider class provides a way for a user to control and
 * access the XML QoS profiles that are loaded by @ndds 
 *  
 *  A QosProvider is created with a URI that identifies a file location 
 * containing QoS profiles, a string representation of the QoS profiles that 
 * you want the QosProvider to load, or a URL group that has a combination of 
 * files and strings from which to load profiles. For more information on the 
 * correct format of these  URIs and URL groups, please see section 
 * 17.11 URL Groups in the  RTI_CoreLibrariesAndUtilities_Users_Manual.pdf. 
 * More information about QoS  Profiles can be found in section 
 * 17.9 QoS Profiles, also in the  User's Manual. 
 *  
 * For examples of how to use the QosProvider see 
 * @ref DDSQosProviderExampleModule. 
 *  
 * @section ProfileNames Specifying a Profile Name
 * Any of the methods that take a profile name can be passed either just 
 * the profile name or the library and profile name as a string in the form of 
 * "library_name::profile_name". 
 *  
 * Passing rti::core::USE_DDS_DEFAULT_QOS_PROFILE for the profile or library name in
 * dds::core::QosProvider::default_profile(const std::string&) or
 * dds::core::QosProvider::default_library(const std::string&) will unset the current
 * default profile or library. 
 *
 * @see \ref DDSQosProviderExampleModule
 */
template <typename DELEGATE>
class dds::core::TQosProvider : public dds::core::Reference<DELEGATE> {
public:
  OMG_DDS_REF_TYPE(TQosProvider, dds::core::Reference, DELEGATE)

protected:
    // Spec error CPPPSM-168: need this constructor
    explicit TQosProvider(const DELEGATE_REF_T& ref)
        : dds::core::Reference<DELEGATE>(ref)
    {
    }

public:
    /**
    * @brief Create a QosProvider fetching QoS configuration from 
    * the specified URI. 
    *  
    * For instance, the following code:
    * \code
    * dds::core::QosProvider xml_file_provider(
    *     "file:///somewhere/on/disk/qos-config.xml", "MyLibrary::MyProfile");
    * \endcode
    * will create a QosProvider which loads all of the QoS profiles from 
    * qos-config.xml and uses "MyLibrary::MyProfile" as the default profile. 
    *  
    * @param uri The URI describing the location of the QoS profiles to load. 
    * @param profile The QoS profile to set as the default, overriding any 
    * is_default_qos tag in the loaded XML file.
    */
    TQosProvider(const std::string& uri, const std::string& profile)
      : dds::core::Reference<DELEGATE>(new DELEGATE(uri, profile))
    {
    }

    /**
    * @brief Create a QosProvider fetching QoS configuration from 
    * the specified URI. 
    *  
    *  For instance, the following code: 
    * \code
    *    QosProvider xml_file_provider("file:///somewhere/on/disk/qos-config.xml");
    * \endcode
    * will create a QosProvider which loads all of the QoS profiles from 
    * qos-config.xml and will only have a default profile if one of the 
    * profiles in qos-config.xml is marked with the is_default_qos set to true. 
    *  
    * @param uri The URI describing the location of the QoS profiles to load. 
    * If no is_default_qos tag is found in the QoS profiles, then no profile 
    * will be set as default. Instead, the QosProvider will be associated with 
    * the DDS default QoS values until a default profile is set using the 
    * default_library and default_profile methods.  
    */
    explicit TQosProvider(const std::string& uri)
    : dds::core::Reference<DELEGATE>(new DELEGATE(uri))
    {
    }

    explicit TQosProvider(const char* uri)
    : dds::core::Reference<DELEGATE>(new DELEGATE(uri))
    {
    }

    /** 
    * @brief Get the dds::domain::qos::DomainParticipantQos currently 
    *        associated with this QosProvider
    *  
    * @return The DomainParticipantQos 
    */
    dds::domain::qos::DomainParticipantQos
    participant_qos()
    {
      return this->delegate()->participant_qos();
    }

    /**
     * @brief Set the dds::domain::qos::DomainParticipantQos that this 
     * QosProvider is currently associated with 
     * 
     * @param id The profile from which to get the DomainParticipantQos
     * 
     * @return The DomainParticipantQos that is located in the profile 
     * specified by id 
     */
      dds::domain::qos::DomainParticipantQos
      participant_qos(const std::string& id)
      {
          return this->delegate()->participant_qos(id);
      }

      /** 
      * @brief Get the dds::topic::qos::TopicQos currently 
      *        associated with this QosProvider
      *  
      * @return The TopicQos 
      */
      dds::topic::qos::TopicQos
      topic_qos()
      {
          return this->delegate()->topic_qos();
      }

      /**
       * @brief Set the dds::topic::qos::TopicQos that this QosProvider is 
       * currently associated with 
       * 
       * @param id The profile from which to get the TopicQos
       * 
       * @return The TopicQos that is located in the profile specified by id 
       */
      dds::topic::qos::TopicQos
      topic_qos(const std::string& id)
      {
          return this->delegate()->topic_qos(id);
      }

      /** 
      * @brief Get the dds::sub::qos::SubscriberQos currently associated 
      * with this QosProvider
      *  
      * @return The SubscriberQos 
      */
      dds::sub::qos::SubscriberQos
      subscriber_qos()
      {
          return this->delegate()->subscriber_qos();
      }

      /**
       * @brief Set the dds::sub::qos::SubscriberQos that this QosProvider 
       * is currently associated with 
       * 
       * @param id The profile from which to get the SubscriberQos
       * 
       * @return The SubscriberQos that is located 
       * in the profile specified by id 
       */
      dds::sub::qos::SubscriberQos
      subscriber_qos(const std::string& id)
      {
          return this->delegate()->subscriber_qos(id);
      }

      /** 
      * @brief Get the dds::sub::qos::DataReaderQos currently associated with 
      * this QosProvider
      *  
      * @return The DataReaderQos 
      */
      dds::sub::qos::DataReaderQos
      datareader_qos()
      {
          return this->delegate()->datareader_qos();
      }

      /**
       * @brief Set the dds::sub::qos::DataReaderQos that this QosProvider is 
       * currently associated with 
       * 
       * @param id The profile from which to get the DataReaderQos
       * 
       * @return The DataReaderQos that is located in the profile 
       * specified by id 
       */
      dds::sub::qos::DataReaderQos
      datareader_qos(const std::string& id)
      {
          return this->delegate()->datareader_qos(id);
      }

      /** 
      * @brief Get the dds::pub::qos::PublisherQos currently associated with 
      * this QosProvider
      *  
      * @return The PublisherQos 
      */
      dds::pub::qos::PublisherQos
      publisher_qos()
      {
          return this->delegate()->publisher_qos();
      }

      /**
       * @brief Set the dds::pub::qos::PublisherQos that this QosProvider is 
       * currently associated with 
       * 
       * @param id The profile from which to get the PublisherQos
       * 
       * @return The PublisherQos that is located 
       * in the profile specified by id 
       */
      dds::pub::qos::PublisherQos
      publisher_qos(const std::string& id)
      {
          return this->delegate()->publisher_qos(id);
      }

      /** 
      * @brief Get the dds::pub::qos::DataWriterQos currently associated with
      * this QosProvider
      *  
      * @return The DataWriterQos 
      */
      dds::pub::qos::DataWriterQos
      datawriter_qos()
      {
          return this->delegate()->datawriter_qos();
      }

     /**
      * @brief Set the dds::pub::qos::DataWriterQos that this QosProvider is 
      * currently associated with 
      * 
      * @param id The profile from which to get the DataWriterQos
      * 
      * @return The DataWriterQos that is located 
      * in the profile specified by id 
      */
      dds::pub::qos::DataWriterQos
      datawriter_qos(const std::string& id)
      {
          return this->delegate()->datawriter_qos(id);
      }

public:
    /**
     * @brief Get the default QosProvider.
     * 
     *  The default QosProvider represents the Qos profiles that 
     * the DDS entities will be created with if no Qos is provided. By 
     * modifying the default QosProvider you are altering the QoS settings 
     * that entities will be created with by default.  
     * 
     * @return The Default QosProvider
     *
     * @see \ref Entity_default_qos
     * @see \ref DDSQosProviderExampleModule_default_provider "Default QosProvider Use Cases"
     */
    static TQosProvider Default() {
        return TQosProvider(DELEGATE::Default());
    }

    /**
     * @brief Reset the default settings of the default QosProvider.  
     * 
     *  If you change the default library or profile associated with 
     * the default QosProvider, calling reset_default will set the library and 
     * profile back to the default values.  
     */
    static void reset_default(){
        DELEGATE::reset_default();
    }

};

#endif /* OMG_DDS_CORE_QOS_TPROVIDER_HPP_ */
