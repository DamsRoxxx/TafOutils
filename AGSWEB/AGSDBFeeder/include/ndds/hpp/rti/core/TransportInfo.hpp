/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_TRANSPORT_INFO_HPP_
#define RTI_DDS_CORE_TRANSPORT_INFO_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace core {

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @brief The definition of the dds::core::safe_enum TransportClassId
 */
struct TransportClassId_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief Invalid
         */
        INVALID = NDDS_TRANSPORT_CLASSID_INVALID,
        ANY = NDDS_TRANSPORT_CLASSID_ANY,
        /**
         * @brief UDPv4
         */
        UDPv4 = NDDS_TRANSPORT_CLASSID_UDPv4,
        /**
         * @brief Shared memory
         */
        SHMEM = NDDS_TRANSPORT_CLASSID_SHMEM,
        /** @brief Shared memory in \ndds 5.1.0 and earlier
         */
        SHMEM_510 = NDDS_TRANSPORT_CLASSID_SHMEM_510,
        INTRA = NDDS_TRANSPORT_CLASSID_INTRA,
        /** @brief UDPv6
         */
        UDPv6 = NDDS_TRANSPORT_CLASSID_UDPv6,
        /** @brief UDPv6 in \ndds 5.1.0 and earlier
         */
        UDPv6_510 =NDDS_TRANSPORT_CLASSID_UDPv6_510,
        /** @brief DTLS
         */
        DTLS = NDDS_TRANSPORT_CLASSID_DTLS,
        /** @brief WAN
         */
        WAN = NDDS_TRANSPORT_CLASSID_WAN,
        /** @brief TCPv4 LAN mode
         */
        TCPV4_LAN = NDDS_TRANSPORT_CLASSID_TCPV4_LAN,
        /** @brief TCPv4 WAN mode
         */
        TCPV4_WAN = NDDS_TRANSPORT_CLASSID_TCPV4_WAN,
        /** @brief TCPv4 LAN mode with TLS
         */
        TLSV4_LAN = NDDS_TRANSPORT_CLASSID_TLSV4_LAN,
        /** @brief TCPv4 WAN mode with TLS
         */
        TLSV4_WAN = NDDS_TRANSPORT_CLASSID_TLSV4_WAN,
        /** @brief Reserved for additional user-defined transport plugins
         */
        RESERVED_RANGE = NDDS_TRANSPORT_CLASSID_RESERVED_RANGE
    }; 
};

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @brief @ref SafeEnumModule of @ref TransportClassId_def
 * @see TransportClassId_def
 */
typedef dds::core::safe_enum<TransportClassId_def> TransportClassId;

class TransportInfoAdapter {
public:
    typedef struct DDS_TransportInfo_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_TransportInfo_t_initialize(&native_value);
    }

    static void finalize(native_type&)
    {
        // Nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_TransportInfo_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return first.class_id == second.class_id &&
               first.message_size_max == second.message_size_max;
    }
};

class TransportInfo;

template <>
struct native_type_traits<TransportInfo> {
    typedef rti::core::TransportInfoAdapter adapter_type;
    typedef DDS_TransportInfo_t native_type;
};

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @RTI_class_definition class TransportInfo
 * @headerfile rti/core/TransportInfo.hpp
 *
 * @brief @extension @st_value_type Contains the class id and message max size
 * of an installed transport
 */
class TransportInfo : public NativeValueType<TransportInfo> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportInfo)

    typedef NativeValueType<TransportInfo> Base;
public:
    /**
     * @brief Creates an instance with default values
     */
    TransportInfo()
    {
    }

    /**
     * @brief Creates an instance with the specified class id and max size
     */
    TransportInfo(const rti::core::TransportClassId::type& the_class_id, 
                 int32_t the_message_size_max)
    {
        class_id(the_class_id);
        message_size_max(the_message_size_max);
    }

    TransportInfo(const struct DDS_TransportInfo_t& native_transport_info) 
      : Base(native_transport_info)
    {
    }


    /**
     * @brief Getter (see setter with the same name)
     */
    rti::core::TransportClassId class_id() const
    {
        return (rti::core::TransportClassId::type) native().class_id;
    }

    /**
     * \dref_TransportInfo_t_class_id
     */
    TransportInfo& class_id(const rti::core::TransportClassId::type& the_class_id)
    {
        native().class_id = (NDDS_Transport_ClassId_t)the_class_id;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t message_size_max() const
    {
        return native().message_size_max;
    }

    /**
     * \dref_TransportInfo_t_message_size_max
     */
    TransportInfo& message_size_max(int32_t the_message_size_max)
    {
        native().message_size_max = the_message_size_max;
        return *this;
    }
};

/**
 * @ingroup DDSBuiltInTopicCommonModule
 * @brief A sequence of TransportInfo
 */
typedef dds::core::vector<TransportInfo> TransportInfoSeq;

} }

#endif // RTI_DDS_CORE_TRANSPORT_INFO_HPP_
