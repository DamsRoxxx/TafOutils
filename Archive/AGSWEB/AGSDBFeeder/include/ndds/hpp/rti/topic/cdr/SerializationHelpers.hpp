/* $Id$

(c) Copyright, Real-Time Innovations, 2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

*/

#ifndef RTI_DDS_TOPIC_CDR_SERIALIZATION_HELPERS_HPP_
#define RTI_DDS_TOPIC_CDR_SERIALIZATION_HELPERS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <vector>
#include <string>

#include "cdr/cdr_stream.h"
#include "dds_c/dds_c_topic.h"

#include <dds/core/SafeEnumeration.hpp>
#include "../../../dds/core/External.hpp"

/*
 * Helper types and functions used in IDL code generation.
 */

namespace rti { namespace topic { namespace cdr {

// integer_case returns an integer type valid in a switch statement.
//
// integer_case(x) returns:
//  - x if x's type is a primitive type, except bool
//  - DDS_BOOLEAN_TRUE/DDS_BOOLEAN_FALSE if x's type is bool
//  - x.underlying() if x's type is safe_enum.
//
// This unifies the generated type-plugin code for switch statements.
//

// Base case
template <typename T>
struct integer_case_impl {
    typedef T return_type;

    static T get(T v)
    {
        return v;
    }
};

// bool specialization
template <>
struct integer_case_impl<bool> {
    typedef DDS_Boolean return_type;

    static DDS_Boolean get(bool v)
    {
        return v ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
    }
};

// safe_enum specialization
template <typename InnerEnum>
struct integer_case_impl<dds::core::safe_enum<InnerEnum> > {
    typedef typename InnerEnum::type return_type;

    static return_type get(dds::core::safe_enum<InnerEnum> e)
    {
        return e.underlying();
    }
};

// The actual function we use (can deduce T).
template <typename T>
typename integer_case_impl<T>::return_type integer_case(T v)
{
    return integer_case_impl<T>::get(v);
}

// --- Pointer allocation: ----------------------------------------------------

template <typename T>
void allocate_pointers(dds::core::external<T>& p)
{
    dds::core::detail::make_locked(p);
}


template <typename T, size_t N>
void allocate_pointers(dds::core::array<T, N>& v)
{
    for (size_t i = 0; i < N; i++) {
        allocate_pointers(v[i]);
    }
}

// --- Alias helper: ----------------------------------------------------------

// alias_helper
//
// Obtains the default value of a type T, which the code generator may not
// be able to identify when T is typedef'd.
//
// Since during template instantiation the compiler resolves all typedefs, this
// utility simplifies the code generation. For example, given
//
//   struct A {};
//   typedef A B;
//
//   alias_helper<A> is the same as alias_helper<B>.
//
//
// Only primitive types, safe_enums and arrays require special treatment (other
// types will be default-constructed with the right values).
//

// General case: default-constructed primitive type
//
// For example alias_helper<int>::default_value() == 0
template <typename T>
struct alias_helper {
    static T default_value()
    {
        return T();
    }
};

// Enumerations: get the first enumerator via the enumeration's get_default()
// method.
template <typename InnerEnum>
struct alias_helper<dds::core::safe_enum<InnerEnum> > {
    static dds::core::safe_enum<InnerEnum> default_value()
    {
        return InnerEnum::get_default();
    }
};

// Arrays and nested arrays: the default value is the inner-most type.
//
// For example:
// alias_helper<array<array<array<int, 10>, 10>, 10> >::default_value()
// resolves as: alias_helper<int>::default_value() == 0.
//
template <typename E, size_t N>
struct alias_helper<dds::core::array<E, N> > : public alias_helper<E> {
};


} } } // namespace rti::topic::cdr

#endif // RTI_DDS_TOPIC_CDR_SERIALIZATION_HELPERS_HPP_
