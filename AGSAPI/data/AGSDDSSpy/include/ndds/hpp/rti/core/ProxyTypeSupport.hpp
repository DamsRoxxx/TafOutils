
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

#ifndef RTI_DDS_CORE_PROXY_TYPE_SUPPORT_HPP_
#define RTI_DDS_CORE_PROXY_TYPE_SUPPORT_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/detail/SelfReference.hpp> // for RetainableType
#include <rti/core/detail/NativeEntity.hpp> // for create_from_native_entity
#include <dds/domain/DomainParticipant.hpp>

#include "dds_c/dds_c_factory_plugin_impl.h"

namespace rti { namespace core {

template<typename TYPE_SUPPORT>
DDS_ReturnCode_t registerType(DDS_DomainParticipant *native_participant,
                 const char * registeredTypeName,
                 void * userData)
{
    typedef typename dds::core::smart_ptr_traits<TYPE_SUPPORT>::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<TYPE_SUPPORT>::weak_ref_type weak_ref_type;

    if (userData == NULL) {
        return DDS_RETCODE_PRECONDITION_NOT_MET;
    }

    try {
        // Get the C++ participant
        dds::domain::DomainParticipant participant = 
            rti::core::detail::create_from_native_entity<
            dds::domain::DomainParticipant, DDS_DomainParticipant>(
                native_participant);
        if (participant == dds::core::null) {
            throw dds::core::Error("Error creating participant");
        }

        ref_type proxy_type_support = 
            (*reinterpret_cast<weak_ref_type*>(userData)).lock();

        proxy_type_support->register_type(
            participant, 
            registeredTypeName);
    } catch (...) {
        // Don't let exceptions get to C
        return DDS_RETCODE_ERROR;
    }

    return DDS_RETCODE_OK;
}

template <typename TYPE_SUPPORT>
void deleteUserData(void * userData)
{
    typedef typename dds::core::smart_ptr_traits<TYPE_SUPPORT>::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<TYPE_SUPPORT>::weak_ref_type weak_ref_type;

    if (userData != NULL) {
        ref_type proxy_type_support = 
            (*reinterpret_cast<weak_ref_type*>(userData)).lock();

        proxy_type_support->unretain();
    }
}    

// --- UserProxyTypeSupport
typedef void 
(*UserProxyTypeSupport_RegisterTypeFunction)(
    dds::domain::DomainParticipant& participant, const std::string& type_name);

class UserProxTypeSupportRegisterTypeHolder
{
public: 
    UserProxTypeSupportRegisterTypeHolder(
        UserProxyTypeSupport_RegisterTypeFunction fcn)
      : register_type_fcn_(fcn)
    {
    }

    UserProxyTypeSupport_RegisterTypeFunction register_type_fcn_;
};

class UserProxyTypeSupportImpl : 
    public detail::RetainableType<UserProxyTypeSupportImpl> {

public: 
    UserProxyTypeSupportImpl(
        UserProxyTypeSupport_RegisterTypeFunction register_type_fcn)
     : registerTypeFcn_(register_type_fcn)
    {
    }

    ~UserProxyTypeSupportImpl()
    {
        registerTypeFcn_ = NULL;
    }
public: 

    void register_type(
        dds::domain::DomainParticipant& participant,
        const std::string& registered_type_name);

private:
    UserProxyTypeSupport_RegisterTypeFunction registerTypeFcn_;
};

class UserProxyTypeSupport : 
    public dds::core::Reference<UserProxyTypeSupportImpl> {
public:
    typedef dds::core::Reference<UserProxyTypeSupportImpl> Base;

    OMG_DDS_REF_TYPE_NOTYPENAME(UserProxyTypeSupport, dds::core::Reference, UserProxyTypeSupportImpl)

public: 
    UserProxyTypeSupport(
        UserProxyTypeSupport_RegisterTypeFunction register_type_fcn)
     : Base(new UserProxyTypeSupportImpl(register_type_fcn))
    {
        this->delegate()->remember_reference(this->delegate());
    }
public: 

    void register_type(
        dds::domain::DomainParticipant& participant,
        const std::string& registered_type_name)
    {
        this->delegate()->register_type(participant, registered_type_name);
    }

};


// --- DynamicDataProxyTypeSupport
class DynamicDataProxyTypeSupportImpl : 
    public detail::RetainableType<DynamicDataProxyTypeSupportImpl> {
public: 

    DynamicDataProxyTypeSupportImpl(
        const DDS_TypeCode* type_code, 
        const struct DDS_DynamicDataTypeProperty_t&  /* unsupported in xml-app creation */)
      : type_support_(NULL)
    {
        static const DDS_DynamicDataTypeProperty_t DEFAULT_PROPERTY =
            DDS_DynamicDataTypeProperty_t_INITIALIZER;

        type_support_ = DDS_DynamicDataTypeSupport_new(
              type_code, &DEFAULT_PROPERTY);
        rti::core::check_create_entity(
            type_support_, "failed to create DynamicData type support");
    }

    ~DynamicDataProxyTypeSupportImpl() 
    {
        if (type_support_ != NULL) {
            DDS_DynamicDataTypeSupport_delete(type_support_);
            type_support_ = NULL;
        }
    }

    void register_type(
        dds::domain::DomainParticipant& participant,
        const std::string& registered_type_name);

private:
    DDS_DynamicDataTypeSupport *type_support_;

};

class DynamicDataProxyTypeSupport : 
    public dds::core::Reference<DynamicDataProxyTypeSupportImpl> {
public: 

    typedef dds::core::Reference<DynamicDataProxyTypeSupportImpl> Base;

    OMG_DDS_REF_TYPE_NOTYPENAME(DynamicDataProxyTypeSupport, dds::core::Reference, DynamicDataProxyTypeSupportImpl)

public: 

    DynamicDataProxyTypeSupport(
        const DDS_TypeCode * type_code, 
        const struct DDS_DynamicDataTypeProperty_t& props)
    : Base(new DynamicDataProxyTypeSupportImpl(type_code, props))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    void register_type(
        dds::domain::DomainParticipant& participant,
        const std::string& registered_type_name)
    {
        this->delegate()->register_type(participant, registered_type_name);
    }
};

} } // namespace rti::core

#endif // RTI_DDS_CORE_PROXY_TYPE_SUPPORT_HPP_
