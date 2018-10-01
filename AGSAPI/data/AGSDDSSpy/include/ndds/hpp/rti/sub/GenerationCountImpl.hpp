/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_GENERATION_COUNT_IMPL_HPP_
#define RTI_DDS_SUB_GENERATION_COUNT_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "ndds/ndds_c.h"

#include <dds/core/types.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace sub {

class GenerationCountImpl {
public:
    GenerationCountImpl() : disposed_(0), no_writers_(0)
    {
    }

    GenerationCountImpl(int32_t disposed_count, int32_t no_writers_count)
        : disposed_(disposed_count),
          no_writers_(no_writers_count)
    {
    }

    int32_t disposed() const
    {
        return disposed_;
    }

    int32_t no_writers() const
    {
        return no_writers_;
    }

private:
    int32_t disposed_;
    int32_t no_writers_;
};

} } // namespace rti::sub

#endif // RTI_DDS_SUB_GENERATION_COUNT_IMPL_HPP_
