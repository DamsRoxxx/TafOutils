/*
 Copyright (c) 2014, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_ENUMTYPE_HPP_
#define RTI_DDS_CORE_XTYPES_ENUMTYPE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/vector.hpp>
#include <dds/core/xtypes/DynamicType.hpp>
#include <rti/core/xtypes/MemberImpl.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

/**
 * @RTI_class_definition class EnumType : public AbstractConstructedType<EnunMember>
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/EnumType.hpp
 * @brief @st_value_type Represents and IDL \p enum type
 */
class OMG_DDS_API EnumTypeImpl : public AbstractConstructedType<EnumMemberImpl> {
public:
    typedef AbstractConstructedType<EnumMemberImpl> Base;

    RTI_DEFINE_DEFAULT_MOVE_OPERATIONS(EnumTypeImpl, Base)

    /**
      * @brief Creates an empty enum type
      *
      * Members can be added after creation.
      *
      * @param name The name of the type
      */
     EnumTypeImpl(const std::string& name);

     /**
      * @brief Creates a enum with the members in a container.
      *
      * @tparam Container A container that provides the member functions
      * begin() and end() to iterate over EnumMember elements.
      * @param the_name The name of the type
      * @param the_members A container with the members for this enum type
      */
     template <typename Container>
     EnumTypeImpl(const std::string& the_name, const Container& the_members)
     {
         initialize(the_name);
         add_members(the_members);
     }

     /**
      * @brief Creates a enum with the members in an iterator range
      *
      * @tparam MemberIter A forward iterator of EnumMember elements
      * @param the_name The name of the type
      * @param begin The beginning of the range of EnumMembers
      * @param end The end of the range of EnumMembers
      */
     template <typename MemberIter>
     EnumTypeImpl(const std::string& the_name, MemberIter begin, MemberIter end)
     {
         initialize(the_name);
         add_members(begin, end);
     }

   #ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
     /**
      * @brief Creates a enum with the members in an initializer_list
      *
      * @param the_name The name of the type
      * @param the_members An ininitalizer_list of EnumMembers
      */
     EnumTypeImpl(
         const std::string& the_name, std::initializer_list<EnumMemberImpl> the_members)
     {
         initialize(the_name);
         add_members(the_members);
     }
   #endif

     EnumTypeImpl& extensibility_kind(
         dds::core::xtypes::ExtensibilityKind kind);

    /**
     * @brief Gets the index of the member with this ordinal value
     *
     * @return The index (which can be passed to member(uint32_t) of the member
     * with this ordinal value or INVALID_INDEX if that ordinal doesn't exist
     */
    MemberIndex find_member_by_ordinal(int32_t ordinal) const;

    /**
     * @brief Adds a member at the end
     */
    EnumTypeImpl& add_member(const EnumMemberImpl& member);

    /**
     * @brief Adds all the members of a container at the end
     */
    template<typename Container>
    EnumTypeImpl& add_members(const Container& the_members)
    {
        return add_members(the_members.begin(), the_members.end());
    }

#ifndef RTI_NO_CXX11_HDR_INITIALIZER_LIST
    /**
     * @brief Adds all the members of an initializer_list at the end
     */
    EnumTypeImpl& add_members(std::initializer_list<EnumMemberImpl> the_members)
    {
        return add_members(the_members.begin(), the_members.end());
    }
#endif

    /**
     * @brief Adds all the members in an iterator range at the end
     */
    template<typename MemberIter>
    EnumTypeImpl& add_members(MemberIter begin, MemberIter end)
    {
        for (; begin != end; ++begin) {
            add_member(*begin);
        }
        return *this;
    }

private:
    void initialize(const std::string& name);
};

} } } // namespace rti::core::xtypes

#endif //RTI_DDS_CORE_XTYPES_ENUMTYPE_HPP_
