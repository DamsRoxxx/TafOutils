#ifndef OMG_DDS_CORE_DETAIL_REF_TRAITS_H_
#define OMG_DDS_CORE_DETAIL_REF_TRAITS_H_

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

/*
 * This file is non-normative. The implementation is
 * provided only as an example.
 */
#include "rtiboost/shared_ptr.hpp"
#include "rtiboost/weak_ptr.hpp"
#include "rtiboost/static_assert.hpp"
#include "rtiboost/type_traits.hpp"

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Exception.hpp>
 
namespace dds { namespace core {
 
template <typename T1, typename T2>
struct is_base_of : public rtiboost::is_base_of<T1, T2> { };
 
template <typename T1, typename T2>
struct is_same : public rtiboost::is_same<T1, T2> { };
 
template <typename T>
struct smart_ptr_traits {
    typedef rtiboost::shared_ptr<T> ref_type;
    typedef rtiboost::weak_ptr<T>   weak_ref_type;
};
 
 
template <typename TO, typename FROM>
TO polymorphic_cast(FROM& from) {
    typename TO::DELEGATE_REF_T dr =
        rtiboost::dynamic_pointer_cast< typename TO::DELEGATE_T>(from.delegate());
    TO to(dr);
 
    if (to == ::dds::core::null)
        throw InvalidDowncastError("Attempted invalid downcast.");
    return to;
}
 
} }

#if defined(__ghs)

// Some versions of Integrity's linker require instantiating a template class
// in a single place. Without this, trying to link two object files that use
// shared_ptr may fail.

namespace rtiboost { namespace detail {

template class spinlock_pool<1>;

} }

#endif
 
#endif /* OMG_DDS_CORE_DETAIL_REF_TRAITS_H_ */
