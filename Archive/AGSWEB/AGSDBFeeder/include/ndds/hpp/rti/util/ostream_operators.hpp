/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_UTIL_OSTREAM_OPERATORS_HPP_
#define RTI_UTIL_OSTREAM_OPERATORS_HPP_

//
// This file defines the operator<< for std types. It is not included by any
// other .hpp in the API to avoid contaminating the std namespace in user
// applications.
//

#include <iosfwd>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include <rti/util/StreamFlagSaver.hpp>
#include <dds/core/array.hpp>

namespace std {

#ifndef RTI_NO_STD_WSTRING
inline std::ostream& operator<<(std::ostream& out, const std::wstring& str)
{
    rti::util::StreamFlagSaver flag_saver(out);
    for (size_t i = 0; i < str.size(); i++) {
        out << std::hex << std::setw(sizeof(wchar_t)) << std::setfill('0')
            << (int) str[i];
    }
    return out;
}
#endif

template<typename T>
std::ostream& operator <<(std::ostream& out, const std::vector<T>& v)
{
    typedef typename std::vector<T>::const_iterator iterator;

    out << "{";
    iterator it;
    for (it = v.begin(); it != v.end();) {
        out << *it;
        ++it;

        if (it != v.end()) {
            out << ", ";
        }
    }

    out << "}";

    return out;
}

} // namespace std

// Add operator<< for array to the right namespace
#ifdef RTI_NO_CXX11_HDR_ARRAY
namespace rtiboost {
#else
namespace std {
#endif

template<typename T, std::size_t N>
std::ostream& operator << (std::ostream& out, const dds::core::array<T, N>& array);

} // namespace rtiboost/std

namespace rti { namespace util { namespace detail {

template<typename T, std::size_t N>
struct array_operator_impl {
    static std::ostream& print(std::ostream& out, const dds::core::array<T, N>& array)
    {
        typedef typename dds::core::array<T, N>::const_iterator iterator;

        out << "{";
        iterator it;
        for (it = array.begin(); it < array.end() - 1; ++it) {
            out << *it << ", ";
        }

        if (it < array.end()) {
            out << * it;
        }

        out << "}";

        return out;
    }
};

template <typename T>
struct array_operator_impl<T, 0> {
    static std::ostream& print(std::ostream& out, const dds::core::array<T, 0>&)
    {
        out << "{}";
        return out;
    }
};

} } }

#ifdef RTI_NO_CXX11_HDR_ARRAY
namespace rtiboost {
#else
namespace std {
#endif

// Add operator << so topic types containing arrays can print them
template<typename T, std::size_t N>
std::ostream& operator << (std::ostream& out, const dds::core::array<T, N>& array)
{
    return rti::util::detail::array_operator_impl<T, N>::print(out, array);
}

} // namespace rtiboost/std

#endif // RTI_UTIL_OSTREAM_OPERATORS_HPP_
