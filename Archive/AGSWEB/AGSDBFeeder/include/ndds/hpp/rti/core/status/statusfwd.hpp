/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,07feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_STATUSFWD_HPP_
#define RTI_DDS_CORE_STATUSFWD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/NativeValueType.hpp>
#include <stdexcept>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_infrastructure_impl.h"

namespace rti { namespace core { namespace status {

class InconsistentTopicStatus;
class SampleLostStatus;
class SampleRejectedStatus;
class LivelinessLostStatus;
class LivelinessChangedStatus;
class OfferedDeadlineMissedStatus;
class RequestedDeadlineMissedStatus;
class OfferedIncompatibleQosStatus;
class RequestedIncompatibleQosStatus;
class SubscriptionMatchedStatus;
class PublicationMatchedStatus;

// Extensions
class DataReaderCacheStatus;
class DataReaderProtocolStatus;
class DataWriterCacheStatus;
class ReliableWriterCacheChangedStatus;
class ReliableReaderActivityChangedStatus;
class DataWriterProtocolStatus;
class DomainParticipantProtocolStatus;
class ServiceRequestAcceptedStatus;

} } } // namespace rti::core::status

#endif // RTI_DDS_CORE_STATUSFWD_HPP_
