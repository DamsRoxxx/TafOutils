#ifndef OMG_DDS_CORE_REF_TRAITS_H_
#define OMG_DDS_CORE_REF_TRAITS_H_

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

/*
 * These traits have to be provided by compliant implementations
 * to enable safe polymorphic casts.
 */
namespace  dds { namespace core {

  template <typename T1, typename T2>
  struct is_base_of;

  template <typename T1, typename T2>
  struct is_same;

  template <typename T>
  struct smart_ptr_traits;

  /**
   * @relatesalso dds::core::Entity
   * @brief Downcasts an Entity to a subclass.
   *
   * @tparam TO The type to cast to
   * @tparam FROM The type to cast from
   * @param from The object to cast to type \p TO
   * @return A reference to the same object \p from, but cast to the type \p TO.
   * Both objects share ownership of the underlying entity.
   *
   * For example:
   * \code
   * using namespace dds::core;
   * using namespace dds::domain;
   *
   * DomainParticipant participant(0);
   * Entity entity = participant; // Assignment to base
   * DomainParticipant participant2 = polymorphic_cast<DomainParticipant>(entity);
   * assert (participant == participant2); // Same reference
   * \endcode
   *
   * @see \ref a_st_ref_type "Reference types"
   */
  template <typename TO, typename FROM>
  TO  polymorphic_cast(FROM& from);


} } /* namespace dds / namespace core */


// This include should stay here as it provides implementations
// for the declaration just above.
#include <dds/core/detail/ref_traits.hpp>

#endif /* OMG_DDS_CORE_REF_TRAITS_H_ */

