/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

*/

#ifndef RTI_DDS_CORE_COND_CONDITION_FUNCTOR_TRAITS_HPP_
#define RTI_DDS_CORE_COND_CONDITION_FUNCTOR_TRAITS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ref_traits.hpp>
#include <dds/core/corefwd.hpp>
#include <rti/core/FunctorHolder.hpp>

namespace rti { namespace core { namespace cond { namespace detail {


 /*
  * A concrete functor holder that holds a Condition as a weak reference so it
  * can be passed as the argument to the functor.
  * The generic OneArgFunctorHolder cannot be used because that would require
  * a shared pointer as an argument, creating a situation in which the condition
  * could never be deleted: The condition would be holding a shared pointer to
  * itself.
  * This concrete functor holder keeps a weak reference and creates the shared
  * pointer every single time the functor is invoked.
  * template <typename Functor>
  */
template <typename Functor>
class ConditionFunctorHolder : public FunctorHolder {
public:
  ConditionFunctorHolder(
        const Functor& func,dds::core::smart_ptr_traits<Condition>::weak_ref_type self)
  : func_(func), self_weak_ref_(self) { }

  virtual ~ConditionFunctorHolder() { }

public:
  virtual void invoke() 
  {
    dds::core::smart_ptr_traits<Condition>::ref_type self_ref =
            self_weak_ref_.lock();
    if (self_ref) {
        func_(self_ref);
    }
  }
private:
  Functor func_;
  dds::core::smart_ptr_traits<Condition>::weak_ref_type self_weak_ref_;
};

// detect if Functor::operator()(Condition) (const or non-const) exists
template<typename Functor>
struct has_condition_operator
{
    // Used to match a member operator()(Condition)
    template<typename U, void (U::*)(dds::core::cond::Condition)>
    struct check_signature {};

    // Overload 1: chosen only when U defines void operator()(Condition)
    typedef char overload1;
    template<typename U>
    static overload1 check_operator(check_signature<U, &U::operator()>*);

    // Overload 2: chosen in all other situations
    typedef int32_t overload2;
    template<typename U>
    static overload2 check_operator(...);

    // value == 1 if overload1 is chosen for T
    enum {
        value = sizeof(check_operator<Functor>(0)) == sizeof(overload1)
    };
};

template<typename Functor>
struct has_const_condition_operator
{
    // Used to match a member operator()(Condition) const
    template<typename U, void (U::*)(dds::core::cond::Condition) const>
    struct check_signature {};

    // Overload 2: chosen only when U defines void operator()(Condition) const
    typedef int16_t overload1;
    template<typename U>
    static overload1 check_operator(check_signature<U, &U::operator()>*);

    // Overload 3: chosen in all other situations
    typedef int32_t overload2;
    template<typename U>
    static overload2 check_operator(...);

    // value == 1 if overload1 is chosen for T
    enum {
        value = sizeof(check_operator<Functor>(0)) == sizeof(overload1)
    };
};

// detect if Functor defines operator()(Condition) or is a function that
// can receive a Condition
template <typename Functor>
struct is_callable_with_condition {
    typedef void (*ConditionFunction)(dds::core::cond::Condition);

    enum {
        value = has_condition_operator<Functor>::value
            || has_const_condition_operator<Functor>::value
            || rtiboost::is_convertible<Functor, ConditionFunction>::value
    };
};


template <typename T, typename U = void>
struct create_functor_holder_helper;

// param(condition) is legal
template <typename Functor>
struct create_functor_holder_helper<Functor,
typename rtiboost::enable_if_c<
    is_callable_with_condition<Functor>::value>::type> {
static FunctorHolder* create_functor_holder(
        dds::core::smart_ptr_traits<Condition>::weak_ref_type cond,
        Functor functor)
{
    return new ConditionFunctorHolder<Functor>(
            functor,
            cond);
}
};

template <typename Functor>
struct create_functor_holder_helper<Functor,
typename rtiboost::disable_if_c<
    is_callable_with_condition<Functor>::value>::type> {
static FunctorHolder* create_functor_holder(
        dds::core::smart_ptr_traits<Condition>::weak_ref_type,
        Functor functor)
{
    return new rti::core::VoidFunctorHolder<Functor>(functor);
}
};

// param(condition) is not legal => use param();
template <typename Functor>
FunctorHolder* create_functor_holder(
        dds::core::smart_ptr_traits<Condition>::weak_ref_type cond,
        Functor functor)
{
    return create_functor_holder_helper<Functor>::create_functor_holder(cond, functor);
}

} } } } // namespace rti::core::cond::detail

#endif // RTI_DDS_CORE_COND_CONDITION_FUNCTOR_TRAITS_HPP_

