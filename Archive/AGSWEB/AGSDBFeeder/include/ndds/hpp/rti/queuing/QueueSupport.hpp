/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_SUPPORT_HPP_
#define RTI_QUEUING_SUPPORT_HPP_

/// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/core/xtypes/DynamicType.hpp>
#include <dds/core/xtypes/StructType.hpp>

#include <rti/queuing/detail/QueueSupportImpl.hpp>

#define WAIT_FOR_ACKNOWLEDGMENT_MODE_PROPERTY "dds.data_writer.ack_mode_in_wait_for_acknowledgments"

#define REPLY_QUEUE_SUFIX "Reply"


namespace rti { namespace queuing { 

XMQCPP2DllExport
bool is_positive_ack(const rti::sub::AckResponseData& response);

XMQCPP2DllExport
void set_consumer_datareader_qos(
        dds::sub::qos::DataReaderQos& reader_qos, 
        const std::string& shared_subscriber_name);

XMQCPP2DllExport
void set_producer_datawriter_qos(
        dds::pub::qos::DataWriterQos& writer_qos);

XMQCPP2DllExport
std::string get_consumer_reader_topic_name(
        const std::string& topic_name,
        const std::string& shared_subscriber_name);

XMQCPP2DllExport
rti::core::Guid create_entity_guid( 
    const std::string& entity_name,    
    const std::string& topic_name);

XMQCPP2DllExport
rti::core::Guid guid_from_filter_string(const std::string& filter_string); 
    

/**
* \dref_NoMatchingQueueException
*/
class NoMatchingQueueException : public dds::core::Exception, public std::logic_error {
public:
    NoMatchingQueueException(const rti::core::Guid& guid)
        : Exception(), std::logic_error(get_exception_string(guid))
    {
    }
    NoMatchingQueueException(const NoMatchingQueueException& src)
        : Exception(), std::logic_error(src)
    {
    }
    ~NoMatchingQueueException() throw ()
    {
    }

    /**
     * @brief Access the message contained in this NoMatchingQueueException exception. 
     * 
     * @return The message. 
     */
    const char* what() const throw ()
    {
        return std::logic_error::what();
    }
private:
    std::string get_exception_string(const rti::core::Guid& guid)
    {
        std::ostringstream expression;
        expression << "No matching queue for " << guid;
        return expression.str();
    } 
};


/**
 * \dref_ConsumerAvailabilityParams
 */
class ConsumerAvailabilityParams {
public:
    /**
     * \dref_ConsumerAvailabilityParams_reception_enabled
     */
    bool reception_enabled;
    /**
     * \dref_ConsumerAvailabilityParams_unacked_threshold
     */
    int unacked_threshold;
};


class ConsumerAvailabilitySupportTypeHolder {
public:
    dds::core::xtypes::StructType guid_type_;
    dds::core::xtypes::StructType availability_type_;

    ConsumerAvailabilitySupportTypeHolder() 
        : guid_type_(create_GUID_type()),
          availability_type_(create_availability_type(guid_type_))
    {
    }

private:
    static dds::core::xtypes::StructType create_GUID_type()
    {
        using namespace dds::core::xtypes;

        StructType GUID_type("GUID_t");
        GUID_type.extensibility_kind(ExtensibilityKind::FINAL);
        GUID_type.add_member(Member("value", ArrayType(primitive_type<uint8_t>(), 16)));
        return GUID_type;
    }

    static dds::core::xtypes::StructType create_availability_type(
            const dds::core::xtypes::StructType& guid_type)
    {
        using namespace dds::core::xtypes;

        StructType availability_type("ConsumerAvailability");
        availability_type.extensibility_kind(ExtensibilityKind::EXTENSIBLE);
        availability_type.add_member(Member("consumer_guid", guid_type).key(true));
        availability_type.add_member(Member("reception_enabled", primitive_type<bool>()));
        availability_type.add_member(Member("unacked_threshold", primitive_type<int32_t>()));
        return availability_type;
    }
};
    

class ConsumerAvailabilitySupport {
public:
    static const dds::core::xtypes::StructType get_guid_type_code()
    {
        return type_codes().guid_type_;
    }
    
    static const dds::core::xtypes::StructType get_availability_type_code()
    {
        return type_codes().availability_type_;
    }
    
    static void initialize_availability_sample(
            dds::core::xtypes:: DynamicData& sample,
            const rti::core::Guid& consumer_guid) 
    {
        using namespace dds::core::xtypes;
        
        DynamicData dynamic_data_guid(type_codes().guid_type_);
        std::vector<uint8_t> guid_vector(16);
        const DDS_GUID_t& native_guid = consumer_guid.native(); 
        for (int k = 0; k < 16; k++)  {  
            guid_vector[k] = native_guid.value[k]; 
        } 
        dynamic_data_guid.set_values<uint8_t>("value", guid_vector);
        sample.value("consumer_guid", dynamic_data_guid);
    }
    
    static void set_availability_params( 
            dds::core::xtypes:: DynamicData& sample,
            const ConsumerAvailabilityParams& availability_params)
    {
        sample.value("reception_enabled", availability_params.reception_enabled);
        sample.value("unacked_threshold", availability_params.unacked_threshold);
    }
    
    static std::string get_availability_topic_name(const std::string& topic_name) 
    {
        std::string type_name_prefix_ = "ConsumerAvailability";
        std::ostringstream availability_topic_name;
        availability_topic_name << type_name_prefix_ << "@" << topic_name;
        return availability_topic_name.str();        
    }

private:
    static ConsumerAvailabilitySupportTypeHolder& type_codes()
    {
        static ConsumerAvailabilitySupportTypeHolder tc;
        return tc;
    }
};
      

} } // namespace rti::queuing

#endif // RTI_QUEUING_SUPPORT_HPP_

