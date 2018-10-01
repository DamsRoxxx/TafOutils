/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20mar14,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_COND_STATUS_HANDLER_HPP_
#define RTI_DDS_SUB_COND_STATUS_HANDLER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/corefwd.hpp>
#include <dds/sub/subfwd.hpp>
#include <dds/sub/AnyDataReader.hpp>
#include <dds/sub/status/DataState.hpp>

#include <rti/core/cond/ConditionImpl.hpp>

namespace rti { namespace sub { namespace cond {

/**
 * @ingroup DDSAsyncWaitSetModule
 * 
 * @details \dref_DataReaderStatusConditionHandler
 */
template <typename T>
class DataReaderStatusConditionHandler {        
    
public:

    /**    
     * @details \dref_DataReaderStatusConditionHandler_new
     */
    DataReaderStatusConditionHandler(
            dds::sub::DataReader<T>& reader,
            dds::sub::DataReaderListener<T>* listener,
            const dds::core::status::StatusMask& listener_mask)
        :_reader(reader), _listener(listener), _mask(listener_mask) 
    {
    }
        
    void operator()(dds::core::cond::Condition) 
    {
        noitfyListener(_reader.status_changes() & _mask);
    }

    void noitfyListener(
            dds::core::status::StatusMask masked_and_active_states) 
    {
        using namespace dds::core::status;
        
        if ((masked_and_active_states
                & StatusMask::requested_deadline_missed()) != 0) {
            _listener->on_requested_deadline_missed(
                    _reader,
                    _reader.requested_deadline_missed_status());
        }

        if ((masked_and_active_states
                & StatusMask::requested_incompatible_qos()) != 0) {
            _listener->on_requested_incompatible_qos(
                    _reader,
                    _reader.requested_incompatible_qos_status());
        }

        if ((masked_and_active_states
                & StatusMask::sample_lost()) != 0) {
            _listener->on_sample_lost(
                    _reader,
                    _reader.sample_lost_status());
        }

        if ((masked_and_active_states
                & StatusMask::sample_rejected()) != 0) {
            _listener->on_sample_rejected(
                    _reader,
                    _reader.sample_rejected_status());
        }

        if ((masked_and_active_states
                & StatusMask::data_available()) != 0) {
            _listener->on_data_available(_reader);
        }

        if ((masked_and_active_states
                & StatusMask::liveliness_changed()) != 0) {
            _listener->on_liveliness_changed(
                    _reader,
                    _reader.liveliness_changed_status());
        }

        if ((masked_and_active_states
                & StatusMask::subscription_matched()) != 0) {
            _listener->on_subscription_matched(
                    _reader,
                    _reader.subscription_matched_status());
        }
    }

private:    
    
    dds::sub::DataReader<T>& _reader;
    dds::sub::DataReaderListener<T>* _listener;
    const dds::core::status::StatusMask _mask;
};

}  } }

#endif // RTI_DDS_SUB_COND_STATUS_HANDLER_HPP_
