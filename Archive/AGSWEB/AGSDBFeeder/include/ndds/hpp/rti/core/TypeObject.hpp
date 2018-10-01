/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_TYPE_OBJECT_HPP_
#define RTI_DDS_CORE_TYPE_OBJECT_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_typeobject.h"
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

class TypeObject {

public:

    TypeObject()
      : type_object_(NULL)
    {
    }

    TypeObject(const TypeObject& other)
      : type_object_(NULL)
    {
        if (other.type_object_ != NULL) {
            type_object_ = (DDS_TypeObject *)
                RTICdrTypeObjectFactory_copyTypeObject(
                    NULL, 
                    (const struct RTICdrTypeObject* )other.type_object_, 
                    RTI_TRUE);
            rti::core::check_create_entity(type_object_, "TypeObject");
        }
    }


  #ifdef RTI_CXX11_RVALUE_REFERENCES
    TypeObject(TypeObject&& other) OMG_NOEXCEPT 
        : type_object_(std::move(other.type_object_)) 
    {
    }

    TypeObject& operator=(TypeObject&& other) OMG_NOEXCEPT 
    { 
        type_object_ = std::move(other.type_object_); 
        return *this; 
    }
   #endif

    ~TypeObject()
    {
        if (type_object_ != NULL) {
            RTICdrTypeObjectFactory_deleteTypeObject(
                NULL, (struct RTICdrTypeObject* ) type_object_);
            type_object_ = NULL;
        }
    }

    TypeObject& operator=(const TypeObject& other)
    {
        if (this != &other) {
            DDS_TypeObject* tmp = NULL;

            if (other.type_object_ != NULL) {
                tmp = (DDS_TypeObject *)
                    RTICdrTypeObjectFactory_copyTypeObject(
                        NULL, 
                        (const struct RTICdrTypeObject* )other.type_object_, 
                        RTI_TRUE);

                rti::core::check_create_entity(tmp, "TypeObject");
            }

            if (type_object_ != NULL) {
                RTICdrTypeObjectFactory_deleteTypeObject(
                    NULL, 
                    (struct RTICdrTypeObject* )type_object_);
            }

            type_object_ = tmp;
        }

        return *this;
    }

    bool operator==(const TypeObject& other) const
    {   
        if (type_object_ == NULL && other.type_object_ ==NULL) {
            return true;
        }

        if (type_object_ == NULL || other.type_object_ == NULL) {
            return false;
        }

        return DDS_TypeObject_equal(this->type_object_, other.type_object_) == 
            DDS_BOOLEAN_TRUE;
    }

    DDS_TypeObject * type_object_;

};

inline void swap(
    TypeObject& left,
    TypeObject& right) OMG_NOEXCEPT
{
    std::swap(left.type_object_, right.type_object_);
}

} } // namespace rti::core

#endif // RTI_DDS_CORE_TYPE_OBJECT_HPP_
