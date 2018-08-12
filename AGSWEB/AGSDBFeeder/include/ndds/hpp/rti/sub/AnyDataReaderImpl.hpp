/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,18mar13,acr Created
===================================================================== */

#ifndef RTI_DDS_SUB_ANY_DATA_READER_HPP_
#define RTI_DDS_SUB_ANY_DATA_READER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_subscription.h"
#include <rti/core/detail/NativeEntity.hpp>

namespace rti { namespace core { namespace detail {

// Template specialization for AnyDataReader. See generic function in
// NativeEntity.hpp
template<>
OMG_DDS_API dds::sub::AnyDataReader create_from_native_entity<
    dds::sub::AnyDataReader, DDS_DataReader>(
        DDS_DataReader * native_object, bool create_new);

} } } // namespace rti::core::detail


#endif // RTI_DDS_SUB_ANY_DATA_READER_HPP_
