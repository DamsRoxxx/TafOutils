/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_DYNAMICDATA_TUPLES_HPP_
#define RTI_DDS_CORE_XTYPES_DYNAMICDATA_TUPLES_HPP_

#if !defined(RTI_NO_CXX11_HDR_TUPLE)

#include <tuple>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/core/xtypes/StructType.hpp>
#include <dds/core/xtypes/PrimitiveTypes.hpp>

namespace rti { namespace core { namespace xtypes {

typedef decltype(std::ignore) ignore_t;

// --- get_tuple implementation: ----------------------------------------------

template <typename T>
T get_reverse(const dds::core::xtypes::DynamicData& data, uint32_t id)
{
    // TODO: try different strategy to avoid calling get_member_count. Iterate
    // through the variadic types in reverse order
    return data.value<T>(data.member_count()-id);
}

template <>
inline ignore_t get_reverse<ignore_t>(
    const dds::core::xtypes::DynamicData&, uint32_t)
{
    return ignore_t();
}

template <size_t N, typename Head, typename... Tail>
struct get_tuple_impl {
    static std::tuple<Head, Tail...> do_it(const dds::core::xtypes::DynamicData& data)
    {
        return std::tuple_cat(
            std::make_tuple(get_reverse<Head>(data, N)),
            get_tuple_impl<N-1, Tail...>::do_it(data));
    }
};

template <typename Head, typename... EmptyTail>
struct get_tuple_impl<0, Head, EmptyTail...> {
    static std::tuple<Head> do_it(const dds::core::xtypes::DynamicData& data)
    {
        return std::make_tuple(get_reverse<Head>(data, 0));
    }
};


template <typename... Types>
struct get_from_tuple_or_type_list {
    static std::tuple<Types...> do_it(const dds::core::xtypes::DynamicData& data)
    {
        return get_tuple_impl<sizeof...(Types)-1, Types...>::do_it(data);
    }
};

//template <typename... Types>
//struct get_from_tuple_or_type_list<std::tuple<Types...> >{
//    static std::tuple<Types...> do_it(const dds::core::xtypes::DynamicData& data)
//    {
//        return get_from_tuple_or_type_list<Types...>::do_it(data);
//    }
//};

// --- get_tuple: -------------------------------------------------------------

/**
 * @relatesalso dds::core::xtypes::DynamicData
 * @brief @st_cpp11 @st_exp @extension Retrieves all the values of a
 * DynamicData object into an std::tuple at once
 *
 * @see @ref DDSXTypesExampleModule_dynamic_data_tuples
 */
template <typename... Types>
std::tuple<Types...> get_tuple(const dds::core::xtypes::DynamicData& data)
{
    return get_from_tuple_or_type_list<Types...>::do_it(data);
}

// --- set_tuple implementation: ----------------------------------------------

template <typename T>
void set(dds::core::xtypes::DynamicData& data, uint32_t id, const T& value)
{
    return data.value<T>(id, value);
}

template <>
inline void set<ignore_t>(
    dds::core::xtypes::DynamicData&, uint32_t, const ignore_t&)
{
    // nothing to do
}

template <size_t N, typename... Types>
struct set_tuple_impl {
    static void do_it(
        dds::core::xtypes::DynamicData& data,
        const std::tuple<Types...>& value)
    {
        set(data, N+1, std::get<N>(value));
        set_tuple_impl<N-1, Types...>::do_it(data, value);
    }
};

template <typename... Types>
struct set_tuple_impl<0, Types...> {
    static void do_it(
        dds::core::xtypes::DynamicData& data,
        const std::tuple<Types...>& value)
    {
        set(data, 1, std::get<0>(value));
    }
};

// --- set_tuple: -------------------------------------------------------------

/**
 * @relatesalso dds::core::xtypes::DynamicData
 * @brief @st_cpp11 @st_exp @extension Assigns the values of a std::tuple to a
 * DynamicData object at once
 *
 * @see @ref DDSXTypesExampleModule_dynamic_data_tuples
 */
template <typename... Types>
void set_tuple(
    dds::core::xtypes::DynamicData& data,
    const std::tuple<Types...>& value)
{
    set_tuple_impl<sizeof...(Types)-1, Types...>::do_it(data, value);
}

// --- Type creation from tuple -----------------------------------------------

inline std::string create_member_name(size_t n)
{
    std::ostringstream os;
    os << "m" << n;
    return os.str();
}

// General case
//
// N is the size of the initial (full) list of types
// i is the size of Tail
// Head + Tail... are the remaining types we're using to create the StructType
template <size_t N, size_t i, typename Head, typename... Tail>
struct create_type_impl {
    static void do_it(dds::core::xtypes::StructType& type)
    {
        type.add_member(
            dds::core::xtypes::Member(
                create_member_name(N - i - 1), // "m0", "m1", ..., mN-1
                dds::core::xtypes::primitive_type<Head>()));
        create_type_impl<N, i - 1, Tail...>::do_it(type);
    }
};

// Base case
template <size_t N, typename Head, typename... EmptyTail>
struct create_type_impl<N, 0, Head, EmptyTail...> {
    static void do_it(dds::core::xtypes::StructType& type)
    {
        type.add_member(
            dds::core::xtypes::Member(
                create_member_name(N - 1),
                dds::core::xtypes::primitive_type<Head>()));
    }
};

// This general case allows calling create_type_from_tuple with a list of types:
//    auto type = create_type_from_tuple<int32_t, uint8_t, double>("my_type");
//
template <typename... Types>
struct create_type_from_list_or_tuple_impl {
    static void do_it(dds::core::xtypes::StructType& type)
    {
        create_type_impl<sizeof...(Types), sizeof...(Types)-1, Types...>::do_it(type);
    }
};

// This specialization allows calling create_type_from_tuple with a tuple:
//    typedef std::tuple<int32_t, uint8_t, double> MyTuple;
//    auto type = create_type_from_tuple<MyTuple>("my_type");
//
template <typename... Types>
struct create_type_from_list_or_tuple_impl<std::tuple<Types...> > {
    static void do_it(dds::core::xtypes::StructType& type)
    {
        create_type_from_list_or_tuple_impl<Types...>::do_it(type);
    }
};

/**
 * @relatesalso dds::core::xtypes::StructType
 * @brief @st_cpp11 @st_exp @extension Creates a StructType from a list of types or a std::tuple
 *
 * @tparam Types A list of types or a std::tuple. The types must be primitive
 * (see dds::core::xtypes::PrimitiveType) or \p std::string.
 *
 * The StructType members are all default-created (i.e. non-key, non-optional, with default IDs...)
 * and their names are m0, m1, m2, etc.
 *
 * @see @ref DDSXTypesExampleModule_dynamic_type_creation_tuples
 */
template <typename... Types>
dds::core::xtypes::StructType create_type_from_tuple(const std::string& name)
{
    dds::core::xtypes::StructType type(name);
    create_type_from_list_or_tuple_impl<Types...>::do_it(type);
    return type;
}

} } } // namespace rti::core::xtypes

#endif // RTI_NO_CXX11_HDR_TUPLE

#endif // RTI_DDS_CORE_XTYPES_DYNAMICDATA_TUPLES_HPP_
