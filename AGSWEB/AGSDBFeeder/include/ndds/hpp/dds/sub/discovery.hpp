#ifndef OMG_DDS_SUB_DISCOVERY_HPP_
#define OMG_DDS_SUB_DISCOVERY_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

// Spec error: missing headers
#include <rti/sub/discoveryImpl.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/topic/topicfwd.hpp>

namespace dds { namespace sub {

/** 
 * @relatesalso dds::sub::DataReader
 * @headerfile dds/sub/discovery.hpp 
 * @brief Instructs \ndds to locally ignore a publication. 
 *  
 * \dref_details_DomainParticipant_ignore_subscription 
 *
 * @param participant The DomainParticipant for which the remote 
 * entity will be ignored
 *
 * @param handle The InstanceHandle of the remote entity that has to be ignored
 */
OMG_DDS_API
void ignore(
    dds::domain::DomainParticipant& participant,
    const dds::core::InstanceHandle& handle);

/**
 * @relatesalso dds::sub::DataReader 
 * @headerfile dds/sub/discovery.hpp 
 * @brief Instructs \ndds to locally ignore subscriptions. 
 *  
 * @param participant The DomainParticipant for which the remote 
 * entity will be ignored
 *
 * @param begin A forward iterator to the initial position in a
 * dds::core::InstanceHandleSeq holding the handles to the remote DataReaders 
 * to be ignored. 
 *  
 * @param end A forward iterator to the final position in a 
 * dds::core::InstanceHandleSeq holding the handles to the remote DataReaders 
 * to be ignored. 
 *  
 * @see ignore(dds::domain::DomainParticipant&, const dds::core::InstanceHandle&);
 */
template<typename FwdIterator>
void ignore(
    dds::domain::DomainParticipant& participant,
    FwdIterator begin,
    FwdIterator end)
{
    for (; begin != end; ++begin) {
        ignore(participant, *begin);
    }
}

//==========================================================================
//== Discovery Management
/**
 * @relatesalso dds::sub::DataReader 
 * @headerfile dds/sub/discovery.hpp 
 * @brief Retrieve the list of publications currently "associated" with a 
 * DataReader. 
 *  
 * \dref_details_DataReader_get_matched_publications
 *  
 * @tparam T The topic-type that the DataReader subscribes to 
 * @param reader The reader whose publications are being retrieved 
 *  
 * @return An InstanceHandleSeq containing the InstanceHandles of the matched 
 * publications for the provided DataReader  
 */
template<typename T>
const ::dds::core::InstanceHandleSeq matched_publications(
    const dds::sub::DataReader<T>& reader)
{
    return rti::sub::matched_publications(*reader.delegate().get());
}

/**
 * @relatesalso dds::sub::DataReader 
 * @headerfile dds/sub/discovery.hpp 
 * @brief Retrieve the list of publications currently "associated" with a 
 * DataReader. 
 *  
 * \dref_details_DataReader_get_matched_publications
 *  
 * @tparam T The topic-type that the DataReader subscribes to 
 * @tparam FwdIterator A forward iterator whose value type is
 * dds::core::InstanceHandle
 * @param reader The reader whose publications are being retrieved 
 * @param begin A forward iterator to the beginning position in the destination 
 * container of matching InstanceHandles 
 * @param end A forward iterator to the ending position in the destination 
 * container of matching InstanceHandles 
 *  
 * @return An iterator placed at the last position in the container where a 
 * InstanceHandle was inserted 
 */
template<typename T, typename FwdIterator>
FwdIterator matched_publications(
    const dds::sub::DataReader<T>& reader,
    FwdIterator begin,
    FwdIterator end)
{
    dds::core::InstanceHandleSeq publications = matched_publications(reader);

    for (dds::core::InstanceHandleSeq::const_iterator it = publications.begin();
        begin != end && it != publications.end();
        ++begin, ++it) {

        *begin = *it;
    }

    return begin;
}

/**
 * @relatesalso dds::sub::DataReader 
 * @headerfile dds/sub/discovery.hpp 
 * @brief  This operation retrieves the information on a 
 * publication that is currently "associated" with the DataReader.
 *  
 * \dref_details_DataReader_get_matched_publication_data
 *  
 * @tparam T The topic-type that the DataReader subscribes to 
 * @param reader The reader associated with the publication whose data is being 
 * retrieved 
 * @param handle The InstanceHandle Handle to a specific publication 
 * associated with the DataWriter. Must correspond to a publication currently 
 * associated with the DataReader. 
 *  
 * @return The dds::topic::PublicationBuiltinTopicData of the publication that 
 * is associated with the provided handle 
 */
template<typename T>
const dds::topic::PublicationBuiltinTopicData matched_publication_data(
    const dds::sub::DataReader<T>& reader,
    const dds::core::InstanceHandle& handle)
{
    return rti::sub::matched_publication_data(
        *reader.delegate().get(), handle);
}

} } // namespace dds::sub

#endif // OMG_DDS_SUB_DISCOVERY_HPP_
