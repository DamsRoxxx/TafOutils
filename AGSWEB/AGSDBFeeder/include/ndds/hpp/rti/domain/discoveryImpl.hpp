#ifndef OMG_RTI_DDS_DOMAIN_DISCOVERY_HPP_
#define OMG_RTI_DDS_DOMAIN_DISCOVERY_HPP_

/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

*/


// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/topic/BuiltinTopic.hpp>

namespace rti { namespace domain {

/** 
 * @relatesalso dds::domain::DomainParticipant 
 *
 * @brief @extension Retrieves the list of other participants discovered by
 * this participant
 *  
 * @details \dref_details_DomainParticipant_get_discovered_participants
 */
OMG_DDS_API
dds::core::InstanceHandleSeq discovered_participants(
        dds::domain::DomainParticipant& participant);

/**
 * @relatesalso dds::domain::DomainParticipant
 *
 * @brief @extension Retrieves the information about one participant discovered
 * by this participant
 *
 * @details \dref_details_DomainParticipant_get_discovered_participant_data
 */
OMG_DDS_API
dds::topic::ParticipantBuiltinTopicData discovered_participant_data(
        dds::domain::DomainParticipant& participant,
        const dds::core::InstanceHandle& participant_handle);

} }
#endif /* OMG_RTI_DDS_DOMAIN_DISCOVERY_HPP_ */
