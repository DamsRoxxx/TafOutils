/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_DETAIL_SUPPORTIMPL_HPP_
#define RTI_QUEUING_DETAIL_SUPPORTIMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include "osapi/osapi_process.h"

#include <rti/request/detail/macros.hpp>
#include <dds/core/QosProvider.hpp>
#include <rti/core/Guid.hpp>

#include <dds/pub/DataWriter.hpp>
#include <rti/queuing/QueueParams.hpp>
#include <iostream>

#define VIRTUAL_GUID_BUFFER_LENGTH 2048


namespace rti { namespace queuing { namespace detail {
    
    
void append_guid(std::ostringstream& os, const rti::core::Guid& guid);

XMQCPP2DllExport
std::string get_queue_reply_topic_name(
        const std::string& request_topic, 
        const std::string& reply_topic);

struct QueuingServiceMatchedInfo {
    long long epoch_;
};  

struct InstanceHandleComparator : 
    public std::binary_function<dds::core::InstanceHandle, dds::core::InstanceHandle, bool>
{
    bool operator()(
            const dds::core::InstanceHandle& lhs, 
            const dds::core::InstanceHandle& rhs) const
    {
        return (MIGRtpsKeyHash_compare(
            &lhs.delegate().native().keyHash,
            &rhs.delegate().native().keyHash) == -1);
    }
};    
   

struct SampleIdentityComparator : 
    public std::binary_function<rti::core::SampleIdentity, rti::core::SampleIdentity, bool>
{
    bool operator()(
            const rti::core::SampleIdentity& lhs, 
            const rti::core::SampleIdentity& rhs) const
    {
        bool sequence_number_compare = (lhs.sequence_number()<rhs.sequence_number());
        if (sequence_number_compare == 0) {
            return lhs.writer_guid()<rhs.writer_guid(); 
        } else {
            return sequence_number_compare;
        }
    }
};

    
rti::core::Guid create_random_guid( 
    const dds::domain::DomainParticipant participant,    
    const std::string& topic_name);

XMQCPP2DllExport
rti::core::Guid ensure_valid_guid(
    const rti::core::Guid& guid, 
    const dds::domain::DomainParticipant participant,  
    const std::string& entity_name, 
    const std::string& topic_name);
 
dds::pub::qos::DataWriterQos 
get_data_writer_qos_from_parameters(
        const std::string& qos_library_name,
        const std::string& qos_profile_name,
        const std::string& topic_name); 


dds::sub::qos::DataReaderQos 
get_data_reader_qos_from_parameters(
        const std::string& qos_library_name,    
        const std::string& qos_profile_name,
        const std::string& topic_name); 



} } } // namespace rti::request::detail

#endif // RTI_QUEUING_DETAIL_SUPPORTIMPL_HPP_

