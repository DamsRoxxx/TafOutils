/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_MEMBERTYPEIMPL_HPP_
#define RTI_DDS_CORE_XTYPES_MEMBERTYPEIMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_typecode_impl.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/String.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/xtypes/DynamicType.hpp>
#include <dds/core/xtypes/PrimitiveTypes.hpp>

#include <rti/core/NativeValueType.hpp>

#include <rti/core/corefwd.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

class AbstractMember;
class AbstractAggregationMember;
class MemberImpl;
class UntypedUnionMember;
class EnumMemberImpl;

} // namespace xtypes

class OMG_DDS_API MemberNativeAdapter {
public:
    typedef DDS_TypeCode_Member native_type;

    static void initialize(native_type& native_value);
    static void finalize(native_type& native_value);
    static void copy(native_type& destination, const native_type& source);
    static bool equals(const native_type& first, const native_type& second);
};

template <>
struct native_type_traits<xtypes::AbstractMember> {
    typedef MemberNativeAdapter adapter_type;
    typedef MemberNativeAdapter::native_type native_type;
};

namespace xtypes {

//
// Abstract base class of the different kinds of Members
// All members have a name and share a common internal representation.
//
class OMG_DDS_API AbstractMember : public NativeValueType<AbstractMember> {
protected:
    typedef NativeValueType<AbstractMember> Base;

    AbstractMember() {}
    AbstractMember(const AbstractMember& other);
    AbstractMember& operator=(const AbstractMember& other);

  #if defined(RTI_CXX11_RVALUE_REFERENCES)
  #if defined(RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS)
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(AbstractMember, Base)
  #else
    AbstractMember(AbstractMember&&) = default;
    AbstractMember& operator=(AbstractMember&&) = default;
  #endif
  #endif

public:
    const dds::core::string& name() const;
    dds::core::string& name();
};

// Common functionality of struct Members and UnionMembers
class OMG_DDS_API AbstractAggregationMember : public AbstractMember {
protected:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(AbstractAggregationMember, AbstractMember)

    AbstractAggregationMember(
        const std::string& name, const DynamicTypeImpl& type);

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    AbstractAggregationMember(const std::string& the_name, DynamicTypeImpl&& the_type)
    {
        typedef rti::core::memory::ObjectAllocator<DynamicTypeImpl> TypeAllocator;
        native_type() = TypeAllocator::create(std::move(the_type));
        try {
            name() = the_name;
        } catch (...) {
            TypeAllocator::destroy(native_type());
            throw;
        }
    }
  #endif

public:
    static OMG_DDS_API_CLASS_VARIABLE const int32_t INVALID_ID;

    const DynamicTypeImpl& type() const;
    bool has_id() const;
    int32_t get_id() const;
    bool is_pointer() const; // Extension


protected:
    // Setters are to be redefined by subclasses to return a reference to the actual type
    AbstractAggregationMember& set_id_impl(int32_t value);
    AbstractAggregationMember& set_pointer_impl(bool value);

public: // for internal use only
    DynamicTypeImpl*& native_type();
    uint8_t get_flags() const;
    void clear(); // clears heap members after a move
};


/**
 * @RTI_class_definition class Member
 * @ingroup DDSXTypesModule
 * @headerfile "dds/core/xtypes/MemberType.hpp"
 * @brief @st_value_type Represents a StructType member
 *
 * Encapsulates the name and type of a StructType member along with several
 * IDL annotations (key, optional, bitset, bitbound, id).
 */
class OMG_DDS_API MemberImpl : public AbstractAggregationMember {
public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(MemberImpl, AbstractAggregationMember)

    /**
     * @brief Creates a member consisting of a name and a type.
     */
    MemberImpl(const std::string& name, const DynamicTypeImpl& type);

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates a member consisting of a name and a type.
     *
     * The type is moved.
     */
    MemberImpl(const std::string& the_name, DynamicTypeImpl&& the_type)
        : AbstractAggregationMember(the_name, std::move(the_type))
    {
    }
  #endif

    bool operator==(const MemberImpl& other) const;
    bool operator!=(const MemberImpl& other) const;

    // Inherited getters (hidden by definition of setter)
    using AbstractMember::name;
    using AbstractAggregationMember::type;

    #ifdef DOXYGEN_DOCUMENTATION_ONLY
    // This member are in the base class. Defined here for documentation only.
    // This is duplicated in UnionMember--keep it synchronized

    /**
     * @brief The special ID of a member without the ID annotation
     */
    static const int32_t INVALID_ID;

    /**
     * @brief Gets the member name
     */
    const dds::core::string& name() const;

    /**
     * @brief Gets the member name
     */
    dds::core::string& name();

    /**
     * @brief Gets the member type
     */
    const DynamicType& type();

    /**
     * @brief Indicates it the member has an ID annotation
     *
     * True if this member has been annotated explicitly with an ID. False if
     * the has a default-assigned ID.
     */
    bool has_id() const;

    /**
     * @brief Returns the ID annotation of this member
     *
     * If has_id() is true, this returns the value of the ID annotation.
     * Otherwise it returns INVALID_ID.
     *
     */
    int32_t get_id() const;

    /**
     * @brief @extension Indicates if this member is a pointer
     */
    bool is_pointer() const;
    #endif

    /**
     * @brief Checks if a member is a key
     *
     * This corresponds to the \@Key IDL member annotation
     */
    bool is_key() const;

    /**
     * @brief Checks if a member is optional
     *
     * This corresponds to the \@Optional IDL member annotation
     */
    bool is_optional() const;

    /**
     * @brief Checks if a member is a bitset
     */
    bool is_bitset() const;

    /**
     * @brief Unsupported, always returns false
     */
    bool has_bitbound() const;

    /**
     * @brief Unsupported, always returns 32
     */
    int32_t get_bitbound() const;

    /**
     * @brief Sets the member name
     */
    MemberImpl& name(const dds::core::string& value);
    /**
     * @brief Sets the key annotation of a member
     *
     * @post If optional() was true and key is set to true,
     *       optional() becomes false, because a member can't
     *       be both a key and optional.
     *
     * @default false
     */
    MemberImpl& key(bool value);
    /**
     * @brief Sets the optional annotation of a member
     *
     * @post If key() was true and optional is set to true,
     *       key() becomes false, because a member can't
     *       be both a key and optional.
     *
     * @default false
     */
    MemberImpl& optional(bool value);
    MemberImpl& bitset(bool value);
    MemberImpl& bitbound(int32_t value);

    /**
     * @brief Sets the ID annotation of a member
     *
     * @default Automatically assigned as the ID of the previous member plus one
     * previous member
     */
    MemberImpl& id(int32_t value);

    /**
     * @brief @extension Makes a member a pointer
     *
     * @default false
     */
    MemberImpl& pointer(bool value);
};

/**
 * @RTI_class_definition class UnionMember
 * @ingroup DDSXTypesModule
 * @headerfile "dds/core/xtypes/MemberType.hpp"
 * @brief @st_value_type Represents a UnionType member
 *
 * Encapsulates the name, type and labels of a UnionType member along with several
 * IDL annotations such as id.
 */
class OMG_DDS_API UnionMember : public AbstractAggregationMember {
public:

    /**
     * @brief The type to represent a union discriminator
     */
    typedef DDS_Long DiscriminatorType;

    /**
     * @brief A sequence of values for the discriminator that
     * select a member.
     */
    typedef std::vector<DiscriminatorType> LabelSeq;

    /**
     * @brief Special value for the \p default: union label.
     */
    static OMG_DDS_API_CLASS_VARIABLE DiscriminatorType DEFAULT_LABEL;

    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(UnionMember, AbstractAggregationMember)

    /**
     * @brief Creates a union member with a name, type and selected by one or
     *  more labels.
     */
    UnionMember(
        const std::string& name,
        const DynamicTypeImpl& type,
        const LabelSeq& labels);

    /**
     * @brief Creates a union member with a name, type and selected by a
     *  single label
     */
    UnionMember(
        const std::string& name,
        const DynamicTypeImpl& type,
        DiscriminatorType label);

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates a union member with a name, type and selected by one or
     *  more labels.
     *
     *  It moves the type.
     */
    UnionMember(
        const std::string& the_name,
        DynamicTypeImpl&& the_type,
        const LabelSeq& the_labels)
        : AbstractAggregationMember(the_name, std::move(the_type))
    {
        labels(the_labels);
    }
  #endif


  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates a union member with a name, type and selected by a
     * single label.
     *
     * It moves the type.
     */
    UnionMember(
        const std::string& the_name,
        DynamicTypeImpl&& the_type,
        DiscriminatorType the_label)
        : AbstractAggregationMember(the_name, std::move(the_type))
    {
        label(the_label);
    }
  #endif

    bool operator==(const UnionMember& other) const;
    bool operator!=(const UnionMember& other) const;

    using AbstractMember::name; // Name getter, hidden by definition of setter

    #ifdef DOXYGEN_DOCUMENTATION_ONLY
    // This member are in the base class. Defined here for documentation only.
    // This documentation is duplicated in Member--keep them synchronized

    /**
     * @brief The special ID of a member without the ID annotation
     */
    static const int32_t INVALID_ID;

    /**
     * @brief Gets the member name
     */
    const dds::core::string& name() const;

    /**
     * @brief Gets the member name
     */
    dds::core::string& name();

    /**
     * @brief Gets the member type
     */
    const DynamicType& type();

    /**
     * @brief Indicates it the member has an ID annotation
     *
     * @return True if this member has been annotated explicitly with an ID;
     * false if the has a default-assigned ID.
     */
    bool has_id() const;

    /**
     * @brief Returns the ID annotation of this member
     *
     * @return If has_id() is true, this returns the value of the ID annotation.
     * Otherwise it returns INVALID_ID.
     *
     */
    int32_t get_id() const;

    /**
     * @brief @extension Indicates if this member is a pointer
     */
    bool is_pointer() const;
    #endif

    /**
     * @brief Gets the number of labels that select this member
     */
    uint32_t label_count() const;

    /**
     * @brief Gets a copy of all the labels that select this member
     */
    LabelSeq labels() const;

    /**
     * @brief Sets the labels that select this member
     */
    UnionMember& labels(const LabelSeq& values);

    /**
     * @brief Sets a single label that selects this member.
     *
     * If more than one label selects this case, use labels(const LabelSeq&)
     */
    UnionMember& label(DiscriminatorType value);

    /**
     * @brief Sets the name
     */
    UnionMember& name(const dds::core::string& value);

    /**
     * @brief Sets the ID annotation of a member
     *
     * @default Automatically assigned as the ID of the previous member plus one
     * previous member
     */
    UnionMember& id(int32_t value);

    /**
     * @brief @extension Makes a member a pointer
     *
     * @default false
     */
    UnionMember& pointer(bool value);
};

/**
 * @RTI_class_definition class EnumMember
 * @ingroup DDSXTypesModule
 * @headerfile "dds/core/xtypes/MemberType.hpp"
 * @brief @st_value_type Represents a EnumType member
 *
 * Encapsulates the name and value (ordinal) of an IDL \p enum type
 */
class OMG_DDS_API EnumMemberImpl : public AbstractMember {
public:
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(EnumMemberImpl, AbstractMember)

    /**
     * Creates a EnumMember with a name and value (ordinal)
     */
    EnumMemberImpl(const std::string& name, int32_t ordinal);

    bool operator==(const EnumMemberImpl& other) const;
    bool operator!=(const EnumMemberImpl& other) const;

    #ifdef DOXYGEN_DOCUMENTATION_ONLY
    /**
     * @brief Gets the name
     */
    const dds::core::string& name() const;
    /**
     * @brief Gets the member name
     */
    dds::core::string& name();
    #endif

    using AbstractMember::name; // name getter

    /**
     * @brief Sets the name
     */
    EnumMemberImpl& name(const dds::core::string& value);

    /**
     * @brief Gets the ordinal
     */
    int32_t ordinal() const;

    /**
     * @brief Sets the ordinal
     */
    EnumMemberImpl& ordinal(int32_t the_ordinal);
};

} } } // namespace rti::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_MEMBERTYPEIMPL_HPP_
