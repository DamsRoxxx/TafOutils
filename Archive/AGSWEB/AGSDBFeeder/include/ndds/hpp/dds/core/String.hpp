#ifndef OMG_DDS_CORE_STRING_HPP_
#define OMG_DDS_CORE_STRING_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Inc.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// This class has not been standarized yet (CPPPSM-139)
//

#include <iomanip>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

// DllExport.hpp should be the second include
#include <rti/core/DllExport.hpp>
#include <string>
#include <memory>
#include <rti/core/memory.hpp>
#include <rti/util/StreamFlagSaver.hpp>

#if defined(RTIUSERDllExport) || defined(NDDS_USER_DLL_EXPORT)
// std::basic_string needs to be exported when IDL-generated types are also
// exported
template class UserDllExport std::basic_string<char>;
template class UserDllExport std::basic_string<wchar_t>;
#endif

namespace dds { namespace core {

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile dds/core/String.hpp
 *
 * @brief @st_value_type A string convertible to std::string and with similar
 * functionality
 *
 * In many cases, for performance reasons and other implementation requirements,
 * the \ndds API uses dds::core::string instead of std::string. The most
 * significant case is the C++ types that \ref DDSNddsgenModule generates from
 * \ref DDSTypesModule "IDL".
 *
 * A dds::core::string provides a subset of the functionality of a \p std::string.
 * It also provides automatic conversion to and from \p std::string.
 */
template<typename CharType, typename Allocator>
class UserDllExport basic_string {
public:
    typedef typename std::basic_string<CharType>::size_type size_type;
    typedef typename std::basic_string<CharType>::traits_type traits_type;

    /**
     * @brief Creates an empty string
     */
    basic_string() : str_(NULL)
    {
        initialize(std::basic_string<CharType>().c_str(), 0);
    }

    /**
     * @brief Copy constructor
     */
    basic_string(const basic_string& other) : str_(NULL)
    {
        initialize(other.c_str(), other.size());
    }

    /**
     * @brief Constructor from C string
     */
    /* implicit */ basic_string(const CharType * other_str) : str_(NULL)
    {
        if (other_str == NULL) {
            throw dds::core::InvalidArgumentError("null string");
        }

        initialize(other_str, traits_type::length(other_str));
    }

    /**
     * @brief Constructor from \p std::basic_string
     */
    /* implicit */ basic_string(const std::basic_string<CharType>& std_string)
        : str_(NULL)
    {
        initialize(std_string.c_str(), std_string.size());
    }

    /**
     * @brief Creates a string of a given size, initialized to '\0'
     */
    explicit basic_string(size_t the_size)
        : str_ (Allocator::allocate_array(the_size + 1))
    {
    	str_[0] = 0;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Move constructor
     */
    basic_string(basic_string&& other) OMG_NOEXCEPT
        : str_(NULL)
    {
        swap(*this, other);
    }
  #endif

    // This constructor is for internal use only, needed by optional<string>.
    //
    // Creating a null string leaves it in an invalid state that
    // optional<string> is prepared to handle.
    struct create_null_tag_t {};
    explicit basic_string(create_null_tag_t) : str_(NULL) {}

    ~basic_string()
    {
        if (str_) {
            Allocator::release(str_);
        }
    }

    /**
     * @brief Gets the underlying C string
     */
    const CharType * c_str() const
    {
        return str_;
    }

    /**
     * @brief Gets the size
     */
    size_type size() const
    {
        return traits_type::length(c_str());
    }

    /**
     * @brief Assignment operator
     */
    basic_string& operator =(const basic_string& other)
    {
        if (str_ != NULL) {
            size_type other_size = other.size();
            if (size() >= other_size) {
                // Can copy without reallocating
                std::copy(other.str_, other.str_ + other_size, str_);
                str_[other_size] = '\0';
                return *this;
            }
        }

        // Need a bigger buffer
        basic_string tmp(other);
        swap(*this, tmp);
        return *this;
    }

  #ifdef RTI_CXX11_RVALUE_REFERENCES
    /**
     * @brief @st_cpp11 Move-assignment operator
     */
    basic_string& operator =(basic_string&& other) OMG_NOEXCEPT
    {
        basic_string tmp(std::move(other));
        swap(*this, tmp);
        return *this;
    }
  #endif

    /**
     * @brief Returns if two strings are equal
     */
    bool operator ==(const basic_string& other) const
    {
        const size_t str_size = size();
        if (str_size != other.size()) {
            return false;
        }
        return traits_type::compare(str_, other.str_, str_size) == 0;
    }

    /**
     * @brief Returns if two strings are different
     */
    bool operator !=(const basic_string& other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Creates a \p std::basic_string from this \p dds::core::basic_string
     */
    std::basic_string<CharType> to_std_string() const
    {
        return std::basic_string<CharType>(c_str());
    }

    /**
     * @brief Creates a \p std::string from this \p dds::core::string
     */
    operator std::basic_string<CharType>() const
    {
        return to_std_string();
    }

    CharType*& native()
    {
        return str_;
    }

    friend void swap(basic_string& left, basic_string& right) OMG_NOEXCEPT
    {
        std::swap(left.str_, right.str_);
    }

private:
    void initialize(const CharType * other_str, size_type the_size)
    {
        str_ = Allocator::allocate_array(the_size + 1);
        std::copy(other_str, other_str + the_size, str_); // shouldn't throw
        str_[the_size] = 0;
    }

    CharType * str_;
};

/**
 * @relatesalso dds::core::basic_string
 *
 * @brief Prints the string
 */
template <typename CharType, typename Allocator>
std::ostream& operator<<(
    std::ostream& out, const basic_string<CharType, Allocator>& the_string)
{
    out << the_string.c_str();
    return out;
}

/**
 * @ingroup DDSCPP2SupportingTypes
 *
 * @brief A string convertible to std::string and with similar functionality
 *
 * @see basic_string
 */
typedef basic_string<char, rti::core::memory::OsapiAllocator<char> > string;

/**
 * @ingroup DDSCPP2SupportingTypes
 *
 * @brief An IDL-derived wide string
 *
 * IDL \p wstring maps to this type in the C++ API.
 *
 * It's character type is \p DDS_Wchar, a portable 4-byte character type.
 *
 * @see basic_string
 */
typedef basic_string<DDS_Wchar, rti::core::memory::OsapiAllocator<DDS_Wchar> > wstring;

} } // namespace dds::core

#endif // OMG_DDS_CORE_STRING_HPP_
