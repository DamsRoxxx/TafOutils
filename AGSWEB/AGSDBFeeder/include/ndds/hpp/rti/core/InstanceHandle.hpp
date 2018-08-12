/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_INSTANCE_HANDLE_HPP_
#define RTI_DDS_CORE_INSTANCE_HANDLE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/detail/NativeSequence.hpp>
#include "ndds/ndds_c.h"

namespace rti { namespace core {

class InstanceHandle;

namespace detail {

RTI_DEFINE_SEQUENCE_TRAITS(DDS_InstanceHandle_t, DDS_InstanceHandleSeq);

} // namespace detail

class InstanceHandleNativeAdapter {
public:

    typedef DDS_InstanceHandle_t native_type;

    static void initialize(native_type& native_value)
    {
        static const DDS_InstanceHandle_t NIL = DDS_HANDLE_NIL_NATIVE;
        native_value = NIL;    
    }

    static void finalize(native_type&)
    {
        // empty
    }

    static void copy(native_type& destination, const native_type& source)
    {
        destination = source;
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_InstanceHandle_equals(&first, &second) != DDS_BOOLEAN_FALSE);
    }
};

template <>
struct native_type_traits<InstanceHandle> {
    typedef InstanceHandleNativeAdapter adapter_type;
    typedef InstanceHandleNativeAdapter::native_type native_type;
};

class InstanceHandle : public NativeValueType<InstanceHandle> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(InstanceHandle)

public:

    typedef NativeValueType<InstanceHandle> Base;

    InstanceHandle(const dds::core::null_type&) : Base() { }

    InstanceHandle(const InstanceHandle& other) : Base(other.native()) { }

    InstanceHandle(const native_type& native_value) : Base(native_value) { }

    ~InstanceHandle() { }

public:

    bool operator==(const InstanceHandle& other) const
    {
        // Need to override operator == because we're adding an overload
        // for null_type
        return Base::operator ==(other);
    }

    bool operator==(const dds::core::null_type&) const
    {
        return is_nil();
    }

public:
    static const InstanceHandle nil()
    {
        return NIL;
    }

    static const InstanceHandle& nil2()
    {
        return NIL;
    }

    bool is_nil() const
    {
        return DDS_InstanceHandle_is_nil(&native());
    }

private:
    static OMG_DDS_API_VARIABLE const InstanceHandle NIL;
};

OMG_DDS_API
std::ostream& operator<<(std::ostream& os, const InstanceHandle& h);

} }
#endif
