/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.7a,28apr14,eam Created
============================================================================= */

#ifndef RTI_DDS_PUB_COHERENT_ACCESS_HPP_
#define RTI_DDS_PUB_COHERENT_ACCESS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/Subscriber.hpp>
#include <rti/core/Exception.hpp>

#include "dds_c/dds_c_subscription.h"

namespace rti { namespace sub {

class OMG_DDS_API CoherentAccessImpl {
public:
    explicit CoherentAccessImpl(const dds::sub::Subscriber& subscriber);

    ~CoherentAccessImpl();

    void end();

private:
    dds::sub::Subscriber subscriber_;
    bool active_;
};

} } // namespace rti::sub

#endif // RTI_DDS_PUB_COHERENT_ACCESS_HPP_
