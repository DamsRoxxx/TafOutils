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

#ifndef RTI_DDS_PUB_SUSPENDED_PUBLICATION_HPP_
#define RTI_DDS_PUB_SUSPENDED_PUBLICATION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/pub/Publisher.hpp>
#include <rti/core/Exception.hpp>

#include "dds_c/dds_c_publication.h"

namespace rti { namespace pub {

class SuspendedPublicationImpl {
public:
    explicit SuspendedPublicationImpl(const dds::pub::Publisher& publisher)
        : publisher_ (publisher), suspended_(true)
    {
        DDS_ReturnCode_t retcode =
            DDS_Publisher_suspend_publications(publisher_->native_publisher());
        rti::core::check_return_code(retcode, "suspend publication");
    }

    ~SuspendedPublicationImpl()
    {
        try {
            resume();
        } catch (...) {
            // Prevent exceptions from leaving destructor
        }
    }

    void resume()
    {
        if (suspended_) {
            DDS_ReturnCode_t retcode =
                DDS_Publisher_resume_publications(publisher_->native_publisher());
            rti::core::check_return_code(retcode, "resume publications");
            suspended_ = false;
        }
    }

private:
    dds::pub::Publisher publisher_;
    bool suspended_;
};

} } // namespace rti::pub

#endif // RTI_DDS_PUB_SUSPENDED_PUBLICATION_HPP_
