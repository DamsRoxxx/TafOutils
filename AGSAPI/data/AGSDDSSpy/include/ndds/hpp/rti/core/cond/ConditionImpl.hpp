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

#ifndef RTI_DDS_CORE_COND_CONDITION_HPP_
#define RTI_DDS_CORE_COND_CONDITION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>
#include <rti/core/corefwd.hpp>
#include <rti/core/detail/SelfReference.hpp>
#include <rti/core/cond/detail/ConditionFunctorTraits.hpp>
#include <rti/core/FunctorHolder.hpp>
#include <rti/core/Exception.hpp>

namespace rti { namespace core { namespace cond {

class OMG_DDS_API Condition {
public:

    typedef dds::core::smart_ptr_traits<Condition>::ref_type
        ref_type;
    typedef dds::core::smart_ptr_traits<Condition>::weak_ref_type
        weak_ref_type;

    virtual ~Condition();

protected:
    Condition(DDS_Condition * native_condition);

    template <typename Functor>
    Condition(DDS_Condition * the_native_condition, const Functor& the_handler)
        : native_condition_(the_native_condition),
          dispatch_func_(NULL)
    {
        rti::core::check_create_entity(native_condition_, "Condition");
        handler_impl(the_handler);
    }

private: // Disable copy
    Condition(const Condition&);
    Condition& operator=(const Condition& other);


public:
    bool trigger_value() const;
    void dispatch();

protected:
    template <typename Functor>
    void handler_impl(const Functor& func) // Extension
    {
        // CPPPSM-177
        // This function and reset_handler() are not thread-safe with respect
        // to dispatching the handler. GuardCondition exposes this and leaves
        // it up to the user to synchronize if needed, whereas in ReadCondition
        // the handler is immutable (can only be set in the constructor).
        // StatusCondition doesn't expose the handler because this condition is
        // unique per entity.
        reset_handler_impl();
        dispatch_func_ = detail::create_functor_holder(
                get_weak_ref(),
                func);
    }


    void reset_handler_impl();

public:
    // --- For internal use only: ---------------------------------------------

    void remember_reference(ref_type reference);

    DDS_Condition * native_condition()
    {
        return native_condition_;
    }

    const DDS_Condition * native_condition() const
    {
        return native_condition_;
    }

    bool is_attached_to_waitset() {
        return self_reference_.get_retain_count() > 0;
    }
    void native_condition(DDS_Condition * entity);

    ref_type create_shared_from_this();
    weak_ref_type get_weak_ref();

    void retain_for_waitset();
    void unretain_for_waitset();

protected:

    void reserved_data(void * ptr);
    void * reserved_data();   

protected:
    DDS_Condition * native_condition_;
    rti::core::detail::SelfReference<Condition> self_reference_;
    FunctorHolder * dispatch_func_;
};

} } } // namespace rti::core::cond

#endif // RTI_DDS_CORE_COND_CONDITION_HPP_

