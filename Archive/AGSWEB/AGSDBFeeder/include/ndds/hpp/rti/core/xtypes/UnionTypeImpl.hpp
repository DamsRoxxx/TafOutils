/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_UNIONTYPEIMPL_HPP_
#define RTI_DDS_CORE_XTYPES_UNIONTYPEIMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/xtypes/DynamicTypeImpl.hpp>
#include <rti/core/xtypes/MemberImpl.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

/**
 * @RTI_class_definition class UnionType : public AbstractConstructedType<UnionMember>
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/UnionType.hpp
 * @brief @st_value_type Represents and IDL \p union type
 */
class OMG_DDS_API UnionTypeImpl : public AbstractConstructedType<UnionMember> {
public:
    typedef AbstractConstructedType<UnionMember> Base;

    /**
     * @brief The type used to set and get discriminator (label) values.
     *
     * Note that this is different from discriminator(), which represents the
     * discriminator type as defined in IDL.
     */
    typedef UnionMember::DiscriminatorType DiscriminatorType;

    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(UnionTypeImpl, Base)

    /**
     * @brief Creates an empty union.
     *
     * Members can be added after creation.
     *
     * @param the_name The name of the type
     * @param discriminator_type The type of the discriminator
     */
    UnionTypeImpl(
        const std::string& the_name,
        const DynamicTypeImpl& discriminator_type)
    {
        initialize(the_name, discriminator_type);
    }

    /**
     * @brief Creates a union with the members in a container.
     *
     * @tparam Container A container that provides the member functions begin()
     * and end() to iterate over UnionMember elements.
     * @param the_name The name of the type
     * @param discriminator_type The type of the discriminator, which can be
     * a primitive type, an EnumType or an AliasType to any of these.
     * @param the_members A container with the members for this union type
     */
    template <typename Container>
    UnionTypeImpl(
        const std::string& the_name,
        const DynamicTypeImpl& discriminator_type,
        const Container& the_members)
    {
        initialize(the_name, discriminator_type);
        add_members(the_members);
    }

    /**
     * @brief Creates a union with the members in an iterator range
     *
     * @tparam MemberIter A forward iterator of UnionMember elements
     * @param the_name The name of the type
     * @param discriminator_type The type of the discriminator
     * @param begin The beginning of the range of UnionMembers
     * @param end The end of the range of UnionMembers
     */
    template <typename MemberIter>
    UnionTypeImpl(
        const std::string& the_name,
        const DynamicTypeImpl& discriminator_type,
        MemberIter begin,
        MemberIter end)
    {
        initialize(the_name, discriminator_type);
        add_members(begin, end);
    }

  #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief Creates a union with the members in an initializer_list
     *
     * @param the_name The name of the type
     * @param discriminator_type The type of the discriminator
     * @param the_members An ininitalizer_list of UnionMembers
     */
    UnionTypeImpl(
        const std::string& the_name,
        const DynamicTypeImpl& discriminator_type,
        std::initializer_list<UnionMember> the_members)
    {
        initialize(the_name, discriminator_type);
        add_members(the_members);
    }
  #endif

    /**
     * @brief Gets the type of the discriminator
     */
    const DynamicTypeImpl& discriminator() const;

    using Base::extensibility_kind; // bring getter hidden by setter
    UnionTypeImpl& extensibility_kind(
        dds::core::xtypes::ExtensibilityKind kind);

    /**
     * @brief Gets the index of the member selected by a label
     *
     * The result of this function can be passed to member(uint32_t).
     *
     * @return The index of the member selected by label or INVALID_INDEX if
     * that label doesn't select any member
     */
    MemberIndex find_member_by_label(DiscriminatorType label) const;

    /**
     * @brief Gets the index of the member with a specific member ID
     *
     * The result of this function can be passed to member(uint32_t).
     *
     * @return The index of the member that has this id or INVALID_INDEX if
     * no member uses that id.
     */
    MemberIndex find_member_by_id(uint32_t id) const;

    /**
     * @brief Add a member to the end of this union
     */
    UnionTypeImpl& add_member(const UnionMember& member);

    /**
     * @brief Adds all the members of a container at the end
     */
    template <typename Container>
    UnionTypeImpl& add_members(const Container& the_members)
    {
        return add_members(the_members.begin(), the_members.end());
    }

  #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief Adds all the members of an initializer_list at the end
     */
    UnionTypeImpl& add_members(std::initializer_list<UnionMember> the_members)
    {
        return add_members(the_members.begin(), the_members.end());
    }
  #endif

    /**
     * @brief Adds all the members in an iterator range at the end
     */
    template <typename MemberIter>
    UnionTypeImpl& add_members(MemberIter begin, MemberIter end)
    {
        for(; begin != end; ++begin) {
            add_member(*begin);
        }
        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief Adds a member, moving it, at the end
     */
    UnionTypeImpl& add_member(UnionMember&& the_member)
    {
        return add_member_impl(the_member, true);
    }
  #endif

private:
    void initialize(
        const std::string& name,
        const DynamicTypeImpl& discriminator_type);
    UnionTypeImpl& add_member_impl(UnionMember& member, bool move);
};

} } } // namespace dds::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_UNIONTYPEIMPL_HPP_
