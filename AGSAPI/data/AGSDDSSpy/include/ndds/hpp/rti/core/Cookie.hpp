/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_COOKIE_HPP_
#define RTI_DDS_CORE_COOKIE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>
#include <dds/core/vector.hpp>

namespace rti { namespace core {

class CookieAdapter {
public:
    typedef struct DDS_Cookie_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_Cookie_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_Cookie_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_Cookie_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_Cookie_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

class Cookie;

template <>
struct native_type_traits<Cookie> {
    typedef rti::core::CookieAdapter adapter_type;
    typedef DDS_Cookie_t native_type;
};

/**
 * @ingroup DDSInfrastructureModule
 *
 * @headerfile rti/core/Cookie.hpp
 * @RTI_class_definition class Cookie
 *
 * @brief Unique identifier for a written data sample in the form of a
 * sequence of bytes
 *
 * @see dds::pub::DataWriter::write(const T&, rti::pub::WriteParams&)
 */
class OMG_DDS_API Cookie : public NativeValueType<Cookie> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Cookie)
    typedef NativeValueType<Cookie> Base;

    /**
     * @brief Creates an empty cookie
     */
    Cookie()
    {
    }

    /**
     * @brief Creates a new cookie with the bytes inside a container
     */
    template <typename ByteContainer>
    explicit Cookie(const ByteContainer& bytes)
    {
        value().resize(bytes.size());
        std::copy(bytes.begin(), bytes.end(), value().begin());
    }

    // For internal use
    Cookie(const DDS_Cookie_t &native_cookie) : Base(native_cookie)
    {
    }

    /**
     * @brief Retrieves a reference to the vector of bytes
     */
    dds::core::vector<uint8_t>& value();

    /**
     * @brief Retrieves a const reference to the vector of bytes
     */
    const dds::core::vector<uint8_t>& value() const;
};

/**
 * @relates Cookie 
 * @brief A sequence of Cookie objects 
 */
typedef dds::core::vector<Cookie> CookieSeq;

/**
 * @relates rti::core::Cookie
 *
 * @brief Prints a Cookie to an output stream
 */
OMG_DDS_API
std::ostream& operator<<(std::ostream& out, const Cookie& cookie);


} } // namespace rti::core

#endif // RTI_DDS_CORE_COOKIE_HPP_
