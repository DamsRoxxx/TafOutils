#ifndef OMG_RTI_DDS_DOMAIN_FIND_HPP_
#define OMG_RTI_DDS_DOMAIN_FIND_HPP_

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

#include <dds/domain/DomainParticipant.hpp>
#include <rti/core/detail/NativeEntity.hpp>

namespace rti { namespace domain {

/** 
 * @relatesalso dds::domain::DomainParticipant
 * @headerfile rti/domain/find.hpp
 *  
 * @brief @extension Locates an existing dds::domain::DomainParticipant by name.
 *
 * \p \#include \p <rti/domain/find.hpp>
 *  
 * If no such DomainParticipant exists, the operation will return 
 * dds::core::null.
 */
OMG_DDS_API
dds::domain::DomainParticipant find_participant_by_name(
    const std::string& participant_name);

/**
 * @relatesalso dds::domain::DomainParticipant
 * @headerfile rti/domain/find.hpp
 *
 * @brief @extension Retrieves all the participants created by the application
 * up to a maximum number
 *
 * \p \#include \p <rti/domain/find.hpp>
 *
 * If no such DomainParticipant exists, the operation will return
 * dds::core::null.
 *
 * @tparam ParticipantFwdIterator A forward iterator whose value type
 * is dds::domain::DomainParticipant
 *
 * @param begin The iterator where to begin adding DomainParticipants.
 * @param max_size The maximum number of elements to add
 * @return The number of elements added
 */
template <typename ParticipantFwdIterator>
uint32_t find_participants(ParticipantFwdIterator begin, uint32_t max_size)
{
    if (max_size == 0) {
        return 0;
    }

    DDS_DomainParticipantSeq native_participants = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DomainParticipant> participants_adapter(
        native_participants);

    DDS_ReturnCode_t retcode = DDS_DomainParticipantFactory_get_participants(
        DDS_DomainParticipantFactory_get_instance(),
        &native_participants);
    rti::core::check_return_code(retcode, "get native participants");

    rti::core::detail::create_from_native_entity<
        dds::domain::DomainParticipant, DDS_DomainParticipant, ParticipantFwdIterator>(
            begin, max_size, participants_adapter);

    return max_size < participants_adapter.size()
        ? max_size : participants_adapter.size();
}

/**
 * @relatesalso dds::domain::DomainParticipant
 * @headerfile rti/domain/find.hpp
 *
 * @brief @extension Retrieves all the participants created by the application
 *
 * \p \#include \p <rti/domain/find.hpp>
 *
 * @tparam ParticipantFwdIterator A forward iterator whose value type
 * is dds::domain::DomainParticipant
 *
 * @param begin The iterator where to begin adding DomainParticipants.
 * @return The number of elements added
 *
 */
template <typename ParticipantFwdIterator>
uint32_t find_participants(ParticipantFwdIterator begin)
{
    DDS_DomainParticipantSeq native_participants = DDS_SEQUENCE_INITIALIZER;
    // Ensure sequence destruction
    rti::core::detail::NativeSequenceAdapter<DDS_DomainParticipant> participants_adapter(
        native_participants);

    DDS_ReturnCode_t retcode = DDS_DomainParticipantFactory_get_participants(
        DDS_DomainParticipantFactory_get_instance(),
        &native_participants);
    rti::core::check_return_code(retcode, "get native participants");

    rti::core::detail::create_from_native_entity<
        dds::domain::DomainParticipant, DDS_DomainParticipant, ParticipantFwdIterator>(
            begin, participants_adapter);

    return participants_adapter.size();
}

} }

#endif // OMG_RTI_DDS_DOMAIN_FIND_HPP_
