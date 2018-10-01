/* $Id$

 (c) Copyright, Real-Time Innovations, 2014-2016.
 All rights reserved.
 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
-------------------- 
5.0.2.x,03sep14,ajm Fixes from CR-402
5.0.2.x,21may14,ajm CODEGENII-173 Added test default constructor
5.0.2.x,10feb14,acr CPPPSM-70 Moved test infrastructure from impl files
============================================================================= */

/*i @file
   Defines reusable templatized tests
*/

#ifndef RTI_TEST_GENERIC_TESTS_HPP_
#define RTI_TEST_GENERIC_TESTS_HPP_

#include <algorithm> // std::find
#include <vector>

#include <dds/core/macros.hpp>
#ifndef RTI_NO_CXX11_HDR_TYPE_TRAITS
#include <type_traits>
#endif

#include <rti/core/memory.hpp> // for ObjectAllocator

#include <rti/test/assertions.hpp>

namespace rti { namespace test {

template <class T1, class T2>
void assert_equal(const T1& a, const T2& b)
{
    RTI_TEST_ASSERT(a == b);
    RTI_TEST_ASSERT(b == a);
    RTI_TEST_ASSERT(!(a != b));
    RTI_TEST_ASSERT(!(b != a));
}

template <class T1, class T2>
void assert_not_equal(const T1& a, const T2& b)
{
    RTI_TEST_ASSERT(a != b);
    RTI_TEST_ASSERT(b != a);
    RTI_TEST_ASSERT(!(a == b));
    RTI_TEST_ASSERT(!(b == a));
}

template <class Container, class T>
bool contains(const Container& c, const T& v)
{
    return std::find(c.begin(), c.end(), v) != c.end();
}

template <class T>
void test_swap(const T& instance1, const T& instance2)
{
    T instance1_copy = instance1;
    T instance2_copy = instance2;

    swap(instance1_copy, instance2_copy);

    RTI_TEST_ASSERT(instance1_copy == instance2);
    RTI_TEST_ASSERT(instance2_copy == instance1);

  #ifndef RTI_NO_CXX11_NOEXCEPT
    RTI_TEST_ASSERT(noexcept(swap(instance1_copy, instance2_copy)));
  #endif
}

template <class T>
void test_copy_ctor_and_operators_no_default_ctor(
    const T& instance1, const T& instance2)
{
    const T instance2_copy(instance2);
    const T instance1_copy(instance1);

    RTI_TEST_TRACE(assert_equal(instance1, instance1_copy));
    RTI_TEST_TRACE(assert_equal(instance2, instance2_copy));
    RTI_TEST_TRACE(assert_not_equal(instance1, instance2_copy));
    RTI_TEST_TRACE(assert_not_equal(instance2, instance1_copy));

    T other_instance = instance2;
    RTI_TEST_TRACE(assert_equal(instance2, other_instance));
    RTI_TEST_TRACE(assert_not_equal(instance1, other_instance));

    // Test assignment operator
    other_instance = instance1;
    RTI_TEST_TRACE(assert_equal(instance1, other_instance));
    RTI_TEST_TRACE(assert_not_equal(instance2, other_instance));

    other_instance = instance2;
    RTI_TEST_TRACE(assert_equal(instance2, other_instance));
    RTI_TEST_TRACE(assert_not_equal(instance1, other_instance));

    // Test comparison to self
    RTI_TEST_TRACE(assert_equal(instance1, instance1));
}

// Copies the bytes of a variable into a vector of bytes
template <typename T>
std::vector<unsigned char> shallow_copy_memory(const T& value)
{
    std::vector<unsigned char> memory(sizeof(value));
    const unsigned char * value_ptr = reinterpret_cast<const unsigned char*>(&value);
    std::copy(value_ptr, value_ptr + sizeof(value), memory.begin());
    return memory;
}

#ifdef RTI_CXX11_RVALUE_REFERENCES
template <class T>
void test_move_ctor_and_assignment(
    const T& default_instance,
    const T& non_default_instance,
    bool bitwise_comparison = true)
{
    // We use this allocator to make sure that all memory is zeroed out before
    // constructing an object, so when we compare two objects byte-wise
    // uninitialized padding memory doesn't make them different. Otherwise
    // this test would only use stack variables, not pointers.
    using rti::core::memory::ObjectAllocator;
    typedef std::vector<unsigned char> ByteVector;
    // Note: we currently don't include unique_ptr in dds_cpp.2.0
    typedef typename ObjectAllocator<T>::shared_ptr shared_ptr;

    shared_ptr object1 = ObjectAllocator<T>::make_shared(default_instance);
    shared_ptr object2 = ObjectAllocator<T>::make_shared(non_default_instance);

    // Save the bytes in non_default_instance
    ByteVector previous_bytes = shallow_copy_memory(*object2);
    shared_ptr object2_copy = ObjectAllocator<T>::make_shared(*object2);

    // Test move constructor
    shared_ptr move_constructed_object = ObjectAllocator<T>::make_shared(
        std::move(*object2));

    // Check that we actually moved the implementation
    if (bitwise_comparison) {
        ByteVector moved_bytes = shallow_copy_memory(*move_constructed_object);
        RTI_TEST_ASSERT(previous_bytes == moved_bytes);
    }

    // Check also that they're logically equal.
    //
    // Note: we're testing the == operator *after* the byte-wise comparison
    // to avoid possible side effects. For example DynamicData may alter internal
    // state in const operations like this one.
    RTI_TEST_ASSERT(*object2_copy == *move_constructed_object);

    // Test move assignment operator
    previous_bytes = shallow_copy_memory(*move_constructed_object);
    *object1 = std::move(*move_constructed_object);
    if (bitwise_comparison) {
        ByteVector moved_bytes = shallow_copy_memory(*object1);
        RTI_TEST_ASSERT(previous_bytes == moved_bytes);
    }
    RTI_TEST_ASSERT(*object1 == *object2_copy);

  #ifndef RTI_NO_CXX11_HDR_TYPE_TRAITS
    // If a test fails here, check that you haven't unnecessarily defined
    // a constructor, destructor or assignment operator where the implicit one
    // is enough. That could cause the removal of the implicit move ctor or
    // assignment operator
    RTI_TEST_ASSERT(std::is_nothrow_move_constructible<T>::value);
    RTI_TEST_ASSERT(std::is_nothrow_move_assignable<T>::value);
  #endif
}
#else
// To avoid unused-parameter warning
template <class T>
void test_move_ctor_and_assignment(
    const T&,
    const T&,
    bool = true)
{
}
#endif

/*
 * Test default constructor, check that there is not
 * uninitialized memory
 */
template <class T>
void test_default_ctor()
{
    T instance1;
    T instance2;

    // Test that there is not uninitialized memory
    RTI_TEST_TRACE(assert_equal(instance1, instance2));
    // Test comparison to self
    RTI_TEST_TRACE(assert_equal(instance1, instance1));
}


/*
 * Test copy constructor, assignment operator and equality operators for any
 * value type T. The argument is any instance such as non_default_instance != T()
 */
template <class T>
void test_copy_ctor_and_operators(const T& non_default_instance)
{
    const T default_instance;
    test_copy_ctor_and_operators_no_default_ctor(
        non_default_instance, default_instance);
}

template <class T>
void test_value_type_no_default_ctor(
    const T& default_instance,
    const T& non_default_instance,
    bool bitwise_comparison = true)
{
    RTI_TEST_TRACE(test_copy_ctor_and_operators_no_default_ctor(
        default_instance, non_default_instance));

    RTI_TEST_TRACE(test_move_ctor_and_assignment(
        default_instance, non_default_instance, bitwise_comparison));

    RTI_TEST_TRACE(test_swap(default_instance, non_default_instance));

}

template <class T>
void test_value_type_no_move(
    const T& non_default_instance)
{
    const T default_instance;
    RTI_TEST_TRACE(test_default_ctor<T>());

    RTI_TEST_TRACE(test_copy_ctor_and_operators_no_default_ctor(
        default_instance, non_default_instance));

    RTI_TEST_TRACE(test_swap(default_instance, non_default_instance));
}

template <class T>
void test_value_type(const T& non_default_instance, bool bitwise_comparison=true)
{
    RTI_TEST_TRACE(test_default_ctor<T>());

#ifndef RTI_CXX11_RVALUE_REFERENCES
    const T default_instance;
    const T *default_instance_ptr = &default_instance;
#else
    using rti::core::memory::ObjectAllocator;
    typedef typename ObjectAllocator<T>::shared_ptr shared_ptr;

    // We use the ObjectAllocator to make sure the memory is zeroed
    // for test_move_ctor_and_assignment (see CORE-7064)
    shared_ptr default_instance_ptr = ObjectAllocator<T>::make_shared();
#endif

    RTI_TEST_TRACE(
            test_value_type_no_default_ctor(
                    *default_instance_ptr,
                    non_default_instance,
                    bitwise_comparison));
}

} } // namespace rti::test

#endif // RTI_TEST_GENERIC_TESTS_HPP_

/* End $Id$ */
