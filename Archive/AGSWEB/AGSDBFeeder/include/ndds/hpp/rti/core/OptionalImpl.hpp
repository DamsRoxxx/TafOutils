/*
 Copyright (c) 2013, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_OPTIONAL_HPP_
#define RTI_DDS_CORE_OPTIONAL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

// DllExport.hpp should be the second include
#include <rti/core/DllExport.hpp>
#include <dds/core/Exception.hpp>
#include <dds/core/String.hpp> // for optional specialization for strings
#include <rti/core/memory.hpp>

/** @RTI_namespace_start dds::core */
namespace rti { namespace core {

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile dds/core/Optional.hpp
 *
 * @brief @st_value_type Represents an object that may not contain a valid value
 *
 * @tparam T The type of the actual object this \p optional<T> wraps
 *
 * Members of an \ref DDSTypesModule "IDL" type marked with the \p \@Optional tag
 * map to this C++ type.
 *
 * When an optional value has a valid value is_set() returns true and get() returns
 * a reference to the actual object of type T. Otherwise is_set() returns false
 * and get() throws dds::core::PreconditionNotMetError. To assing a value you
 * can use the assignment operator or set().
 *
 * An optional object has full \ref a_st_value_type "value-type semantics";
 * copying an optional value copies the underlying object if it exists.
 *
 * This class is similar to boost::optional.
 *
 * @see DDSTypesModule
 */
template <typename T>
class UserDllExport optional {
public:
    typedef T value_type;
    typedef memory::ObjectAllocator<T> Allocator;

    /**
     * @brief Create an unset optional object
     *
     * @post !is_set()
     */
    optional() OMG_NOEXCEPT
        : value_ (NULL)
    {
    }

    /**
     * @brief Create an optional object with a copy of a value
     *
     * @post is_set() && get() == value
     */
    optional(const T& value)
        : value_ (Allocator::create(value))
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Create an optional object moving a value
     *
     * @post is_set()
     */
    optional(T&& value)
        : value_(Allocator::create(std::forward<T>(value)))
    {
    }
  #endif

    /**
     * @brief Create an optional member conditionally set or unset.
     *
     * @param condition If true creates an optional member with \p value otherwise
     * it creates an unset optional member
     * @param value The value to set if condition is true
     *
     * @post is_set() == condition
     */
    optional(bool condition, const T& value)
        : value_ (NULL)
    {
        if (condition) {
            value_ = Allocator::create(value);
        }
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Creates an optional member conditionally set or unset
     * by moving a value.
     *
     * Moves the value rather than copying it.
     *
     * @see optional(bool, const T&)
     */
    optional(bool condition, T&& value)
        : value_ (NULL)
    {
        if (condition) {
            value_ = Allocator::create(std::forward<T>(value));
        }
    }
  #endif

    /*
     * @brief Copy constructor
     *
     * If \p other is set it copies the underlying object.
     */
    optional(const optional<T>& other)
        : value_ (NULL)
    {
        if (other.is_set()) {
            value_ = Allocator::create(other.get());
        }
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /*
     * @brief @st_cpp11 Move constructor
     *
     * If \p other is set it moves the underlying object.
     */
    optional(optional<T>&& other) OMG_NOEXCEPT
        : value_(other.value_)
    {
        other.value_ = NULL;
    }
  #endif

    /**
     * @brief Destroys the underlying object if it exists
     */
    ~optional()
    {
        reset();
    }

    /**
     * @brief Assigns a copy of an object
     */
    void set(const T& value)
    {
        if (value_ == NULL) {
            value_ = Allocator::create(value);
        } else {
            *value_ = value;
        }
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Assigns an object by moving it
     */
    void set(T&& value)
    {
        if (value_ == NULL) {
            // Create by using T's move ctor if available
            value_ = Allocator::create(std::forward<T>(value));
        } else {
            // Use T's move assignment operator if available
            *value_ = std::move(value);
        }
    }
  #endif


    /**
     * @brief Checks if this optional instance contains a valid object
     *
     * If this->is_set(), then this->get() is a valid object
     */
    bool is_set() const
    {
        return value_ != NULL;
    }

    /**
     * @brief Returns is_set()
     */
    operator bool() const
    {
        return is_set();
    }

    /**
     * @brief Destroys the underlying object and leaves this optional with
     * an invalid (unset) value
     *
     * @post !is_set()
     */
    void reset()
    {
        if (value_ != NULL) {
            Allocator::destroy(value_);
            value_ = NULL;
        }
    }

    /**
     * @brief Retrieves the underlying object if it exists
     *
     * @throws dds::core::PreconditionNotMetError if !is_set().
     */
    const T& get() const
    {
        if (!is_set()) {
            throw dds::core::PreconditionNotMetError(
                "uninitialized optional value");
        }

        return *value_;
    }

    /**
     * @brief Retrieves the underlying object if it exists
     *
     * @throws dds::core::PreconditionNotMetError if !is_set().
     */
    T& get()
    {
        if (!is_set()) {
            throw dds::core::PreconditionNotMetError(
                "uninitialized optional value");
        }

        return *value_;
    }

    /**
     * @brief Returns &get() if the object is initialized or NULL otherwise.
     */
    const T* get_ptr() const
    {
        return value_;
    }

    /**
     * @brief Returns &get() if the object is initialized or NULL otherwise.
     */
    T* get_ptr()
    {
        return value_;
    }

    /**
     * @brief Assignment operator
     *
     * Copies other.get() if it exists.
     */
    optional<T>& operator= (const optional<T>& other)
    {
        if (other.is_set()) {
            set(other.get());
        } else {
            reset();
        }

        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Move-assignment operator
     *
     * Moves other.get() if it exists.
     */
    optional<T>& operator= (optional<T>&& other) OMG_NOEXCEPT
    {
        std::swap(value_, other.value_);
        return *this;
    }
  #endif

    /**
     * @brief Assign a (valid) value
     *
     * @param value The value to assign to this optional member
     *
     * @post get() == value
     */
    optional<T>& operator= (const T& value)
    {
        set(value);
        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief Assign a (valid) value by moving an object
     *
     * @param value The value to move into this optional member
     *
     * @post is_set()
     */
    optional<T>& operator= (T&& value)
    {
        set(std::forward<T>(value)); // call move overload of set()
        return *this;
    }
  #endif

    /**
     * @brief Swaps the underlying objects
     *
     * This operation is always O(1).
     */
    friend void swap(optional<T>& left, optional<T>& right) OMG_NOEXCEPT
    {
        std::swap(left.value_, right.value_); // swap the underlying pointer
    }

private:
    T * value_;
};

// --- Specialization for strings
//
template <typename CharType>
class UserDllExport optional<
    typename dds::core::basic_string<
        CharType,
        typename memory::OsapiAllocator<CharType> > > {
public:
    typedef typename memory::OsapiAllocator<CharType> Allocator;
    typedef typename dds::core::basic_string<CharType, Allocator> StringType;
    typedef StringType value_type;
    typedef typename StringType::create_null_tag_t create_null_tag_t;

    /**
     * Initialize an unset optional member.
     *
     * Postcondition: !this->is_set()
     */
    optional() OMG_NOEXCEPT
        : value_ (create_null_tag_t())
    {
    }

    /**
     * Initialize an optional member with a value (makes a copy)
     *
     */
    optional(const StringType& value)
        : value_ (value)
    {
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    optional(StringType&& value)
        : value_(std::forward<StringType>(value))
    {
    }
  #endif

    /**
     * Initialize an optional member conditionally. If the condition is true
     * it initializes it with a copy of value; otherwise it is not set
     */
    optional(bool condition, const StringType& value)
        : value_ (create_null_tag_t())
    {
        if (condition) {
            value_ = value;
        }
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    optional(bool condition, StringType&& value)
        : value_ (create_null_tag_t())
    {
        if (condition) {
            value_ = std::forward<StringType>(value);
        }
    }
  #endif

    /*
     * Initializes an optional by copying the content of another optional
     * member if it is set
     */
    optional(const optional<StringType>& other)
        : value_ (create_null_tag_t())
    {
        if (other.is_set()) {
            value_ = other.value_;
        }
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    optional(optional<StringType>&& other) OMG_NOEXCEPT
        : value_(std::move(other.value_))
    {
    }
  #endif

    ~optional()
    {
    }

    void set(const StringType& value)
    {
        value_ = value;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    void set(StringType&& value)
    {
        value_ = std::move(value);
    }
  #endif


    /**
     * Returns true only if the attribute is set.
     */
    bool is_set() const
    {
        return value_.c_str() != NULL;
    }

    /**
     * Reset the attribute.
     *
     * Postcondition: !this->is_set()
     */
    void reset()
    {
        if (is_set()) {
            Allocator::release(value_.native());
            value_.native() = NULL;
        }
    }

    /**
     *  Get the attribute. An exception is thrown if the attribute is not set.
     */
    const StringType& get() const
    {
        if (!is_set()) {
            throw dds::core::PreconditionNotMetError(
                "uninitialized optional value");
        }

        return value_;
    }

    /**
     *  Get the attribute. An exception is thrown if the attribute is not set.
     */
    StringType& get()
    {
        if (!is_set()) {
            throw dds::core::PreconditionNotMetError(
                "uninitialized optional value");
        }

        return value_;
    }

    /**
     * @brief Returns &get() if the object is initialized or NULL otherwise.
     */
    const StringType* get_ptr() const
    {
        if (is_set()) {
            return &value_;
        } else {
            return NULL;
        }
    }

    /**
     * @brief Returns &get() if the object is initialized or NULL otherwise.
     */
    StringType* get_ptr()
    {
        if (is_set()) {
            return &value_;
        } else {
            return NULL;
        }
    }

    optional<StringType>& operator= (const optional<StringType>& other)
    {
        if (other.is_set()) {
            set(other.get());
        } else {
            reset();
        }

        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    optional<StringType>& operator= (optional<StringType>&& other) OMG_NOEXCEPT
    {
        swap(value_, other.value_);
        return *this;
    }
  #endif

    optional<StringType>& operator= (const StringType& value)
    {
        set(value);
        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    optional<StringType>& operator= (StringType&& value)
    {
        set(std::forward<StringType>(value)); // call move overload of set()
        return *this;
    }
  #endif

    friend void swap(optional<StringType>& left, optional<StringType>& right) OMG_NOEXCEPT
    {
        swap(left.value_, right.value_); // swap the underlying pointer
    }

private:
    StringType value_;
};

// comparison operators:

/**
 * @relatesalso dds::core::optional
 *
 * @brief Compares two optional values
 *
 * @return true if both are unset or both are set and a.get() == b.get().
 *
 */
template <typename T>
bool operator ==(const optional<T>& a, const optional<T>& b)
{
    if (a.is_set() != b.is_set()) {
        return false; // one is set and one isn't
    }

    if (!a.is_set()) {
        return true; // none is set
    }

    return a.get() == b.get(); // both are set
}

/**
 * @relatesalso dds::core::optional
 *
 * @brief Compares two optional values
 *
 * @return false if both are unset or both are set and a.get() == b.get().
 *
 */
template <typename T>
bool operator !=(const optional<T>& a, const optional<T>& b)
{
    return !(a == b);
}

/**
 * @relatesalso dds::core::optional
 *
 * @brief Compares an optional member and a value of the underlying type
 *
 * @return Return true if optional_value is set and optional_value.get() == value
 */
template <typename T>
bool operator ==(const optional<T>& optional_value, const T& value)
{
    if (!optional_value.is_set()) {
        return false;
    }

    return optional_value.get() == value;
}

/**
 * @relatesalso dds::core::optional
 *
 * @brief Compares an optional member and a value of the underlying type
 *
 * @return Return true if optional_value is set and optional_value.get() == value
 */
template <typename T>
bool operator ==(const T& value, const optional<T>& optional_value)
{
    return optional_value == value;
}

/**
 * @relatesalso dds::core::optional
 *
 * @brief Compares an optional member and a value of the underlying type
 *
 * @return Return false if optional_value is set and optional_value.get() == value
 */
template <typename T>
bool operator !=(const optional<T>& optional_value, const T& value)
{
    return !(optional_value == value);
}

/**
 * @relatesalso dds::core::optional
 *
 * @brief Compares an optional member and a value of the underlying type
 *
 * @return Return false if optional_value is set and optional_value.get() == value
 */
template <typename T>
bool operator !=(const T& value, const optional<T>& optional_value)
{
    return !(optional_value == value);
}

/**
 * @relatesalso dds::core::optional
 *
 * @brief Applies the operator<< to optional.get() or the string \p "NULL" if
 * !optional.is_set()
 */
template<typename T>
std::ostream& operator <<(std::ostream& out, const optional<T>& optional)
{
    if (optional.is_set()) {
        out << optional.get();
    } else {
        out << "null";
    }
    return out;
}

} }
#endif /* RTI_DDS_CORE_OPTIONAL_HPP_ */
