/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_XTYPES_DYNAMICDATA_HPP_
#define RTI_DDS_CORE_XTYPES_DYNAMICDATA_HPP_

#include <vector>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_dynamicdata.h"
#include "dds_c/dds_c_dynamicdataformatter.h"
#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/xtypes/DynamicType.hpp>

#include <dds/topic/TopicTraits.hpp>
#include <dds/domain/domainfwd.hpp>

#include <rti/core/NativeValueType.hpp>
#include <rti/core/xtypes/DynamicDataProperty.hpp>
#include <rti/core/xtypes/DynamicDataInfo.hpp>
#include <rti/core/xtypes/DynamicDataMemberInfo.hpp>
#include <rti/core/LongDouble.hpp>
#include <rti/topic/cdr.hpp>
#include <rti/topic/PrintFormat.hpp>

/** @RTI_namespace_start dds::core::xtypes */
namespace rti { namespace core { namespace xtypes {

class DynamicDataImpl;
class LoanedDynamicData;
#if !defined(RTI_CXX11_RVALUE_REFERENCES)
struct MoveConstructProxy;
#endif

} // namespace xtypes

class DynamicDataNativeAdapter {
public:

    typedef DDS_DynamicData native_type;

    static void initialize(native_type&)
    {
        // nothing to do -- default construction is not available
    }

    static void finalize(native_type& native_value)
    {
        DDS_DynamicData_finalize(&native_value);
    }

    static OMG_DDS_API void copy(native_type& destination, const native_type& source);

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_DynamicData_equal(&first, &second) == DDS_BOOLEAN_TRUE;
    }
};

template <>
struct native_type_traits<xtypes::DynamicDataImpl> {
    typedef DynamicDataNativeAdapter adapter_type;
    typedef DynamicDataNativeAdapter::native_type native_type;
};

namespace xtypes {

class LoanedDynamicData;

/**
 * @RTI_class_definition class DynamicData
 * @ingroup DDSXTypesModule
 * @headerfile dds/core/xtypes/DynamicData.hpp
 * @brief @st_value_type A data sample of any complex data type, which can be
 * inspected and manipulated reflectively.
 *
 * DynamicData allows manipulating a data sample whose type is unknown at compilation
 * time. A DynamicData object is created by passing its DynamicType, which can
 * be a StructType, a UnionType, ArrayType, SequenceType or AliasType. DynamicData
 * is a valid topic-type, so you can instantiate a Topic<DynamicData> (using
 * \link dds::topic::Topic::Topic(const dds::domain::DomainParticipant&, const std::string&, const dds::core::xtypes::DynamicType&)
 * the constructor that receives a DynamicType\endlink), and then a
 * DataReader<DynamicData> or a DataWriter<DynamicData>.
 *
 * Several overloaded versions of the function value() allow reading or writing the
 * value of a member \ref DDSDynamicDataModule_member_name_id "by name or index".
 * Another set of functions, loan_value(),
 * can access a non-primitive member (for reading and writing) without making a copy.
 * For primitive arrays and sequences DynamicData also provides a way to get or set all
 * the values at once, using set_values() and get_values().
 *
 * A number of other functions allow querying information about the sample and
 * its type.
 *
 * Applications that use both statically typed data and DynamicData can benefit
 * from the conversion between them, using rti::core::xtypes::convert().
 *
 * For examples on how to use DynamicData, see \ref DDSXTypesExampleModule_dynamic_data.
 *
 * @section DDSDynamicDataModule_member_name_id Member Names and Indexes
 *
 * As mentioned before, to access a member you need to specify its name or its
 * index. Depending on the DynamicType of the DynamicData sample, the name
 * may apply or not and the index can mean different things. This table summarizes
 * that:
 *
 * | DynamicType of the sample | Can access by name?| What does index mean?
 * | ------------------------- | ------------------ | ----------------------------
 * | StructType                | Yes                | The position of the member in the type (starting at 1)
 * | UnionType                 | Yes                | The value of the label that selects a member, see discriminator_value()
 * | ArrayType                 | No                 | The position of the element in the array (1 to ArrayType::total_element_count())
 * | SequenceType              | No                 | The position of the element in the sequence (1 to member_count()) or past member_count() to increase the length of the sequence.
 * | Any other type            | N/A                | N/A
 *
 * For example, given the following IDL description of a type:
 *
 * \code
 * struct Foo {
 *     long x;
 *     long y;
 * };
 * \endcode
 *
 * If we have a DynamicData \p sample representing data of that type, we can
 * access the member \p y in two different ways:
 *
 * \code
 * sample.value("y", 33); // Set value to 33
 * sample.value(2, 33); // Same effect
 * \endcode
 *
 * Accessing a member by index can be more efficient, so when accessing a member
 * repeatedly it may be beneficial to obtain its index first:
 *
 * \code
 * const uint32_t y_index = sample.member_index("y");
 * while (...) {
 *     int32_t y_value = sample.value<int32_t>(y_index);
 *     // ...
 * }
 * \endcode
 *
 * For an example on how to access a union member, see discriminator_value(),
 * and for more examples, including how to access elements in a collection see
 * \ref DDSXTypesExampleModule_dynamic_data.
 *
 *
 * @section DDSDynamicDataModule_exceptions Exceptions accessing a member
 *
 * The different DynamicData functions that access members may throw the
 * following exceptions:
 *
 * - dds::core::InvalidArgumentError when attempting to <strong>get</strong>
 *   the value a member that doesn't exist in the type, is optional and is not set,
 *   or is part of a union and not currently selected (see discriminator_value).
 *   Attempting to <strong>set</strong> an unset optional member or an unselected
 *   union member is legal and will set the optional member or change the
 *   active union member.
 *
 * - dds::core::IllegalOperationError when attempting to get or set a member
 *   of the wrong type--that is, when the DynamicType of that member doesn't
 *   match the template type \p T of the function. For example assumming that
 *   \p my_string_member is a string, the two following statements are illegal:
 *   \code
 *   data.value("my_string_member", 3);
 *   int v = data.value<int>("my_string_member");
 *   \endcode
 *
 * @see \ref DDSXTypesExampleModule_dynamic_data
 */
class OMG_DDS_API DynamicDataImpl : public NativeValueType<DynamicDataImpl> {
public:
    typedef NativeValueType<DynamicDataImpl> Base;

    /**
     * @brief Creates a DynamicData instance for a type.
     *
     * Uses default DynamicDataProperty.
     *
     * @pre !is_primitive(type) -- a DynamicData object cannot encapsulate
     * a primitive type.
     *
     * @param type The type of this data sample
     */
    DynamicDataImpl(const dds::core::xtypes::DynamicType& type);

    /**
     * @brief Creates a DynamicData instance for a type with specific
     * memory-management
     *
     * @pre !is_primitive(type) -- a DynamicData object cannot encapsulate
     * a primitive type.
     *
     * @param type The type of this data sample
     * @param property Memory-management configuration
     */
    DynamicDataImpl(
        const dds::core::xtypes::DynamicType& type,
        const DynamicDataProperty& property);

    DynamicDataImpl(const DynamicDataImpl& other);

  #if defined(RTI_CXX11_RVALUE_REFERENCES)
    // We would use defaulted functions if all compilers supported it:
    //
    // DynamicDataImpl(DynamicDataImpl&& other) = default;
    // DynamicDataImpl& operator=(DynamicDataImpl&& other) = default;
    //
    // But since they don't:
    //
    DynamicDataImpl(DynamicDataImpl&& other) OMG_NOEXCEPT
        : Base(std::move(other))
    {
    }

    DynamicDataImpl& operator=(DynamicDataImpl&& other) OMG_NOEXCEPT
    {
        Base::operator=(std::move(other));
        return *this;
    }
  #endif

    DynamicDataImpl& operator=(const DynamicDataImpl& other)
    {
        NativeValueType<DynamicDataImpl>::operator=(other);
        return *this;
    }

    // --- Getters and setters: -----------------------------------------------

    /**
     * @brief Sets the value of a member by member name
     *
     * @tparam T The type of the member to set. The possible types are:
     * those accepted by PrimitiveType, std::string or dds::core::string,
     * and DynamicData.
     *
     * For examples on how to set member values, see
     * \ref DDSXTypesExampleModule_dynamic_data_publication.
     *
     * If the member is optional and unset, this function will set it. To unset
     * it again, see clear_optional_member().
     *
     * Note that it is not always possible to rely on inferring the type \p T based
     * on the argument \p v. For example, if the member being set is a short,
     * this statement will throw an exception, because \p T is deduced as \p int:
     * \code
     * sample.value("my_short", 10);
     * \endcode
     *
     * To solve this problem we have two options:
     * \code
     * sample.value<short>("my_short", 10);
     * sample.value("my_short", (short) 10);
     * \endcode
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     * This function also allows to access nested members
     * @param v The value to set for that member
     *
     * @throw See \ref DDSDynamicDataModule_exceptions
     *
     * @see member_exists(const std::string&) const
     * @see \ref DDSXTypesExampleModule_dynamic_data_publication
     */
    template <typename T>
    void value(const std::string& name, const T& v);

    /**
     * @brief Sets the value of a member by member index
     *
     * @param index The position of the member in the type,
     * see \ref DDSDynamicDataModule_member_name_id.
     * @param v The value to set for that member
     *
     * @throw See \ref DDSDynamicDataModule_exceptions
     *
     * @see value(const std::string&, const T&)
     * @see \ref DDSDynamicDataModule_member_name_id
     */
    template <typename T>
    void value(uint32_t index, const T& v);

    /**
     * @brief Gets the value of a member by member name
     *
     * @tparam T The type of the member. See value(const std::string&, const T&)
     *
     * For examples on how to get member values, see
     * \ref DDSXTypesExampleModule_dynamic_data_subscription.
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     * @return The value of that member
     *
     * @throw See \ref DDSDynamicDataModule_exceptions
     *
     * @see value(const std::string&, const T&)
     * @see \ref DDSXTypesExampleModule_dynamic_data_subscription
     */
    template <typename T>
    T value(const std::string& name) const;

    /**
     * @brief Gets the value of a member by member index
     *
     * @tparam T The type of the member. See value(const std::string&, const T&)
     *
     * For examples on how to get member values, see
     * \ref DDSXTypesExampleModule_dynamic_data_subscription.
     *
     * @param index The position of the member in the type,
     * see \ref DDSDynamicDataModule_member_name_id.
     * @return The value of that member
     *
     * @throw See \ref DDSDynamicDataModule_exceptions
     *
     * @see value(const std::string&, const T&)
     * @see \ref DDSDynamicDataModule_member_name_id
     */
    template <typename T>
    T value(uint32_t index) const;

    /**
     * @brief Obtains the values of an array or sequence member by member name
     *
     * This function reuses an existing vector
     *
     * @tparam T The element type of the array or sequence. These are the possible types:
     * char, (u)int8_t, (u)int16_t, DDS_Long, DDS_UnsignedLong, DDS_LongLong,
     * DDS_UnsignedLongLong, float, double. The types int and unsigned int may
     * be used instead of DDS_Long and DDS_UnsignedLong except in some platforms
     * (VxWorks).
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     * @param out_array A vector containing the values of that array or sequence.
     * The vector will be resized accordingly.
     */
    template <typename T>
    void get_values(const std::string& name, std::vector<T>& out_array) const;

    /**
     * @brief Obtains the values of an array or sequence member by member index
     *
     * This function reuses an existing vector
     *
     * @tparam T The element type of the array or sequence.
     *
     * @param index The position of the array or sequence member in the type,
     * see \ref DDSDynamicDataModule_member_name_id.
     * @param out_array A vector containing the values of that array or sequence.
     * The vector will be resized accordingly.
     *
     * @see \ref DDSDynamicDataModule_member_name_id
     * @see get_values(const std::string& name, std::vector<T>& out_array) const
     */
    template <typename T>
    void get_values(uint32_t index, std::vector<T>& out_array) const;

    /**
     * @brief Obtains the values of an array or sequence member by member index
     *
     * This function returns a new vector.
     *
     * @tparam T The element type of the array or sequence
     *
     * @param index The position of the array or sequence member in the type
     * @return A vector containing the values of that array or sequence.
     *
     * @see \ref DDSDynamicDataModule_member_name_id
     * @see get_values(const std::string& name, std::vector<T>& out_array) const
     */
    template <typename T>
    std::vector<T> get_values(uint32_t index) const;

    /**
     * @brief Obtains the values of an array or sequence member by member name
     *
     * This function returns a new vector.
     *
     * @tparam T The element type of the array or sequence
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     * @return A vector containing the values of that array or sequence.
     *
     * @see get_values(const std::string& name, std::vector<T>& out_array) const
     */
    template <typename T>
    std::vector<T> get_values(const std::string& name) const;

    /**
     * @brief Sets the values of an array or sequence member by member index
     *
     * @tparam T The element type of the array or sequence
     *
     * @param index The position of the array or sequence member in the type
     * @param v A vector containing the values to be set for that array or sequence.
     *
     * @see \ref DDSDynamicDataModule_member_name_id
     * @see get_values(const std::string& name, std::vector<T>& out_array) const
     */
    template <typename T>
    void set_values(uint32_t index, const std::vector<T>& v);

    /**
     * @brief Sets the values of an array or sequence member by member name
     *
     * @tparam T The element type of the array or sequence.
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     * @param v A vector containing the values to be set for that array or sequence.
     *
     * @see get_values(const std::string& name, std::vector<T>& out_array) const
     */
    template <typename T>
    void set_values(const std::string& name, const std::vector<T>& v);

    /**
     * @brief Gets a view of a complex member
     *
     * This function returns a new LoanedDynamicData instance.
     *
     * Only a single member of a given DynamicData object may be loaned
     * at a time. However, members of members may be recursively loaned
     * to any depth. Furthermore, while the outer object has a bound member, it
     * may only be modified through that bound member. That is, after loaning
     * this member, the outer object disables all calls to set value() until
     * the loan is returned.
     *
     * This method, as opposed to value<DynamicData>() doesn't make a copy;
     * it provides a view of the member so changes to the loaned member change
     * the outer object.
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     * @return The object to access the complex member
     *
     * @see rti::core::xtypes::LoanedDynamicData
     * @see \ref DDSXTypesExampleModule_dynamic_data.
     */
    LoanedDynamicData loan_value(const std::string& name);

    /**
     * @brief Gets a view of a complex member
     *
     * This function returns a new LoanedDynamicData instance.
     *
     *
     * @param index The position of the member in the type,
     * see \ref DDSDynamicDataModule_member_name_id.
     * @return The object to access the complex member
     *
     * @see loan_value(const std::string&)
     * @see rti::core::xtypes::LoanedDynamicData
     * @see \ref DDSDynamicDataModule_member_name_id
     */
    LoanedDynamicData loan_value(uint32_t index);


    /**
     * @brief Gets a view of a complex member
     *
     * This function reuses a LoanedDynamicData instance, returning its previous loan.
     *
     * @param data The object to access the complex member
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     *
     * @see loan_value(const std::string&)
     * @see rti::core::xtypes::LoanedDynamicData
     */
    LoanedDynamicData& loan_value(LoanedDynamicData& data, const std::string& name);

    /**
     * @brief Gets a view of a complex member
     *
     * This function reuses a LoanedDynamicData instance, returning its previous loan.
     *
     * @param data The object to access the complex member
     * @param mid The position of the member in the type,
     * see \ref DDSDynamicDataModule_member_name_id.
     *
     * @see loan_value(const std::string&)
     * @see rti::core::xtypes::LoanedDynamicData
     */
    LoanedDynamicData& loan_value(LoanedDynamicData& data, uint32_t mid);

    /**
     * @brief Obtains the value of the union discriminator (UnionType only)
     *
     * Use the value that this function returns in any function expecting a
     * member index to access the active member in this union.
     *
     * For example, given the following IDL Union:
     * \code
     * union Foo switch (short) {
     * case 1:
     *     long x;
     * case 2:
     * case 3:
     *     string y;
     * };
     * \endcode
     *
     * If we have a DynamicData \p sample of that type whose active member is
     * "y", we can access it as follows:
     *
     * \code
     * std::string y_value = sample.value<std::string>(sample.discriminator_value());
     * y_value = sample.value<std::string>("y"); // Same effect
     * y_value = sample.value<std::string>(3); // Same effect
     * \endcode
     *
     * If you set a different member, the discriminator value automatically
     * changes:
     *
     * \code
     * sample.value("x", 10);
     * assert (sample.discriminator_value() == 1);
     * \endcode
     *
     * @pre type().kind() == TypeKind::UNION_TYPE -- Only applies to samples
     * of a UnionType.
     *
     * @return The value of this sample's discriminator.
     */
    uint32_t discriminator_value() const;

    // ------------------------------------------------------------------------

    /**
     * @brief Clear the contents of all data members of this object, including
     * key members.
     * @details \dref_details_DynamicData_clear_all_members
     */
    void clear_all_members();

    /**
     * @brief Clear the contents of a single optional data member of this object.
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     */
    void clear_optional_member(const std::string& name);

    /**
     * @brief Clear the contents of a single optional data member of this object.
     *
     * @param index The position of the member in the type,
     * see \ref DDSDynamicDataModule_member_name_id.
     */
    void clear_optional_member(uint32_t index);

    void compact();

    /**
     * @brief Associate a buffer with this dynamic data object.
     *
     * @details \dref_details_DynamicData_set_buffer
     */
    void set_buffer(uint8_t * storage, int32_t size);

    /**
     * @brief Get the estimated maximum buffer size for a DynamicData object.
     *
     * @details \dref_details_DynamicData_get_estimated_max_buffer_size
     */
    int32_t estimated_max_buffer_size() const;
    void ensure_buffer_size(int32_t required_size);

    // Data-type queries

    /**
     * @brief Gets the data type of this DynamicData
     */
    const dds::core::xtypes::DynamicType& type() const;

    /**
     * @brief Gets the data type kind of this DynamicData
     *
     * @return this->type().kind().
     */
    dds::core::xtypes::TypeKind type_kind() const;

    /**
     * @brief Get the number of members in this sample
     *
     * For objects of type ArrayType or SequenceType, this method returns the
     * number of elements in the collection.
     *
     * For objects of type kind StructType, it returns the number of fields in
     * the sample, which will always be the same as the number of fields in the
     * type.
     */
    uint32_t member_count() const;

    /**
     * @brief Determines if an optional member is set by member name
     *
     * For a non-optional member this function always returns the same result
     * as member_exists_in_type().
     */
    bool member_exists(const std::string& name) const;

    /**
     * @brief Determines if an optional member is set by member index
     *
     * For a non-optional member this function always returns the same result
     * as member_exists_in_type().
     */
    bool member_exists(uint32_t index) const;

    /**
     * @brief Indicates whether a member with a particular name exists in type()
     */
    bool member_exists_in_type(const std::string& name) const;

    /**
     * @brief Indicates whether a member of a particular index exists in type()
     */
    bool member_exists_in_type(uint32_t index) const;

    /**
     * @brief Returns information about this sample.
     */
    DynamicDataInfo info() const;

    /**
     * @brief Returns information about a member.
     *
     * @param name The member name.
     * @return Information about the member.
     * @throw See \ref DDSDynamicDataModule_exceptions
     */
    DynamicDataMemberInfo member_info(const std::string& name) const;

    /**
     * @brief Returns information about a member.
     *
     * @param index The member index, see \ref DDSDynamicDataModule_member_name_id.
     * @return Information about the member.
     * @throw See \ref DDSDynamicDataModule_exceptions
     */
    DynamicDataMemberInfo member_info(uint32_t index) const;

    /**
     * @brief Translates from member name to member index
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     * @return The member index for the member with that name
     * @throw See \ref DDSDynamicDataModule_exceptions
     */
    uint32_t member_index(const std::string& name) const; // standard

    /**
     * @brief Returns whether a member is a key
     *
     * @param name The member name, see \ref DDSDynamicDataModule_member_name_id.
     *
     * @throw See \ref DDSDynamicDataModule_exceptions
     */
    bool is_member_key(const std::string& name) const;

    /**
     * @brief Returns whether a member is a key
     *
     * @param index The member index, see \ref DDSDynamicDataModule_member_name_id.
     *
     * @throw See \ref DDSDynamicDataModule_exceptions
     */
    bool is_member_key(uint32_t index) const;

private:
    friend class LoanedDynamicData; // allow default construction
  #if !defined(RTI_CXX11_RVALUE_REFERENCES)
    friend struct MoveConstructProxy;
  #endif

    DynamicDataImpl();
    void initialize(const dds::core::xtypes::DynamicType& type);
};

/**
 * @relatesalso DynamicData
 */
OMG_DDS_API
std::ostream& operator<<(std::ostream& out, const DynamicDataImpl& data);

// ----------------------------------------------------------------------------

} } } // close and reopen for documentation purposes

namespace rti { namespace core { namespace xtypes {

#if !defined(RTI_CXX11_RVALUE_REFERENCES)
// Enables the safe-move-constructor idiom without C++11 move constructors
struct MoveConstructProxy {
    MoveConstructProxy(LoanedDynamicData& object);
    DynamicDataImpl data;
    DynamicDataImpl * parent;
    bool loaned;
};
#endif

void swap(LoanedDynamicData& a, LoanedDynamicData& b) OMG_NOEXCEPT;

/**
 * @ingroup DDSXTypesModule
 * @brief @st_move_type Gives temporary access to a member of another
 * DynamicData object.
 *
 * This type can only be instantiated through
 * dds::core::xtypes::DynamicData::loan_value.
 * This type can't be copied. It can be moved @st_cpp11.
 *
 * An instance of this type contains a direct reference to a member of another
 * DynamicData object, retrieved with get(). That object can be both inspected
 * or modified and has to be eventually returned.
 *
 * There are three ways to return the loan:
 * -# Letting the destructor do it
 * -# Calling return_loan()
 * -# Reusing this object to obtain another loan (see
 *    dds::core::xtypes::DynamicData::loan_value(LoanedDynamicData&,uint32_t))
 *
 * @see dds::core::xtypes::DynamicData::loan_value
 * @see \ref DDSXTypesExampleModule_dynamic_data
 */
class OMG_DDS_API LoanedDynamicData {
private:
    LoanedDynamicData(DynamicDataImpl * parent, uint32_t mid);
    LoanedDynamicData(DynamicDataImpl * parent, const std::string& mid);

    friend class DynamicDataImpl; // only class allowed to create LoanedDynamicData
    friend void swap(LoanedDynamicData& a, LoanedDynamicData& b) OMG_NOEXCEPT;

public:
    /**
     * @brief Returns the loan if it has not been returned with
     * return_loan()
     */
    ~LoanedDynamicData();

    /**
     * @brief Explicitly returns the loan
     */
    void return_loan();

    /**
     * @brief Obtains the loaned DynamicData object representing a member of
     * DynamicData object.
     *
     * The object can be modified and the changes will take effect in the
     * DynamicData object that contains this one.
     */
    DynamicDataImpl& get()
    {
        return data_;
    }

    /**
     * @brief Obtains the loaned DynamicData object representing a member of
     * DynamicData object.
     */
    const DynamicDataImpl& get() const
    {
        return data_;
    }

    /**
     * @brief Conversion to DynamicData for convenience
     */
    operator DynamicDataImpl&()
    {
        return data_;
    }

    /**
     * @brief Conversion to DynamicData for convenience
     */
    operator const DynamicDataImpl&() const
    {
        return data_;
    }

#if !defined(RTI_CXX11_RVALUE_REFERENCES)
    friend struct MoveConstructProxy;

    // Enables the safe-move-constructor idiom without C++11 move constructors
    LoanedDynamicData(MoveConstructProxy proxy) throw()
        : parent_(proxy.parent), loaned_(proxy.loaned)
    {
        swap(data_, proxy.data);
    }

    LoanedDynamicData& operator= (MoveConstructProxy proxy) throw ()
    {
        // copy-and-swap idiom: copy new value, use temp's destructor to
        // clean up existing values
        LoanedDynamicData temp(proxy);
        swap(*this, temp);
        return *this;
    }

    operator MoveConstructProxy() throw()
    {
        return MoveConstructProxy(*this);
    }

private:
    // Copy disabled
    LoanedDynamicData(LoanedDynamicData &);
    LoanedDynamicData& operator= (const LoanedDynamicData&);

#endif


#if defined(RTI_CXX11_RVALUE_REFERENCES) || defined(DOXYGEN_DOCUMENTATION_ONLY)
    // Move constructor
    // (defining move ctor disables default copy constructor automatically)
    LoanedDynamicData(LoanedDynamicData&& other) OMG_NOEXCEPT
        : data_ (std::move(other.data_)),
          parent_ (other.parent_),
          loaned_ (other.loaned_)
    {
        other.loaned_ = false;
    }

    /**
     * @brief @st_cpp11 Allows reusing a LoanedDynamicData instance.
     *
     * Since copying a LoanedDynamicData is disabled, only the move-assignment
     * operator is allowed.
     *
     * This operation returns the loan that \p *this currently holds.
     *
     * For example:
     * \code
     * LoanedDynamicData member = sample.loan_value(1);
     * member = sample.loan_value(2);
     * \endcode
     *
     * @see dds::core::xtypes::DynamicData::loan_value(LoanedDynamicData&, const std::string&)
     */
    LoanedDynamicData& operator= (LoanedDynamicData&& other) OMG_NOEXCEPT
    {
        // copy-and-swap idiom: copy new value, use temp's destructor to
        // clean up existing values
        LoanedDynamicData temp(std::move(other));
        swap(*this, temp);
        return *this;
    }
#endif // !defined(RTI_CXX11_RVALUE_REFERENCES)

private:

    DynamicDataImpl data_;
    DynamicDataImpl * parent_;
    bool loaned_;
};

#if !defined(RTI_CXX11_RVALUE_REFERENCES)
inline MoveConstructProxy::MoveConstructProxy(LoanedDynamicData& object)
    : parent(object.parent_), loaned(object.loaned_)
{
    swap(data, object.data_);
    object.loaned_ = false; // the content has been transferred to the proxy
}
#endif

// --- Standalone functions: --------------------------------------------------

/**
 * @relatesalso dds::core::xtypes::DynamicData
 * @brief @extension Serializes a DynamicData sample into CDR format
 *
 * @param buffer The output buffer, which will be resized to the correct size
 * @param sample The sample to serialize
 * @return A reference to \p buffer
 */
OMG_DDS_API
std::vector<char>& to_cdr_buffer(
    std::vector<char>& buffer, const DynamicDataImpl& sample);

/**
 * @relatesalso dds::core::xtypes::DynamicData
 * @brief @extension Creates a DynamicData sample by deserializing a CDR buffer'
 *
 * @param sample The sample to deserialize.
 * @param buffer The buffer containing the CDR data
 * @return A reference to \p sample
 *
 */
OMG_DDS_API
DynamicDataImpl& from_cdr_buffer(
    DynamicDataImpl& sample, const std::vector<char>& buffer);

/**
 * @relatesalso dds::core::xtypes::DynamicData
 *
 * @brief @extension Creates a typed sample from a DynamicData sample.
 *
 * This function is useful when an application uses DynamicData and regular
 * typed Topics at the same time.
 *
 * For example, given this IDL type:
 *
 * \code
 * struct Foo {
 *     long x;
 * };
 * \endcode
 *
 * We can convert from \p Foo and \p DynamicData:
 *
 * \code
 * using dds::core::xtypes::DynamicData;
 *
 * // Receive a DynamicData sample
 * dds::sub::DataReader<DynamicData> reader = // ...;
 * dds::sub::LoanedSamples<DynamicData> samples = reader.take();
 * assert (samples.size() > 0);
 *
 * // Create a Foo sample
 * const DynamicData& dynamic_data = samples[0].data();
 * assert (can_convert<Foo>(dynamic_data));
 * Foo typed_data = convert<Foo>(dynamic_data);
 * assert (typed_data.x() == dynamic_data.value<int32_t>("x"));
 * \endcode
 *
 *
 * @pre can_convert<TopicType>(sample), otherwise the behavior is undefined.
 *
 * @tparam TopicType An IDL topic-type
 * @param sample The DynamicData sample to convert to type \p TopicType
 * @return An instance of \p TopicType containing the data in \p sample.
 */
template <typename TopicType>
TopicType convert(const DynamicDataImpl& sample)
{
    OMG_DDS_STATIC_ASSERT(
        (dds::topic::is_topic_type<TopicType>::value),
        "Type TopicType must be a DDS topic type");

    std::vector<char> tmp_buffer;
    return rti::topic::from_cdr_buffer<TopicType>(
            to_cdr_buffer(tmp_buffer, sample));
}


/**
 * @relatesalso dds::core::xtypes::DynamicData
 *
 * @brief @extension Creates a DynamicData sample from a typed sample
 *
 * @tparam TopicType An IDL topic-type
 * @param sample The typed sample to convert to DynamicData
 * @return A new DynamicData object whose type is
 * rti::topic::dynamic_type<TopicType> and contains the data from \p sample
 */
template <typename TopicType>
DynamicDataImpl convert(const TopicType& sample)
{
    OMG_DDS_STATIC_ASSERT(
        (dds::topic::is_topic_type<TopicType>::value),
        "Type TopicType must be a DDS topic type");

    std::vector<char> tmp_buffer;
    DynamicDataImpl result(rti::topic::dynamic_type<TopicType>::get());
    rti::topic::to_cdr_buffer(tmp_buffer, sample);
    return from_cdr_buffer(result, tmp_buffer);
}

/**
 * @relatesalso dds::core::xtypes::DynamicData
 * @brief @extension Determines if the DynamicType of this sample is equal to the
 * DynamicType of \p TopicType
 *
 * @tparam TopicType An IDL topic-type
 *
 * @return True if the DynamicType of TopicType is the same as this sample's
 * and therefore it is possible to create an instance of \p TopicType from this
 * DynamicData object.
 *
 * @see convert()
 */
template <typename TopicType>
bool can_convert(const DynamicDataImpl& sample)
{
    OMG_DDS_STATIC_ASSERT(
        (dds::topic::is_topic_type<TopicType>::value),
        "Type TopicType must be a DDS topic type");

    return sample.type() == rti::topic::dynamic_type<TopicType>::get();
}

inline void swap(LoanedDynamicData& a, LoanedDynamicData& b) OMG_NOEXCEPT
{
    swap(a.data_, b.data_);
    std::swap(a.parent_, b.parent_);
    std::swap(a.loaned_, b.loaned_);
}

OMG_DDS_API
std::ostream& to_string(
    std::ostream& out,
    const DynamicDataImpl& sample,
    const rti::topic::PrintFormatProperty& format = rti::topic::PrintFormatProperty::Default());

OMG_DDS_API
std::string to_string(
    const DynamicDataImpl& sample,
    const rti::topic::PrintFormatProperty& format = rti::topic::PrintFormatProperty::Default());

} } } // namespace rti::core::xtypes

namespace dds { namespace topic {

template<>
struct topic_type_name<rti::core::xtypes::DynamicDataImpl> {
    // Empty.
    // cannot retrieve the type name at compile type--different DynamicData
    // instances may have different type names.
};

template<>
struct is_topic_type<rti::core::xtypes::DynamicDataImpl> {
    enum {
        value = 1
    };
};

template<>
struct OMG_DDS_API topic_type_support<rti::core::xtypes::DynamicDataImpl> {
    static void register_type(
        dds::domain::DomainParticipant& participant,
        const std::string& type_name);

    static void initialize_sample(rti::core::xtypes::DynamicDataImpl&)
    {
        // empty; DynamicData doesn't have to be initialized to max size
    }

    static std::vector<char>& to_cdr_buffer(
        std::vector<char>& buffer,
        const rti::core::xtypes::DynamicDataImpl& sample);

    static void from_cdr_buffer(
        rti::core::xtypes::DynamicDataImpl& sample,
        const std::vector<char>& buffer);
};

} } // namespace dds::topic

// --- generic code impl: -----------------------------------------------------

namespace rti { namespace core { namespace xtypes {

template <typename T>
std::vector<T> DynamicDataImpl::get_values(uint32_t mid) const
{
    std::vector<T> v;
    get_values(mid, v);
    return v;
}

template <typename T>
std::vector<T> DynamicDataImpl::get_values(const std::string& mid) const
{
    std::vector<T> v;
    get_values(mid, v);
    return v;
}

// --- Getter and setter specializations: -------------------------------------

#define RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(TYPE)\
template <>\
OMG_DDS_API void DynamicDataImpl::value(uint32_t mid, const TYPE& value);\
template <>\
OMG_DDS_API void DynamicDataImpl::value(const std::string& mid, const TYPE& value);\
template <>\
OMG_DDS_API TYPE DynamicDataImpl::value(uint32_t mid) const;\
template <>\
OMG_DDS_API TYPE DynamicDataImpl::value(const std::string& mid) const;\

RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(char)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(uint8_t)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(int16_t)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(uint16_t)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(int32_t)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(uint32_t)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(int)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(unsigned int)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(int64_t)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(uint64_t)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(long long)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(unsigned long long)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(float)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(double)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(bool)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(rti::core::LongDouble)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(std::string)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(dds::core::string)
RTI_DECL_DYNAMICDATA_GETTERS_AND_SETTERS(DynamicDataImpl)

#define RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(TYPE) \
template <>\
OMG_DDS_API void DynamicDataImpl::get_values(\
    uint32_t mid, std::vector<TYPE>& out_array) const;\
template <>\
OMG_DDS_API void DynamicDataImpl::get_values(\
    const std::string& mid, std::vector<TYPE>& out_array) const;\
template <>\
OMG_DDS_API void DynamicDataImpl::set_values(\
    uint32_t mid, const std::vector<TYPE>& array);\
template <>\
OMG_DDS_API void DynamicDataImpl::set_values(\
    const std::string& mid, const std::vector<TYPE>& array);\

RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(char)
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(uint8_t)
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(int16_t)
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(uint16_t)

// int32_t, uint32_t, int64_t and uint64_t are not the same type as DDS_Long
// DDS_LongLong, etc. in some 64-bit platforms, so we can't
// interchange their pointer types. See CPPPSM-274
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(DDS_Long)
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(DDS_UnsignedLong)
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(DDS_LongLong)
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(DDS_UnsignedLongLong)

RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(float)
RTI_DECL_DYNAMICDATA_ARRAY_GETTERS_AND_SETTERS(double)

} } } // namespace rti::core::xtypes

#endif // RTI_DDS_CORE_XTYPES_DYNAMICDATA_HPP_
