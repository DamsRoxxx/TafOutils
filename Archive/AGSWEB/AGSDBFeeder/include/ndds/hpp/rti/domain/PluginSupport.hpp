/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,24jun14,acr Created
============================================================================= */

#ifndef RTI_DDS_DOMAIN_PLUGIN_SUPPORT_HPP_
#define RTI_DDS_DOMAIN_PLUGIN_SUPPORT_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/domain/DomainParticipant.hpp>
#include <rti/domain/FactoryPluginSupport.hpp>
#include <rti/core/LockGuard.hpp>
#include <dds/topic/TopicTraits.hpp>
#include <dds/core/xtypes/DynamicType.hpp>
#include <rti/core/xtypes/DynamicDataProperty.hpp>

#include "dds_c/dds_c_domain_impl.h"

#include "ndds/ndds_c.h"

namespace rti { namespace domain {

typedef PRESTypePlugin* (*CreateTypePluginFunction)();
typedef void (*DeleteTypePluginFunction)(PRESTypePlugin*);

void default_delete_type_plugin_function(PRESTypePlugin * plugin);

OMG_DDS_API
void register_type_plugin(
    dds::domain::DomainParticipant& participant,
    const std::string& name,
    CreateTypePluginFunction create_plugin_function,
    DeleteTypePluginFunction delete_plugin_function = default_delete_type_plugin_function);


void register_typeI(
    dds::domain::DomainParticipant& participant,
    DDS_DynamicDataTypeSupport *type_support, 
    const std::string& name);

/**
 * @relatesalso dds::domain::DomainParticipant
 * @brief @extension Registers a DynamicType with specific serialization properties
 *
 * Typically you don't need to call this function, since this
 * \link dds::topic::Topic::Topic(const dds::domain::DomainParticipant&, const std::string&, const dds::core::xtypes::DynamicType&) topic constructor\endlink
 * takes care of that automatically. You do need to call this function before
 * creating the topic if you want to change the default data-serialization property.
 *
 * Calling this function also allows to change the registered name of the type, which
 * by default is \p type.name().
 *
 * @param participant The participant where to register this type
 * @param name The name to use to register this type
 * @param type The type definition
 * @param serialization_property The data-serialization property
 *
 * @see dds::core::xtypes::DynamicType
 * @see dds::core::xtypes::DynamicData
 */
OMG_DDS_API
void register_type(
    dds::domain::DomainParticipant& participant,
    const std::string& name,
    const dds::core::xtypes::DynamicType& type,
    const rti::core::xtypes::DynamicDataTypeSerializationProperty& serialization_property
        = rti::core::xtypes::DynamicDataTypeSerializationProperty::DEFAULT);

/**
 * @relatesalso dds::domain::DomainParticipant
 * @brief @extension Registers a User-Generated Type with \ndds. This function 
 * is used along with XML Application Creation.  
 *  
 * When using XML Application creation, you must use this function to register 
 * any user-generated types with \ndds before creating your system. 
 *  
 * Typically you don't need to call this function, since the
 * \link dds::topic::Topic::Topic(const dds::domain::DomainParticipant&, const std::string&, const dds::core::xtypes::DynamicType&) topic constructor\endlink
 * takes care of that automatically. 
 * 
 * @tparam T The user-generated type that is being registered
 * @param registered_type_name The name to use when registering the type. This 
 * is the name that will be used in your XML configuration file to refer to the 
 * type. 
 *  
 * @see dds::domain::DomainParticipant::create_participant_from_config 
 * @see XMLAppCreationExampleModule 
 */
template <typename T>
void register_type(
    const std::string& registered_type_name = 
    dds::topic::topic_type_name<T>::value())
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    rti::core::LockGuard guard(rti::domain::FactoryPluginSupport::mutex());

    // Set the FactoryPluginSupport if it isn't set yet
    if (!rti::domain::FactoryPluginSupport::is_set) {
        DDS_FactoryPluginSupport factory_plugin_support;
        rti::domain::FactoryPluginSupport::create_factory_plugin_support(
            &factory_plugin_support);

        retcode = 
            DDS_DomainParticipantFactory_set_factory_plugin_supportI(
            DDS_DomainParticipantFactory_get_instance(),
            &factory_plugin_support);
        rti::core::check_return_code(retcode, "set_factory_plugin_support");

        rti::domain::FactoryPluginSupport::is_set = true;
    }

    // We end up just storing the pointer to register_type in 
    // the UserProxyTypeSupport, so this object can be temporary. It is just to
    // aviod this compiler error: 
    // ISO C++ forbids casting between pointer-to-function and pointer-to-object
    rti::core::UserProxTypeSupportRegisterTypeHolder
        holder(dds::topic::topic_type_support<T>::register_type);

    retcode = DDS_DomainParticipantFactory_register_type_supportI(
        DDS_DomainParticipantFactory_get_instance(),
        reinterpret_cast<void*>(&holder),
        registered_type_name.c_str());
    rti::core::check_return_code(retcode, "register_type_support");
}

} } // namespace rti::domain

#endif // RTI_DDS_DOMAIN_PLUGIN_SUPPORT_HPP_
