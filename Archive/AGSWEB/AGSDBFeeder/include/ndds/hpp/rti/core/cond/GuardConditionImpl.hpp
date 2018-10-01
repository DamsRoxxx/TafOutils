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

#ifndef RTI_DDS_CORE_COND_GUARD_CONDITION_HPP_
#define RTI_DDS_CORE_COND_GUARD_CONDITION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/corefwd.hpp>
#include <dds/core/status/State.hpp>
#include <rti/core/cond/ConditionImpl.hpp>


namespace rti { namespace core { namespace cond {

class OMG_DDS_API GuardCondition : public Condition {
public:
    GuardCondition();
    ~GuardCondition();

    using Condition::trigger_value; // getter overload in base class
    void trigger_value(bool value);

    template <typename Functor>
    void handler(const Functor& func)
    {
        handler_impl(func);
    }

    void reset_handler()
    {
        reset_handler_impl();
    }
};

} } } // namespace rti::core::cond

#endif // RTI_DDS_CORE_COND_GUARD_CONDITION_HPP_

