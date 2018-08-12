/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_DETAIL_REPLIERIMPL_HPP_
#define RTI_QUEUING_DETAIL_REPLIERIMPL_HPP_


// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/sub/SampleInfoImpl.hpp>
#include <rti/request/detail/Common.hpp>
#include <rti/queuing/QueueParams.hpp>
#include <rti/queuing/QueueReplierListener.hpp>
#include <rti/queuing/detail/QueueSupportImpl.hpp>
#include <rti/queuing/detail/QueueProducerImpl.hpp>
#include <rti/queuing/detail/QueueConsumerImpl.hpp>


namespace rti { namespace queuing { namespace detail {
    

/**
 */
template <typename TReq, typename TRep>
class QueueReplierImpl
    : public rti::core::detail::RetainableType<QueueReplierImpl<TReq, TRep> > {
public:
    typedef rti::queuing::QueueReplierListener<TReq, TRep> Listener;

    /* producer and consumer are created disabled  */
    explicit QueueReplierImpl(
        const rti::queuing::QueueReplierParams& parameters,       
        const rti::core::Guid& replier_guid)
            : listener_(NULL),
              consumer_(get_consumer_params(parameters), false, NULL, replier_guid),
              producer_(get_producer_params(parameters), false, NULL, consumer_.guid()),
              internal_producer_listener_(NULL),
              internal_consumer_listener_(NULL),
              is_closed_(false)
    {
       
    }
    
    void initialize(
        rti::queuing::QueueProducerListener<TRep>* producer_listener,    
        rti::queuing::QueueConsumerListener<TReq>* consumer_listener,   
        Listener* replier_listener,
        bool is_enabled) 
    {
        internal_producer_listener_ = producer_listener;
        internal_consumer_listener_ = consumer_listener;
        consumer_.listener(
             internal_consumer_listener_,
             dds::core::status::StatusMask::all());
        producer_.listener(
             internal_producer_listener_,
             dds::core::status::StatusMask::all());
        
        if (replier_listener) {
            listener(replier_listener, dds::core::status::StatusMask::all());
        }
        
        if (is_enabled) 
        {  
            enable(); 
        }
    }
    
      
    Listener* listener() 
    {
        return listener_; 
    }
    
    /* event_mask is required by listener binder and has no effect */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask&)
    {
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
    }
    
    rti::pub::WriteParams get_write_params_for_related_request(
        rti::pub::WriteParams& write_params, 
        const dds::sub::SampleInfo& related_request_info) 
    {
        write_params.related_sample_identity(
            related_request_info->related_original_publication_virtual_sample_identity());
        write_params.related_source_guid(
            related_request_info->related_source_guid());
        return write_params;
    }
    
    dds::sub::LoanedSamples<TReq> receive_request(
        const dds::core::Duration& max_wait)
    {
        return consumer_.receive_samples(max_wait);
    }   
    
    void send_reply(const TRep& data, rti::pub::WriteParams& write_params) 
    {
        producer_.send_sample(data, write_params);
    }

    void send_reply(
        const TRep& data,
        const dds::sub::SampleInfo& related_request_info) 
    {
        rti::pub::WriteParams write_params;
        get_write_params_for_related_request(write_params, related_request_info);
        send_reply(data, write_params);
    }
    
    void acknowledge_request(
        const dds::sub::SampleInfo& sample_info, 
        bool is_positive_acknowledgent) 
    { 
        consumer_.acknowledge_sample(sample_info, is_positive_acknowledgent);
    }
    
    void acknowledge_all( 
        bool is_positive_acknowledgent) 
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
            
    rti::queuing::QueueConsumer<TReq> consumer() const
    {
        return consumer_;
    }
    
    rti::queuing::QueueProducer<TRep> producer() const
    {
        return producer_;
    }
    
    void send_availability(ConsumerAvailabilityParams availability_params) 
    {
        consumer_.send_availability(availability_params);
    }
    
     bool has_matching_request_reader_queue()
    {
        return consumer_.has_matching_reader_queue();
    }
    
    bool has_matching_reply_reader_queue()
    {
        return producer_.has_matching_reader_queue();
    }
    
    bool wait_for_requests(const dds::core::Duration& max_wait)
    {
        return consumer_.wait_for_samples(max_wait);
    }
    
    bool wait_for_requests(int min_count, const dds::core::Duration& max_wait)
    {
        return consumer_.wait_for_samples(min_count, max_wait);
    }
    
    dds::sub::LoanedSamples<TReq> receive_requests(const dds::core::Duration& max_wait) 
    {
        return consumer_.receive_samples(max_wait);
    }
    
    dds::sub::LoanedSamples<TReq> receive_requests(
            int min_count, 
            int max_count,
            const dds::core::Duration& max_wait) 
    {
        return consumer_.receive_samples(min_count, max_count, max_wait);
    }
    
    dds::sub::LoanedSamples<TReq> take_requests()
    {
        return consumer_.take_samples();
    }
    
    dds::sub::LoanedSamples<TReq> take_requests(int max_count)
    {
        return consumer_.take_samples(max_count);
    }
    
    dds::sub::LoanedSamples<TReq> read_requests()
    {
        return consumer_.read_samples();
    }
    
    dds::sub::LoanedSamples<TReq> read_requests(int max_count)
    {
        return consumer_.read_samples(max_count);
    }
    
    dds::pub::DataWriter<TRep> writer() const
    {
        return producer_.writer();
    }
    
    dds::sub::DataReader<TReq> reader() const
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
    
    ~QueueReplierImpl() 
    {
        close();
    }  
    
private: 
    
    rti::queuing::QueueConsumerParams get_consumer_params(
        const rti::queuing::QueueReplierParams& parameters) 
    {
        rti::queuing::QueueConsumerParams consumer_params(parameters.participant());
        consumer_params.service_name(parameters.service_name());
        consumer_params.request_topic_name(parameters.request_topic_name());
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
        const rti::queuing::QueueReplierParams& parameters) 
    {
        rti::queuing::QueueProducerParams producer_params(parameters.participant());
        producer_params.service_name(parameters.service_name());
        producer_params.request_topic_name(
            get_queue_reply_topic_name(
                parameters.request_topic_name(), 
                parameters.reply_topic_name()));
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
    
    Listener* listener_;
    rti::queuing::QueueConsumer<TReq> consumer_;
    rti::queuing::QueueProducer<TRep> producer_;
    rti::queuing::QueueProducerListener<TRep>* internal_producer_listener_;
    rti::queuing::QueueConsumerListener<TReq>* internal_consumer_listener_;
    bool is_closed_;
};

} } } // namespace rti::request::detail

#endif // RTI_QUEUING_DETAIL_REPLIERIMPL_HPP_

