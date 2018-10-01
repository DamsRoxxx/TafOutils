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

#ifndef RTI_DDS_SUB_FIND_IMPL_HPP_
#define RTI_DDS_SUB_FIND_IMPL_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/status/DataState.hpp>

#include <rti/core/detail/NativeEntity.hpp>
#include <rti/core/Exception.hpp> // for check_return_code

#include <dds/sub/AnyDataReader.hpp>

#include "dds_c/dds_c_subscription.h"

namespace dds { namespace sub {

/** 
 * @relatesalso dds::sub::DataReader
 * @brief This function retrieves a previously-created DataReader
 * belonging to the Subscriber that is attached to a Topic with a
 * matching topic name. 
 *  
 * \dref_details_Subscriber_lookup_datareader 
 *  
 * @tparam READER The Typed DataReader that is being lookup up 
 * @tparam FwdIterator The type of forward iterator passed to this function
 * @param subscriber The dds::sub::Subscriber the DataReader belongs to
 * @param topic_name Name of the dds::topic::Topic associated with the 
 * DataReader that is to be looked up.
 * @param begin A forward iterator to the position in the destination container 
 * to insert the found DataReader into
 * @param max_size Only 1 DataReader will be returned from this function
 * @return The number of DataReaders that were found (either 0 or 1)
 */
template<typename READER, typename FwdIterator>
uint32_t find(
    const dds::sub::Subscriber& subscriber,
    const std::string& topic_name,
    FwdIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_DataReader * native_reader = DDS_Subscriber_lookup_datareader(
        (DDS_Subscriber *) subscriber->native_subscriber(), topic_name.c_str());

    if (native_reader == NULL) {
        return 0;
    }

    // Return a C++ object from the existing native object
    *begin++ = rti::core::detail::create_from_native_entity<
        READER, DDS_DataReader>(
            native_reader);

    return 1;
}

/**
 * @relatesalso dds::sub::DataReader
 * @brief This function retrieves a previously-created DataReader
 * belonging to the Subscriber that is attached to a Topic with a
 * matching topic name. 
 *  
 * \dref_details_Subscriber_lookup_datareader
 *  
 * @tparam READER The Typed DataReader that is being lookup up 
 * @tparam BinIterator The type of back-inserting iterator passed to this function
 * @param subscriber The dds::sub::Subscriber the DataReader belongs to
 * @param topic_name Name of the dds::topic::Topic associated with the 
 * DataReader that is to be looked up.
 * @param begin A back-inserting iterator to the position in the 
 * destination container to insert the found DataReader into
 * @return The number of DataReaders that were found (either 0 or 1)
 *
 */
template<typename READER, typename BinIterator>
uint32_t find(
    const dds::sub::Subscriber& subscriber,
    const std::string& topic_name,
    BinIterator begin)
{
    DDS_DataReader * native_reader = DDS_Subscriber_lookup_datareader(
        (DDS_Subscriber *) subscriber->native_subscriber(), topic_name.c_str());

    if (native_reader == NULL) {
        return 0;
    }

    // Return a C++ object from the existing native object
    *begin++ = rti::core::detail::create_from_native_entity<
        READER, DDS_DataReader>(
            native_reader);

    return 1;
}

/** 
 * @relatesalso dds::sub::DataReader
 * This function retrieves a previously-created DataReader
 * belonging to the Subscriber that is attached to a Topic with a
 * matching TopicDescription. 
 *  
 * @see find(const dds::sub::Subscriber& subscriber,const std::string& topic_name,FwdIterator begin,uint32_t max_size)
 */
template<typename READER, typename T, typename FwdIterator>
uint32_t find(
    const dds::sub::Subscriber& subscriber,
    const dds::topic::TopicDescription<T>& topic_description,
    FwdIterator begin,
    uint32_t max_size)
{
    return find(subscriber, topic_description.name(), begin, max_size);
}

/** 
 * @relatesalso dds::sub::DataReader
 * @brief This function retrieves a previously-created DataReader
 * belonging to the Subscriber that is attached to a Topic with a
 * matching TopicDescription. 
 *  
 * @see uint32_t find(const dds::sub::Subscriber& subscriber,const std::string& topic_name,BinIterator begin)
 *  
 */
template<typename READER, typename T, typename BinIterator>
uint32_t find(
    const dds::sub::Subscriber& subscriber,
    const dds::topic::TopicDescription<T>& topic_description,
    BinIterator begin)
{
    return find(subscriber, topic_description.name(), begin);
}

// Spec issue: we only allow AnyDataReader for safety
/**
 * @brief Allows the application to access the AnyDataReaders that contain 
 * samples with the specified dds::sub::status::DataState 
 *  
 * \dref_Subscriber_get_datareaders 
 *  
 * @tparam AnyDataReaderFwdIterator A forward iterator whose \p value_type
 * is \p dds::sub::AnyDataReader
 * @param subscriber The dds::sub::Subscriber the DataReaders belong to
 * @param data_state The DataState describing what kinds of samples the returned 
 * DataReaders must contain 
 * @param begin A forward iterator to the position in the destination container 
 * to insert the found DataReaders into. This container should be a container 
 * of AnyDataReaders, not typed DataReaders 
 * @param max_size The maximum number of DataReaders to return
 * 
 * @return The number of DataReaders that were found with a matching DataState
 */
template<typename AnyDataReaderFwdIterator>
uint32_t find(
    const dds::sub::Subscriber& subscriber,
    const dds::sub::status::DataState& data_state,
    AnyDataReaderFwdIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_DataReaderSeq native_readers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DataReader> readers_adapter(
        native_readers);

    DDS_ReturnCode_t retcode = DDS_Subscriber_get_datareaders(
        const_cast<DDS_Subscriber*>(subscriber->native_subscriber()),
        &native_readers,
        data_state.sample_state().to_ulong(),
        data_state.view_state().to_ulong(),
        data_state.instance_state().to_ulong());
    rti::core::check_return_code(retcode, "get native datareaders");

    rti::core::detail::create_from_native_entity<
        dds::sub::AnyDataReader,
        DDS_DataReader,
        AnyDataReaderFwdIterator>(begin, max_size, readers_adapter);

    return max_size < readers_adapter.size() ? max_size : readers_adapter.size();
}

/**
 * @brief Allows the application to access the AnyDataReaders that contain 
 * samples with the specified dds::sub::status::DataState 
 *  
 * \dref_Subscriber_get_datareaders 
 *  
 * @tparam AnyDataReaderBackInsertIterator A back-inserting iterator whose 
 * \p value_type is \p dds::sub::AnyDataReader
 * @param subscriber The dds::sub::Subscriber the DataReaders belong to
 * @param data_state The DataState describing what kinds of samples the returned 
 * DataReaders must contain 
 * @param begin A back-inserting iterator to the position in the destination container 
 * to insert the found DataReaders into. This container should be a container 
 * of AnyDataReaders, not typed DataReaders 
 * 
 * @return The number of DataReaders that were found with a matching DataState
 */
// Spec issue: we only allow AnyDataReader for safety
template<typename AnyDataReaderBackInsertIterator>
uint32_t find(
    const dds::sub::Subscriber& subscriber,
    const dds::sub::status::DataState& data_state,
    AnyDataReaderBackInsertIterator begin)
{
    DDS_DataReaderSeq native_readers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DataReader> readers_adapter(
        native_readers);

    DDS_ReturnCode_t retcode = DDS_Subscriber_get_datareaders(
        const_cast<DDS_Subscriber*>(subscriber->native_subscriber()),
        &native_readers,
        data_state.sample_state().to_ulong(),
        data_state.view_state().to_ulong(),
        data_state.instance_state().to_ulong());
    rti::core::check_return_code(retcode, "get native datareaders");

    rti::core::detail::create_from_native_entity<
        dds::sub::AnyDataReader,
        DDS_DataReader,
        AnyDataReaderBackInsertIterator>(begin, readers_adapter);

    return readers_adapter.size();
}


} } // namespace dds::sub

namespace rti { namespace sub {

/**
 * @relatesalso dds::sub::Subscriber 
 *  
 * @brief @extension Retrieve all of the dds::sub::Subscriber created from this 
 * dds::domain::DomainParticipant 
 *  
 * @tparam SubscriberForwardIterator Type of the forward iterator passed into 
 * this function 
 * @param participant The dds::domain::DomainParticipant the Publishers 
 * belong to
 * @param begin A forward iterator to the position in the destination container 
 * to insert the found Subscribers into
 * @param max_size The maximum size of Subscribers to add 
 *  
 * @return The number of found Subscribers
 */
template <typename SubscriberForwardIterator>
uint32_t find_subscribers(
    const dds::domain::DomainParticipant participant,
    SubscriberForwardIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_SubscriberSeq native_subscribers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_Subscriber> subscribers_adapter(
        native_subscribers);

    DDS_ReturnCode_t retcode = DDS_DomainParticipant_get_subscribers(
        (DDS_DomainParticipant *) participant->native_participant(),
        &native_subscribers);
    rti::core::check_return_code(retcode, "get native subscribers");

    rti::core::detail::create_from_native_entity<
        dds::sub::Subscriber, DDS_Subscriber, SubscriberForwardIterator>(
            begin, max_size, subscribers_adapter);

    return (max_size < subscribers_adapter.size() ? max_size : subscribers_adapter.size());
}

template <typename SubscriberBackInsertIterator>
uint32_t find_subscribers_impl(
    const rti::domain::DomainParticipantImpl& participant,
    SubscriberBackInsertIterator begin,
    bool create_new = true)
{
    DDS_SubscriberSeq native_subscribers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_Subscriber> subscribers_adapter(
        native_subscribers);

    DDS_ReturnCode_t retcode = DDS_DomainParticipant_get_subscribers(
        (DDS_DomainParticipant *) participant.native_participant(),
        &native_subscribers);
    rti::core::check_return_code(retcode, "get native subscribers");


    rti::core::detail::create_from_native_entity<
        dds::sub::Subscriber, DDS_Subscriber, SubscriberBackInsertIterator>(
            begin, subscribers_adapter, create_new);

    return subscribers_adapter.size();
}

/**
 * @relatesalso dds::sub::Subscriber 
 *  
 * @brief @extension Retrieve all of the dds::sub::Subscriber created from this 
 * dds::domain::DomainParticipant 
 *  
 * @tparam SubscriberBackInsertIterator Type of the back-inserting iterator 
 * passed into this function 
 * @param participant The dds::domain::DomainParticipant the Subscribers 
 * belong to
 * @param begin A back-inserting iterator to the position in the destination
 * container to insert the found Subscribers into
 *  
 * @return The number of found Subscribers
 */
template <typename SubscriberBackInsertIterator>
uint32_t find_subscribers(
    const dds::domain::DomainParticipant participant,
    SubscriberBackInsertIterator begin)
{
    return find_subscribers_impl(*participant.delegate(), begin);
}

/** 
 * @relatesalso dds::sub::Subscriber 
 * @brief @extension Finds a Subscriber by name
 * 
 * @param participant The dds::domain::DomainParticipant the Subscribers 
 * belong to
 * @param subscriber_name The name of the Subscriber
 * 
 * @return A valid reference if the a subscriber with that name exists or a
 *         reference equals to \p dds::core::null otherwise.
 */
OMG_DDS_API
dds::sub::Subscriber find_subscriber(
    const dds::domain::DomainParticipant participant,
    const std::string& subscriber_name);


template <typename AnyDataReaderBackInsertIterator>
uint32_t find_datareaders_impl(
    rti::sub::SubscriberImpl& subscriber,
    AnyDataReaderBackInsertIterator begin,
    bool create_new = true)
{
    DDS_DataReaderSeq native_readers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DataReader> readers_adapter(
        native_readers);

    DDS_ReturnCode_t retcode = DDS_Subscriber_get_all_datareaders(
        subscriber.native_subscriber(), &native_readers);
    rti::core::check_return_code(retcode, "get native datareaders");

    rti::core::detail::create_from_native_entity<
        dds::sub::AnyDataReader,
        DDS_DataReader,
        AnyDataReaderBackInsertIterator>(begin, readers_adapter, create_new);

    return readers_adapter.size();
}

/** 
 * @relatesalso dds::sub::DataReader 
 *  
 * @brief @extension Retrieve all the dds::sub::DataReader created from this 
 * dds::sub::Subscriber
 * 
 * @tparam AnyDataReaderBackInsertIterator Type of the back-inserting iterator 
 * passed into this function 
 * @param subscriber The dds::sub::Subscriber the DataReaders belong to
 * @param begin A back-inserting iterator to the position in the destination 
 * container to insert the found DataReaders into
 * 
 * @return The number of found DataReaders
 */
template <typename AnyDataReaderBackInsertIterator>
uint32_t find_datareaders(
    dds::sub::Subscriber subscriber,
    AnyDataReaderBackInsertIterator begin)
{
    return find_datareaders_impl(*subscriber.delegate(), begin);
}

/** 
 * @relatesalso dds::sub::DataReader 
 *  
 * @brief @extension Retrieve all the readers created from a subscriber.
 * 
 * @tparam AnyDataReaderForwardIterator A forward iterator whose \p value_type
 * is \p dds::sub::AnyDataReader
 * @param subscriber The dds::sub::Subscriber the readers belong to
 * @param begin A forward iterator to the position in the destination container 
 * to insert the found readers in.
 * @param max_size The maximum number of readers to return
 * 
 * @return The number of found readers
 */
template <typename AnyDataReaderForwardIterator>
uint32_t find_datareaders(
    dds::sub::Subscriber subscriber,
    AnyDataReaderForwardIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_DataReaderSeq native_readers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DataReader> readers_adapter(
        native_readers);

    DDS_ReturnCode_t retcode = DDS_Subscriber_get_all_datareaders(
        subscriber->native_subscriber(), &native_readers);
    rti::core::check_return_code(retcode, "get native datareaders");

    rti::core::detail::create_from_native_entity<
        dds::sub::AnyDataReader, 
        DDS_DataReader, 
        AnyDataReaderForwardIterator>(begin, max_size, readers_adapter);

    return (max_size < readers_adapter.size() ? 
            max_size : readers_adapter.size());
}

/** 
 * @relatesalso dds::sub::DataReader 
 *  
 * @brief @extension Retrieves a dds::sub::DataReader with the given topic name 
 * within the dds::sub::Subscriber  
 *   
 * \dref_details_Subscriber_lookup_datareader 
 *  
 * @param subscriber The dds::sub::Subscriber that created the DataReader to 
 * find 
 * @param topic_name Topic name of the DataReader to find
 * @return The DataReader with the given topic name 
 */
template<typename READER>
READER find_datareader_by_topic_name(
    dds::sub::Subscriber subscriber, const std::string& topic_name)
{
    std::vector<READER> found_reader;
    
    int32_t num_found = 
        dds::sub::find<READER>(
            subscriber, topic_name, std::back_inserter(found_reader));
    if (num_found != 1) {
        return dds::core::null;
    }

    return found_reader[0];
}

/** 
 * @relatesalso dds::sub::DataReader 
 *  
 * @brief @extension Retrieves a dds::sub::DataReader with the given name 
 * within the dds::sub::Subscriber  
 *   
 * @details @dref_Shared_Subscriber_lookup_datareader_by_name 
 * @param subscriber The dds::sub::Subscriber that created the DataReader to 
 * find 
 * @param datareader_name Entity name of the DataReader to find
 * @return The DataReader with the given name 
 */
template<typename READER>
READER find_datareader_by_name(
    dds::sub::Subscriber subscriber, const std::string& datareader_name)
{
    DDS_DataReader *native_reader = 
        DDS_Subscriber_lookup_datareader_by_name(
            subscriber->native_subscriber(), datareader_name.c_str());
    if (native_reader == NULL) {
        return dds::core::null;
    }

    return rti::core::detail::create_from_native_entity<
        READER, DDS_DataReader>(native_reader);
}

/** 
 * @relatesalso dds::sub::DataReader  
 * @brief @extension Retrieves a dds::sub::DataReader with the given 
 * TopicDescription within the dds::sub::Subscriber  
 * 
 * @tparam READER The type of Reader that is being looked up
 * @tparam T The topic-type  
 * @param subscriber The Subscriber to which the DataReader belongs
 * @param topic_description The TopicDescription identifying the DataReader to 
 * find 
 * 
 * @return The found DataReader
 */
template<typename READER, typename T>
READER find_datareader_by_topic_description(
    const dds::sub::Subscriber& subscriber,
    const dds::topic::TopicDescription<T>& topic_description)
{
    std::vector<READER> found_reader;
    
    int32_t num_found = 
        dds::sub::find<READER>(
            subscriber, 
            topic_description.name(), 
            std::back_inserter(found_reader));
    if (num_found != 1) {
        return dds::core::null;
    }

    return found_reader[0];
}

/** 
 * @relatesalso dds::sub::DataReader 
 *  
 * @brief @extension Retrieves a dds::sub::DataReader within the 
 * dds::domain::DomainParticipant with the given name
 *
 * @details \dref_details_DomainParticipant_lookup_datareader_by_name
 */
template<typename READER>
READER find_datareader_by_name(
    dds::domain::DomainParticipant participant, 
    const std::string& datareader_name)
{

    DDS_DataReader* native_reader = 
        DDS_DomainParticipant_lookup_datareader_by_name(
            const_cast<DDS_DomainParticipant*>(
                participant->native_participant()), 
            datareader_name.c_str());
    if (native_reader == NULL) {
        return dds::core::null;
    }

    return rti::core::detail::create_from_native_entity<
        READER, DDS_DataReader>(native_reader);
}

/** 
 * @relatesalso dds::sub::Subscriber 
 *  
 * @brief @extension Retrieves the implicit dds::sub::Subscriber for the given
 *        dds::domain::DomainParticipant.
 *  
 * @details If an implicit Subscriber does not already exist, this creates one. 
 *  
 * The implicit Subscriber is created with default dds::sub::qos::SubscriberQos 
 * and no listener. When a DomainParticipant is deleted, if there are no 
 * attached dds::sub::DataReader that belong to the implicit Subscriber, 
 * the implicit Subscriber will be implicitly deleted. 
 *  
 * @dref_Shared_implicit_subscriber_mt_safety
 * @param dp The DomainParticipant that the implicit subscriber belongs to.
 * @return The implicit Subscriber
 */
OMG_DDS_API
dds::sub::Subscriber implicit_subscriber(
    const dds::domain::DomainParticipant& dp);

} } // namespace rti::sub

#endif // RTI_DDS_SUB_FIND_IMPL_HPP_
