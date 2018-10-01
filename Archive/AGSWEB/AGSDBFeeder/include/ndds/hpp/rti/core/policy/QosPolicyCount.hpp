/* $Id$

(c) Copyright, Real-Time Innovations, 2014
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_POLICY_QOS_POLICY_COUNT_HPP_
#define RTI_DDS_CORE_POLICY_QOS_POLICY_COUNT_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/detail/NativeSequence.hpp>
#include "ndds/ndds_c.h"

namespace rti { namespace core { namespace policy {

class QosPolicyCountImpl;

class QosPolicyCountNativeAdapter {
public:

    typedef DDS_QosPolicyCount native_type;

    static void initialize(native_type& native_value)
    {
        native_value.policy_id = DDS_INVALID_QOS_POLICY_ID;
        native_value.count = 0;
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
        return first.policy_id == second.policy_id &&
            first.count == second.count;
    }
};

} // close namespace policy

template <>
struct native_type_traits<rti::core::policy::QosPolicyCountImpl> {
    typedef rti::core::policy::QosPolicyCountNativeAdapter adapter_type;
    typedef rti::core::policy::QosPolicyCountNativeAdapter::native_type native_type;
};

namespace policy {

class QosPolicyCountImpl : public NativeValueType<QosPolicyCountImpl> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(QosPolicyCountImpl)

public:

    typedef NativeValueType<QosPolicyCountImpl> Base;

    QosPolicyCountImpl(dds::core::policy::QosPolicyId the_policy_id, int32_t the_count)
    {
        native().policy_id = static_cast<DDS_QosPolicyId_t>(the_policy_id);
        native().count = the_count;
    }

    QosPolicyCountImpl(const QosPolicyCountImpl& other) : Base(other.native())
    {
    }

    /**
     * Constructor from DDS_QosPolicyCount_t (for internal usage only)
     *
     * It's implicit, so we can use it to convert from native sequences into
     * vector easily.
     */
    QosPolicyCountImpl(const native_type& native_value) : Base(native_value)
    {
    }

    ~QosPolicyCountImpl()
    {
    }

public:
    dds::core::policy::QosPolicyId policy_id() const
    {
        return static_cast<dds::core::policy::QosPolicyId>(native().policy_id);
    }

    int32_t count() const
    {
        return native().count;
    }
};

} } } // namespace rti::core::policy

#endif // RTI_DDS_CORE_POLICY_QOS_POLICY_COUNT_HPP_

