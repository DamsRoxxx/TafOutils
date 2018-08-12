/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_LONGDOUBLE_HPP_
#define RTI_DDS_CORE_LONGDOUBLE_HPP_

// DllExport.hpp should be the first include
#include <rti/core/DllExport.hpp>

#include "dds_c/dds_c_common.h"
#include <iterator> // for ostream_iterator

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/util/StreamFlagSaver.hpp>

namespace rti { namespace core {

#if (RTI_CDR_SIZEOF_LONG_DOUBLE == 16)

typedef long double LongDouble;

#else

class LongDouble;

template <>
struct native_type_traits<LongDouble> {
    typedef PODNativeAdapter<DDS_LongDouble> adapter_type;
    typedef DDS_LongDouble native_type;
};

/**
 * @ingroup DDSCPP2SupportingTypes
 * @brief @extension @st_value_type Encapsulates an IDL \p long \p double
 *
 * Since the representation of a C++ \p long \p double is not portable, this
 * class encapsulates an \ref DDSTypesModule "IDL" 16-byte \p long \p double.
 */
class UserDllExport LongDouble : public NativeValueType<LongDouble> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(LongDouble)

public:
    /**
     * @brief Creates a long double with value 0.
     */
    LongDouble()
    {
    }

    // For internal use only
    explicit LongDouble(double d) : NativeValueType<LongDouble>()
    {
        // This constructor exists to unify how the IDL-generated types treat
        // long doubles in their default constructors regardless of if they
        // are defined as this class or as the primtive type long double. They
        // can always initialize it to zero by passing 0.0.
        if (d != 0.0) {
            throw dds::core::IllegalOperationError(
                "LongDouble(double) constructor is for internal use only");
        }
    }

    /**
     * @brief Access a byte (0 to 15)
     */
    char operator[](size_t i) const
    {
        return native().bytes[i];
    }

    /**
     * @brief Access a byte (0 to 15)
     */
    char& operator[](size_t i)
    {
        return native().bytes[i];
    }

    // For internal use
    operator const DDS_LongDouble&() const
    {
        return native();
    }
};

inline std::ostream& operator<< (
    std::ostream& out, const LongDouble& the_type)
{
    rti::util::StreamFlagSaver flag_saver(out);
    out<<"<";
    out<<std::hex;
    out.width(2);
    out.fill('0');
    std::copy(
        the_type.native().bytes,
        the_type.native().bytes + 16,
        std:: ostream_iterator<int>(out, ""));
    out<<">";
    return out;
}

#endif

} }

#endif // RTI_DDS_CORE_LONGDOUBLE_HPP_
