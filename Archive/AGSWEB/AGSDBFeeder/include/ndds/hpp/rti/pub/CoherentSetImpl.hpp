/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,28mar14,acr Created
============================================================================= */

#ifndef RTI_DDS_PUB_COHERENT_SET_HPP_
#define RTI_DDS_PUB_COHERENT_SET_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/pub/Publisher.hpp>
#include <rti/core/Exception.hpp>

#include "dds_c/dds_c_publication.h"

namespace rti { namespace pub {

class CoherentSetImpl {
public:
    explicit CoherentSetImpl(const dds::pub::Publisher& publisher)
        : publisher_ (publisher), active_(true)
    {
        DDS_ReturnCode_t retcode =
            DDS_Publisher_begin_coherent_changes(publisher_->native_publisher());
        rti::core::check_return_code(retcode, "begin coherent changes");
    }

    ~CoherentSetImpl()
    {
        try {
            end();
        } catch (...) {
            // Prevent exceptions from leaving destructor
        }
    }

    void end()
    {
        if (active_) {
            DDS_ReturnCode_t retcode =
                DDS_Publisher_end_coherent_changes(publisher_->native_publisher());
            rti::core::check_return_code(retcode, "end coherent changes");
            active_ = false;
        }
    }

private:
    dds::pub::Publisher publisher_;
    bool active_;
};

} } // namespace rti::pub

#endif // RTI_DDS_PUB_COHERENT_SET_HPP_
