/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
5.20,08aug14,ajm CODEGENII-303 Adding impl_type trait
5.20,16jun14,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_TOPICTRAITS_HPP_
#define RTI_DDS_TOPIC_TOPICTRAITS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rtiboost/type_traits/is_arithmetic.hpp>
#include <rtiboost/utility/enable_if.hpp>

#include <dds/topic/TopicTraits.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/array.hpp>
#include <dds/core/String.hpp>
#include <dds/core/Optional.hpp>
#include <dds/core/SafeEnumeration.hpp>
#include <rti/core/BoundedSequence.hpp>
#include <rti/core/LongDouble.hpp>
#include <dds/core/External.hpp>

namespace rti { namespace topic {

// Used in the generated topic_type_support<T>::type_plugin_kind to indicate
// if the generated code supports STL types or not
struct TypePluginKind_def {
    enum type {
        NON_STL,
        STL
    };
};

typedef dds::core::safe_enum<TypePluginKind_def> TypePluginKind;

/**
 * @ingroup DDSTopicTraitsModule
 * @headerfile rti/topic/TopicTraits.hpp
 * @brief @extension Indicates the extensibility kind of a topic-type
 *
 * This trait type is specialized for \ref DDSTypesModule "IDL-generated types"
 * provide a member \p kind of type \p dds::core::xtypes::ExtensibilityKind.
 *
 * For example, given the following IDL type, \p Foo:
 * \code
 * struct Foo {
 *     long x;
 * }; //@Extensibility MUTABLE_EXTENSIBILITY
 * \endcode
 *
 * You can obtain its extensility kind:
 *
 * \code
 * assert (rti::topic::extensibility<Foo>::kind
 *      == dds::core::xtypes::ExtensibilityKind::MUTABLE);
 * \endcode
 *
 */
template <typename TopicType>
struct extensibility {
    // specializations define:
    //
    // static ExtensibilityKind kind = ...;
};

/**
 * @ingroup DDSTopicTraitsModule
 * @headerfile rti/topic/TopicTraits.hpp
 * @brief @extension Indicates if a topic type contains directly or indirectly
 *  IDL pointer members.
 *
 * This template is specialized in the generated code for topic types that do
 * contain pointers.
 *
 * This trait enables (when it's \p false_type) or disables (when it's
 * \p true_type) the DataReader read/take operations that copy instead of
 * loaning the data (for example,
 * dds::sub::DataReader::take(SamplesFWIterator, int32_t))
 *
 */
template <typename TopicType>
struct topic_type_has_pointer_members : public dds::core::false_type {};

/**
 * @ingroup DDSTopicTraitsModule
 * @headerfile rti/topic/TopicTraits.hpp
 * @brief @extension Indicates if a topic type contains directly or indirectly
 *  IDL external members.
 *
 * This template is specialized in the generated code for topic types that do
 * contain \p &amp;external members.
 */
template <typename TopicType>
struct topic_type_has_external_members : public dds::core::false_type {};

/*
 * For internal use.
 *
 * This template is specialized in the generated code to return the equivalent
 * generated type in C
 */
template <typename TopicType>
struct impl_type {};

/**
 * @ingroup DDSTopicTraitsModule
 * @headerfile rti/topic/TopicTraits.hpp
 * @brief Provides a DynamicType that represents an IDL-generated type.
 *
 * This type is specialized for \ref DDSTypesModule "IDL-generated types" to
 * provide a \p get() function whose return type is a const reference to a
 * concrete subclass of dds::core::xtypes::DynamicType, such as
 * dds::core::xtypes::StructType, dds::core::xtypes::UnionType,
 * dds::core::xtypes::EnumType.
 *
 * For example, given the following IDL type \p Foo:
 *
 * \code
 * struct Foo {
 *     long x;
 * };
 * \endcode
 *
 * You can obtain its DynamicType (in this case a StructType) as follows:
 *
 * \code
 * const dds::core::xtypes::StructType& foo_dynamic = rti::topic::dynamic_type<Foo>::get();
 * std::cout << foo_dynamic.name() << std::endl; // Output: Foo
 * \endcode
 *
 * Note that if the type is an IDL alias such as the following:
 *
 * \code
 * typedef Foo Bar;
 * \endcode
 *
 * Then \p rti::topic::dynamic_type<Bar> resolves to \p rti::topic::dynamic_type<Foo>,
 * both returning the same \p StructType. If you want to explicitly access the \p AliasType
 * use the special tag type \p Bar_AliasTag_t:
 *
 * \code
 * const dds::core::xtypes::AliasType& bar_dynamic = rti::topic::dynamic_type<Bar_AliasTag_t>::get();
 * std::cout << bar_dynamic.name() << std::endl; // Output: Bar
 * \endcode
 *
 * @see
 */
template <typename TopicType>
struct dynamic_type {
    // specializations define:
    // static const dds::core::xtypes::DynamicType& get();
};

// For internal use
template <typename TopicType>
struct native_type_code {
    // specializations define:
    // static const DDS_TypeCode * get();
};

// Helper to unify calls to reset_sample by deducing the argument type
template <typename T>
typename rtiboost::enable_if_c<!rtiboost::is_arithmetic<T>::value, void>::type
reset_sample(T& value)
{
    dds::topic::topic_type_support<T>::reset_sample(value);
}

template <typename T>
typename rtiboost::enable_if_c<rtiboost::is_arithmetic<T>::value, void>::type
reset_sample(T& value)
{
    value = static_cast<T>(0);
}

template <typename T>
typename rtiboost::enable_if_c<!rtiboost::is_arithmetic<T>::value, void>::type
allocate_sample(T& value, int max_seq_length = -1, int max_str_length = -1)
{
    dds::topic::topic_type_support<T>::allocate_sample(
            value,
            max_seq_length,
            max_str_length);
}

template <typename T>
typename rtiboost::enable_if_c<rtiboost::is_arithmetic<T>::value, void>::type
allocate_sample(T&, int = -1, int = -1)
{
}

} }  // namespace rti::topic

namespace dds { namespace topic {

//
// Template specializations for topic_type_support<T>
// (for non-constructed T types)
//
// These templates help the code generator define reset_sample for
// IDL types
//

namespace detail {

// Initialize range (array/sequence) of non-primitive type
template <typename Iterator>
typename rtiboost::enable_if_c<
    !rtiboost::is_arithmetic<
        typename std::iterator_traits<Iterator>::value_type>::value,
void>::type
reset_range(Iterator begin, Iterator end)
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    // Apply reset_sample to all members
    std::for_each(begin, end, rti::topic::reset_sample<value_type>);
}

// Initialize range (array/sequence) of primitive (arithmetic) type
template <typename Iterator>
typename rtiboost::enable_if_c<
    rtiboost::is_arithmetic<
        typename std::iterator_traits<Iterator>::value_type>::value,
void>::type
reset_range(Iterator begin, Iterator end)
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    // Apply reset_sample to all members
    std::fill(begin, end, static_cast<value_type>(0));
}

// Initialize range (array/sequence) of non-primitive type
template <typename Iterator>
typename rtiboost::enable_if_c<
    !rtiboost::is_arithmetic<
        typename std::iterator_traits<Iterator>::value_type>::value,
void>::type
allocate_range(
        Iterator begin,
        Iterator end,
        int max_seq_length,
        int max_str_length)
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    for (; begin != end; ++begin) {
        rti::topic::allocate_sample<value_type>(
                *begin,
                max_seq_length,
                max_str_length);
    }
}

// Initialize range (array/sequence) of primitive (arithmetic) type
template <typename Iterator>
typename rtiboost::enable_if_c<
    rtiboost::is_arithmetic<
        typename std::iterator_traits<Iterator>::value_type>::value,
void>::type
allocate_range(Iterator, Iterator, int, int)
{
    // primitive types don't need allocation
}

} // namespace detail

template <typename T>
struct topic_type_support<std::vector<T> > {
    static void reset_sample(std::vector<T>& v)
    {
        // Default value: empty sequence
        v.clear();
    }

    static void allocate_sample(
            std::vector<T>& v,
            int max_seq_length,
            int)
    {
        if (max_seq_length > 0) {
            v.reserve(max_seq_length);
        }

        // We can't preallocate the elements because the extra capacity is
        // uninitialized (memory). That's the optimization that bounded_sequence
        // provides
    }
};

template <typename T, size_t N>
struct topic_type_support<rti::core::bounded_sequence<T, N> > {
    static void reset_sample(rti::core::bounded_sequence<T, N>& s)
    {
        // TODO: call reserve(N) ?

        // First, reset the existing values, because the next call to deserialize
        // will call resize_uninitialized()
        detail::reset_range(s.begin(), s.end());

        // now set the actual size to 0. This will not destroy the objects
        // from s.begin()..s.end(), so they can be reused and make the
        // deserialization more efficient.
        s.clear();
    }

    static void allocate_sample(
            rti::core::bounded_sequence<T, N>& s,
            int max_seq_length,
            int max_str_length)
    {
        size_t current_size = s.size();
        // Allocate the underlying buffer
        s.resize_uninitialized(N);
        // initialize the elements
        detail::allocate_range(s.begin(), s.end(), max_seq_length, max_str_length);
        // Reset to the previous size. This will not destroy the extra elements
        // we may have allocated in the previous line. The will remain at full
        // length even if we expand or shrink this sequence.
        s.resize(current_size);
    }
};

template <typename T, size_t N>
struct topic_type_support<dds::core::array<T, N> > {
    static void reset_sample(dds::core::array<T, N> & v)
    {
        // Default value depends on whether T is primitive or not
        detail::reset_range(v.begin(), v.end());
    }

    static void allocate_sample(
            dds::core::array<T, N> & v,
            int max_seq_length,
            int max_str_length)
    {
        // Default value depends on whether T is primitive or not
        detail::allocate_range(v.begin(), v.end(), max_seq_length, max_str_length);
    }
};

template <typename CharType, typename Allocator>
struct topic_type_support<dds::core::basic_string<CharType, Allocator> > {
    static void reset_sample(dds::core::basic_string<CharType, Allocator>& s)
    {
        // Default value: empty string
        s = dds::core::basic_string<CharType, Allocator>();
    }
};

template <typename CharType, typename Allocator>
struct topic_type_support<std::basic_string<CharType, Allocator> > {
    static void reset_sample(std::basic_string<CharType, Allocator>& s)
    {
        // Default value: empty string
        s.resize(0);
    }

    static void allocate_sample(
            std::basic_string<CharType, Allocator>& s,
                int,
                int max_str_length)
    {
        if (max_str_length > 0) {
            s.reserve(max_str_length);
        }
    }
};

template <>
struct topic_type_support<rti::core::LongDouble> {
    static void reset_sample(rti::core::LongDouble& ld)
    {
        // Default value: 0.0
        ld = rti::core::LongDouble();
    }

    static void allocate_sample(rti::core::LongDouble&, int, int)
    {
        // nothing to allocate
    }
};

template <typename EnumDef>
struct topic_type_support<dds::core::safe_enum<EnumDef> > {
    static void reset_sample(dds::core::safe_enum<EnumDef>& e)
    {
        // Default value: first element of the enumeration
        e = EnumDef::get_default();
    }

    static void allocate_sample(dds::core::safe_enum<EnumDef>&, int, int)
    {
        // nothing to allocate
    }
};

template <typename T>
struct topic_type_support<dds::core::external<T> > {
    static void reset_sample(dds::core::external<T>& p)
    {
        if (!p) {
            dds::core::detail::make_locked(p);
        }

        rti::topic::reset_sample(*p);
    }

    // When T is not arithmetic (U will be just T, but we
    // need to templatize the function so that enable_if works)
    template <typename U>
    static
    typename rtiboost::enable_if_c<
        !rtiboost::is_arithmetic<U>::value,
        void>::type
    allocate_sample(
            dds::core::external<U>& p,
            int max_seq_length,
            int max_str_length)
    {
        if (!p) {
            dds::core::detail::make_locked(p);
        }

        rti::topic::allocate_sample(*p, max_seq_length, max_str_length);
    }

    // When T is arithmetic, we need to explicitly
    // initialize the value, because 'new T' won't.
    template <typename U>
    static
    typename rtiboost::enable_if_c<
        rtiboost::is_arithmetic<U>::value,
        void>::type
    allocate_sample(
            dds::core::external<U>& p,
            int max_seq_length,
            int max_str_length)
    {
        if (!p) {
            dds::core::detail::make_locked(p);
        }

        rti::topic::allocate_sample(*p, max_seq_length, max_str_length);
        *p = static_cast<U>(0);
    }
};

template <typename T>
struct topic_type_support<dds::core::optional<T> > {
    static void reset_sample(dds::core::optional<T>& p)
    {
        p.reset();
    }

    static void allocate_sample(dds::core::optional<T>&, int, int)
    {
    }
};

} } // namespace dds::topic

#endif // RTI_DDS_TOPIC_TOPICTRAITS_HPP_
