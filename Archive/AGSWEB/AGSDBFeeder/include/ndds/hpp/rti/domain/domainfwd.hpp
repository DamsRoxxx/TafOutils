/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,21mar13,acr Created
===================================================================== */

#ifndef RTI_DDS_DOMAIN_DOMAIN_FWD_HPP_
#define RTI_DDS_DOMAIN_DOMAIN_FWD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace rti { namespace domain {

class DomainParticipantImpl;

namespace qos {
    class DomainParticipantQosImpl;
}

} }

#endif // RTI_DDS_DOMAIN_DOMAIN_FWD_HPP_
