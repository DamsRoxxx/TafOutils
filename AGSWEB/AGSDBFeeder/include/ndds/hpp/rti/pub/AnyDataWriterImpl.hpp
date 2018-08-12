/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,05mar13,acr Created
===================================================================== */

#ifndef RTI_DDS_PUB_ANY_DATA_WRITER_HPP_
#define RTI_DDS_PUB_ANY_DATA_WRITER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_publication.h"
#include <rti/core/detail/NativeEntity.hpp>

namespace rti { namespace core { namespace detail {

// Template specialization for AnyDataWriter. See generic function in
// NativeEntity.hpp
template<>
OMG_DDS_API dds::pub::AnyDataWriter create_from_native_entity<
    dds::pub::AnyDataWriter, DDS_DataWriter>(
        DDS_DataWriter * native_object, bool create_new);

} } } // namespace rti::core::detail


#endif // RTI_DDS_PUB_ANY_DATA_WRITER_HPP_
