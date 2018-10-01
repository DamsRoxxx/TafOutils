/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_LOCATOR_HPP_
#define RTI_DDS_CORE_LOCATOR_HPP_

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
 * @brief The definition of the dds::core::safe_enum LocatorKind
 */
struct LocatorKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief An invalid locator.
         */
        INVALID = NDDS_TRANSPORT_CLASSID_INVALID,
        ANY = NDDS_TRANSPORT_CLASSID_ANY,
        /**
         * @brief A locator for a UDPv4 address.
         */
        UDPv4 = NDDS_TRANSPORT_CLASSID_UDPv4,
        /**
         * @brief A locator for an address acessed via shared memory.
         */
        SHMEM = NDDS_TRANSPORT_CLASSID_SHMEM,
        SHMEM_510 = NDDS_TRANSPORT_CLASSID_SHMEM_510,
        INTRA = NDDS_TRANSPORT_CLASSID_INTRA,
        /**
         * @brief  A locator for a UDPv6 address.
         */
        UDPv6 = NDDS_TRANSPORT_CLASSID_UDPv6,
        UDPv6_510 = NDDS_TRANSPORT_CLASSID_UDPv6_510,
        DTLS = NDDS_TRANSPORT_CLASSID_DTLS,
        WAN = NDDS_TRANSPORT_CLASSID_WAN,
        TCPV4_LAN = NDDS_TRANSPORT_CLASSID_TCPV4_LAN,
        TCPV4_WAN = NDDS_TRANSPORT_CLASSID_TCPV4_WAN,
        TLSV4_LAN = NDDS_TRANSPORT_CLASSID_TLSV4_LAN,
        TLSV4_WAN = NDDS_TRANSPORT_CLASSID_TLSV4_WAN,
        RESERVED = NDDS_TRANSPORT_CLASSID_RESERVED_RANGE
    }; 
};

/**
 * @ingroup DDSBuiltInTopicCommonModule 
 * @brief @ref SafeEnumModule of @ref LocatorKind_def 
 * @see @ref LocatorKind_def 
 */
typedef dds::core::safe_enum<LocatorKind_def> LocatorKind;

class Locator;

namespace detail {

RTI_DEFINE_SEQUENCE_TRAITS(DDS_Locator_t, DDS_LocatorSeq);

} // namespace detail

class LocatorAdapter {
public:
    typedef struct DDS_Locator_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_Locator_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_Locator_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_Locator_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
/* Don't check EncapsultationId for now. It is an internal field and there
   seems to be something wrong when retrieving the unicast locators for the
   SubscriptionBuiltinTopicData from a listener vs. matched_subscription_data()
 
        if (DDS_EncapsulationIdSeq_get_length(&first.encapsulations) !=
            DDS_EncapsulationIdSeq_get_length(&second.encapsulations)) {
            return false;
        }

        int32_t length = 
            DDS_EncapsulationIdSeq_get_length(&first.encapsulations);

        for (int32_t i = 0; i < length; i++) {
            if (DDS_EncapsulationIdSeq_get(&first.encapsulations, i) != 
                DDS_EncapsulationIdSeq_get(&second.encapsulations, i)) {
                return false;
            }
        }
*/
        return first.kind == second.kind && 
            first.port == second.port && 
            std::equal(first.address, 
                       first.address + DDS_LOCATOR_ADDRESS_LENGTH_MAX, 
                       second.address);
    }
};

class Locator;

template <>
struct native_type_traits<Locator> {
    typedef rti::core::LocatorAdapter adapter_type;
    typedef DDS_Locator_t native_type;
};

/** 
 * @ingroup DDSBuiltInTopicCommonModule 
 *  
 * @headerfile Locator.hpp "rti/core/Locator.hpp" 
 *  
 * @RTI_class_definition class Locator
 * @brief @extension @st_value_type Type used to represent the addressing 
 * information needed to send a message to an RTPS Endpoint using one of the 
 * supported transports. 
 * 
 */
class Locator : public NativeValueType<Locator> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(Locator)

    typedef NativeValueType<Locator> Base;
public:

    Locator() {}

    /**
     * @brief Construct a Locator with the provided kind, port and address
     */
    Locator(const rti::core::LocatorKind::type the_kind, 
            uint32_t the_port, const dds::core::ByteSeq& the_address)
    {
        kind(the_kind);
        port(the_port);
        address(the_address);
    }

    Locator(const struct DDS_Locator_t& native_locator) 
      : Base(native_locator)
    {
    }

public:
    /**
     * @brief Get the kind associated with this Locator. 
     *  
     * @dref_Locator_t_kind 
     * @see rti::core::LocatorKind_def
     */
    rti::core::LocatorKind::type kind() const
    {
        return (rti::core::LocatorKind::type)native().kind;
    }

    /**
     * @brief Set the kind associated with this Locator. 
     * @see rti::core::LocatorKind_def
     */
    Locator& kind(const rti::core::LocatorKind::type the_kind)
    {
        native().kind = (DDS_Long)the_kind;
        return *this;
    }

    /**
     * @brief Get the port number associated with this Locator
     */
    uint32_t port() const 
    {
        return native().port;
    }

    /**
     * @brief Set the port number associated with this Locator
     */
    Locator& port(uint32_t the_port)
    {
        native().port = the_port;
        return *this;
    }

    /**
     * @brief Get the IP address associated with this Locator.
     */
    dds::core::ByteSeq address() const 
    {
        return dds::core::ByteSeq(
           &native().address[0], 
           &(native().address[DDS_LOCATOR_ADDRESS_LENGTH_MAX - 1]) + 1);
    }

    /**
     * @brief Set the address associated with this Locator object
     */
    Locator& address(const dds::core::ByteSeq& the_address)
    {
        if (the_address.size() > DDS_LOCATOR_ADDRESS_LENGTH_MAX) {
            throw dds::core::InvalidArgumentError("address too long");
        }
        std::copy(the_address.begin(), the_address.end(), native().address);
        return *this;
    }

    /**
     * @brief Construct an invalid locator
     *
     * Since this class doesn't provide a default constructor if you don't
     * know the values of a Locator at the moment of construction use this
     * function explicitly to obtain an invalid object to be filled out.
     */
    static Locator Invalid()
    {
        return Locator(LocatorKind::INVALID, 0, dds::core::ByteSeq());
    }
};

/**
 * @relatesalso rti::core::Locator 
 * @brief A sequence of rti::core::Locator
 */
typedef std::vector<Locator> LocatorSeq;


} }

#endif // RTI_DDS_CORE_LOCATOR_HPP_
