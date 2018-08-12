/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,21mar13,acr Created
===================================================================== */

#ifndef RTI_DDS_TOPIC_TOPIC_FWD_HPP_
#define RTI_DDS_TOPIC_TOPIC_FWD_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace rti { namespace topic {

class AnyTopic;

class UntypedTopic;

template <typename T>
class TopicImpl;

template <typename T>
class TopicDescriptionImpl;

template <typename T>
class ContentFilteredTopicImpl;

namespace qos {
    class TopicQosImpl;
}

class ParticipantBuiltinTopicDataImpl;
class TopicBuiltinTopicDataImpl;
class PublicationBuiltinTopicDataImpl;
class SubscriptionBuiltinTopicDataImpl;
class VirtualSubscriptionBuiltinTopicData;
class ServiceRequest;

class FilterImpl;

} }

#endif // RTI_DDS_TOPIC_TOPIC_FWD_HPP_
