/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,22jan13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_ENTITY_HPP_
#define RTI_DDS_CORE_ENTITY_HPP_

#include <string>
#include <utility> // for std::pair

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/core/status/Status.hpp>
#include <rti/core/detail/SelfReference.hpp>
#include <rti/core/cond/StatusConditionImpl.hpp>

namespace rti { namespace core {

class EntityLock;

class OMG_DDS_API Entity : public detail::RetainableType<Entity, 2> {
public:
    typedef detail::RetainableType<Entity, 2> RetainableType;
    typedef RetainableType::ref_type ref_type;
    typedef RetainableType::weak_ref_type weak_ref_type;

    virtual ~Entity();

protected:
    Entity(DDS_Entity * native_entity);
    Entity(const std::pair<DDS_Entity *, bool>& native_entity_enable);

private: // Disable copy
    Entity(const Entity&);
    Entity& operator=(const Entity& other);

public:
    void enable();
    const dds::core::status::StatusMask status_changes();
    const dds::core::InstanceHandle instance_handle() const;


    /* To be specialized by subclasses. The overridden method must call
     * Entity::close() at the end
     */
    virtual void close();
    void retain();

public:

    // --- RTI extensions: ----------------------------------------------------

    bool enabled();
    virtual bool closed() const
    {
        return native_entity_ == NULL;
    }

public:
    // --- For internal use only: ---------------------------------------------

    void remember_reference(ref_type reference);

    DDS_Entity * native_entity()
    {
        assert_not_closed();
        return native_entity_;
    }

    const DDS_Entity * native_entity() const
    {
        assert_not_closed();
        return native_entity_;
    }

    void native_entity(DDS_Entity * entity);

    dds::core::smart_ptr_traits<rti::core::cond::StatusCondition>::ref_type
    status_condition_ref()
    {
        assert_not_closed();
        return status_condition_ref_;
    }

    const dds::core::smart_ptr_traits<rti::core::cond::StatusCondition>::ref_type
    status_condition_ref() const
    {
        assert_not_closed();
        return status_condition_ref_;
    }

protected:
    void assert_not_closed() const
    {
        if (closed()) {
            throw dds::core::AlreadyClosedError("already closed");
        }
    }

    // must be called by subclasses when a listener is set
    void retain_for_listener();

    // must be called by subclasses the listener is unset
    void unretain_for_listener();

    virtual void reserved_data(void * ptr);
    virtual void * reserved_data();

public:
    void created_from_c(bool the_created_from_c)
    {
        created_from_c_ = the_created_from_c;
    }

    bool created_from_c() const
    {
        return created_from_c_;
    }

private:
    friend class EntityLock; // allow access to get_self_reference()

    static volatile unsigned int entityID_;
    DDS_Entity * native_entity_;
    rti::core::cond::StatusCondition::ref_type status_condition_ref_;
    bool created_from_c_;
};

} } // namespace rti::core

#endif // RTI_DDS_CORE_ENTITY_HPP_

