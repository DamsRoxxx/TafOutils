/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,14mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_TOPIC_BUILTIN_TOPIC_KEY_HPP_
#define RTI_DDS_TOPIC_BUILTIN_TOPIC_KEY_HPP_

#include <vector>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/policy/CorePolicy.hpp>
#include <dds/core/types.hpp>
#include <rti/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace topic {

class BuiltinTopicKeyImpl;

class BuiltinTopicKeyAdapter
    : public rti::core::SimpleTypeAdapter<DDS_BuiltinTopicKey_t> {
public:

    static void initialize(native_type& native_value)
    {
        static const native_type DEFAULT = DDS_BuiltinTopicKey_t_INITIALIZER;
        native_value = DEFAULT;
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_BuiltinTopicKey_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

} // namespace topic

namespace core {

template <>
struct native_type_traits<rti::topic::BuiltinTopicKeyImpl> {
    typedef rti::topic::BuiltinTopicKeyAdapter adapter_type;
    typedef rti::topic::BuiltinTopicKeyAdapter::native_type native_type;
};

} // namespace core

namespace topic {

class OMG_DDS_API BuiltinTopicKeyImpl :
    public rti::core::NativeValueType<BuiltinTopicKeyImpl> {

public:

    typedef const std::vector<uint32_t> VALUE_T;

    VALUE_T value() const;
};

} } // namespace rti::topic


#endif // RTI_DDS_TOPIC_BUILTIN_TOPIC_KEY_HPP_
