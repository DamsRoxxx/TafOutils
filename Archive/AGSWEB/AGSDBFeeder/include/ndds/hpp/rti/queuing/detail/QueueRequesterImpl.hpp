/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_DETAIL_REQUESTERIMPL_HPP_
#define RTI_QUEUING_DETAIL_REQUESTERIMPL_HPP_


// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include <rti/core/detail/NativeConversion.hpp>
#include <dds/core/cond/GuardCondition.hpp>
#include <rti/request/detail/Common.hpp>
#include <rti/queuing/QueueParams.hpp>
#include <rti/queuing/QueueRequesterListener.hpp>
#include <rti/queuing/detail/QueueSupportImpl.hpp>
#include <rti/queuing/detail/QueueProducerImpl.hpp>
#include <rti/queuing/detail/QueueConsumerImpl.hpp>


namespace rti { namespace queuing {

template <typename TReq, typename TRep>
class QueueRequester;

}}

namespace rti { namespace queuing { namespace detail {
    
XMQCPP2DllExport
void create_queue_correlation_index(DDS_DataReader *reader);

class IndexConditionImpl : public rti::sub::cond::ReadConditionImpl {
public:
    IndexConditionImpl(
        DDS_IndexCondition * native_condition,
        const dds::sub::AnyDataReader& reader)
        :  rti::sub::cond::ReadConditionImpl(
            DDS_IndexCondition_as_readcondition(native_condition),
            reader)
    {
    }
};    
   
XMQCPP2DllExport
dds::sub::cond::ReadCondition create_queue_correlation_condition(
    dds::sub::AnyDataReader reader,
    dds::sub::status::SampleState sample_state,
    const rti::core::SampleIdentity& related_request);

/**
 */
template <typename TReq, typename TRep>
class QueueRequesterImpl
    : public rti::core::detail::RetainableType<QueueRequesterImpl<TReq, TRep> > {
public:
    typedef rti::queuing::QueueRequesterListener<TReq, TRep> Listener;
    
    /* producer and consumer are created disabled  */
    explicit QueueRequesterImpl(
        const rti::queuing::QueueRequesterParams& parameters,       
        const rti::core::Guid& requester_guid)
            : waiting_(false),
              listener_(NULL),
              consumer_(get_consumer_params(parameters), false, NULL, requester_guid),
              producer_(get_producer_params(parameters), false, NULL, consumer_.guid()),
              internal_producer_listener_(NULL),
              internal_consumer_listener_(NULL),
              is_closed_(false)
    {
        
    }
    
     void initialize(
        rti::queuing::QueueProducerListener<TReq>* producer_listener,    
        rti::queuing::QueueConsumerListener<TRep>* consumer_listener,    
        Listener* requester_listener,
        bool is_enabled) 
    {
        /* The ConsumerImpl object is required to construct the listeners.
         * The construction of the ConsumerImpl object is then splitted
         * out in two stages, a first stage carried out in the constructor and a
         * second stage (once listeners are available) in this initialize method. */
        internal_producer_listener_ = producer_listener;
        internal_consumer_listener_ = consumer_listener;
        consumer_.listener(
             internal_consumer_listener_,
             dds::core::status::StatusMask::all());
        producer_.listener(
             internal_producer_listener_,
             dds::core::status::StatusMask::all());
        
        if (requester_listener) {
            listener(requester_listener, dds::core::status::StatusMask::all());
        }
        
        if (is_enabled) 
        {  
            enable(); 
        }
    }
    
      
    Listener* listener() {
        return listener_; 
    }
      
    
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask&)
    {
        /* event_mask is required by listener binder and has no effect */
        listener_ = the_listener;
        if (listener_ == NULL) {
            this->unretain();
        } else {
            this->retain();
        }
    }
    
    bool closed() 
    {
        return is_closed_;
    }
    
    void enable() 
    {
        consumer_.enable();
        producer_.enable();
        
        create_queue_correlation_index(consumer_.delegate()->receiver().reader()->native_reader());
    }
    
    
    dds::sub::LoanedSamples<TRep> receive_replies(const dds::core::Duration& max_wait) 
    {
        return consumer_.receive_samples(max_wait);
    }
    
    dds::sub::LoanedSamples<TRep> receive_replies(
            int min_count, 
            int max_count,
            const dds::core::Duration& max_wait) 
    {
        return consumer_.receive_samples(min_count, max_count, max_wait);
    }
    
    dds::sub::LoanedSamples<TRep> take_replies()
    {
        return consumer_.take_samples();
    }
    
    dds::sub::LoanedSamples<TRep> take_replies(int max_count)
    {
        return consumer_.take_samples(max_count);
    }
    
    dds::sub::LoanedSamples<TRep> read_replies()
    {
        return consumer_.read_samples();
    }
    
    dds::sub::LoanedSamples<TRep> read_replies(int max_count)
    {
        return consumer_.read_samples(max_count);
    }
    
    dds::sub::LoanedSamples<TRep> take_replies(
        int maxCount,
        const rti::core::SampleIdentity& related_request) 
    {
        using dds::sub::cond::ReadCondition;
        using namespace dds::sub::status;
        
        dds::sub::AnyDataReader reader(consumer_.delegate()->receiver().reader());
        ReadCondition correlation_condition = create_queue_correlation_condition(
            reader,
            SampleState::any(),
            related_request);
        
        return consumer_.delegate()->receiver().read_or_take(maxCount, correlation_condition, true);
    } 
    
    dds::sub::LoanedSamples<TRep> take_replies(
        const rti::core::SampleIdentity& related_request) 
    {
        return take_replies(dds::core::LENGTH_UNLIMITED, related_request);
    } 
    
    dds::sub::LoanedSamples<TRep> read_replies(
        int maxCount,
        const rti::core::SampleIdentity& related_request) 
    {
        using dds::sub::cond::ReadCondition;
        using namespace dds::sub::status;
        
        dds::sub::AnyDataReader reader(consumer_.delegate()->receiver().reader());
        ReadCondition correlation_condition = create_queue_correlation_condition(
            reader,
            SampleState::any(),
            related_request);
        
        return consumer_.delegate()->receiver().read_or_take(maxCount, correlation_condition, false);
    } 
    
    dds::sub::LoanedSamples<TRep> read_replies(
        const rti::core::SampleIdentity& related_request) 
    {
        return read_replies(dds::core::LENGTH_UNLIMITED, related_request);
    }     
   
    void send_request(const TReq& data) 
    {
        rti::pub::WriteParams write_params;
        send_request(data, write_params);
    }
    
    void send_request(const TReq& data, rti::pub::WriteParams& write_params) 
    {
        producer_.send_sample(data, write_params);
    }
    
    void acknowledge_reply(
        const dds::sub::SampleInfo& sample_info, 
        bool is_positive_acknowledgent) 
    { 
        consumer_.acknowledge_sample(sample_info, is_positive_acknowledgent);
    }
    
    void acknowledge_all(bool is_positive_acknowledgent) 
    { 
        consumer_.acknowledge_all(is_positive_acknowledgent);
    }
    
    bool wait_for_acknowledgments(const dds::core::Duration& max_wait) 
    {   
        return producer_.wait_for_acknowledgments(max_wait);
    }
    
    bool wait_for_acknowledgments(
        const rti::core::SampleIdentity& identity,
        const dds::core::Duration& max_wait) 
    {
        return producer_.wait_for_acknowledgments(identity, max_wait);
    }
    
    /* returns true if producer listener should be called  */
    bool process_received_acknowledgment(
        const rti::pub::AcknowledgmentInfo&,
        QueueRequester<TReq,TRep>&)
    {
        return true;
    }
    
     /* returns true if producer listener should be called  */
    bool process_on_reply_available(
        QueueRequester<TReq,TRep>&)
    {
        return true;
    }
    
    rti::queuing::QueueConsumer<TRep> consumer() const
    {
        return consumer_;
    }
    
    rti::queuing::QueueProducer<TReq> producer() const
    {
        return producer_;
    }
       
    
    bool wait_for_replies(const dds::core::Duration& max_wait)
    {
        return consumer_.wait_for_samples(max_wait);
    } 
    
    bool wait_for_replies(int min_count, const dds::core::Duration& max_wait)
    {
        return consumer_.wait_for_samples(min_count, max_wait);
    } 
    
    bool wait_for_replies(
        int min_count,
        const dds::core::Duration& max_wait,
        const rti::core::SampleIdentity& related_request)
    {
        using dds::sub::cond::ReadCondition;
        using namespace dds::sub::status;

        dds::sub::AnyDataReader reader(consumer_.delegate()->receiver().reader());
        ReadCondition correlation_condition = create_queue_correlation_condition(
            reader,
            SampleState::not_read(),
            related_request);

        dds::core::cond::WaitSet waitset;
        waitset.attach_condition(correlation_condition);

        ReadCondition initial_condition = create_queue_correlation_condition(
            reader,
            SampleState::any(),
            related_request);

        return consumer_.delegate()->receiver().wait_for_samples(
            min_count,
            max_wait,
            waitset,
            initial_condition,
            correlation_condition);
    }
    
    void send_availability(ConsumerAvailabilityParams availability_params) 
    {
        consumer_.send_availability(availability_params);
    }
    
    bool has_matching_request_reader_queue()
    {
        return producer_.has_matching_reader_queue();
    }
    
    bool has_matching_reply_reader_queue()
    {
        return consumer_.has_matching_reader_queue();
    }
    
    dds::pub::DataWriter<TReq> writer() const
    {
        return producer_.writer();
    }
    
    dds::sub::DataReader<TRep> reader() const
    {
        return consumer_.reader();
    }
    
    rti::core::Guid guid()
    {
        return consumer_.guid();
    }
            
    void close()
    {
        if (internal_producer_listener_ != NULL) {
            producer_.listener(
                NULL,
                dds::core::status::StatusMask::none());
            delete internal_producer_listener_;
            internal_producer_listener_ = NULL;
        }

        if (internal_consumer_listener_ != NULL) {
            consumer_.listener(
                NULL,
                dds::core::status::StatusMask::none());
            delete internal_consumer_listener_;
            internal_consumer_listener_ = NULL;
        }
        is_closed_ = true;
    }
    
    ~QueueRequesterImpl() 
    {
        close();
    }  
   
private: 
    
    rti::queuing::QueueConsumerParams get_consumer_params(
        const rti::queuing::QueueRequesterParams& parameters) 
    {
        rti::queuing::QueueConsumerParams consumer_params(parameters.participant());
        consumer_params.service_name(parameters.service_name());
        consumer_params.request_topic_name(
            get_queue_reply_topic_name(
                parameters.request_topic_name(), 
                parameters.reply_topic_name()));
        consumer_params.qos_profile(
            parameters.qos_library_name(),
            parameters.qos_profile_name());
        consumer_params.datareader_qos(parameters.datareader_qos());
        consumer_params.subscriber(parameters.subscriber());
        consumer_params.shared_subscriber_name(parameters.shared_subscriber_name());
        consumer_params.enable_availability(parameters.enable_availability());
        consumer_params.availability_datawriter_qos(parameters.availability_datawriter_qos());
        consumer_params.entity_name(parameters.entity_name());
        return consumer_params;
    }
    
    rti::queuing::QueueProducerParams get_producer_params(
        const rti::queuing::QueueRequesterParams& parameters) 
    {
        rti::queuing::QueueProducerParams producer_params(parameters.participant());
        producer_params.service_name(parameters.service_name());
        producer_params.request_topic_name(parameters.request_topic_name());
        producer_params.qos_profile(
            parameters.qos_library_name(),
            parameters.qos_profile_name());
        producer_params.datawriter_qos(parameters.datawriter_qos());
        producer_params.subscriber(parameters.subscriber());
        producer_params.shared_subscriber_name(parameters.shared_subscriber_name());
        producer_params.enable_sample_replication(parameters.enable_sample_replication());
        producer_params.enable_wait_for_ack(parameters.enable_wait_for_ack());
        producer_params.entity_name(parameters.entity_name());
        return producer_params;
    }
    
    /* ------------------------------------------------------------ */
    /* ------------------------------------------------------------ */
    /* -------------------- Private variables --------------------- */
    /* ------------------------------------------------------------ */
    /* ------------------------------------------------------------ */
    
    bool waiting_;
    Listener* listener_;
    rti::queuing::QueueConsumer<TRep> consumer_;
    rti::queuing::QueueProducer<TReq> producer_;
    rti::queuing::QueueProducerListener<TReq>* internal_producer_listener_;
    rti::queuing::QueueConsumerListener<TRep>* internal_consumer_listener_;
    bool is_closed_;
};

} } } // namespace rti::request::detail 

#endif // RTI_QUEUING_DETAIL_REQUESTERIMPL_HPP_

