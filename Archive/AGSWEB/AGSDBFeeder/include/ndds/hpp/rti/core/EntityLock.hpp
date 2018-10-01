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

#ifndef RTI_DDS_CORE_ENTITY_LOCK_HPP_
#define RTI_DDS_CORE_ENTITY_LOCK_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Entity.hpp>

namespace rti { namespace core {

class OMG_DDS_API EntityLock {
public:
    EntityLock(dds::core::Entity entity);
    EntityLock(rti::core::Entity& entity_impl); // for internal use
    ~EntityLock();

    void unlock();

private:
    // disable copy
    EntityLock(const EntityLock&);
    EntityLock& operator=(const EntityLock&);

    void lock_impl();

    rti::core::Entity::ref_type related_entity_;
    bool locked_;
};

} } // namespace rti::core

#endif // RTI_DDS_CORE_ENTITY_LOCK_HPP_

