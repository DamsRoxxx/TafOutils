/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_DYNAMICTYPEIMPL_HPP_
#define RTI_DDS_CORE_XTYPES_DYNAMICTYPEIMPL_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_typecode.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/xtypes/TypeKind.hpp>
#include <dds/core/xtypes/Annotations.hpp>
#include <rti/core/NativeValueType.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

class DynamicTypeImpl;

} // namespace xtypes

class OMG_DDS_API DynamicTypeNativeAdapter {
public:
    typedef DDS_TypeCode native_type;

    static void initialize(native_type&) {}
    static void finalize(native_type& native_value);
    static void copy(native_type& destination, const native_type& source);
    static bool equals(const native_type& first, const native_type& second);
};

template <>
struct native_type_traits<xtypes::DynamicTypeImpl> {
    typedef DynamicTypeNativeAdapter adapter_type;
    typedef DynamicTypeNativeAdapter::native_type native_type;
};

namespace xtypes {

namespace detail {

dds::core::xtypes::TypeKind get_type_kind_from_native(DDS_TCKind native_kind);

} // namespace detail

/**
 * @RTI_class_definition class DynamicType
 * @ingroup DDSXTypesModule
 * @headerfile "dds/core/xtypes/DynamicType.hpp"
 * @brief @st_value_type Represents a runtime type.
 *
 * A DynamicType is a mechanism for representing a type at
 * runtime. DynamicTypes allow the reflective manipulation of data (DynamicData)
 * and the inspection of the type information about discovered readers and writers.
 *
 * You can obtain a DynamicType in a few different ways:
 * -# Creating one by instantiating a subclass of dds::core::xtypes::DynamicType
 *    instance, such as dds::core::xtypes::StructType and adding members to it. For example:
 *    \code
 *    using namespace dds::core::xtypes;
 *
 *    StructType point_type("Point");
 *    point_type.add_member(Member("x", PrimitiveType<double>()));
 *    point_type.add_member(Member("y", PrimitiveType<double>()));
 *    \endcode
 * -# From an IDL-generated type, using the rti::topic::dynamic_type trait type. @extension
 * -# From an XML description, using dds::core::QosProvider::type().
 * -# Constructing it using tuples. @st_cpp11 @st_exp @extension
 * -# From a discovered DataReader or DataWriter, using the \ref DDSBuiltInTopicModule "built-in topics".
 *
 * For examples, see \ref DDSXTypesExampleModule
 *
 * This an abstract base class of all the types. This class contains all of the
 * internal state&mdash;derived classes don't add any new state. That means that
 * it is safe to copy a DynamicType without slicing.
 *
 * To downcast a DynamicType into a concrete class, you can check its kind()
 * and then apply a static_cast to the appropriate class.
 *
 * For example, let's assume we have the following IDL type:
 *
 * \code
 * struct Bar {
 *     long x;
 * };
 *
 * struct Foo {
 *     Bar bar;
 *     long y;
 * };
 * \endcode
 *
 * We obtain the type of \p Foo and want to know the type of its member \p bar:
 *
 * \code
 * // Get the DynamicType of the IDL-generated type Foo
 * const StructType& foo_type = rti::topic::dynamic_type<Foo>::get();
 * // Get the type of its member bar
 * const DynamicType& bar_type = foo_type.member("bar").type();
 * // Check type kind and downcast
 * if (bar_type.kind() == TypeKind::STRUCTURE_TYPE) {
 *     const StructType& bar_struct = static_cast<const StructType&>(bar_type);
 * }
 * \endcode
 *
 *  @see dds::core::xtypes::DynamicData, the class that represents data samples
 *  for a DynamicType
 *  @see dds::topic::SubscriptionBuiltinTopicData::type() and
 *  dds::topic::PublicationBuiltinTopicData::type() to obtain the type of a
 *  remote subscription or publication
 *  @see rti::topic::dynamic_type to obtain the equivalent DynamicType of an
 *  IDL-generated type
 *  @see \ref DDSXTypesExampleModule
 */
class OMG_DDS_API DynamicTypeImpl : public NativeValueType<DynamicTypeImpl> {
public:
    typedef NativeValueType<DynamicTypeImpl> Base;

protected:
    DynamicTypeImpl() {}
    DynamicTypeImpl(const native_type& native_value) : Base(native_value)
    {
    }

public:
    DynamicTypeImpl(const DynamicTypeImpl& other) : Base(other) {}
    DynamicTypeImpl& operator=(const DynamicTypeImpl& other);

  #if defined(RTI_CXX11_RVALUE_REFERENCES)
    // We would use defaulted functions if all compilers supported it
    DynamicTypeImpl(DynamicTypeImpl&& other) OMG_NOEXCEPT
        : Base(std::move(other))
    {
    }

    DynamicTypeImpl& operator=(DynamicTypeImpl&& other) OMG_NOEXCEPT
    {
        Base::operator=(std::move(other));
        return *this;
    }
  #endif

    /**
     * @brief Gets the type kind
     */
    dds::core::xtypes::TypeKind kind() const;

    /**
     * @brief Gets the name
     */
    std::string name() const;
};

/**
 * @ingroup DDSXtypesModule
 * @brief The base class of types that have members and an extensibility kind
 *
 * @tparam MemberType The concrete member type, specified by the subclasses, can
 * be Member, UnionMember and EnumMember
 *
 * This is the base class of StructType, UnionType and EnumType.
 */
template <typename MemberType>
class AbstractConstructedType : public DynamicTypeImpl {
public:

    /**
     * @brief The member type (specified by the subclasses of this class)
     */
    typedef MemberType Member;

    /**
     * @brief The meber index type
     */
    typedef uint32_t MemberIndex;

    /**
     * @brief Indicates that a member doesn't exist
     */
    static OMG_DDS_API_CLASS_VARIABLE const MemberIndex INVALID_INDEX;

    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(AbstractConstructedType, DynamicTypeImpl)

    /**
     * @brief Gets the extensibility kind
     */
    dds::core::xtypes::ExtensibilityKind extensibility_kind() const;

    /**
     * @brief Gets the number of members
     */
    size_t member_count() const;

    /**
     * @brief Gets a member by its index
     *
     * @param index The index of the member (0 to member_count() - 1)
     */
    const MemberType& member(MemberIndex index) const;

    /**
     * @brief Gets a member by its name
     */
    const MemberType& member(const std::string& name) const;

    /**
     * @brief Obtains the member index from its name
     */
    MemberIndex find_member_by_name(const std::string& name) const;

    /**
     * @brief Gets a copy of all the members
     */
    std::vector<MemberType> members() const;

protected:
    AbstractConstructedType() {}

    // Used by Enum and Union
    MemberIndex find_member_by_label_impl(int32_t label) const;

    // Used by Struct and Union
    MemberIndex find_member_by_id_impl(uint32_t id) const;

    void set_extensibility_kind_impl(dds::core::xtypes::ExtensibilityKind kind);
};

} } } // close and reopen namespace for documentation purposes

namespace rti { namespace core { namespace xtypes {

/**
 * @relatesalso dds::core::xtypes::DynamicType
 * @brief @extension Prints the IDL representation of this type to the standard output
 */
OMG_DDS_API
void print_idl(const DynamicTypeImpl& type, unsigned int indent = 0);

} } } // namespace rti::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_DYNAMICTYPEIMPL_HPP_
