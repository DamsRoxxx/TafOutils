//  (C) Copyright John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

//  See boost/type_traits/*.hpp for full copyright notices.

#ifndef RTIBOOST_TYPE_TRAITS_HPP
#define RTIBOOST_TYPE_TRAITS_HPP

#include <rtiboost/type_traits/add_const.hpp>
#include <rtiboost/type_traits/add_cv.hpp>
#include <rtiboost/type_traits/add_lvalue_reference.hpp>
#include <rtiboost/type_traits/add_pointer.hpp>
#include <rtiboost/type_traits/add_reference.hpp>
#include <rtiboost/type_traits/add_rvalue_reference.hpp>
#include <rtiboost/type_traits/add_volatile.hpp>
#include <rtiboost/type_traits/aligned_storage.hpp>
#include <rtiboost/type_traits/alignment_of.hpp>
#include <rtiboost/type_traits/common_type.hpp>
#include <rtiboost/type_traits/conditional.hpp>
#include <rtiboost/type_traits/copy_cv.hpp>
#include <rtiboost/type_traits/decay.hpp>
#include <rtiboost/type_traits/declval.hpp>
#include <rtiboost/type_traits/extent.hpp>
#include <rtiboost/type_traits/floating_point_promotion.hpp>
#include <rtiboost/type_traits/function_traits.hpp>

#include <rtiboost/type_traits/has_bit_and.hpp>
#include <rtiboost/type_traits/has_bit_and_assign.hpp>
#include <rtiboost/type_traits/has_bit_or.hpp>
#include <rtiboost/type_traits/has_bit_or_assign.hpp>
#include <rtiboost/type_traits/has_bit_xor.hpp>
#include <rtiboost/type_traits/has_bit_xor_assign.hpp>
#include <rtiboost/type_traits/has_complement.hpp>
#include <rtiboost/type_traits/has_dereference.hpp>
#include <rtiboost/type_traits/has_divides.hpp>
#include <rtiboost/type_traits/has_divides_assign.hpp>
#include <rtiboost/type_traits/has_equal_to.hpp>
#include <rtiboost/type_traits/has_greater.hpp>
#include <rtiboost/type_traits/has_greater_equal.hpp>
#include <rtiboost/type_traits/has_left_shift.hpp>
#include <rtiboost/type_traits/has_left_shift_assign.hpp>
#include <rtiboost/type_traits/has_less.hpp>
#include <rtiboost/type_traits/has_less_equal.hpp>
#include <rtiboost/type_traits/has_logical_and.hpp>
#include <rtiboost/type_traits/has_logical_not.hpp>
#include <rtiboost/type_traits/has_logical_or.hpp>
#include <rtiboost/type_traits/has_minus.hpp>
#include <rtiboost/type_traits/has_minus_assign.hpp>
#include <rtiboost/type_traits/has_modulus.hpp>
#include <rtiboost/type_traits/has_modulus_assign.hpp>
#include <rtiboost/type_traits/has_multiplies.hpp>
#include <rtiboost/type_traits/has_multiplies_assign.hpp>
#include <rtiboost/type_traits/has_negate.hpp>
#if !defined(__BORLANDC__) && !defined(__CUDACC__)
#include <rtiboost/type_traits/has_new_operator.hpp>
#endif
#include <rtiboost/type_traits/has_not_equal_to.hpp>
#include <rtiboost/type_traits/has_nothrow_assign.hpp>
#include <rtiboost/type_traits/has_nothrow_constructor.hpp>
#include <rtiboost/type_traits/has_nothrow_copy.hpp>
#include <rtiboost/type_traits/has_nothrow_destructor.hpp>
#include <rtiboost/type_traits/has_plus.hpp>
#include <rtiboost/type_traits/has_plus_assign.hpp>
#include <rtiboost/type_traits/has_post_decrement.hpp>
#include <rtiboost/type_traits/has_post_increment.hpp>
#include <rtiboost/type_traits/has_pre_decrement.hpp>
#include <rtiboost/type_traits/has_pre_increment.hpp>
#include <rtiboost/type_traits/has_right_shift.hpp>
#include <rtiboost/type_traits/has_right_shift_assign.hpp>
#include <rtiboost/type_traits/has_trivial_assign.hpp>
#include <rtiboost/type_traits/has_trivial_constructor.hpp>
#include <rtiboost/type_traits/has_trivial_copy.hpp>
#include <rtiboost/type_traits/has_trivial_destructor.hpp>
#include <rtiboost/type_traits/has_trivial_move_assign.hpp>
#include <rtiboost/type_traits/has_trivial_move_constructor.hpp>
#include <rtiboost/type_traits/has_unary_minus.hpp>
#include <rtiboost/type_traits/has_unary_plus.hpp>
#include <rtiboost/type_traits/has_virtual_destructor.hpp>

#include <rtiboost/type_traits/integral_constant.hpp>

#include <rtiboost/type_traits/is_abstract.hpp>
#include <rtiboost/type_traits/is_arithmetic.hpp>
#include <rtiboost/type_traits/is_array.hpp>
#include <rtiboost/type_traits/is_assignable.hpp>
#include <rtiboost/type_traits/is_base_and_derived.hpp>
#include <rtiboost/type_traits/is_base_of.hpp>
#include <rtiboost/type_traits/is_class.hpp>
#include <rtiboost/type_traits/is_complex.hpp>
#include <rtiboost/type_traits/is_compound.hpp>
#include <rtiboost/type_traits/is_const.hpp>
#include <rtiboost/type_traits/is_constructible.hpp>
#include <rtiboost/type_traits/is_convertible.hpp>
#include <rtiboost/type_traits/is_copy_assignable.hpp>
#include <rtiboost/type_traits/is_copy_constructible.hpp>
#include <rtiboost/type_traits/is_default_constructible.hpp>
#include <rtiboost/type_traits/is_destructible.hpp>
#include <rtiboost/type_traits/is_empty.hpp>
#include <rtiboost/type_traits/is_enum.hpp>
#include <rtiboost/type_traits/is_final.hpp>
#include <rtiboost/type_traits/is_float.hpp>
#include <rtiboost/type_traits/is_floating_point.hpp>
#include <rtiboost/type_traits/is_function.hpp>
#include <rtiboost/type_traits/is_fundamental.hpp>
#include <rtiboost/type_traits/is_integral.hpp>
#include <rtiboost/type_traits/is_lvalue_reference.hpp>
#include <rtiboost/type_traits/is_member_function_pointer.hpp>
#include <rtiboost/type_traits/is_member_object_pointer.hpp>
#include <rtiboost/type_traits/is_member_pointer.hpp>
#include <rtiboost/type_traits/is_nothrow_move_assignable.hpp>
#include <rtiboost/type_traits/is_nothrow_move_constructible.hpp>
#include <rtiboost/type_traits/is_object.hpp>
#include <rtiboost/type_traits/is_pod.hpp>
#include <rtiboost/type_traits/is_pointer.hpp>
#include <rtiboost/type_traits/is_polymorphic.hpp>
#include <rtiboost/type_traits/is_reference.hpp>
#include <rtiboost/type_traits/is_rvalue_reference.hpp>
#include <rtiboost/type_traits/is_same.hpp>
#include <rtiboost/type_traits/is_scalar.hpp>
#include <rtiboost/type_traits/is_signed.hpp>
#include <rtiboost/type_traits/is_stateless.hpp>
#include <rtiboost/type_traits/is_union.hpp>
#include <rtiboost/type_traits/is_unsigned.hpp>
#include <rtiboost/type_traits/is_virtual_base_of.hpp>
#include <rtiboost/type_traits/is_void.hpp>
#include <rtiboost/type_traits/is_volatile.hpp>
#include <rtiboost/type_traits/make_signed.hpp>
#include <rtiboost/type_traits/make_unsigned.hpp>
#include <rtiboost/type_traits/rank.hpp>
#include <rtiboost/type_traits/remove_all_extents.hpp>
#include <rtiboost/type_traits/remove_bounds.hpp>
#include <rtiboost/type_traits/remove_const.hpp>
#include <rtiboost/type_traits/remove_cv.hpp>
#include <rtiboost/type_traits/remove_extent.hpp>
#include <rtiboost/type_traits/remove_pointer.hpp>
#include <rtiboost/type_traits/remove_reference.hpp>
#include <rtiboost/type_traits/remove_volatile.hpp>
#include <rtiboost/type_traits/type_identity.hpp>
#include <rtiboost/type_traits/type_with_alignment.hpp>

#if !(defined(__sgi) && defined(__EDG_VERSION__) && (__EDG_VERSION__ == 238))
#include <rtiboost/type_traits/integral_promotion.hpp>
#include <rtiboost/type_traits/promote.hpp>
#endif

#endif // RTIBOOST_TYPE_TRAITS_HPP
