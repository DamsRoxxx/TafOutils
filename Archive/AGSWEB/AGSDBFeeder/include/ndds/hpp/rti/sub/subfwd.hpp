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

#ifndef RTI_DDS_SUB_SUB_FWD_HPP_
#define RTI_DDS_SUB_SUB_FWD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace rti { namespace sub {

class UntypedDataReader;

template <typename T>
class DataReaderImpl;

class SubscriberImpl;

template <typename T>
class SampleImpl;

template <typename T>
class LoanedSample;

template <typename T>
class DefaultSelector;

template <typename T>
class Selector;

template <typename T>
class ManipulatorSelector;

class SelectorState;

namespace qos {
    class DataReaderQosImpl;
    class SubscriberQosImpl;
}

namespace cond {
    class ReadConditionImpl;
    class QueryConditionImpl;
    
    template <typename T>
    class DataReaderStatusConditionHandler;
}

} }

#endif // RTI_DDS_SUB_SUB_FWD_HPP_
