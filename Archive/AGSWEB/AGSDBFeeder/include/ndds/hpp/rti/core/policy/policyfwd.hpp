/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
-------------------- 
1.7a,27feb14,eam Added ResourceLimits 
1.0a,07feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_POLICYFWD_HPP_
#define RTI_DDS_CORE_POLICYFWD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/NativeValueType.hpp>
#include <stdexcept>

#include "dds_c/dds_c_infrastructure.h"
#include "dds_c/dds_c_infrastructure_impl.h"

namespace rti { namespace core { namespace policy {

// --- Standard:
class UserDataImpl;
class DurabilityImpl;
class PresentationImpl;
class DeadlineImpl;
class LatencyBudgetImpl;
class OwnershipImpl;
class OwnershipStrengthImpl;
class LivelinessImpl;
class PartitionImpl;
class ResourceLimitsImpl;
class TimeBasedFilterImpl;
class EntityFactoryImpl;
class ReliabilityImpl;
class HistoryImpl;
class WriterDataLifecycleImpl;
class TransportPriorityImpl;
class LifespanImpl;
class ReaderDataLifecycleImpl;
class DestinationOrderImpl;
class DurabilityServiceImpl;
class TopicDataImpl;
class GroupDataImpl;
class TypeConsistencyEnforcementImpl;

class QosPolicyCountImpl;

// --- Extensions:
class Database;
class Discovery;
class EntityName;
class DomainParticipantResourceLimits;
class TransportBuiltin;
class Property;
class LocatorFilter;
class TransportUnicast;
class UserObject;
class Service;
class MultiChannel;
class PublishMode;
class WireProtocol;
class Batch;
class SystemResourceLimits;
class DataWriterResourceLimits;
class DataReaderResourceLimits;
class TransportSelection;
class DataReaderProtocol;
class AsynchronousPublisher;
class Event;
class Availability;
class DataWriterProtocol;
class ExclusiveArea;
class ReceiverPool;
class DiscoveryConfig;
class TypeSupport;
class TransportMulticast;
class TransportMulticastMapping;
class TransportEncapsulation;
class DomainParticipantProtocol;
class TopicProtocol;
class SubscriberProtocol;
class PublisherProtocol;
class Logging;
class Profile;
class TopicQueryDispatch;

} } } // namespace rti::core::policy

#endif // RTI_DDS_CORE_POLICYFWD_HPP_
