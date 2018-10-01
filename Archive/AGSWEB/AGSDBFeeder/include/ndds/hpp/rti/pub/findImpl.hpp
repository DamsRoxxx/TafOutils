/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,12feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_PUB_FIND_IMPL_HPP_
#define RTI_DDS_PUB_FIND_IMPL_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/detail/NativeEntity.hpp>
#include <dds/pub/AnyDataWriter.hpp>
#include <rti/core/Exception.hpp> // for check_return_code

#include "dds_c/dds_c_publication.h"

namespace dds { namespace pub {

/** 
 * @relatesalso dds::pub::DataWriter 
 *  
 * @brief Retrieves the dds::pub::DataWriter for a specific topic name
 *  
 * @details @dref_Shared_Publisher_lookup_datawriter 
 * This function retrieves a previously-created DataWriter
 * belonging to the dds::pub::Publisher that is attached to a dds::topic::Topic 
 * with a matching topic name. If no such DataWriter exists, the operation
 * will return an empty container.  The use of this
 * operation on the built-in Publisher allows access to the
 * built-in DataWriter entities for the built-in topics  
 * @tparam WRITER The typed-DataWriter type to look up
 * @tparam FwdIterator The type of forward iterator passed to this function 
 * @param publisher The dds::pub::Publisher the DataWriter belongs to
 * @param topic_name Name of the dds::topic::Topic associated with the 
 * DataWriter that is to be looked up. 
 * @param begin A forward iterator to the position in the destination container 
 * to insert the found DataWriter in  
 * @param max_size Only 1 DataWriter will be returned from this function
 * @return The number of DataWriters that were found (either 0 or 1)
 */
template<typename WRITER, typename FwdIterator>
uint32_t find(
    const dds::pub::Publisher& publisher,
    const std::string& topic_name,
    FwdIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_DataWriter * native_writer = DDS_Publisher_lookup_datawriter(
        (DDS_Publisher *) publisher->native_publisher(), topic_name.c_str());

    if (native_writer == NULL) {
        return 0;
    }

    // Return a C++ object from the existing native object
    *begin++ = rti::core::detail::create_from_native_entity<
        WRITER, DDS_DataWriter>(
            native_writer);
    return 1;
}

/** 
 * @relatesalso dds::pub::DataWriter 
 *  
 * @brief Retrieves the dds::pub::DataWriter for a specific topic name 
 *  
 * @details @dref_Shared_Publisher_lookup_datawriter 
 * This function retrieves a previously created DataWriter
 * belonging to the dds::pub::Publisher that is attached to a dds::topic::Topic 
 * with a matching topic name. If no such DataWriter exists, the operation
 * will return an empty container.  The use of this
 * operation on the built-in Publisher allows access to the
 * built-in DataWriter entities for the built-in topics 
 *  
 * @tparam WRITER The Typed DataWriter that is being looked up
 * @tparam BinIterator BinIterator The type of back-inserting iterator passed to this function
 * @param publisher The dds::pub::Publisher the DataWriter belongs to
 * @param topic_name Name of the dds::topic::Topic associated with the 
 * DataWriter that is to be looked up. 
 * @param begin A back-inserting iterator to the position in the 
 * destination container to insert the found DataWriter into  
 * 
 * @return The number of DataWriters that were found (either 0 or 1)
 */
template<typename WRITER, typename BinIterator>
uint32_t find(
    const dds::pub::Publisher& publisher,
    const std::string& topic_name,
    BinIterator begin)
{
    DDS_DataWriter * native_writer = DDS_Publisher_lookup_datawriter(
        (DDS_Publisher *) publisher->native_publisher(), topic_name.c_str());

    if (native_writer == NULL) {
        return 0;
    }

    // Return a C++ object from the existing native object
    *begin++ = rti::core::detail::create_from_native_entity<
        WRITER, DDS_DataWriter>(
            native_writer);
    return 1;
}

} } // namespace dds::pub

namespace rti { namespace pub {

/** 
 * @relatesalso dds::pub::Publisher 
 *  
 * @brief @extension Retrieve all of the dds::pub::Publisher created from this 
 * dds::domain::DomainParticipant
 * 
 * @tparam PublisherForwardIterator A forward iterator whose value type
 * is dds::pub::Publisher
 * @param participant The dds::domain::DomainParticipant the Publishers 
 * belong to
 * @param begin A forward iterator to the position in the destination container 
 * to insert the found Publishers into  
 * @param max_size The maximum number of Publishers to add
 * 
 * @return The number of found Publishers
 */
template <typename PublisherForwardIterator>
uint32_t find_publishers(
    const dds::domain::DomainParticipant participant,
    PublisherForwardIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_PublisherSeq native_publishers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_Publisher> publishers_adapter(
        native_publishers);

    DDS_ReturnCode_t retcode = DDS_DomainParticipant_get_publishers(
        (DDS_DomainParticipant *) participant->native_participant(),
        &native_publishers);
    rti::core::check_return_code(retcode, "get native publishers");

    rti::core::detail::create_from_native_entity<
        dds::pub::Publisher, DDS_Publisher, PublisherForwardIterator>(
            begin, max_size, publishers_adapter);

    return (max_size < publishers_adapter.size() ? max_size : publishers_adapter.size());
}

template <typename PublisherBackInsertIterator>
uint32_t find_publishers_impl(
    const rti::domain::DomainParticipantImpl& participant,
    PublisherBackInsertIterator begin,
    bool create_new = true)
{
    DDS_PublisherSeq native_publishers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_Publisher> publishers_adapter(
        native_publishers);

    DDS_ReturnCode_t retcode = DDS_DomainParticipant_get_publishers(
        (DDS_DomainParticipant *) participant.native_participant(),
        &native_publishers);
    rti::core::check_return_code(retcode, "get native publishers");


    rti::core::detail::create_from_native_entity<
        dds::pub::Publisher, DDS_Publisher, PublisherBackInsertIterator>(
            begin, publishers_adapter, create_new);

    return publishers_adapter.size();
}

/**
 * @relatesalso dds::pub::Publisher
 *
 * @brief Retrieve all the dds::pub::Publisher created from this
 * dds::domain::DomainParticipant
 *
 * @tparam PublisherBackInsertIterator A back-inserting iterator whose value type
 * is dds::pub::Publisher
 * @param participant The dds::domain::DomainParticipant the Publishers
 * belong to
 * @param begin A back-inserting iterator to the position in the
 * destination container to insert the found Publishers in
 *
 * @return The number of found Publishers
 */
template <typename PublisherBackInsertIterator>
uint32_t find_publishers(
    const dds::domain::DomainParticipant participant,
    PublisherBackInsertIterator begin)
{
    return find_publishers_impl(*participant.delegate(), begin);
}

/** 
 * @relatesalso dds::pub::Publisher 
 *  
 * @brief @extension Looks up a dds::pub::Publisher by its entity name within 
 * the dds::domain::DomainParticipant. 
 *  
 * @details @dref_Shared_publisher_by_name 
 *
 * @param participant The dds::domain::DomainParticipant to look for the 
 * dds::pub::Publisher in.  
 * @param publisher_name Entity name of the Publisher
 * @return The first Publisher found with the specified name or dds::core::null 
 * if it is not found.  
 */
OMG_DDS_API
dds::pub::Publisher find_publisher(
    const dds::domain::DomainParticipant participant,
    const std::string& publisher_name);

template <typename AnyDataWriterBackInsertIterator>
uint32_t find_datawriters_impl(
    rti::pub::PublisherImpl& publisher,
    AnyDataWriterBackInsertIterator begin,
    bool create_new = true)
{
    DDS_DataWriterSeq native_writers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DataWriter> writers_adapter(
        native_writers);

    DDS_ReturnCode_t retcode = DDS_Publisher_get_all_datawriters(
        publisher.native_publisher(), &native_writers);
    rti::core::check_return_code(retcode, "get native datawriters");

    rti::core::detail::create_from_native_entity<
        dds::pub::AnyDataWriter,
        DDS_DataWriter,
        AnyDataWriterBackInsertIterator>(begin, writers_adapter, create_new);

    return writers_adapter.size();
}

/** 
 * @relatesalso dds::pub::DataWriter 
 *  
 * @brief Retrieve all the dds::pub::DataWriter created from this 
 * dds::pub::Publisher
 * 
 * @tparam AnyDataWriterBackInsertIterator Type of the back-inserting iterator 
 * passed into this function 
 * @param publisher The dds::pub::Publisher the DataWriters belong to
 * @param begin A back-inserting iterator to the position in the destination 
 * container to insert the found DataWriters into
 * 
 * @return The number of found DataWriters
 */
template <typename AnyDataWriterBackInsertIterator>
uint32_t find_datawriters(
    dds::pub::Publisher publisher,
    AnyDataWriterBackInsertIterator begin)
{
    return find_datawriters_impl(*publisher.delegate(), begin);
}

/** 
 * @relatesalso dds::pub::DataWriter 
 *  
 * @brief Retrieve all the dds::pub::DataWriter created from this 
 * dds::pub::Publisher
 * 
 * @tparam AnyDataWriterForwardIterator A forward iterator whose value type
 * is dds::pub::AnyDataWriter
 * @param publisher The dds::pub::Publisher the DataWriters belong to
 * @param begin A forward iterator to the position in the destination container 
 * to insert the found DataWriters in  
 * @param max_size The maximum number of DataWriters to return
 * 
 * @return The number of found DataWriters
 */
template <typename AnyDataWriterForwardIterator>
uint32_t find_datawriters(
    dds::pub::Publisher publisher,
    AnyDataWriterForwardIterator begin,
    uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_DataWriterSeq native_writers = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DataWriter> writers_adapter(
        native_writers);

    DDS_ReturnCode_t retcode = DDS_Publisher_get_all_datawriters(
        publisher->native_publisher(), &native_writers);
    rti::core::check_return_code(retcode, "get native datawriters");

    rti::core::detail::create_from_native_entity<
        dds::pub::AnyDataWriter, 
        DDS_DataWriter, 
        AnyDataWriterForwardIterator>(begin, max_size, writers_adapter);

    return (max_size < writers_adapter.size() ? 
            max_size : writers_adapter.size());
}

/** 
 * @relatesalso dds::pub::DataWriter 
 *  
 * @brief @extension Retrieves a dds::pub::DataWriter with the given name 
 * within the dds::pub::Publisher  
 *   
 * @details @dref_Shared_Publisher_lookup_datawriter_by_name
 *
 * @tparam WRITER The writer type, for example \p dds::pub::DataWriter<Foo>
 * @param publisher The dds::pub::Publisher that created the DataWriter to 
 * find 
 * @param topic_name Entity name of the DataWriter to find
 * @return The AnyDataWriter with the given name 
 */
template<typename WRITER>
WRITER find_datawriter_by_topic_name(
    dds::pub::Publisher publisher, const std::string& topic_name)
{
    std::vector<WRITER> found_writer;
    
    int32_t num_found = 
        dds::pub::find<WRITER>(
            publisher, topic_name, std::back_inserter(found_writer));
    if (num_found != 1) {
        return dds::core::null;
    }

    return found_writer[0];
}

/** 
 * @relatesalso dds::pub::DataWriter 
 *  
 * @brief @extension Retrieves a dds::pub::DataWriter with the given name 
 * within the dds::pub::Publisher  
 *   
 * @details @dref_Shared_Publisher_lookup_datawriter_by_name 
 *
 * @tparam WRITER The writer type, for example \p dds::pub::DataWriter<Foo>
 * @param publisher The dds::pub::Publisher that created the DataWriter to 
 * find 
 * @param datawriter_name Entity name of the DataWriter to find
 * @return The WRITER with the given name
 */
template<typename WRITER>
WRITER find_datawriter_by_name(
    dds::pub::Publisher publisher, const std::string& datawriter_name)
{
    DDS_DataWriter *native_writer = 
        DDS_Publisher_lookup_datawriter_by_name(
            publisher->native_publisher(), datawriter_name.c_str());
    if (native_writer == NULL) {
        return dds::core::null;
    }

    return rti::core::detail::create_from_native_entity<
        WRITER, DDS_DataWriter>(native_writer);
}

/** 
 * @relatesalso dds::pub::DataWriter 
 *  
 * @brief @extension Retrieves a dds::pub::DataWriter within the 
 * dds::domain::DomainParticipant with the given name
 *  
 * @details @dref_Shared_datawriter_by_name 
 *
 * @tparam WRITER The writer type, for example \p dds::pub::DataWriter<Foo>
 * @param participant The dds::domain::DomainParticipant within which the 
 * dds::pub::DataWriter exists 
 * @param datawriter_name \link rti::core::policy::EntityName EntityName\endlink
 * of the DataWriter to find
 * @return The WRITER with the given name
 * @see implicit_publisher(const dds::domain::DomainParticipant& dp);
 */
template<typename WRITER>
WRITER find_datawriter_by_name(
    dds::domain::DomainParticipant participant, 
    const std::string& datawriter_name)
{

    DDS_DataWriter* native_writer = 
        DDS_DomainParticipant_lookup_datawriter_by_name(
            const_cast<DDS_DomainParticipant*>(
                participant->native_participant()), 
            datawriter_name.c_str());
    if (native_writer == NULL) {
        return dds::core::null;
    }

    return rti::core::detail::create_from_native_entity<
        WRITER, DDS_DataWriter>(native_writer);
}

/** 
 * @relatesalso dds::pub::Publisher
 *  
 * @brief @extension Get the implicit dds::pub::Publisher for a given 
 *        dds::domain::DomainParticipant.
 *  
 * @details If an implicit Publisher does not already exist, this creates one.
 *  
 * The implicit Publisher is created with default dds::pub::qos::PublisherQos 
 * and no listener. When a DomainParticipant is deleted, if there are no 
 * attached dds::pub::DataWriter that belong to the implicit Publisher, 
 * the implicit Publisher will be implicitly deleted. 
 *  
 * @mtsafety UNSAFE. It is not safe to create an
 * implicit Publisher while another thread may be simultaneously
 * calling \idref_DomainParticipant_set_default_publisher_qos.
 *
 * @param dp The DomainParticipant that the implicit publisher belongs to
 * @return The implicit publisher
 */
OMG_DDS_API
dds::pub::Publisher implicit_publisher(
    const dds::domain::DomainParticipant& dp);

} } // namespace rti::pub

#endif /* RTI_DDS_PUB_FIND_IMPL_HPP_ */
