/*
 Copyright (c) 2013, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_DOMAIN_SCOPED_LISTENER_HPP_
#define RTI_DDS_DOMAIN_SCOPED_LISTENER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/ListenerBinder.hpp>
#include <dds/domain/domainfwd.hpp>

namespace rti { namespace domain {

typedef rti::core::ListenerBinder<dds::domain::DomainParticipant>
    DomainParticipantListenerBinder;

} }
#endif // RTI_DDS_DOMAIN_SCOPED_LISTENER_HPP_
