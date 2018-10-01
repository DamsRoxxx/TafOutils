/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_STRUCTTYPEIMPL_HPP_
#define RTI_DDS_CORE_XTYPES_STRUCTTYPEIMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/xtypes/DynamicTypeImpl.hpp>
#include <rti/core/xtypes/MemberImpl.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

/**
 * @RTI_class_definition class StructType : public AbstractConstructedType<Member>
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/StructType.hpp
 * @brief @st_value_type Represents and IDL \p struct type
 */
class OMG_DDS_API StructTypeImpl : public AbstractConstructedType<MemberImpl> {
public:
    typedef AbstractConstructedType<MemberImpl> Base;
    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(StructTypeImpl, Base)

    /**
     * @brief Creates an empty struct type
     *
     * The struct doesn't have a base type. Members can be added after
     * creation.
     *
     * @param name The name of the type
     */
    StructTypeImpl(const std::string& name);

    /**
     * @brief Creates an empty struct type with a base type.
     *
     * Members can be added after creation.
     *
     * @param name The name of the type
     * @param parent The base type
     */
    StructTypeImpl(const std::string& name, const StructTypeImpl& parent);

    /**
     * @brief Creates a struct with the members in a container.
     *
     * The struct doesn't have a base type.
     *
     * @tparam Container A container that provides the member functions
     * begin() and end() to iterate over Member elements.
     * @param the_name The name of the type
     * @param the_members A container with the members for this struct type
     */
    template <typename Container>
    StructTypeImpl(const std::string& the_name, const Container& the_members)
    {
        initialize(the_name);
        add_members(the_members);
    }

    /**
     * @brief Creates a struct with a base type and the members in a container.
     *
     * @tparam Container A container that provides the member functions
     * begin() and end() to iterate over Member elements.
     * @param the_name The name of the type 
     * @param the_parent The base type
     * @param the_members A container with the members for this struct type
     */
    template <typename Container>
    StructTypeImpl(
        const std::string& the_name,
        const StructTypeImpl& the_parent,
        const Container& the_members)
    {
        initialize(the_name, &the_parent);
        add_members(the_members);
    }

    /**
     * @brief Creates a struct with the members in an iterator range
     *
     * The struct doesn't have a base type.
     *
     * @tparam MemberIter A forward iterator of Member elements
     * @param the_name The name of the type
     * @param begin The beginning of the range of Members
     * @param end The end of the range of Members
     */
    template <typename MemberIter>
    StructTypeImpl(const std::string& the_name, MemberIter begin, MemberIter end)
    {
        initialize(the_name);
        add_members(begin, end);
    }

    /**
     * @brief Creates a struct with a base type and the members in an iterator range
     *
     * @tparam MemberIter A forward iterator of Member elements
     * @param the_parent The base type
     * @param the_name The name of the type
     * @param begin The beginning of the range of Members
     * @param end The end of the range of Members
     */
    template <typename MemberIter>
    StructTypeImpl(
        const std::string& the_name,
        const StructTypeImpl& the_parent,
        MemberIter begin,
        MemberIter end)
    {
        initialize(the_name, &the_parent);
        add_members(begin, end);
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates an empty struct type with a base type.
     *
     * The base type is moved. This is useful to save a copy in situations like
     * the following example:
     * \code
     * StrucType my_type("my_type", StructType("parent_type", parent_members));
     * \endcode
     *
     */
    StructTypeImpl(const std::string& the_name, StructTypeImpl&& the_parent)
    {
        initialize(the_name, &the_parent, false);
    }

    /**
     * @brief @st_cpp11 Creates an empty struct type with a base type
     * and the members in an iterator range.
     *
     * The base type is moved.
     */
    template <typename MemberIter>
    StructTypeImpl(
        const std::string& the_name,
        StructTypeImpl&& the_parent,
        MemberIter begin,
        MemberIter end)
    {
        initialize(the_name, &the_parent, false);
        add_members(begin, end);
    }

    /**
     * @brief @st_cpp11 Creates an empty struct type with a base type
     * and the members in a container.
     *
     * The base type is moved.
     */
    template <typename Container>
    StructTypeImpl(
        const std::string& the_name,
        StructTypeImpl&& the_parent,
        const Container& the_members)
    {
        initialize(the_name, &the_parent, false);
        add_members(the_members);
    }
  #endif

  #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief @st_cpp11 Creates a struct with the members in an initializer_list
     *
     * @param the_name The name of the type
     * @param the_members An ininitalizer_list of Members
     */
    StructTypeImpl(
        const std::string& the_name, std::initializer_list<MemberImpl> the_members)
    {
        initialize(the_name);
        add_members(the_members);
    }

    /**
     * @brief @st_cpp11 Creates a struct with the members in an initializer_list
     * and a base type
     *
     * @param the_name The name of the type
     * @param the_parent The base type
     * @param the_members An ininitalizer_list of Members
     */
    StructTypeImpl(
        const std::string& the_name,
        const StructTypeImpl& the_parent,
        std::initializer_list<MemberImpl> the_members)
    {
        initialize(the_name, &the_parent);
        add_members(the_members);
    }

   #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates a struct with the members in an initializer_list
     * and a base type
     *
     * @param the_name The name of the type
     * @param the_parent The base type (moved)
     * @param the_members An ininitalizer_list of Members
     */
    StructTypeImpl(
        const std::string& the_name,
        StructTypeImpl&& the_parent,
        std::initializer_list<MemberImpl> the_members)
    {
        initialize(the_name, &the_parent, false);
        add_members(the_members);
    }
   #endif
  #endif

    using Base::extensibility_kind; // bring getter hidden by setter

    /**
     * @brief Sets the type extensibility kind
     */
    StructTypeImpl& extensibility_kind(
        dds::core::xtypes::ExtensibilityKind kind);

    /**
     * @brief Indicates if this type has a base type
     */
    bool has_parent() const;

    /**
     * @brief Retrieves the base type
     *
     * If this type doesn't have a base type it throws PreconditionNotMetError.
     *
     * @see has_parent()
     */
    const StructTypeImpl& parent() const;

    /**
     * @brief Gets the index of the member with a specific member ID
     *
     * @return The index (which can be passed to member(uint32_t) of the member
     * selected by label or INVALID_INDEX if the ID doesn't exist in this type
     */
    MemberIndex find_member_by_id(uint32_t id) const;

    /**
     * @brief Adds a member at the end
     */
    StructTypeImpl& add_member(const MemberImpl& member);

    /**
     * @brief Adds all the members of a container at the end
     */
    template <typename Container>
    StructTypeImpl& add_members(const Container& the_members)
    {
        return add_members(the_members.begin(), the_members.end());
    }

  #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief @st_cpp11 Adds all the members of an initializer_list at the end
     */
    StructTypeImpl& add_members(std::initializer_list<MemberImpl> the_members)
    {
        return add_members(the_members.begin(), the_members.end());
    }
  #endif

    /**
     * @brief Adds all the members in an iterator range at the end
     */
    template <typename MemberIter>
    StructTypeImpl& add_members(MemberIter begin, MemberIter end)
    {
        for(; begin != end; ++begin) {
            add_member(*begin);
        }
        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Adds a member, moving it, at the end
     */
    StructTypeImpl& add_member(MemberImpl&& the_member)
    {
        return move_member_impl(the_member);
    }
  #endif

private:
    void initialize(
        const std::string& name,
        const StructTypeImpl * parent = NULL,
        bool clone_parent = true);
    StructTypeImpl& move_member_impl(MemberImpl& member);
};

} } } // namespace dds::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_STRUCTTYPEIMPL_HPP_
