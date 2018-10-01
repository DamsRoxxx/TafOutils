/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,24mar15,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_POLICY_KIND_HPP_
#define RTI_DDS_CORE_POLICY_KIND_HPP_

#include <stdexcept>
#include <bitset>
#include <map>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace rti { namespace core { namespace policy {

/** 
 * @ingroup DDSReliabilityQosModule
 * @brief @extension The enumeration for Reliability acknowledgment kinds
 */
struct AcknowledgmentKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * @brief Samples are acknowledged by RTPS protocol
       * @details @dref_details_ReliabilityQosPolicyAcknowledgmentModeKind_PROTOCOL_ACKNOWLEDGMENT_MODE
       */
      PROTOCOL,
      /**
       * @brief Samples are acknowledged automatically after a subscribing
       *        application has accessed them.
       *
       * The DataReader automatically acknowledges a sample after it has been
       * taken and the loan returned.
       *
       * @see dds::sub::DataReader::take()
       * @see dds::sub::LoanedSamples::~LoanedSamples().
       */
      APPLICATION_AUTO,
      /**
       * @brief Samples up to a specified sequence number are
       *        acknowledged
       */
      APPLICATION_ORDERED,
      /**
       * @brief Samples are acknowledged after the subscribing
       *        application explicitly calls acknowledge on the samples.
       * @details @dref_details_ReliabilityQosPolicyAcknowledgmentModeKind_APPLICATION_EXPLICIT_ACKNOWLEDGMENT_MODE
       */
      APPLICATION_EXPLICIT
  };
};

/** 
 * @ingroup DDSReliabilityQosModule
 * @brief @extension  @ref SafeEnumModule of @ref AcknowledgmentKind_def
 * @see @ref AcknowledgmentKind_def
 */
typedef dds::core::safe_enum<AcknowledgmentKind_def> AcknowledgmentKind;

// ----------------------------------------------------------------------------

/**
 * \dref_RefilterQosPolicyKind
 */
struct RefilterKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /** \dref_RefilterQosPolicyKind_NONE_REFILTER_QOS
         */
        NOTHING,
        /** \dref_RefilterQosPolicyKind_ALL_REFILTER_QOS
         */
        EVERYTHING,
        /** \dref_RefilterQosPolicyKind_ON_DEMAND_REFILTER_QOS
         */
        ON_DEMAND
    };
};

/**
 * @ingroup DDSHistoryQosModule
 * @brief @extension @extension \ref SafeEnumModule of RefilterKind_def
 * @see \ref RefilterKind_def
 */
typedef dds::core::safe_enum<RefilterKind_def> RefilterKind;

// ----------------------------------------------------------------------------

/**
 * @ingroup DDSTransportBuiltinQosModule
 * @brief @extension Mask that specifies which built-in transports are used
 */
class TransportBuiltinMask : public std::bitset<4> {
public:
    /**
     * @brief The base type, std::bitset
     */
    typedef std::bitset<4> MaskType;

    TransportBuiltinMask()
    {
    }

    /**
     * @brief Creates a mask from the bits in an integer
     */
    explicit TransportBuiltinMask(uint64_t mask)
        : MaskType(mask)
    {
    }

    /**
     * @brief Creates a mask from a std::bitset
     */
    TransportBuiltinMask(const MaskType& mask)
        : MaskType(mask)
    {
    }

    /**
     * @brief All bits are set
     */
    static const TransportBuiltinMask all()
    {
        return TransportBuiltinMask(DDS_TRANSPORTBUILTIN_MASK_ALL);
    }

    /**
     * @brief No bits are set
     */
    static const TransportBuiltinMask none()
    {
        return TransportBuiltinMask(DDS_TRANSPORTBUILTIN_MASK_NONE);
    }

    /**
     * @brief Selects the built-in shared-memory transport
     */
    static const TransportBuiltinMask shmem()
    {
        return TransportBuiltinMask(DDS_TRANSPORTBUILTIN_SHMEM);
    }

    /**
     * @brief Selects the built-in UDPv4 transport
     */
    static const TransportBuiltinMask udpv4()
    {
        return TransportBuiltinMask(DDS_TRANSPORTBUILTIN_UDPv4);
    }

    /**
     * @brief Selects the built-in UDPv6 transport
     */
    static const TransportBuiltinMask udpv6()
    {
        return TransportBuiltinMask(DDS_TRANSPORTBUILTIN_UDPv6);
    }
};

// ----------------------------------------------------------------------------

/**
 * @ingroup DDSDomainParticipantResourceLimitsQosModule
 * @brief @extension The enumeration for DomainParticipantResourceLimits
 * ignored entity replacement kinds
 */
struct IgnoredEntityReplacementKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      NO_REPLACEMENT,
      NOT_ALIVE_FIRST
  };
};

/**
 * @ingroup DDSDomainParticipantResourceLimitsQosModule
 * @brief @extension  @ref SafeEnumModule of @ref IgnoredEntityReplacementKind_def
 * @see @ref IgnoredEntityReplacementKind_def
 */
typedef dds::core::safe_enum<IgnoredEntityReplacementKind_def> IgnoredEntityReplacementKind;

// ----------------------------------------------------------------------------

/** 
 * @ingroup DDSServiceQosModule 
 * @brief @extension The definition of the dds::core::safe_enum ServiceKind
 */
struct ServiceKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * @brief There is no service associated to the Entity
       */
      NO_SERVICE,
      /**
       * @brief The Entity is associated to RTI Persistence Service
       */
      PERSISTENCE, 
      /**
       * @brief The Entity is associated to RTI Queuing Service
       */
      QUEUING,
      /**
       * @brief The Entity is associated to RTI Routing Service
       */
      ROUTING,
      /**
       * @brief The Entity is associated to RTI Recording Service
       */
      RECORDING,
      /**
       * @brief The Entity is associated to RTI Replay Service
       */
      REPLAY,      
      /**
       * @brief The Entity is associated to RTI Database Integration Service
       */
      DATABASE_INTEGRATION,
      /**
       * @brief The Entity is associated to RTI Web Integration Service
       */
      WEB_INTEGRATION
  };
};

/** 
 * @ingroup DDSServiceQosModule 
 * @brief @extension @ref SafeEnumModule of @ref ServiceKind_def
 * @see @ref ServiceKind_def 
 */ 
typedef dds::core::safe_enum<ServiceKind_def> ServiceKind;

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

/**
 * @ingroup DDSPublishModeQosModule
 * @brief @extension The enumeration for PublishMode kinds
 */
struct PublishModeKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * \dref_PublishModeQosPolicyKind_SYNCHRONOUS_PUBLISH_MODE_QOS
       */
      SYNCHRONOUS = DDS_SYNCHRONOUS_PUBLISH_MODE_QOS,
      /**
       * \dref_PublishModeQosPolicyKind_ASYNCHRONOUS_PUBLISH_MODE_QOS
       */
      ASYNCHRONOUS = DDS_ASYNCHRONOUS_PUBLISH_MODE_QOS
  };
};

/**
 * @ingroup DDSPublishModeQosModule
 * @brief @extension @ref SafeEnumModule of @ref PublishModeKind_def
 * @see @ref PublishModeKind_def
 */
typedef dds::core::safe_enum<PublishModeKind_def> PublishModeKind;

// ----------------------------------------------------------------------------

/** 
 * @ingroup DDSWireProtocolQosModule 
 * @brief @extension  The definition of the dds::core::safe_enum WireProtocolAutoKind
 */
struct WireProtocolAutoKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * \dref_WireProtocolQosPolicyAutoKind_RTPS_AUTO_ID_FROM_IP
       */
      RTPS_AUTO_ID_FROM_IP,
      /**
       * \dref_WireProtocolQosPolicyAutoKind_RTPS_AUTO_ID_FROM_MAC
       */
      RTPS_AUTO_ID_FROM_MAC,
      /**
       * \dref_WireProtocolQosPolicyAutoKind_RTPS_AUTO_ID_FROM_UUID
       */
      RTPS_AUTO_ID_FROM_UUID
  };
};

/** 
 * @ingroup DDSWireProtocolQosModule 
 * @brief @extension @ref SafeEnumModule of @ref WireProtocolAutoKind_def
 * @see @ref WireProtocolAutoKind_def 
 */ 
typedef dds::core::safe_enum<WireProtocolAutoKind_def> WireProtocolAutoKind;

/**
 * @ingroup DDSWireProtocolQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Mask of reserved ports
 *
 * @details \dref_details_RtpsReservedPortKindMask
 */
class RtpsReservedPortKindMask : public std::bitset<4> {
public:
    /**
     * @brief The base type, \p std::bitset
     */
    typedef std::bitset<4> MaskType;

    /**
     * @brief Creates the mask none()
     */
    RtpsReservedPortKindMask()
    {
    }

    /**
     * @brief Creates a mask from the bits in an integer
     */
    explicit RtpsReservedPortKindMask(uint64_t mask) : MaskType(mask)
    {
    }

    /**
     * @brief Creates a mask from a \p std::bitset
     */
    RtpsReservedPortKindMask(const MaskType& mask) 
        : MaskType(mask)
    {
    }

    /**
     * @brief All bits are set
     *
     * @details \dref_details_RTPS_RESERVED_PORT_MASK_ALL
     */
    static const RtpsReservedPortKindMask all()
    {
        return RtpsReservedPortKindMask(DDS_RTPS_RESERVED_PORT_MASK_ALL);
    }

    /**
     * @brief No bits are set
     *
     * @details \dref_details_RTPS_RESERVED_PORT_MASK_NONE
     */
    static const RtpsReservedPortKindMask none()
    {
        return RtpsReservedPortKindMask(DDS_RTPS_RESERVED_PORT_MASK_NONE);
    }

    /**
     * \dref_RTPS_RESERVED_PORT_MASK_DEFAULT
     */
    static const RtpsReservedPortKindMask default_mask()
    {
        return RtpsReservedPortKindMask(DDS_RTPS_RESERVED_PORT_MASK_DEFAULT);
    }

    /**
     * \dref_RtpsReservedPortKind_BUILTIN_UNICAST
     */
    static const RtpsReservedPortKindMask builtin_unicast()
    {
        return RtpsReservedPortKindMask(DDS_RTPS_RESERVED_PORT_BUILTIN_UNICAST);
    }

    /**
     * \dref_RtpsReservedPortKind_BUILTIN_MULTICAST
     */
    static const RtpsReservedPortKindMask builtin_multicast()
    {
        return RtpsReservedPortKindMask(DDS_RTPS_RESERVED_PORT_BUILTIN_MULTICAST);
    }

    /**
     * \dref_RtpsReservedPortKind_USER_UNICAST
     */
    static const RtpsReservedPortKindMask user_unicast()
    {
        return RtpsReservedPortKindMask(DDS_RTPS_RESERVED_PORT_USER_UNICAST);
    }

    /**
     * \dref_RtpsReservedPortKind_USER_MULTICAST
     */
    static const RtpsReservedPortKindMask user_multicast()
    {
        return RtpsReservedPortKindMask(DDS_RTPS_RESERVED_PORT_USER_MULTICAST);
    }
};

// ----------------------------------------------------------------------------

/** 
 * @ingroup DDSDataWriterResourceLimitsQosModule 
 * @brief @extension The enumeration for DataWriter Resource Limits
 *
 * @details \dref_details_DataWriterResourceLimitsInstanceReplacementKind
 */
struct DataWriterResourceLimitsInstanceReplacementKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * \dref_DataWriterResourceLimitsInstanceReplacementKind_UNREGISTERED_INSTANCE_REPLACEMENT
       */
      UNREGISTERED,
      /**
       * \dref_DataWriterResourceLimitsInstanceReplacementKind_ALIVE_INSTANCE_REPLACEMENT
       */
      ALIVE,
      /**
       * \dref_DataWriterResourceLimitsInstanceReplacementKind_DISPOSED_INSTANCE_REPLACEMENT
       */
      DISPOSED,
      /**
       * \dref_DataWriterResourceLimitsInstanceReplacementKind_ALIVE_THEN_DISPOSED_INSTANCE_REPLACEMENT
       */
      ALIVE_THEN_DISPOSED,
      /**
       * \dref_DataWriterResourceLimitsInstanceReplacementKind_DISPOSED_THEN_ALIVE_INSTANCE_REPLACEMENT
       */
      DISPOSED_THEN_ALIVE,
      /**
       * \dref_DataWriterResourceLimitsInstanceReplacementKind_ALIVE_OR_DISPOSED_INSTANCE_REPLACEMENT
       */
      ALIVE_OR_DISPOSED
  };
};

/** 
 * @ingroup DDSDataWriterResourceLimitsQosModule 
 * @brief @extension @ref SafeEnumModule of @ref DataWriterResourceLimitsInstanceReplacementKind_def
 * @see @ref DataWriterResourceLimitsInstanceReplacementKind_def 
 */ 
typedef dds::core::safe_enum<DataWriterResourceLimitsInstanceReplacementKind_def> DataWriterResourceLimitsInstanceReplacementKind;

/** 
 * @ingroup DDSDiscoveryConfigQosModule
 * @brief @extension A mask that selects the built-in discovery plugins to be used
 */
class DiscoveryConfigBuiltinPluginKindMask : public std::bitset<3> {
public:
    /**
     * @brief The base type, std::bitset
     */
    typedef std::bitset<3> MaskType;

    /**
     * @brief Creates an empty mask
     */
    DiscoveryConfigBuiltinPluginKindMask()
    {
    }

    /**
     * @brief Creates a mask from the bits in an integer
     */
    explicit DiscoveryConfigBuiltinPluginKindMask(uint64_t mask) 
        : MaskType(mask)
    {
    }

    /**
     * @brief Creates a mask from a std::bitset
     */
    DiscoveryConfigBuiltinPluginKindMask(const MaskType& mask) 
        : MaskType(mask)
    {
    }

    /**
     * @brief All the bits are set
     */
    static const DiscoveryConfigBuiltinPluginKindMask all()
    {
        return DiscoveryConfigBuiltinPluginKindMask(
            DDS_DISCOVERYCONFIG_BUILTIN_PLUGIN_MASK_ALL);
    }

    /**
     * @brief No bits are set
     */
    static const DiscoveryConfigBuiltinPluginKindMask none()
    {
        return DiscoveryConfigBuiltinPluginKindMask(
            DDS_DISCOVERYCONFIG_BUILTIN_PLUGIN_MASK_NONE);
    }

    static const DiscoveryConfigBuiltinPluginKindMask SPDP()
    {
        return DiscoveryConfigBuiltinPluginKindMask(
            DDS_DISCOVERYCONFIG_BUILTIN_SPDP);
    }

    static const DiscoveryConfigBuiltinPluginKindMask SEDP()
    {
        return DiscoveryConfigBuiltinPluginKindMask(
            DDS_DISCOVERYCONFIG_BUILTIN_SEDP);
    }

    /**
     * @brief Selects the Simple discovery plugin (default)
     */
    static const DiscoveryConfigBuiltinPluginKindMask SDP()
    {
        return DiscoveryConfigBuiltinPluginKindMask(
            DDS_DISCOVERYCONFIG_BUILTIN_SDP);
    }
};

/** 
 * @ingroup DDSDiscoveryConfigQosModule 
 * @brief @extension The definition of the dds::core::safe_enum RemoteParticipantPurgeKind
 *
 * Available behaviors for halting communication with remote
 * participants (and their contained entities) with which
 * discovery communication has been lost.
 *
 * @details \dref_details_RemoteParticipantPurgeKind
 */
struct RemoteParticipantPurgeKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * \dref_RemoteParticipantPurgeKind_LIVELINESS_BASED_REMOTE_PARTICIPANT_PURGE
       */
      LIVELINESS_BASED,
      /**
       * \dref_RemoteParticipantPurgeKind_NO_REMOTE_PARTICIPANT_PURGE
       */
      NO_PURGE
  };
};

/** 
 * @ingroup DDSDiscoveryConfigQosModule 
 * @brief @extension @ref SafeEnumModule of @ref RemoteParticipantPurgeKind_def
 * @see @ref RemoteParticipantPurgeKind_def 
 */ 
typedef dds::core::safe_enum<RemoteParticipantPurgeKind_def> RemoteParticipantPurgeKind;

// ----------------------------------------------------------------------------

/** 
 * @ingroup DDSTypeSupportQosModule 
 * @brief @extension The definition of the dds::core::safe_enum CdrPaddingKind
 *
 * The CDR padding kind determines whether or not the
 * padding bytes will be set to zero during CDR serialization.
 */
struct CdrPaddingKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * @brief Set padding bytes to zero during CDR serialization
       */
      ZERO,
      /**
       * @brief Don't set padding bytes to any value
       */
      NOT_SET, 
      /**
       * @brief Set the value automatically, depending on the Entity
       *
       * When set on a DomainParticipant the default behavior is NOT_SET
       *
       * When set on a DataWriter or DataReader the behavior is to inherit the
       * value from the DomainParticipant.
       */
      AUTO
  };
};

/** 
 * @ingroup DDSTypeSupportQosModule 
 * @brief @extension  @ref SafeEnumModule of @ref CdrPaddingKind_def
 * @see @ref CdrPaddingKind_def 
 */ 
typedef dds::core::safe_enum<CdrPaddingKind_def> CdrPaddingKind;

// ----------------------------------------------------------------------------

/** 
 * @ingroup DDSTransportMulticastQosModule 
 * @brief @extension The definition of the dds::core::safe_enum TransportMulticastKind
 */
struct TransportMulticastKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
      /**
       * @brief Selects the multicast address automatically
       * @details \dref_details_TransportMulticastQosPolicyKind_AUTOMATIC_TRANSPORT_MULTICAST_QOS
       */
      AUTOMATIC,
      /**
       * @brief Selects a unicast-only mode
       * @details \dref_details_TransportMulticastQosPolicyKind_UNICAST_ONLY_TRANSPORT_MULTICAST_QOS
       */
      UNICAST
  };
};

/** 
 * @ingroup DDSTransportMulticastQosModule 
 * @brief @extension @ref SafeEnumModule of @ref TransportMulticastKind_def
 * @see @ref TransportMulticastKind_def 
 */ 
typedef dds::core::safe_enum<TransportMulticastKind_def> TransportMulticastKind;

/**
 * @ingroup DDSDestinationOrderQosModule
 * @brief @extension The definition of the dds::core::safe_enum DestinationOrderScopeKind
 */
struct DestinationOrderScopeKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * \dref_DestinationOrderQosPolicyScopeKind_INSTANCE_SCOPE_DESTINATIONORDER_QOS
         */
        INSTANCE,
        /**
         * \dref_DestinationOrderQosPolicyScopeKind_TOPIC_SCOPE_DESTINATIONORDER_QOS
         */
        TOPIC
    };
};

/**
 * @ingroup DDSDestinationOrderQosModule
 * @brief @ref SafeEnumModule of @ref DestinationOrderScopeKind_def
 * @see @ref DestinationOrderScopeKind_def
 * */
typedef dds::core::safe_enum<DestinationOrderScopeKind_def> DestinationOrderScopeKind;




} } } // namespace rti::core::policy

#endif // RTI_DDS_CORE_POLICY_KIND_HPP_
