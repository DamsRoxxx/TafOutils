/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.7a,18mar14,eam Created
============================================================================= */

#ifndef RTI_DDS_CORE_LOCK_GUARD_HPP_
#define RTI_DDS_CORE_LOCK_GUARD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/Semaphore.hpp>

namespace rti { namespace core {

template <typename Lock>
class GenericLockGuard {
public:
    GenericLockGuard(Lock& lock) :
        lock_(lock)
    {
        lock_.take();
    }

    ~GenericLockGuard()
    {
        lock_.give();
    }

private:
    GenericLockGuard(const GenericLockGuard&); // disable copy ctor/assignment operator

    Lock& lock_;
};

typedef GenericLockGuard<Semaphore> LockGuard;

} } // namespace rti::core

#endif // RTI_DDS_CORE_LOCK_GUARD_HPP_

