/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,09feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_DOMAIN_DOMAIN_ID_HPP_
#define RTI_DDS_DOMAIN_DOMAIN_ID_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>
#include <dds/core/Value.hpp>

#include "ndds/ndds_c.h"

namespace rti { namespace domain {

class DomainId {
public:

    DomainId(uint32_t domain_id) : domain_id_(domain_id) { }

    uint32_t value() const
    {
        return domain_id_;
    }

    static const DomainId default_domain()
    {
        static const DomainId ZERO(0);
        return ZERO;
    }

private:
    uint32_t domain_id_;
};

} }

#endif // RTI_DDS_DOMAIN_DOMAIN_ID_HPP_
