/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,14mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_BUILTIN_TOPIC_HPP_
#define RTI_DDS_TOPIC_BUILTIN_TOPIC_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_builtin.h"
#include "dds_c/dds_c_builtin_impl.h"

#include <dds/topic/BuiltinTopicKey.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/core/policy/CorePolicy.hpp>
#include <dds/core/Optional.hpp>
#include <dds/topic/topicfwd.hpp>
#include <dds/topic/TopicTraits.hpp>
#include <rti/core/ProductVersion.hpp>
#include <rti/core/ProtocolVersion.hpp>
#include <rti/core/ContentFilterProperty.hpp>
#include <rti/core/VendorId.hpp>
#include <rti/core/TypeObject.hpp>
#include <rti/core/Locator.hpp>
#include <rti/core/DiscoveryPluginPromiscuityKind.hpp>
#include <rti/core/Pointer.hpp>
#include <rti/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/Guid.hpp>
#include <rti/core/TransportInfo.hpp>
#include <rti/core/ServiceRequestId.hpp>
#include <dds/core/String.hpp>
#include <dds/core/xtypes/DynamicType.hpp>

/** @RTI_namespace_start dds::topic */
namespace rti { namespace topic {

/** @RTI_class_definition NA */
class OMG_DDS_API ParticipantBuiltinTopicDataImpl {

public: 
friend OMG_DDS_API void swap(
    ParticipantBuiltinTopicDataImpl& left,
    ParticipantBuiltinTopicDataImpl& right) OMG_NOEXCEPT;

public:
    ParticipantBuiltinTopicDataImpl()
      : dds_builtin_endpoints_(0), 
        plugin_promiscuity_kind_(
            rti::core::DiscoveryPluginPromiscuityKind::DISCOVER_MATCHING_REMOTE_ENTITIES),
        domain_id_(0),
        vendor_builtin_endpoints_(0)
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
   #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    ParticipantBuiltinTopicDataImpl(
        const ParticipantBuiltinTopicDataImpl&) = default;
    ParticipantBuiltinTopicDataImpl& operator=(
        const ParticipantBuiltinTopicDataImpl&) = default;
   #endif

    ParticipantBuiltinTopicDataImpl(
        ParticipantBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    ParticipantBuiltinTopicDataImpl& operator=(
        ParticipantBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        ParticipantBuiltinTopicDataImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }

  #endif

    bool operator==(const ParticipantBuiltinTopicDataImpl& other) const;

    bool operator!=(const ParticipantBuiltinTopicDataImpl& other) const
    {
        return !(*this == other);
    }

    // --- Getters ---------------------------------------------------- 

    const dds::topic::BuiltinTopicKey& key() const
    {
        return key_;
    }

    const dds::core::policy::UserData& user_data() const
    {
        return user_data_;
    }

    /* --- Extensions: ---------------------------------------------------- */

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the name-value pair properties to be
	  stored with dds::domin::DomainParticipant
     * 
     * @return The name-value pair properties that were propagated from the 
     * corresponding dds::domain::DomainParticipant 
     */
    const rti::core::policy::Property& property() const
    {
        return property_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the version number of the RTPS wire protocol used.
     * 
     * @return The protocol version.
     */
    const rti::core::ProtocolVersion& rtps_protocol_version() const
    {
        return rtps_protocol_version_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the ID of the vendor implementing the RTPS 
     * wire protocol.
     * 
     * @return The vendor id.
     */
    const rti::core::VendorId& rtps_vendor_id() const
    {
        return rtps_vendor_id_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Bitmap of builtin endpoints supported by the participant
     * 
     * @details \dref_details_ParticipantBuiltinTopicData_dds_builtin_endpoints
     */
    uint32_t dds_builtin_endpoints() const
    {
        return dds_builtin_endpoints_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the unicast locators used when individual 
     * entities do not specify unicast locators.
     * 
     * @return A sequence of the default unicast locators used
     */
    const dds::core::vector<rti::core::Locator>& default_unicast_locators() const
    {
        return default_unicast_locators_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the current version for \ndds.
     * 
     * @return The \ndds version being used
     */
    const rti::core::ProductVersion& product_version() const
    {
        return product_version_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the participant name and role name.
     * 
     * @return The rti::core::policy::EntityName QoS policy for the 
     * corresponding dds::domain::DomainParticipant.
     *  
     */
    const rti::core::policy::EntityName& participant_name() const
    {
        return participant_name_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the domain ID associated with the 
     * discovered dds::domain::DomainParticipant.
     * 
     * @return The domain id
     */
    int32_t domain_id() const
    {
        return domain_id_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the sequence of \idref_TransportInfo_t 
     * containing information about each of the installed transports 
     * of the discovered dds::domain::DomainParticipant.
     *  
     * This parameter contains a sequence of \idref_TransportInfo_t containing
     * the class_id and message_size_max for all installed transports of the 
     * discovered participant. The maximum number of \idref_TransportInfo_t that 
     * will be stored in this sequence is controlled by the DomainParticipant's 
     * resource limit 
     * @idref_DomainParticipantResourceLimitsQosPolicy_transport_info_list_max_length.
     *  
     * @return The sequence of transport infos
     */
    const rti::core::TransportInfoSeq& transport_info() const
    {
        return transport_info_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Get the reachability lease duration.
     */
    const dds::core::Duration& reachability_lease_duration() const
    {
        return reachability_lease_duration_;
    }

    /** 
     * @memberof dds::topic::ParticipantBuiltinTopicData 
     * @brief @extension Bitmap of vendor-specific builtin endpoints 
     * supported by the participant
     * 
     */
    uint32_t vendor_builtin_endpoints() const
    {
        return vendor_builtin_endpoints_;
    }

    // For internal use:
    const DDS_ParticipantBuiltinTopicData * native() const
    {
        return reinterpret_cast<const DDS_ParticipantBuiltinTopicData *>(this);
    }

    DDS_ParticipantBuiltinTopicData * native()
    {
        return reinterpret_cast<DDS_ParticipantBuiltinTopicData *>(this);
    }

private:
    dds::topic::BuiltinTopicKey key_;

    dds::core::policy::UserData user_data_;

    /* --- Extensions: ---------------------------------------------------- */

    rti::core::policy::Property property_;
     
    rti::core::ProtocolVersion rtps_protocol_version_;

    rti::core::VendorId rtps_vendor_id_;

    DDS_UnsignedLong dds_builtin_endpoints_;

    dds::core::vector<rti::core::Locator> metatraffic_unicast_locators_;

    dds::core::vector<rti::core::Locator> metatraffic_multicast_locators_;

    dds::core::vector<rti::core::Locator> default_unicast_locators_;

    dds::core::Duration lease_duration_;

    rti::core::ProductVersion product_version_;

    rti::core::DiscoveryPluginPromiscuityKind plugin_promiscuity_kind_;

    rti::core::policy::EntityName participant_name_;
    
    int32_t domain_id_;

    rti::core::TransportInfoSeq transport_info_;

    dds::core::Duration reachability_lease_duration_;

    DDS_UnsignedLong vendor_builtin_endpoints_;

    rti::core::policy::Service service_;
};

/** @RTI_class_definition NA */
class OMG_DDS_API TopicBuiltinTopicDataImpl {

public: 
friend OMG_DDS_API void swap(
    TopicBuiltinTopicDataImpl& left,
    TopicBuiltinTopicDataImpl& right) OMG_NOEXCEPT;

public:

    // The C API expects that the strings have been allocated to their max size
    TopicBuiltinTopicDataImpl()
      : name_(MIG_RTPS_PATHNAME_LEN_MAX), 
        type_name_(MIG_RTPS_PATHNAME_LEN_MAX)
    {
    }

  #ifdef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    // Define move operations only if the compiler doesn't already generate
    // the default ones, which work just fine

    TopicBuiltinTopicDataImpl(TopicBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }


    TopicBuiltinTopicDataImpl& operator=(
        TopicBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        TopicBuiltinTopicDataImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const TopicBuiltinTopicDataImpl& other) const;

    bool operator!=(const TopicBuiltinTopicDataImpl& other) const
    {
        return !(*this == other);
    }

    // --- Getters ------------------------------------------------------------

    const dds::topic::BuiltinTopicKey& key() const
    {
        return key_;
    }

    const dds::core::string& name() const
    {
        return name_;
    }

    const dds::core::string& type_name() const
    {
        return type_name_;
    }

    const dds::core::policy::Durability& durability() const
    {
        return durability_;
    }

#ifdef OMG_DDS_PERSISTENCE_SUPPORT

    const dds::core::policy::DurabilityService& durability_service() const
    {
        return durability_service_;
    }

#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    const dds::core::policy::Deadline& deadline() const
    {
        return deadline_;
    }

    const dds::core::policy::LatencyBudget& latency_budget() const
    {
        return latency_budget_;
    }

    const dds::core::policy::Liveliness& liveliness() const
    {
        return liveliness_;
    }

    const dds::core::policy::Reliability& reliability() const
    {
        return reliability_;
    }

    const dds::core::policy::TransportPriority& transport_priority() const
    {
        return transport_priority_;
    }

    const dds::core::policy::Lifespan& lifespan() const
    {
        return lifespan_;
    }

    const dds::core::policy::DestinationOrder& destination_order() const
    {
        return destination_order_;
    }

    const dds::core::policy::History& history() const
    {
        return history_;
    }

    const dds::core::policy::ResourceLimits& resource_limits() const
    {
        return resource_limits_;
    }

    const dds::core::policy::Ownership& ownership() const
    {
        return ownership_;
    }

    const dds::core::policy::TopicData& topic_data() const
    {
        return topic_data_;
    }

    // For internal use:
    const DDS_TopicBuiltinTopicData * native() const
    {
        return reinterpret_cast<const DDS_TopicBuiltinTopicData *>(this);
    }

    DDS_TopicBuiltinTopicData * native()
    {
        return reinterpret_cast<DDS_TopicBuiltinTopicData *>(this);
    }

private:
    dds::topic::BuiltinTopicKey key_;

    dds::core::string name_; 

    dds::core::string type_name_; 

    dds::core::policy::Durability durability_; 

#ifdef OMG_DDS_PERSISTENCE_SUPPORT

    dds::core::policy::DurabilityService durability_service_; 

#endif  // OMG_DDS_PERSISTENCE_SUPPORT

    dds::core::policy::Deadline deadline_; 

    dds::core::policy::LatencyBudget latency_budget_; 

    dds::core::policy::Liveliness liveliness_; 

    dds::core::policy::Reliability reliability_; 

    dds::core::policy::TransportPriority transport_priority_; 

    dds::core::policy::Lifespan lifespan_; 

    dds::core::policy::DestinationOrder destination_order_; 

    dds::core::policy::History history_; 

    dds::core::policy::ResourceLimits resource_limits_; 

    dds::core::policy::Ownership ownership_; 

    dds::core::policy::TopicData topic_data_; 

    // --- Extensions: ----------------------------------------------------
};

/** @RTI_class_definition NA */
class OMG_DDS_API PublicationBuiltinTopicDataImpl {

public: 
friend OMG_DDS_API void swap(
    PublicationBuiltinTopicDataImpl& left,
    PublicationBuiltinTopicDataImpl& right) OMG_NOEXCEPT;

public:
    PublicationBuiltinTopicDataImpl()
      : topic_name_(MIG_RTPS_PATHNAME_LEN_MAX), 
        type_name_(MIG_RTPS_PATHNAME_LEN_MAX),
        max_sample_serialized_size_(0),
        disable_positive_acks_(DDS_BOOLEAN_FALSE),
        send_queue_size_(PRES_PS_PUBLICATION_PARAMETER_SEND_QUEUE_SIZE_DEFAULT),
        is_incompatible_(DDS_BOOLEAN_FALSE)
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
   #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    PublicationBuiltinTopicDataImpl(
        const PublicationBuiltinTopicDataImpl&) = default;
    PublicationBuiltinTopicDataImpl& operator=(
        const PublicationBuiltinTopicDataImpl&) = default;
   #endif

    PublicationBuiltinTopicDataImpl(
        PublicationBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    PublicationBuiltinTopicDataImpl& operator=(
        PublicationBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        PublicationBuiltinTopicDataImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const PublicationBuiltinTopicDataImpl& other) const;

    bool operator!=(const PublicationBuiltinTopicDataImpl& other) const
    {
        return !(*this == other);
    }

    // --- Getters ---------------------------------------------------- 

    const dds::topic::BuiltinTopicKey& key() const
    {
        return key_;
    }

    const dds::topic::BuiltinTopicKey& participant_key() const
    {
        return participant_key_;
    }

    const dds::core::string& topic_name() const
    {
        return topic_name_;
    }

    const dds::core::string& type_name() const
    {
        return type_name_;
    }

    const dds::core::policy::Durability& durability() const
    {
        return durability_;
    }

    const dds::core::policy::DurabilityService& durability_service() const
    {
        return durability_service_;
    }

    const dds::core::policy::Deadline& deadline() const
    {
        return deadline_;
    }

    const dds::core::policy::LatencyBudget& latency_budget() const
    {
        return latency_budget_;
    }

    const dds::core::policy::Liveliness& liveliness() const
    {
        return liveliness_;
    }

    const dds::core::policy::Reliability& reliability() const
    {
        return reliability_;
    }

    const dds::core::policy::Lifespan& lifespan() const
    {
        return lifespan_;
    }

    const dds::core::policy::UserData& user_data() const
    {
        return user_data_;
    }

    const dds::core::policy::Ownership& ownership() const
    {
        return ownership_;
    }

    const dds::core::policy::OwnershipStrength& ownership_strength() const
    {
        return ownership_strength_;
    }

    const dds::core::policy::DestinationOrder& destination_order() const
    {
        return destination_order_;
    }

    const dds::core::policy::Presentation& presentation() const
    {
        return presentation_;
    }

    const dds::core::policy::Partition& partition() const
    {
        return partition_;
    }

    const dds::core::policy::TopicData& topic_data() const
    {
        return topic_data_;
    }

    const dds::core::policy::GroupData& group_data() const
    {
        return group_data_;
    }

    /* --- Extensions: ---------------------------------------------------- */
    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the type
     *
     * @note This is not a lightweight getter--obtaining the type may require
     * some processing so it is recommended that you keep the value if you need
     * to use it multiple times rather than look it up every time. See also
     * get_type_no_copy().
     *
     * @return The type or an unset optional value if the type is not
     * available
     */
    dds::core::optional<dds::core::xtypes::DynamicType> type() const;

    /**
     * @memberof dds::topic::PublicationBuiltinTopicData
     * @brief @extension Get the type by reference if possible
     * 
     * @throws dds::core::PreconditionNotMet If the type is available but is not
     * in a format that is directly accessible. In that case it needs some extra
     * processing and has to be accessed using type(). You can also ensure that
     * it is in the right format by setting
     * rti::core::policy::DomainParticipantResourceLimits::type_code_max_serialized_length() to 0.
     *
     * @return The type or an unset optional value if the type is not
     * available
     *
     * @see type()
     */
    const dds::core::optional<dds::core::xtypes::DynamicType>& get_type_no_copy() const;

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the DCPS key of the dds::pub::Publisher to which 
     * the dds::pub::DataWriter belongs
     * 
     * @return The key
     */
    const dds::topic::BuiltinTopicKey& publisher_key() const
    {
        return publisher_key_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the propagated name-value properties of the 
     * corresponding dds::pub::DataWriter.
     * 
     * @return The properties
     */
    const rti::core::policy::Property& property() const
    {
        return property_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the custom unicast locators that the endpoint 
     * can specify. 
     *  
     * The default locators will be used if this is not specified.
     * 
     * @return The custom unicast locators specified by the corresponding 
     * DataWriter 
     */
    const dds::core::vector<rti::core::Locator>& unicast_locators() const
    {
        return unicast_locators_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the virtual rti::core::Guid associated to the 
     * dds::pub::DataWriter.
     * 
     * @return The virtual guid
     */
    const rti::core::Guid& virtual_guid() const
    {
        return virtual_guid_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the version number of the RTPS wire protocol used.
     * 
     * @return The RTPS wire protocol version
     */
    const rti::core::ProtocolVersion& rtps_protocol_version() const
    {
        return rtps_protocol_version_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the ID of the vendor implementing the RTPS 
     * wire protocol.
     * 
     * @return The vendor ID
     */
    const rti::core::VendorId& rtps_vendor_id() const
    {
        return rtps_vendor_id_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the current version for \ndds.
     * 
     * @return The 
     */
    const rti::core::ProductVersion& product_version() const
    {
        return product_version_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the locator filters of the corresponding 
     * dds::pub::DataWriter 
     * 
     * @return The rti::core::LocatorFilterQosPolicy 
     * @see rti::core::policy::MultiChannel 
     */
    const rti::core::policy::LocatorFilter& locator_filter() const
    {
        return locator_filter_;
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension See whether or not a matching dds::sub::DataReader will 
     * send positive acknowledgments for reliability.
     * 
     * @return true if positive acks are disabled, false otherwise
     */
    bool disable_positive_acks() const
    {
        return (disable_positive_acks_ == DDS_BOOLEAN_TRUE);
    }

    /** 
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the publication name and role name.
     * 
     * @return The rti::core::policy::EntityName policy of the corresponding 
     * DataWriter 
     */
    const rti::core::policy::EntityName& publication_name() const
    {
        return publication_name_;
    }

    /**
     * @memberof dds::topic::PublicationBuiltinTopicData 
     * @brief @extension Get the Service policy
     */
    const rti::core::policy::Service& service() const
    {
        return service_;
    }

// Not documented
    const DDS_PublicationBuiltinTopicData * native() const
    {
        return reinterpret_cast<const DDS_PublicationBuiltinTopicData *>(this);
    }

    DDS_PublicationBuiltinTopicData * native()
    {
        return reinterpret_cast<DDS_PublicationBuiltinTopicData *>(this);
    }

private:
    dds::topic::BuiltinTopicKey key_;
    dds::topic::BuiltinTopicKey participant_key_;
    dds::core::string topic_name_;
    dds::core::string type_name_;

    int32_t max_sample_serialized_size_; // non-documented field in C API

    dds::core::policy::Durability durability_;
    dds::core::policy::DurabilityService durability_service_;
    dds::core::policy::Deadline deadline_;
    dds::core::policy::LatencyBudget latency_budget_;

    dds::core::policy::Liveliness liveliness_;

    dds::core::policy::Reliability reliability_;

    dds::core::policy::Lifespan lifespan_;

    dds::core::policy::UserData user_data_;

    dds::core::policy::Ownership ownership_;

    dds::core::policy::OwnershipStrength ownership_strength_;

    dds::core::policy::DestinationOrder destination_order_;

    dds::core::policy::Presentation presentation_;

    dds::core::policy::Partition partition_;

    dds::core::policy::TopicData topic_data_;

    dds::core::policy::GroupData group_data_;

    /*i \dref_PublicationBuiltinTopicData_type
    */
    rti::core::TypeObject type_;

    /* --- Extensions: ---------------------------------------------------- */

    dds::core::optional<dds::core::xtypes::DynamicType> type_code_;

    dds::topic::BuiltinTopicKey publisher_key_;

    rti::core::policy::Property property_;

    dds::core::vector<rti::core::Locator> unicast_locators_;

    rti::core::Guid virtual_guid_;

    /*i \dref_PublicationBuiltinTopicData_service
     */
    rti::core::policy::Service service_;

    rti::core::ProtocolVersion rtps_protocol_version_;

    rti::core::VendorId rtps_vendor_id_;

    rti::core::ProductVersion product_version_;

    rti::core::policy::LocatorFilter locator_filter_;

    DDS_Boolean disable_positive_acks_;

    /*i \dref_PublicationBuiltinTopicData_send_queue_size
     * If making this field externally documented, add it to the print function
     */
    int32_t send_queue_size_;

    /*i \dref_PublicationBuiltinTopicData_is_incompatible
     * If making this field externally documented, add it to the print function
     */
    DDS_Boolean is_incompatible_;

    rti::core::policy::EntityName publication_name_;
};

/** @RTI_class_definition NA */
class OMG_DDS_API SubscriptionBuiltinTopicDataImpl {

public: 
friend OMG_DDS_API void swap(
    SubscriptionBuiltinTopicDataImpl& left,
    SubscriptionBuiltinTopicDataImpl& right) OMG_NOEXCEPT;

public:
    SubscriptionBuiltinTopicDataImpl()
        : topic_name_(MIG_RTPS_PATHNAME_LEN_MAX), 
          type_name_(MIG_RTPS_PATHNAME_LEN_MAX),
          disable_positive_acks_(DDS_BOOLEAN_FALSE), 
          expects_inline_qos_(DDS_BOOLEAN_FALSE),
          receive_queue_size_(PRES_PS_SUBSCRIPTION_PARAMETER_RECV_QUEUE_SIZE_DEFAULT),
          is_incompatible_(DDS_BOOLEAN_FALSE)
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
   #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    SubscriptionBuiltinTopicDataImpl(
        const SubscriptionBuiltinTopicDataImpl&) = default;
    SubscriptionBuiltinTopicDataImpl& operator=(
        const SubscriptionBuiltinTopicDataImpl&) = default;
   #endif

    SubscriptionBuiltinTopicDataImpl(
        SubscriptionBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    SubscriptionBuiltinTopicDataImpl& operator=(
        SubscriptionBuiltinTopicDataImpl&& other) OMG_NOEXCEPT
    {
        SubscriptionBuiltinTopicDataImpl tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const SubscriptionBuiltinTopicDataImpl& other) const;

    bool operator!=(const SubscriptionBuiltinTopicDataImpl& other) const
    {
        return !(*this == other);
    }

    // --- Getters ---------------------------------------------------- 

    const dds::topic::BuiltinTopicKey& key() const
    {
        return key_;
    }

    const dds::topic::BuiltinTopicKey& participant_key() const
    {
        return participant_key_;
    }

    const dds::core::string& topic_name() const
    {
        return topic_name_;
    }

    const dds::core::string& type_name() const
    {
        return type_name_;
    }

    const dds::core::policy::Durability& durability() const
    {
        return durability_;
    }

    const dds::core::policy::Deadline& deadline() const
    {
        return deadline_;
    }

    const dds::core::policy::LatencyBudget& latency_budget() const
    {
        return latency_budget_;
    }

    const dds::core::policy::Liveliness& liveliness() const
    {
        return liveliness_;
    }

    const dds::core::policy::Reliability& reliability() const
    {
        return reliability_;
    }

    const dds::core::policy::Ownership& ownership() const
    {
        return ownership_;
    }

    const dds::core::policy::DestinationOrder& destination_order() const
    {
        return destination_order_;
    }

    const dds::core::policy::UserData& user_data() const
    {
        return user_data_;
    }

    const dds::core::policy::TimeBasedFilter& time_based_filter() const
    {
        return time_based_filter_;
    }

    const dds::core::policy::Presentation& presentation() const
    {
        return presentation_;
    }

    const dds::core::policy::Partition& partition() const
    {
        return partition_;
    }

    const dds::core::policy::TopicData& topic_data() const
    {
        return topic_data_;
    }

    const dds::core::policy::GroupData& group_data() const
    {
        return group_data_;
    }

    const dds::core::policy::TypeConsistencyEnforcement& type_consistency() const
    {
        return type_consistency_;
    }

    /* --- Extensions: ---------------------------------------------------- */

    /**
     * @memberof dds::topic::SubscriptionBuiltinTopicData
     * @brief @extension Get the type
     *
     * @note This is not a lightweight getter--obtaining the type may require
     * some processing so it is recommended that you keep the value if you need
     * to use it multiple times rather than look it up every time. See also
     * get_type_no_copy().
     *
     * @return The type or an unset optional value if the type is not
     * available
     */
    dds::core::optional<dds::core::xtypes::DynamicType> type() const;

    /**
     * @memberof dds::topic::SubscriptionBuiltinTopicData
     * @brief @extension Get the type by reference if possible
     * 
     * @throws dds::core::PreconditionNotMet If the type is available but is not
     * in a format that is directly accessible. In that case it needs some extra
     * processing and has to be accessed using type(). You can also ensure that
     * it is in the right format by setting
     * rti::core::policy::DomainParticipantResourceLimits::type_code_max_serialized_length() to 0.
     *
     * @return The type or an unset optional value if the type is not
     * available
     *
     * @see type()
     */
    const dds::core::optional<dds::core::xtypes::DynamicType>& get_type_no_copy() const;

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get the DCPS key of the subscriber to which the
     * DataReader belongs.
     */
    const dds::topic::BuiltinTopicKey& subscriber_key() const
    {
        return subscriber_key_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get the Property policy of the corresponding DataReader
     * 
     * @return 
     */
    const rti::core::policy::Property& property() const
    {
        return property_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get the custom unicast locators that the endpoint
     * can specify. The default locators will be used if this is not specified.
     */
    const dds::core::vector<rti::core::Locator>& unicast_locators() const
    {
        return unicast_locators_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get the custom multicast locators that the endpoint
     * can specify. The default locators will be used if this is not specified.
     */
    const dds::core::vector<rti::core::Locator>& multicast_locators() const
    {
        return multicast_locators_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension This provides all the required information to
     * enable content filtering on the Writer side.
     */
    const rti::core::ContentFilterProperty& content_filter_property() const
    {
        return content_filter_property_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Gets the virtual GUID associated to the DataReader.
     */
    const rti::core::Guid& virtual_guid() const
    {
        return virtual_guid_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get the version of the RTPS wire protocol used.
     */
    const rti::core::ProtocolVersion& rtps_protocol_version() const
    {
        return rtps_protocol_version_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get the ID of vendor implementing the RTPS wire protocol
     */
    const rti::core::VendorId& rtps_vendor_id() const
    {
        return rtps_vendor_id_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Gets the version of \ndds
     * 
     * @return 
     */
    const rti::core::ProductVersion& product_version() const
    {
        return product_version_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get whether or not the corresponding 
     * dds::sub::DataReader sends positive acknowledgments for reliability.
     * 
     * @return false if positive acknowledgments are disabled, true otherwise
     */
    bool disable_positive_acks() const
    {
        return (disable_positive_acks_ == DDS_BOOLEAN_TRUE);
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData 
     * @brief @extension Get the subscription name and role name.
     */
    const rti::core::policy::EntityName& subscription_name() const
    {
        return subscription_name_;
    }

    /** 
     * @memberof dds::topic::SubscriptionBuiltinTopicData  
     * @brief @extension Get the Service policy of the corresponding DataReader.
     */
    const rti::core::policy::Service& service() const
    {
        return service_;
    }

    // For internal use:
    const DDS_SubscriptionBuiltinTopicData * native() const
    {
        return reinterpret_cast<const DDS_SubscriptionBuiltinTopicData *>(this);
    }

    DDS_SubscriptionBuiltinTopicData * native()
    {
        return reinterpret_cast<DDS_SubscriptionBuiltinTopicData *>(this);
    }

private:
    dds::topic::BuiltinTopicKey key_;
    dds::topic::BuiltinTopicKey participant_key_;
    dds::core::string topic_name_;
    dds::core::string type_name_;
    dds::core::policy::Durability durability_;
    dds::core::policy::Deadline deadline_;
    dds::core::policy::LatencyBudget latency_budget_;
    dds::core::policy::Liveliness liveliness_;
    dds::core::policy::Reliability reliability_;
    dds::core::policy::Ownership ownership_;
    dds::core::policy::DestinationOrder destination_order_;
    dds::core::policy::UserData user_data_;
    dds::core::policy::TimeBasedFilter time_based_filter_;
    dds::core::policy::Presentation presentation_;
    dds::core::policy::Partition partition_;
    dds::core::policy::TopicData topic_data_;
    dds::core::policy::GroupData group_data_;
    dds::core::policy::TypeConsistencyEnforcement type_consistency_;
    rti::core::TypeObject type_;

    // --- Extensions: --------------------------------------------------------

    dds::core::optional<dds::core::xtypes::DynamicType> type_code_;
    dds::topic::BuiltinTopicKey subscriber_key_;
    rti::core::policy::Property property_;
    dds::core::vector<rti::core::Locator> unicast_locators_;
    dds::core::vector<rti::core::Locator> multicast_locators_;
    rti::core::ContentFilterProperty content_filter_property_;
    rti::core::Guid virtual_guid_;
    rti::core::policy::Service service_;
    rti::core::ProtocolVersion rtps_protocol_version_;
    rti::core::VendorId rtps_vendor_id_;
    rti::core::ProductVersion product_version_;
    DDS_Boolean disable_positive_acks_;
    DDS_Boolean expects_inline_qos_;
    int32_t receive_queue_size_;
    DDS_Boolean is_incompatible_;
    rti::core::policy::EntityName subscription_name_;
};

class VirtualSubscriptionBuiltinTopicData {

public: 
friend void swap(
    VirtualSubscriptionBuiltinTopicData& left,
    VirtualSubscriptionBuiltinTopicData& right) OMG_NOEXCEPT;

public:
    VirtualSubscriptionBuiltinTopicData()
        : quorum_(0)
    {
    }

    VirtualSubscriptionBuiltinTopicData(
        const VirtualSubscriptionBuiltinTopicData& other)
      : key_(other.key()), 
        topic_name_(other.topic_name()), 
        name_(other.name()), 
        quorum_(other.quorum())
    {
    }

    #ifdef RTI_CXX11_RVALUE_REFERENCES
    VirtualSubscriptionBuiltinTopicData(
        VirtualSubscriptionBuiltinTopicData&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    VirtualSubscriptionBuiltinTopicData& operator=(
        VirtualSubscriptionBuiltinTopicData&& other) OMG_NOEXCEPT
    {
        VirtualSubscriptionBuiltinTopicData tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
    #endif

    bool operator==(const VirtualSubscriptionBuiltinTopicData& other) const;

    bool operator!=(const VirtualSubscriptionBuiltinTopicData& other) const
    {
        return !(*this == other);
    }

    // --- Getters ---------------------------------------------------- 

    const dds::topic::BuiltinTopicKey& key() const
    {
        return key_;
    }

    const dds::core::string& topic_name() const
    {
        return topic_name_;
    }

    const dds::core::string& name() const
    {
        return name_;
    }

    int32_t quorum() const
    {
        return quorum_;
    }


    const DDS_VirtualSubscriptionBuiltinTopicData * native() const
    {
        return reinterpret_cast<const DDS_VirtualSubscriptionBuiltinTopicData *>(this);
    }

    DDS_VirtualSubscriptionBuiltinTopicData * native()
    {
        return reinterpret_cast<DDS_VirtualSubscriptionBuiltinTopicData *>(this);
    }

private:
    dds::topic::BuiltinTopicKey key_;

    dds::core::string topic_name_;

    dds::core::string name_;
     
    int32_t quorum_;

};

/** @RTI_namespace_end dds::topic */
} } // namespace rti::topic

namespace rti { namespace topic {

/**
 *  @dref_ServiceRequestBuiltInTopicGroupDocs
 */

/**
 * @ingroup DDSServiceRequestBuiltInTopicModule
 * @headerfile dds/topic/BuiltinTopic.hpp
 *
 * @brief @extension @st_value_type A request coming from one of the built-in
 * services
 *
 * @details \dref_details_ServiceRequest
 */
class OMG_DDS_API ServiceRequest {
public: 

    friend OMG_DDS_API void swap(
        ServiceRequest& left, ServiceRequest& right) OMG_NOEXCEPT;

    ServiceRequest()
            : service_id_(rti::core::ServiceRequestId::UNKNOWN)
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
   #ifndef RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS
    ServiceRequest(const ServiceRequest&) = default;
    ServiceRequest& operator=(const ServiceRequest&) = default;
   #endif

    ServiceRequest(ServiceRequest&& other) OMG_NOEXCEPT
    {
        memset(this, 0, sizeof(*this));
        swap(*this, other);
    }

    ServiceRequest& operator=(ServiceRequest&& other) OMG_NOEXCEPT
    {
        ServiceRequest tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    bool operator==(const ServiceRequest& other) const;

    bool operator!=(const ServiceRequest& other) const
    {
        return !(*this == other);
    }

    // --- Getters ---------------------------------------------------- 

    /** 
     * @brief Get the service id of the request
     * 
     * @return The service id of the request
     */
    rti::core::ServiceRequestId service_id() const
    {
        return (rti::core::ServiceRequestId::type) service_id_;
    }

    /** 
     * @brief Get the instance id of the request
     * 
     * @return The instance id of the request
     */
    const rti::core::Guid& instance_id() const
    {
        return instance_id_;
    }

    /** 
     * @brief Get the request body of the request
     * 
     * @return The request body of the request
     */
    const dds::core::vector<uint8_t>& request_body() const
    {
        return request_body_;
    }

private:

    int32_t service_id_;
    rti::core::Guid instance_id_;
    dds::core::vector<uint8_t> request_body_;
};

} } // namespace rti::topic


namespace dds { namespace topic {

// Template specializations for the builtin topics

// ParticipantBuiltinTopicData ------------------------------------------------
template<>
struct topic_type_name<ParticipantBuiltinTopicData> {
    static std::string value() {
        return DDS_PARTICIPANT_TYPE_NAME;
    }
};

template<>
struct is_topic_type<ParticipantBuiltinTopicData> {
    enum {
        value = 1
    };
};

// TopicBuiltinTopicData ------------------------------------------------
template<>
struct topic_type_name<TopicBuiltinTopicData> {
    static std::string value() {
        return DDS_TOPIC_TYPE_NAME;
    }
};

template<>
struct is_topic_type<TopicBuiltinTopicData> {
    enum {
        value = 1
    };
};

// PublicationBuiltinTopicData ------------------------------------------------
template<>
struct topic_type_name<PublicationBuiltinTopicData> {
    static std::string value() {
        return DDS_PUBLICATION_TYPE_NAME;
    }
};

template<>
struct is_topic_type<PublicationBuiltinTopicData> {
    enum {
        value = 1
    };
};

// SubscriptionBuiltinTopicData ------------------------------------------------
template<>
struct topic_type_name<SubscriptionBuiltinTopicData> {
    static std::string value() {
        return DDS_SUBSCRIPTION_TYPE_NAME;
    }
};

template<>
struct is_topic_type<SubscriptionBuiltinTopicData> {
    enum {
        value = 1
    };
};

// ServiceRequest ------------------------------------------------
template<>
struct topic_type_name<rti::topic::ServiceRequest> {
    static std::string value() {
        return DDS_SERVICE_REQUEST_TYPE_NAME;
    }
};

template<>
struct is_topic_type<rti::topic::ServiceRequest> {
    enum {
        value = 1
    };
};

// VirtualSubscriptionBuiltinTopicData ------------------------------------------------
template<>
struct topic_type_name<rti::topic::VirtualSubscriptionBuiltinTopicData> {
    static std::string value() {
        return DDS_VirtualSubscriptionBuiltinTopicDataTYPENAME;
    }
};

template<>
struct is_topic_type<rti::topic::VirtualSubscriptionBuiltinTopicData> {
    enum {
        value = 1
    };
};

template<>
struct topic_type_support<rti::topic::VirtualSubscriptionBuiltinTopicData> {
    static void register_type(
        dds::domain::DomainParticipant& participant,
        const std::string&)
    {
        DDS_VirtualSubscriptionBuiltinTopicDataTypeSupport_register_type(
            participant->native_participant(), 
            topic_type_name<rti::topic::VirtualSubscriptionBuiltinTopicData>::value().c_str());
    }
};



} } // namespace dds::topic


#endif // RTI_DDS_TOPIC_BUILTIN_TOPIC_HPP_
