/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,13feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_STATUS_ADAPTER_HPP_
#define RTI_DDS_CORE_STATUS_ADAPTER_HPP_

/*i @file
 *
 * This file defines:
 *  1) Adapters between native status structures and their corresponding
 *     C++ classes
 *
 *  2) The native_type_traits that associate a C++ class with its native type
 *     and the adapter class.
 *
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_infrastructure_impl.h"

#include <rti/core/NativeValueType.hpp>
#include <rti/core/status/statusfwd.hpp>

/*
 * This macro defines an adapter for a status class. All status adapters look
 * the same: the C API consistently define native initialize, finalize and copy
 * functions (e.g., for SampleLost we have DDS_SampleLostStatus_initialize()).
 * The C API doesn't define equality functions, but since all statuses are
 * simple types, the default == operator suffices.
 */
#define RTI_STATUS_DEFINE_ADAPTER(STATUS_CLASS)                                \
class STATUS_CLASS ## Adapter {                                                \
                                                                               \
public:                                                                        \
    typedef DDS_ ## STATUS_CLASS native_type;                                  \
                                                                               \
    static void initialize(native_type& native_value)                          \
    {                                                                          \
        memset(&native_value, 0, sizeof(native_value));                        \
        DDS_ ## STATUS_CLASS ## _initialize(&native_value);                    \
    }                                                                          \
                                                                               \
    static void finalize(native_type& native_value)                            \
    {                                                                          \
        DDS_ ## STATUS_CLASS ## _finalize(&native_value);                      \
    }                                                                          \
                                                                               \
    static void copy(native_type& destination, const native_type& source)      \
    {                                                                          \
        DDS_ ## STATUS_CLASS ## _copy(&destination, &source);                  \
    }                                                                          \
                                                                               \
    static bool equals(const native_type& first, const native_type& second)    \
    {                                                                          \
        return memcmp(&first, &second, sizeof(native_type)) == 0;              \
    }                                                                          \
}

/*
 * This macro declares the native_type_traits for a specific status
 */
#define RTI_STATUS_DECLARE_ADAPTER_TRAITS(STATUS_CLASS)                        \
template<>                                                                     \
struct native_type_traits<rti::core::status::STATUS_CLASS> {                   \
    typedef rti::core::status::STATUS_CLASS##Adapter adapter_type;             \
    typedef rti::core::status::STATUS_CLASS##Adapter::native_type native_type; \
}

namespace rti { namespace core {

namespace status {

RTI_STATUS_DEFINE_ADAPTER(InconsistentTopicStatus);
RTI_STATUS_DEFINE_ADAPTER(SampleLostStatus);
RTI_STATUS_DEFINE_ADAPTER(SampleRejectedStatus);
RTI_STATUS_DEFINE_ADAPTER(LivelinessLostStatus);
RTI_STATUS_DEFINE_ADAPTER(LivelinessChangedStatus);
RTI_STATUS_DEFINE_ADAPTER(OfferedDeadlineMissedStatus);
RTI_STATUS_DEFINE_ADAPTER(RequestedDeadlineMissedStatus);
RTI_STATUS_DEFINE_ADAPTER(OfferedIncompatibleQosStatus);
RTI_STATUS_DEFINE_ADAPTER(RequestedIncompatibleQosStatus);
RTI_STATUS_DEFINE_ADAPTER(SubscriptionMatchedStatus);
RTI_STATUS_DEFINE_ADAPTER(PublicationMatchedStatus);

// Extensions
RTI_STATUS_DEFINE_ADAPTER(DataReaderCacheStatus);
RTI_STATUS_DEFINE_ADAPTER(DataReaderProtocolStatus);
RTI_STATUS_DEFINE_ADAPTER(DataWriterCacheStatus);
RTI_STATUS_DEFINE_ADAPTER(ReliableWriterCacheChangedStatus);
RTI_STATUS_DEFINE_ADAPTER(ReliableReaderActivityChangedStatus);
RTI_STATUS_DEFINE_ADAPTER(DataWriterProtocolStatus);
RTI_STATUS_DEFINE_ADAPTER(DomainParticipantProtocolStatus);
RTI_STATUS_DEFINE_ADAPTER(ServiceRequestAcceptedStatus);

} // namespace status

RTI_STATUS_DECLARE_ADAPTER_TRAITS(InconsistentTopicStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(SampleLostStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(SampleRejectedStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(LivelinessLostStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(LivelinessChangedStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(OfferedDeadlineMissedStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(RequestedDeadlineMissedStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(OfferedIncompatibleQosStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(RequestedIncompatibleQosStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(SubscriptionMatchedStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(PublicationMatchedStatus);

// Extensions
RTI_STATUS_DECLARE_ADAPTER_TRAITS(DataReaderCacheStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(DataReaderProtocolStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(DataWriterCacheStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(ReliableWriterCacheChangedStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(ReliableReaderActivityChangedStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(DataWriterProtocolStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(DomainParticipantProtocolStatus);
RTI_STATUS_DECLARE_ADAPTER_TRAITS(ServiceRequestAcceptedStatus);

} } // namespace rti::core

#endif // RTI_DDS_CORE_STATUS_ADAPTER_HPP_
