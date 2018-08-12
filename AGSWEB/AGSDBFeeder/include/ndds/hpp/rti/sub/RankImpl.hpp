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

#ifndef RTI_DDS_SUB_RANK_IMPL_HPP_
#define RTI_DDS_SUB_RANK_IMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/types.hpp>

#include "ndds/ndds_c.h"

namespace rti { namespace sub {

class RankImpl {
public:
    RankImpl()
        : sample_(0),
          generation_(0),
          absolute_generation_(0)
    {
    }

    RankImpl(
        int32_t sample_rank,
        int32_t generation_rank,
        int32_t absolute_generation_rank)
        : sample_(sample_rank),
          generation_(generation_rank),
          absolute_generation_(absolute_generation_rank)
    {
    }

    int32_t sample() const
    {
        return sample_;
    }

    int32_t generation() const
    {
        return generation_;
    }

    int32_t absolute_generation() const
    {
        return absolute_generation_;
    }

private:
    int32_t sample_;
    int32_t generation_;
    int32_t absolute_generation_;
};

} } // namespace rti::sub

#endif // RTI_DDS_SUB_RANK_IMPL_HPP_
