/* $Id$
 (c) Copyright, Real-Time Innovations, 2013-2016.
 All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_CONSTANTS_HPP_
#define RTI_DDS_CORE_CONSTANTS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace rti { namespace core {

const uint32_t nanosec_per_sec = 1000000000;
const uint32_t millisec_per_sec = 1000;
const uint32_t microsec_per_sec = 1000000;
const uint32_t nanosec_per_millisec = 1000000;
const uint32_t nanosec_per_microsec = 1000;

} } // namespace dds::core

#endif // RTI_DDS_CORE_CONSTANTS_HPP_
