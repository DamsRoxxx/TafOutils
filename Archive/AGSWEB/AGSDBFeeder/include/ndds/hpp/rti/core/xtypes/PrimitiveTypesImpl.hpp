/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_PRIMITIVETYPESIMPL_HPP_
#define RTI_DDS_CORE_XTYPES_PRIMITIVETYPESIMPL_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/xtypes/DynamicTypeImpl.hpp>
#include <dds/core/xtypes/CollectionTypes.hpp>
#include <rti/core/LongDouble.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

template <typename T>
struct native_primitive_type_code {
    // Undefined -- T has to match a template specialization for one valid
    // primitive type
};

template <>
struct native_primitive_type_code<uint8_t> {
    static const DDS_TypeCode& value() { return DDS_g_tc_octet; }
};

template <>
struct native_primitive_type_code<int16_t> {
    static const DDS_TypeCode& value() { return DDS_g_tc_short; }
};

template <>
struct native_primitive_type_code<uint16_t> {
    static const DDS_TypeCode& value() { return DDS_g_tc_ushort; }
};

template <>
struct native_primitive_type_code<int32_t> {
    static const DDS_TypeCode& value() { return DDS_g_tc_long; }
};

template <>
struct native_primitive_type_code<uint32_t> {
    static const DDS_TypeCode& value() { return DDS_g_tc_ulong; }
};

template <>
struct native_primitive_type_code<float> {
    static const DDS_TypeCode& value() { return DDS_g_tc_float; }
};

template <>
struct native_primitive_type_code<double> {
    static const DDS_TypeCode& value() { return DDS_g_tc_double; }
};

template <>
struct native_primitive_type_code<bool> {
    static const DDS_TypeCode& value() { return DDS_g_tc_boolean; }
};

template <>
struct native_primitive_type_code<char> {
    static const DDS_TypeCode& value() { return DDS_g_tc_char; }
};

template <>
struct native_primitive_type_code<rti::core::int64> {
    static const DDS_TypeCode& value() { return DDS_g_tc_longlong; }
};

template <>
struct native_primitive_type_code<rti::core::uint64> {
    static const DDS_TypeCode& value() { return DDS_g_tc_ulonglong; }
};

template <>
struct native_primitive_type_code<rti::core::LongDouble> {
    static const DDS_TypeCode& value() { return DDS_g_tc_longdouble; }
};

template <>
struct native_primitive_type_code<wchar_t> {
    static const DDS_TypeCode& value() { return DDS_g_tc_wchar; }
};

// Although strings are not primitive types, by treating them as such we
// can enable std::string in create_type_from_tuple().
template <>
struct native_primitive_type_code<std::string> {
    static const DDS_TypeCode& value()
    {
        static const dds::core::xtypes::StringType singleton(
            dds::core::xtypes::StringType::UNBOUNDED);
        return singleton.native();
    }
};

/**
 * @RTI_class_definition class PrimitiveType : public DynamicType
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/PrimitiveTypes.hpp
 * @brief @st_value_type Represents and IDL primitive type
 * @tparam T The C++ primitive type for which to obtain a DynamicType. These
 * are the possible types:
 * | C++ type (T)          | IDL type            |
 * | --------------------- | ------------------- |
 * | char                  | char                |
 * | bool                  | boolean             |
 * | uint8_t               | octet               |
 * | (u)int16_t            | (unsigned) short    |
 * | (u)int32_t            | (unsigned) long     |
 * | (u)int64_t            | (unsigned) long long|
 * | float                 | float               |
 * | double                | double              |
 * | rti::core::LongDouble | long double         |
 * | wchar_t               | wchar               |
 *
 * Instead of instantiating this class it is recommended to obtain a singleton
 * for each primitive type T using primitive_type.
 *
 * Note: this class doesn't have any members other than those inherited from
 * DynamicType.
 *
 * @see primitive_type()
 */
template <typename T>
class PrimitiveType : public DynamicTypeImpl {
public:
    PrimitiveType() : DynamicTypeImpl(native_primitive_type_code<T>::value())
    {
    }
};

template <typename T>
const PrimitiveType<T>& primitive_type_impl()
{
    static const PrimitiveType<T> singleton;
    return singleton;
}

} } } // namespace rti::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_PRIMITIVETYPESIMPL_HPP_
