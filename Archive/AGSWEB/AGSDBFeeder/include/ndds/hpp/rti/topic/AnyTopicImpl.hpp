/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,07mar13,acr Created
===================================================================== */

#ifndef RTI_DDS_TOPIC_ANY_TOPIC_IMPL_HPP_
#define RTI_DDS_TOPIC_ANY_TOPIC_IMPL_HPP_

#include <string>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/topic/AnyTopic.hpp>
#include <rti/core/detail/NativeEntity.hpp>

namespace rti { namespace core { namespace detail {

// Template specialization for AnyTopic. See generic function in
// NativeEntity.hpp
template<>
dds::topic::AnyTopic create_from_native_entity<dds::topic::AnyTopic, DDS_Topic>(
    DDS_Topic * native_object, bool create_new);

} } } // namespace rti::core::detail


#endif // RTI_DDS_TOPIC_ANY_TOPIC_IMPL_HPP_
