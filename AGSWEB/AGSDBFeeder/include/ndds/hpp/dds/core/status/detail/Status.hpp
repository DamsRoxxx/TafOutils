#ifndef OMG_DDS_CORE_STATUS_DETAIL_STATUS_HPP_
#define OMG_DDS_CORE_STATUS_DETAIL_STATUS_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/status/TStatus.hpp>
#include <rti/core/status/Status.hpp>


namespace dds { namespace core { namespace status { namespace detail {

    typedef dds::core::status::TInconsistentTopicStatus<rti::core::status::InconsistentTopicStatus>
    InconsistentTopicStatus;
    
    typedef dds::core::status::TLivelinessChangedStatus <rti::core::status::LivelinessChangedStatus>
    LivelinessChangedStatus;
    
    typedef dds::core::status::TLivelinessLostStatus<rti::core::status::LivelinessLostStatus>
    LivelinessLostStatus;
    
    typedef dds::core::status::TOfferedDeadlineMissedStatus<rti::core::status::OfferedDeadlineMissedStatus>
    OfferedDeadlineMissedStatus;
    
    typedef dds::core::status::TOfferedIncompatibleQosStatus<rti::core::status::OfferedIncompatibleQosStatus>
    OfferedIncompatibleQosStatus;
    
    typedef dds::core::status::TPublicationMatchedStatus<rti::core::status::PublicationMatchedStatus>
    PublicationMatchedStatus;
    
    typedef dds::core::status::TSampleRejectedStatus< rti::core::status::SampleRejectedStatus >
    SampleRejectedStatus;
    
    typedef dds::core::status::TRequestedDeadlineMissedStatus<rti::core::status::RequestedDeadlineMissedStatus>
    RequestedDeadlineMissedStatus;
    
    typedef dds::core::status::TRequestedIncompatibleQosStatus<rti::core::status::RequestedIncompatibleQosStatus>
    RequestedIncompatibleQosStatus;
    
    typedef dds::core::status::TSampleLostStatus<rti::core::status::SampleLostStatus>
    SampleLostStatus;
    
    typedef dds::core::status::TSubscriptionMatchedStatus<rti::core::status::SubscriptionMatchedStatus>
    SubscriptionMatchedStatus;

} } } } // namespace dds::core::status::detail


#endif /* OMG_DDS_CORE_STATUS_DETAIL_STATUS_HPP_ */
