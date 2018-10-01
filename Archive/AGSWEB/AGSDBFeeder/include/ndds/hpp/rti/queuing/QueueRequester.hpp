/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_REQUESTER_HPP_
#define RTI_QUEUING_REQUESTER_HPP_

#include <dds/sub/LoanedSamples.hpp>
#include <dds/core/status/Status.hpp>
#include <rti/queuing/QueueRequesterListener.hpp>
#include <rti/queuing/QueueParams.hpp>
#include <rti/queuing/detail/QueueRequesterImpl.hpp>

namespace rti { namespace queuing {   
    
/**
 * \dref_QueueRequester
 *
 * @headerfile rti/queuing/QueueRequester.hpp
 */
template <typename TReq, typename TRep>
class QueueRequester
    : public dds::core::Reference< detail::QueueRequesterImpl<TReq, TRep> > {
public:

    typedef detail::QueueRequesterImpl<TReq, TRep> Delegate;
    typedef dds::core::Reference<Delegate> Base;
    typedef QueueRequesterListener<TReq, TRep> Listener;
    typedef typename dds::core::smart_ptr_traits<Delegate >::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<Delegate >::weak_ref_type weak_ref_type;


    OMG_DDS_REF_TYPE(QueueRequester, dds::core::Reference, Delegate);
    
    /**
     * \dref_QueueRequester_new_w_params
     */
    explicit QueueRequester(
        const QueueRequesterParams& params,    
        bool is_enabled = true,    
        Listener* requester_listener = NULL,    
        const rti::core::Guid& requester_guid = rti::core::Guid::unknown())
            : Base(new Delegate(params, requester_guid))
    {
        /* The listeners cannot be passed to the base class constructor because 
         * the listeners need the base class to be constructed. We use the
         * following initialize method to set the listeners and finish the
         * base class construction. */
        this->delegate()->initialize(
                new RequesterInternalProducerListener(this->delegate()), 
                new RequesterInternalConsumerListener(this->delegate()),
                requester_listener,
                is_enabled);
        
        this->delegate()->remember_reference(this->delegate());
    }
    
    QueueRequester(ref_type delegate_ref)
        : Base(delegate_ref)
    {
        this->delegate()->remember_reference(this->delegate());
    }
    
    /**
     * @brief Sets the listener associated with this queue requester.
     *
     * @param the_listener The QueueRequesterListener to set
     * @param event_mask The dds::core::status::StatusMask associated with the listener  
     */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask& event_mask = dds::core::status::StatusMask::none())
    {
        this->delegate()->listener(the_listener, event_mask);
    }
    
    /**
    * @brief Returns the listener currently associated with this requester.
    *
    * If there is no listener it returns NULL.
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }
    
    /**
     * \dref_QueueRequester_enable
     */ 
    void enable() 
    {
        this->delegate()->enable();
    } 
    
    /**
     * \dref_QueueRequester_receive_replies_simple
     */
    dds::sub::LoanedSamples<TRep> receive_replies(
            const dds::core::Duration& max_wait) 
    {
        return this->delegate()->receive_replies(max_wait);
    }
    
    /**
     * \dref_QueueRequester_receive_replies
     */
    dds::sub::LoanedSamples<TRep> receive_replies(
            int min_count, 
            int max_count,
            const dds::core::Duration& max_wait) 
    {
        return this->delegate()->receive_replies(min_count, max_count, max_wait);
    }
    
    /**
     * \dref_QueueRequester_take_replies_simple
     */
    dds::sub::LoanedSamples<TRep> take_replies()
    {
        return this->delegate()->take_replies();
    }
    
    /**
     * \dref_QueueRequester_take_replies
     */
    dds::sub::LoanedSamples<TRep> take_replies(int max_count)
    {
        return this->delegate()->take_replies(max_count);
    }
    
    /**
     * \dref_QueueRequester_read_replies_simple
     */
    dds::sub::LoanedSamples<TRep> read_replies()
    {
        return this->delegate()->read_replies();
    }
    
    /**
     * \dref_QueueRequester_read_replies_w_related_request
     */
    dds::sub::LoanedSamples<TRep> read_replies(int max_count)
    {
        return this->delegate()->read_replies(max_count);
    }
    
    /**
     * \dref_QueueRequester_take_replies_w_related_request
     */
    dds::sub::LoanedSamples<TRep> take_replies(
        int max_count,
        const rti::core::SampleIdentity& related_request_id) 
    {
        return this->delegate()->take_replies(max_count, related_request_id);
    } 
    
    /**
     * \dref_QueueRequester_take_replies_w_related_request_simple
     */
    dds::sub::LoanedSamples<TRep> take_replies(
        const rti::core::SampleIdentity& related_request_id) 
    {
        return this->delegate()->take_replies(related_request_id);
    } 
    
    dds::sub::LoanedSamples<TRep> read_replies(
        int max_count,
        const rti::core::SampleIdentity& related_request_id) 
    {
        return this->delegate()->read_replies(max_count, related_request_id);
    } 
    
    /**
     * \dref_QueueRequester_read_replies_w_related_request_simple
     */
    dds::sub::LoanedSamples<TRep> read_replies(
        const rti::core::SampleIdentity& related_request_id) 
    {
        return this->delegate()->read_replies(related_request_id);
    } 
    
    /**
     * \dref_QueueRequester_send_request
     */
    void send_request(const TReq& request) 
    {
        this->delegate()->send_request(request);
    }
    
    /**
     * \dref_QueueRequester_send_request_w_write_params
     */
    void send_request(const TReq& request, rti::pub::WriteParams& write_params)
    {
        this->delegate()->send_request(request, write_params);
    }
 
    /**
     * \dref_QueueRequester_acknowledge_reply
     */
    void acknowledge_reply(
        const dds::sub::SampleInfo& sample_info, 
        bool is_positive_acknowledgment = true) 
    { 
        this->delegate()->acknowledge_reply(sample_info, is_positive_acknowledgment);
    }
    
    /**
     * \dref_QueueRequester_acknowledge_all
     */
    void acknowledge_all( 
        bool is_positive_acknowledgment = true) 
    { 
        this->delegate()->acknowledge_all(is_positive_acknowledgment);
    }
    
    /**
     * \dref_QueueRequester_wait_for_acknowledgements
     */
    bool wait_for_acknowledgments(const dds::core::Duration& max_wait) 
    {
        return this->delegate()->wait_for_acknowledgments(max_wait);
    }
    
    /**
     * \dref_QueueRequester_wait_for_sample_acknowledgement
     */
    bool wait_for_acknowledgments(
        const rti::core::SampleIdentity& identity,
        const dds::core::Duration& max_wait) 
    {
        return this->delegate()->wait_for_acknowledgments(identity, max_wait);
    }
    
    /**
     * \dref_QueueRequester_get_consumer
     */
    rti::queuing::QueueConsumer<TRep> consumer() const
    {
        return this->delegate()->consumer();
    }
    
    /**
     * \dref_QueueRequester_get_producer
     */
    rti::queuing::QueueProducer<TReq> producer() const
    {
        return this->delegate()->producer();
    }
    
   /**
     * \dref_QueueRequester_wait_for_replies_simple
     */
    bool wait_for_replies(const dds::core::Duration& max_wait)
    {
        return this->delegate()->wait_for_replies(max_wait);
    } 
    
    /**
     * \dref_QueueRequester_wait_for_replies
     */
    bool wait_for_replies(int min_count, const dds::core::Duration& max_wait)
    {
        return this->delegate()->wait_for_replies(min_count, max_wait);
    } 
    
    /**
     * \dref_QueueRequester_wait_for_replies_w_related_request
     */
    bool wait_for_replies(
        int min_count,
        const dds::core::Duration& max_wait,
        const rti::core::SampleIdentity& related_request_id)
    {
        return this->delegate()->wait_for_replies(min_count, max_wait, related_request_id);
    }
    
    /**
     * \dref_QueueRequester_send_availability
     */
    void send_availability(ConsumerAvailabilityParams parameters) 
    {
        this->delegate()->send_availability(parameters);
    }
    
    /**
     * \dref_QueueRequester_has_matching_request_shared_reader_queue
     */
    bool has_matching_request_reader_queue()
    {
        return this->delegate()->has_matching_request_reader_queue();
    }
    
    /**
     * \dref_QueueRequester_has_matching_reply_shared_reader_queue
     */
    bool has_matching_reply_reader_queue()
    {
        return this->delegate()->has_matching_reply_reader_queue();
    }
    
    /**
     * \dref_QueueRequester_get_datawriter
     */
    dds::pub::DataWriter<TReq> writer() const
    {
        return this->delegate()->writer();
    }
    
    /**
     * \dref_QueueRequester_get_datareader
     */
    dds::sub::DataReader<TRep> reader() const
    {
        return this->delegate()->reader();
    }
    
    /**
     * \dref_QueueRequester_get_guid
     */
    rti::core::Guid guid() {
        return this->delegate()->guid();
    }
    
    void close() 
    {
        this->delegate()->close();
    }
    
private:
    /* We need to pass a QueueRequester<T> object to the user so we are forced to
     * define the internal listener here instead of in the implementation */
    class RequesterInternalProducerListener : public rti::queuing::NoOpQueueProducerListener<TReq> {
        public:

        virtual void on_sample_acknowledged(
            QueueProducer<TReq>&,
            const rti::pub::AcknowledgmentInfo &info) 
        { 
            ref_type delegate_ref = requester_weak_ref_.lock();
            if (delegate_ref) {
                QueueRequester<TReq, TRep> requester_(delegate_ref);    
                /* process function controls whether or not the user's listener 
                 * should be called */
                if (requester_.delegate()->process_received_acknowledgment(info, requester_)) 
                {
                    Listener* listener = requester_.delegate()->listener();
                    if (listener) {
                        listener->on_request_acknowledged(requester_, info);
                    }
                }
            }  
        }
        
        virtual void on_shared_reader_queue_matched(
            QueueProducer<TReq>&,
            const dds::core::status::PublicationMatchedStatus& status) 
        {
            ref_type delegate_ref = requester_weak_ref_.lock();
            if (delegate_ref) {
                QueueRequester<TReq, TRep> requester_(delegate_ref);    
                Listener* listener = requester_.delegate()->listener();
                if (listener) {
                    listener->on_request_shared_reader_queue_matched(requester_, status);
                }
            }  
        }
        
        RequesterInternalProducerListener(ref_type requester) 
            : requester_weak_ref_(requester)
        {
            
        }
        
    private:
        weak_ref_type requester_weak_ref_;
    };
    
    
    class RequesterInternalConsumerListener : public rti::queuing::NoOpQueueConsumerListener<TRep> {
        public:

        virtual void on_sample_available(QueueConsumer<TRep>&)
        { 
            ref_type delegate_ref = requester_weak_ref_.lock();
            if (delegate_ref) {
                QueueRequester<TReq, TRep> requester_(delegate_ref);    
                if (requester_.delegate()->process_on_reply_available(requester_)) {
                    Listener* listener = requester_.delegate()->listener();
                    if (listener != NULL) {
                        listener->on_reply_available(requester_);
                    }
                }
            }  
        }
        
        virtual void on_shared_reader_queue_matched(
            QueueConsumer<TRep>&,
            const dds::core::status::SubscriptionMatchedStatus& status)
        {
            ref_type delegate_ref = requester_weak_ref_.lock();
            if (delegate_ref) {
                QueueRequester<TReq, TRep> requester_(delegate_ref);    
                Listener* listener = requester_.delegate()->listener();
                if (listener != NULL) {
                    listener->on_reply_shared_reader_queue_matched(
                            requester_, status);
                }
            }  
        }
        
        
        RequesterInternalConsumerListener(ref_type requester) 
            : requester_weak_ref_(requester)
        {
            
        }
        
    private:
        weak_ref_type requester_weak_ref_;
    };
    
    /* This class should hold no state. */
};


} } // namespace rti::queuing

#endif // RTI_QUEUING_REQUESTER_HPP_
