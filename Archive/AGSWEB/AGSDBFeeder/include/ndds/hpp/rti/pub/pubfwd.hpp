/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,22feb13,acr Created
===================================================================== */

#ifndef RTI_DDS_PUB_PUB_FWD_HPP_
#define RTI_DDS_PUB_PUB_FWD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace rti { namespace pub {

class AnyDataWriter;
class AnyDataWriterListener;

template <typename T>
class DataWriterImpl;

class PublisherImpl;

class AcknowledgmentInfo;
class WriteParams;

namespace qos {
    class DataWriterQosImpl;
    class PublisherQosImpl;
}

} }

#endif /* RTI_DDS_PUB_PUB_FWD_HPP_ */
