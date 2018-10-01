/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

/*
 * This header defines supporting types that CorePolicy.hpp uses
 */

#ifndef RTI_DDS_CORE_POLICY_SETTINGS_HPP_
#define RTI_DDS_CORE_POLICY_SETTINGS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/vector.hpp>
#include <dds/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/core/detail/NativeSequence.hpp>

namespace rti { namespace core {

class ChannelSettings;

class ChannelSettingsAdapter {
public:
    typedef struct DDS_ChannelSettings_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_ChannelSettings_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_ChannelSettings_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_ChannelSettings_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return
            (DDS_ChannelSettings_t_equals(&first, &second) == DDS_BOOLEAN_TRUE);
    }
};

template<>
struct native_type_traits<ChannelSettings> {
    typedef ChannelSettingsAdapter adapter_type;
    typedef ChannelSettingsAdapter::native_type native_type;
};

class TransportUnicastSettings;

class TransportUnicastSettingsAdapter {
public:
    typedef DDS_TransportUnicastSettings_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_TransportUnicastSettings_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_TransportUnicastSettings_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_TransportUnicastSettings_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return (DDS_TransportUnicastSettings_t_equals(&first, &second)
                == DDS_BOOLEAN_TRUE);
    }
};

template<>
struct native_type_traits<TransportUnicastSettings> {
    typedef TransportUnicastSettingsAdapter adapter_type;
    typedef TransportUnicastSettingsAdapter::native_type native_type;
};

class TransportMulticastSettings;

class TransportMulticastSettingsAdapter {
public:
    typedef struct DDS_TransportMulticastSettings_t native_type;

    static void initialize(native_type& native_value)
    {
        DDS_TransportMulticastSettings_t_initialize(&native_value);
    }

    static void finalize(native_type& native_value)
    {
        DDS_TransportMulticastSettings_t_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_TransportMulticastSettings_t_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return
            (DDS_TransportMulticastSettings_equals(&first, &second) == RTI_TRUE);
    }
};

template<>
struct native_type_traits<TransportMulticastSettings> {
    typedef TransportMulticastSettingsAdapter adapter_type;
    typedef TransportMulticastSettingsAdapter::native_type native_type;
};

/**
 * @RTI_class_definition class TransportUnicastSettings
 * @ingroup DDSTransportUnicastQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Represents a list of unicast locators
 *
 * @details \dref_details_TransportUnicastSettings_t
 */
class OMG_DDS_API TransportUnicastSettings
    : public NativeValueType<TransportUnicastSettings> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportUnicastSettings)
    typedef NativeValueType<TransportUnicastSettings> Base;

    /**
     * @brief Creates the default policy
     */
    TransportUnicastSettings() { }

    /**
     * @brief Creates an instance with the specified transports and receive_port
     */
    explicit TransportUnicastSettings(
        const dds::core::StringSeq& transports,
        int32_t receive_port = 0);

    // For internal use
    /* implicit */ TransportUnicastSettings(
        const DDS_TransportUnicastSettings_t& native_value) : Base(native_value)
    {
    }

    /**
     * @brief Sets a sequence of transport aliases that specifies the unicast
     * interfaces on which to receive \em unicast traffic for the entity.
     *
     * @dref_TransportUnicastSettings_t_transports
     */
    TransportUnicastSettings& transports(const dds::core::StringSeq& value);

    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::StringSeq transports() const;

    /**
     * @brief The unicast port on which the entity can receive data.
     *
     * @dref_TransportUnicastSettings_t_receive_port
     */
    TransportUnicastSettings& receive_port(int32_t value);

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t receive_port() const;
};

/**
 * @ingroup DDSTransportUnicastQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension A sequence of TransportUnicastSettings
 */
typedef std::vector<TransportUnicastSettings> TransportUnicastSettingsSeq;

namespace detail { // rti::core::detail

RTI_DEFINE_SEQUENCE_TRAITS(DDS_TransportUnicastSettings_t, DDS_TransportUnicastSettingsSeq);

} // namespace detail

/**
 * @RTI_class_definition class TransportMulticastSettings
 * @ingroup DDSTransportMulticastQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Represents a list of multicast locators
 *
 * @details \dref_details_TransportMulticastSettings_t
 */
class OMG_DDS_API TransportMulticastSettings : public NativeValueType<TransportMulticastSettings> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TransportMulticastSettings)

    typedef NativeValueType<TransportMulticastSettings> Base;
public:

    TransportMulticastSettings() {}

    /**
     * @brief Creates an instance with the specified transport aliases, receive
     * address and receive port
     *
     * See individual setters.
     */
    TransportMulticastSettings(
        const dds::core::StringSeq& the_transports,
        const std::string& the_receive_address,
        int32_t the_receive_port)
    {
        transports(the_transports);
        receive_address(the_receive_address);
        receive_port(the_receive_port);
    }

    TransportMulticastSettings(
        const struct DDS_TransportMulticastSettings_t&
            native_transport_multicast_settings)
      : Base(native_transport_multicast_settings)
    {
    }

public:

    /**
     * \dref_TransportMulticastSettings_t_transports
     */
    TransportMulticastSettings& transports(
        const dds::core::StringSeq& the_transports)
    {
        using namespace rti::core::native_conversions;
        to_native(native().transports, the_transports);

        return *this;
    }

    /**
     * @brief Getter (see the setter with the same name)
     */
    dds::core::StringSeq transports() const
    {
        using namespace rti::core::native_conversions;
        return from_native<std::string, DDS_StringSeq>(
            native().transports);
    }

    /**
     * \dref_TransportMulticastSettings_t_receive_address
     */
    TransportMulticastSettings& receive_address(
        const std::string& the_receive_address);


    /**
     * @brief Getter (see the setter with the same name)
     */
    std::string receive_address() const
    {
        return native().receive_address;
    }

    /**
     * \dref_TransportMulticastSettings_t_receive_port
     */
    TransportMulticastSettings& receive_port(int32_t the_receive_port)
    {
        native().receive_port = (DDS_Long)the_receive_port;
        return *this;
    }

    /**
     * @brief Getter (see the setter with the same name)
     */
    int32_t receive_port() const
    {
        return native().receive_port;
    }
};

/**
 * @ingroup DDSTransportMulticastQosModule
 * @brief A sequence of TransportMulticastSettings
 */
typedef std::vector<TransportMulticastSettings> TransportMulticastSettingsSeq;

namespace detail { // rti::core::detail

RTI_DEFINE_SEQUENCE_TRAITS(DDS_TransportMulticastSettings_t, DDS_TransportMulticastSettingsSeq);

} // namespace detail

/**
 * \dref_PUBLICATION_PRIORITY_UNDEFINED
 */
const int32_t PUBLICATION_PRIORITY_UNDEFINED = DDS_PUBLICATION_PRIORITY_UNDEFINED;

/**
 * \dref_PUBLICATION_PRIORITY_AUTOMATIC
 */
const int32_t PUBLICATION_PRIORITY_AUTOMATIC = DDS_PUBLICATION_PRIORITY_AUTOMATIC;

// ----------------------------------------------------------------------------

/**
 * @RTI_class_definition class ChannelSettings
 * @ingroup DDSMultiChannelQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures the properties of a channel in rti::core::policy::MultiChannel
 *
 * @details \dref_details_ChannelSettings_t
 */
class OMG_DDS_API ChannelSettings : public NativeValueType<ChannelSettings> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ChannelSettings)

    typedef NativeValueType<ChannelSettings> Base;

public:

    ChannelSettings() {}

    /**
     * @brief Creates an instance with the specified multicast settings, filter
     * expression and priority.
     *
     * See individual setters.
     */
    ChannelSettings(
        const TransportMulticastSettingsSeq& the_multicast_settings,
        const std::string& the_filter_expression,
        int32_t the_priority)
    {
        multicast_settings(the_multicast_settings);
        filter_expression(the_filter_expression);
        priority(the_priority);
    }

    ChannelSettings(const struct DDS_ChannelSettings_t& native_channel_settings)
      : Base(native_channel_settings)
    {
    }

    /**
     * \dref_ChannelSettings_t_multicast_settings
     */
    ChannelSettings& multicast_settings(
        const TransportMulticastSettingsSeq& the_multicast_settings);

    /**
     * @brief Getter (see the setter with the same name)
     */
    TransportMulticastSettingsSeq multicast_settings() const;

    /**
     * \dref_ChannelSettings_t_filter_expression
     */
    ChannelSettings& filter_expression(
        const std::string& the_filter_expression)
    {
        if (!DDS_String_replace(
                &native().filter_expression, the_filter_expression.c_str())) {
            throw std::bad_alloc();
        }
        return *this;
    }

    /**
     * @brief Getter (see the setter with the same name)
     */
    std::string filter_expression() const
    {
        return native().filter_expression;
    }

    /**
     * \dref_ChannelSettings_t_priority
     */
    ChannelSettings& priority(int32_t the_priority)
    {
        native().priority = (DDS_Long)the_priority;
        return *this;
    }

    /**
     * @brief Getter (see the setter with the same name)
     */
    int32_t priority() const
    {
        return native().priority;
    }
};

/**
 * @ingroup DDSMultiChannelQosModule
 * @brief @extension A sequence of ChannelSettings
 */
typedef std::vector<ChannelSettings> ChannelSettingsSeq;

namespace detail { // rti::core::detail

RTI_DEFINE_SEQUENCE_TRAITS(DDS_ChannelSettings_t, DDS_ChannelSettingsSeq);

} // namespace detail

class RtpsReliableReaderProtocol;

class RtpsReliableReaderProtocolAdapter {
public:
    typedef struct DDS_RtpsReliableReaderProtocol_t native_type;

    static void initialize(native_type& native_value)
    {
        static const DDS_RtpsReliableReaderProtocol_t default_value =
            DDS_RTPS_RELIABLE_READER_PROTOCOL_DEFAULT;
        native_value = default_value;
    }

    static void finalize(native_type&)
    {
        // nothing to do
    }

    static void copy(native_type& destination, const native_type& source)
    {
        DDS_RtpsReliableReaderProtocol_copy(&destination, &source);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        return DDS_RtpsReliableReaderProtocol_equals(
            &first, &second) == DDS_BOOLEAN_TRUE;
    }
};

template <>
struct native_type_traits<RtpsReliableReaderProtocol> {
    typedef RtpsReliableReaderProtocolAdapter adapter_type;
    typedef DDS_RtpsReliableReaderProtocol_t native_type;
};


/**
 * @RTI_class_definition class RtpsReliableReaderProtocol
 * @ingroup DDSDataReaderProtocolQosModule
 * @headerfile rti/core/policy/CorePolicy.hpp
 *
 * @brief @extension Configures aspects of the RTPS protocol related to a
 * reliable DataReader
 *
 * @details \dref_details_RtpsReliableReaderProtocol_t
 */
class OMG_DDS_API RtpsReliableReaderProtocol :
    public NativeValueType<RtpsReliableReaderProtocol> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(
        RtpsReliableReaderProtocol)

    typedef NativeValueType<RtpsReliableReaderProtocol> Base;

public:
    /**
     * @brief Creates an instance with the default settings
     */
    RtpsReliableReaderProtocol() {}

    RtpsReliableReaderProtocol(
        const DDS_RtpsReliableReaderProtocol_t& native_value)
      : Base(native_value)
    {
    }

    /**
     * \dref_RtpsReliableReaderProtocol_t_min_heartbeat_response_delay
     */
    RtpsReliableReaderProtocol& min_heartbeat_response_delay(
        const dds::core::Duration& the_min_heartbeat_response_delay);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration min_heartbeat_response_delay() const;

    /**
     * \dref_RtpsReliableReaderProtocol_t_max_heartbeat_response_delay
     */
    RtpsReliableReaderProtocol& max_heartbeat_response_delay(
        const dds::core::Duration& the_max_heartbeat_response_delay);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration max_heartbeat_response_delay() const;

    /**
     * \dref_RtpsReliableReaderProtocol_t_heartbeat_suppression_duration
     */
    RtpsReliableReaderProtocol& heartbeat_suppression_duration(
        const dds::core::Duration& the_heartbeat_suppression_duration);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration heartbeat_suppression_duration() const;

    /**
     * \dref_RtpsReliableReaderProtocol_t_nack_period
     */
    RtpsReliableReaderProtocol& nack_period(
        const dds::core::Duration& the_nack_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration nack_period() const;

    /**
     * \dref_RtpsReliableReaderProtocol_t_receive_window_size
     */
    RtpsReliableReaderProtocol& receive_window_size(
        int32_t the_receive_window_size);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t receive_window_size() const;

    /**
     * \dref_RtpsReliableReaderProtocol_t_round_trip_time
     */
    RtpsReliableReaderProtocol& round_trip_time(
        const dds::core::Duration& the_round_trip_time);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration round_trip_time() const;

    /**
     * \dref_RtpsReliableReaderProtocol_t_app_ack_period
     */
    RtpsReliableReaderProtocol& app_ack_period(
        const dds::core::Duration& the_app_ack_period);
    /**
     * @brief Getter (see setter with the same name)
     */
    dds::core::Duration app_ack_period() const;

    /**
     * \dref_RtpsReliableReaderProtocol_t_samples_per_app_ack
     */
    RtpsReliableReaderProtocol& samples_per_app_ack(
        int32_t the_samples_per_app_ack);
    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t samples_per_app_ack() const;
};


} } // namespace rti::core

#endif // RTI_DDS_CORE_POLICY_SETTINGS_HPP_
