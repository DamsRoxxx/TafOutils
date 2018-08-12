/* $Id$
 (c) Copyright, Real-Time Innovations, 2014-2016.
 All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
--------------------
1.0,18feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_SEMAPHORE_HPP_
#define RTI_DDS_CORE_SEMAPHORE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "osapi/osapi_semaphore.h"

namespace rti { namespace core {

class OMG_DDS_API Semaphore {

public:
    Semaphore();
    Semaphore(RTIOsapiSemaphoreKind sem_kind);
    Semaphore(RTIOsapiSemaphoreKind sem_kind, const struct RTIOsapiSemaphoreProperty* p_in);
    ~Semaphore();

public:

    void take();
    void take(const struct RTINtpTime* blockDurationIn);
    void give();

private:
    struct RTIOsapiSemaphore* semaphore_;
};

}} // namespace rti::core

#endif // RTI_DDS_CORE_SEMAPHORE_HPP_
