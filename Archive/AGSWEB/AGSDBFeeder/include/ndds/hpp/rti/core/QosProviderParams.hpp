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

#ifndef RTI_DDS_CORE_QOS_PROVIDER_PARAMS_HPP_
#define RTI_DDS_CORE_QOS_PROVIDER_PARAMS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_infrastructure_impl.h"
#include <string>

#include <dds/core/types.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

// Forward Declaration
class QosProviderParams;

class QosProviderParamsAdapter {
public:
    typedef DDS_ProfileQosPolicy native_type;

    static void initialize(native_type& native_value)
    {
        DDS_ProfileQosPolicy_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_ProfileQosPolicy_finalize(&native_value);
    }
                                                                               
    static void copy(native_type& destination, const native_type& source)
    {
        DDS_ProfileQosPolicy_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_ProfileQosPolicy_equals(&first, &second)
                != DDS_BOOLEAN_FALSE);
    }
};

template<>
struct native_type_traits<rti::core::QosProviderParams> {
    typedef rti::core::QosProviderParamsAdapter adapter_type;
    typedef rti::core::QosProviderParamsAdapter::native_type native_type;
};

/** 
 * @ingroup NDDSXmlConfigurationModule
 * @RTI_class_definition class QosProviderParams 
 * @headerfile rti/core/QosProviderParams.hpp
 *  
 * @brief @extension @st_value_type Configure options that control the way that
 * XML documents containing QoS profiles are loaded by a dds::core::QosProvider.
 *
 * @dref_details_ProfileQosPolicy
 *
 * Note: This class is equivalent to DDS_ProfileQosPolicy the other \ndds
 * language APIs.
 */
class OMG_DDS_API QosProviderParams : public NativeValueType<QosProviderParams> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(QosProviderParams)

public:
    /**
     * @brief Create a QosProviderParams with default settings. 
     */
    QosProviderParams() {}

    /**
     * @brief Get the current list of string profiles stored by 
     * this QosProviderParams.
     * 
     * @return dds::core::StringSeq The list of string profiles. 
     */
    dds::core::StringSeq string_profile() const;

    /**
     * @brief Set the current list of string profiles stored by 
     * this QosProviderParams. 
     *  
     * @param the_string_profile A sequence of strings containing an XML 
     * document to load. The concatenation of the strings in this sequence must 
     * be a valid XML document according to the XML QoS profile schema.
     *  
     * @default An empty list 
     */
    QosProviderParams& string_profile(const dds::core::StringSeq& the_string_profile);

    /**
     * @brief Get the current list of @ref XMLUrlGroups stored by 
     * this QosProviderParams.
     * 
     * @return dds::core::StringSeq The list of string profiles. 
     */
    dds::core::StringSeq url_profile() const;

    /**
     * @brief Set the current list of  @ref XMLUrlGroups stored by 
     * this QosProviderParams. 
     *  
     * @param the_url_profile Sequence of @ref XMLUrlGroups  containing a set 
     * of XML documents to load. Only one of the elements of each group will be 
     * loaded by @ndds, starting from the left. 
     *  
     * @default An empty list 
     */
    QosProviderParams& url_profile(const dds::core::StringSeq& the_url_profile);

    /**
     * @brief Get the value that is currently set for ignore_user_profile.
     * 
     * @return bool Whether or not the dds::core::QosProvider set with these 
     * QosProviderParams will ignore the USER_QOS_PROFILES.xml. 
     */
    bool ignore_user_profile() const; 

    /**
     * @brief Choose whether or not to ignore USER_QOS_PROFILES.xml.
     * 
     *  When this field is set to true, the QoS profiles 
     * contained in the file USER_QOS_PROFILES.xml in the current working 
     * directory will not be loaded. 
     *  
     * @param the_ignore_user_profile Whether or not to ignore 
     * the USER_QOS_PROFILES.xml in the current working directory. 
     * 
     * @return QosProviderParams& This QosProviderParams 
     *  
     * @default false
     */
    QosProviderParams& ignore_user_profile(bool the_ignore_user_profile);

    /**
     * @brief Get the value that is currently set for 
     * ignore_environment_profile.
     * 
     * @return bool Whether or not the dds::core::QosProvider set with these 
     * QosProviderParams will ignore the 
     * @ref XMLEnvironmentVariable "NDDS_QOS_PROFILES". 
     */
    bool ignore_environment_profile() const; 

    /**
     * @brief Choose whether or not to ignore the 
     * @ref XMLEnvironmentVariable "NDDS_QOS_PROFILES". 
     * 
     *  When this field is set to true, the QoS profiles 
     * pointed to by the 
     * @ref XMLEnvironmentVariable "NDDS_QOS_PROFILES" will not be loaded.  
     *  
     * @param the_ignore_environment_profile Whether or not to ignore 
     * @ref XMLEnvironmentVariable "NDDS_QOS_PROFILES".
     * 
     * @return QosProviderParams& This QosProviderParams 
     *  
     * @default false
     */
    QosProviderParams& ignore_environment_profile(bool the_ignore_environment_profile);

    /**
     * @brief Get the value that is currently set for ignore_resource_profile.
     * 
     * @return bool Whether or not the dds::core::QosProvider set with these 
     * QosProviderParams will ignore NDDS_QOS_PROFILES.xml.
     */
    bool ignore_resource_profile() const; 

    /**
     * @brief Choose whether or not to ignore NDDS_QOS_PROFILES.xml.
     * 
     *  When this field is set to true, the QoS profiles 
     * contained in the file NDDS_QOS_PROFILES.xml in 
     * $NDDSHOME/resource/qos_profiles_$(RTI_NDDS_VERSION_MAJOR).$(RTI_NDDS_VERSION_MINOR).$(RTI_NDDS_VERSION_RELEASE)/xml
     * will not be loaded. 
     *  
     * @param the_ignore_resource_profile Whether or not to ignore 
     * the NDDS_QOS_PROFILES.xml.
     * 
     * @return QosProviderParams& This QosProviderParams 
     *  
     * @default false
     */
    QosProviderParams& ignore_resource_profile(bool the_ignore_resource_profile);

};
} } // namespace rti::core

#endif // RTI_DDS_CORE_QOS_PROVIDER_PARAMS_HPP_

