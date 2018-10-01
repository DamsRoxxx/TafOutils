/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,19mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_DISCOVERY_IMPL_HPP_
#define RTI_DDS_SUB_DISCOVERY_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/topic/BuiltinTopic.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <rti/sub/subfwd.hpp>

namespace rti { namespace sub {

void ignore(
    dds::domain::DomainParticipant& participant,
    const dds::core::InstanceHandle& handle);

OMG_DDS_API
dds::core::InstanceHandleSeq matched_publications(
    const UntypedDataReader& writer);

OMG_DDS_API
dds::topic::PublicationBuiltinTopicData matched_publication_data(
    const UntypedDataReader& writer,
    const dds::core::InstanceHandle& handle);


// --- Extensions 
OMG_DDS_API
dds::topic::ParticipantBuiltinTopicData matched_publication_participant_data_impl(
    const UntypedDataReader& reader,
    const dds::core::InstanceHandle& handle);

/** 
 * @relatesalso dds::sub::DataReader
 * @headerfile rti/sub/discoveryImpl.hpp 
 * @brief @extension This operation retrieves the information on the discovered 
 * dds::domain::DomainParticipant associated with the publication 
 * that is currently matching with the dds::sub::DataReader. 
 *  
 * \dref_details_DataReader_get_matched_publication_participant_data
 * 
 * @tparam T The topic-type that the DataReader subscribes to 
 * @param reader The reader to lookup the matched participant data of
 * @param handle The InstanceHandle to a specific publication associated with 
 * a DataWriter. Must correspond to a publication currently associated 
 * with the DataReader. This handle is available in the 
 * dds::sub::SampleInfo::publication_handle()
 * 
 * @return The dds::topic::ParticipantBuiltinTopicData of the DomainParticipant 
 * of a matched publication of a dds::sub::DataReader 
 */
template <typename T>
dds::topic::ParticipantBuiltinTopicData matched_publication_participant_data(
    const dds::sub::DataReader<T>& reader,
    const dds::core::InstanceHandle& handle)
{
    return matched_publication_participant_data_impl(
        *reader.delegate().get(), handle);
}

} } // namespace rti::sub

#endif // RTI_DDS_SUB_DISCOVERY_IMPL_HPP_
