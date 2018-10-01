#ifndef OMG_DDS_CORE_T_STATUS_CONDITION_HPP_
#define OMG_DDS_CORE_T_STATUS_CONDITION_HPP_

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

#include <dds/core/status/State.hpp>
#include <dds/core/cond/TCondition.hpp>
#include <dds/core/Entity.hpp>

namespace dds { namespace core { namespace cond {

template <typename DELEGATE>
class TStatusCondition;

/**
 * @ingroup DDSConditionsModule
 * @RTI_class_definition class StatusCondition : public Condition
 * @headerfile dds/core/cond/StatusCondition.hpp
 *
 * @brief @st_ref_type A condition associated with each dds::core::Entity
 *
 * @details \dref_details_StatusCondition.
 *
 * @note There is exactly one StatusCondition per Entity and one Entity per StatusCondition.
 *
 * @warning Destroying an Entity invalidates all references to its
 * StatusCondition. To avoid that, always keep a reference to the Entity
 * while you also have one to its StatusCondition or
 * \link dds::core::Entity::retain() retain\endlink the Entity.
 */
template <typename DELEGATE>
class TStatusCondition : public TCondition<DELEGATE> {
public:
    OMG_DDS_BASIC_REF_TYPE(TStatusCondition, dds::core::cond::TCondition, DELEGATE)

    /**
     * @brief Obtains a reference to the StatusCondition in an entity
     *
     * @param the_entity The Entity whose status condition we're getting a reference to.
     * There is exactly one StatusCondition per Entity and one Entity per StatusCondition.
     *
     * @note This constructor doesn't create a new Condition.
     * It obtains a reference to the StatusCondition that each Entity owns. You
     * can use this constructor as many times as needed to obtain a reference
     * to the same StatusCondition.
     */
    TStatusCondition(const dds::core::Entity& the_entity)
        : TCondition<DELEGATE>(the_entity->status_condition_ref())
    {
    }

    /**
     * @brief Defines the list of communication statuses that determine the
     * trigger value
     *
     * @details \dref_details_StatusCondition_set_enabled_statuses
     */
    void enabled_statuses(const dds::core::status::StatusMask& status)
    {
        this->delegate()->enabled_statuses(status);
    }

    /**
     * @brief Gets the list of enabled statuses
     *
     * @see enabled_statuses(const dds::core::status::StatusMask&)
     */
    const dds::core::status::StatusMask enabled_statuses() const
    {
        return this->delegate()->enabled_statuses();
    }

    /**
     * @brief Get the dds::core::Entity associated with this StatusCondition
     *
     * There is exactly one Entity associated with each StatusCondition.
     */
    dds::core::Entity entity() const
    {
        return this->delegate()->entity();
    }
};

} } } // namespace dds::core::cond

#endif  /* OMG_DDS_CORE_T_STATUS_CONDITION_HPP_ */


