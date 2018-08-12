#ifndef OMG_TDDS_CORE_INSTANCE_HANDLE_HPP_
#define OMG_TDDS_CORE_INSTANCE_HANDLE_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
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

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>

namespace dds {
  namespace core {
    template <typename DELEGATE>
    class TInstanceHandle;
  }
}

/** 
 * @ingroup DDSUserDataModule 
 * @RTI_class_definition class dds::core::InstanceHandle
 * @headerfile dds/core/InstanceHandle.hpp
 * @brief @st_value_type Handle to identiy different instances of the same 
 * \idref_Topic of a certain type.
 *  
 * @details \dref_details_InstanceHandle_t
 *
 * @see dds::pub::DataWriter::register_instance 
 * @see dds::sub::SampleInfo::instance_handle 
 */
template <typename DELEGATE>
class dds::core::TInstanceHandle : public dds::core::Value<DELEGATE> {
public:
    OMG_DDS_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        TInstanceHandle, DELEGATE)

    /**
     * @brief Create a nil instance handle.
     */
    TInstanceHandle(const dds::core::null_type& null_handle)
        : dds::core::Value<DELEGATE>(null_handle) { }

    TInstanceHandle(const TInstanceHandle& other)
        : dds::core::Value<DELEGATE>(other.delegate()) { }

    ~TInstanceHandle() { }

    template <typename ARG0>
    explicit TInstanceHandle(const ARG0& arg0)
        : dds::core::Value<DELEGATE>(arg0)
    {
    }

    TInstanceHandle& operator=(const TInstanceHandle& other)
    {
        this->delegate().operator=(other);
        return *this;
    }

    bool operator==(const TInstanceHandle& other) const
    {
        return this->delegate().operator ==(other.delegate());
    }

    /**
     * @brief Returns is_nil()
     */
    // Spec error: this method was missing
    bool operator==(const dds::core::null_type&) const
    {
        return this->is_nil();
    }

    /**
     * @brief Returns the nil instance handle
     *
     * @details \dref_details_InstanceHandle_t_NIL
     */
    static TInstanceHandle nil()
    {
        static TInstanceHandle value(DELEGATE::nil());
        return value;
    }

    /**
     * @brief Check if this InstanceHandle represents the nil InstanceHandle
     * 
     * @return true if the InstanceHandle is nil, false otherwise
     */
    bool is_nil() const
    {
        return this->delegate().is_nil();
    }
};


#endif // !defined(OMG_TDDS_CORE_INSTANCE_HANDLE_HPP_)
