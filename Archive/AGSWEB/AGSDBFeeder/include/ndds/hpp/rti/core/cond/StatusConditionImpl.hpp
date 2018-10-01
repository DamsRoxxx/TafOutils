/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,22jan13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_COND_STATUS_CONDITION_HPP_
#define RTI_DDS_CORE_COND_STATUS_CONDITION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/corefwd.hpp>
#include <dds/core/status/State.hpp>
#include <rti/core/cond/ConditionImpl.hpp>

namespace rti { namespace core { namespace cond {

/** @RTI_class_definition NA */
class OMG_DDS_API StatusCondition : public rti::core::cond::Condition {
public:

    typedef dds::core::smart_ptr_traits<StatusCondition>::ref_type
        ref_type;
    typedef dds::core::smart_ptr_traits<rti::core::Entity>::ref_type
        entity_ref_type;
    typedef dds::core::smart_ptr_traits<rti::core::Entity>::weak_ref_type
        entity_weak_ref_type;

    // --- Implementation of TStatusCondition: --------------------------------

    void enabled_statuses(const dds::core::status::StatusMask& status);

    dds::core::status::StatusMask enabled_statuses() const;

    dds::core::Entity entity() const;

    // --- API extensions: ---------------------------------------------

    /**
     * @memberof dds::core::cond::StatusCondition
     * @brief @extension Registers a custom handler with this condition.
     *
     * For information about condition handlers, see
     * \link dds::sub::cond::ReadCondition::ReadCondition(const dds::sub::DataReader&,const dds::sub::status::DataState&,const Functor&)
     * this ReadCondition constructor\endlink
     *
     * @note Changing this handler will affect any other references to this
     * Entity's StatusCondition.
     *
     * @mtsafety It is not safe to call handler() or reset_handler() while
     * this condition is attached to a waitset being dispatched.
     */
    template <typename Functor>
    void handler(const Functor& func) // Extension
    {
        handler_impl(func);
    }

    /**
     * @memberof dds::core::cond::StatusCondition
     * @brief @extension Resets the handler for this condition.
     *
     * After the invocation of this method no handler will be registered with
     * this condition.
     *
     * @note Changing this handler will affect any other references to this
     * Entity's StatusCondition.
     *
     * @mtsafety It is not safe to call handler() or reset_handler() while
     * this condition is attached to a waitset being dispatched.
     *
     */
    void reset_handler()
    {
        reset_handler_impl();
    }

    // --- For internal use only: ---------------------------------------------

    DDS_StatusCondition * native_status_condition()
    {
        return reinterpret_cast<DDS_StatusCondition*>(native_condition());
    }

    const DDS_StatusCondition * native_status_condition() const
    {
        return reinterpret_cast<const DDS_StatusCondition*>(native_condition());
    }


private:
    StatusCondition(DDS_StatusCondition * native_status_condition);

    void set_entity_ref(entity_ref_type entity_ref)
    {
        entity_weak_ref_ = entity_ref;
    }

#ifndef DOXYGEN_DOCUMENTATION_ONLY
    // Only an entity can create StatusConditions
    friend class rti::core::Entity;
#endif

private:
    // Issue CPPPSM-179: The weak reference doesn't prevent the Entity from
    // being deleted
    entity_weak_ref_type entity_weak_ref_;
};

} } } // namespace rti::core::cond

#endif // RTI_DDS_CORE_COND_STATUS_CONDITION_HPP_

