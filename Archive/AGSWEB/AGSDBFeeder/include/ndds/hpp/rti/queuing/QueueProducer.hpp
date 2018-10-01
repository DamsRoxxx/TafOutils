/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_PRODUCER_HPP_
#define RTI_QUEUING_PRODUCER_HPP_

#include <dds/sub/LoanedSamples.hpp>
#include <dds/core/status/Status.hpp>
#include <rti/queuing/QueueProducerListener.hpp>
#include <rti/queuing/detail/QueueProducerImpl.hpp>

namespace rti { namespace queuing {
   
/**
 * \dref_QueueProducer
 *
 * @headerfile rti/queuing/QueueProducer.hpp
 */
template <typename T>
class QueueProducer
    : public dds::core::Reference< detail::QueueProducerImpl<T> > {
public:

    typedef detail::QueueProducerImpl<T> Delegate;
    typedef dds::core::Reference<Delegate> Base;
    typedef QueueProducerListener<T> Listener;
    typedef typename dds::core::smart_ptr_traits<Delegate >::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<Delegate >::weak_ref_type weak_ref_type;


    OMG_DDS_REF_TYPE(QueueProducer, dds::core::Reference, Delegate);
     
    /**
     * \dref_QueueProducer_new_w_params
     */
    explicit QueueProducer(
        const QueueProducerParams& params, 
        bool is_enabled = true,
        Listener* producer_listener = NULL, 
        const rti::core::Guid& producer_guid = rti::core::Guid::unknown())
            : Base(new Delegate(params, producer_guid))
    {
        /* The listener cannot be passed to the base class constructor because 
         * the listener needs the base class to be constructed. We use the
         * following initialize method to set the listener and finish the base
         * class construction. */
        this->delegate()->initialize(
                new ProducerInternalListener(*this->delegate()),
                producer_listener,
                is_enabled);
        this->delegate()->remember_reference(this->delegate());
    }
    
    QueueProducer(ref_type delegate_ref)
        : Base(delegate_ref)
    {
        this->delegate()->remember_reference(this->delegate());
    }
    
    ~QueueProducer()
    {
    }

    /**
     * @brief Sets the listener associated with this producer.
     *
     * @param the_listener The QueueProducerListener to set
     * @param event_mask The dds::core::status::StatusMask associated with the listener  
     */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask& event_mask = dds::core::status::StatusMask::none())
    {
        this->delegate()->listener(the_listener, event_mask);
    }
    
    /**
   * @brief Returns the listener currently associated with this Producer.
   *
   * If there is no listener it returns NULL.
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }
    

    /**
     * \dref_QueueProducer_enable
     */ 
    void enable() {
        this->delegate()->enable();
    }
    
    /**
     * \dref_QueueProducer_send_sample
     */    
    void send_sample(const T& sample)
    {
        this->delegate()->send_sample(sample);
    }
    
    /**
     * \dref_QueueProducer_send_sample_w_write_params
     */ 
    void send_sample(const T& sample, rti::pub::WriteParams& write_params)
    {
        this->delegate()->send_sample(sample, write_params);
    }
    
    /**
     * \dref_QueueProducer_wait_for_acknowledgements
     */
    bool wait_for_acknowledgments(const dds::core::Duration& max_wait) {
        return this->delegate()->wait_for_acknowledgments(max_wait);
    }
    
    /**
     * \dref_QueueProducer_wait_for_sample_acknowledgement
     */
    bool wait_for_acknowledgments(
        const rti::core::SampleIdentity& identity,
        const dds::core::Duration& max_wait) 
    {
        return this->delegate()->wait_for_acknowledgments(identity, max_wait);
    }
    
    /**
     * \dref_QueueProducer_get_datawriter
     */
    dds::pub::DataWriter<T> writer() const
    {
        return this->delegate()->writer();
    }
    
    /**
     * \dref_QueueProducer_get_guid
     */
    rti::core::Guid guid() const 
    {
        return this->delegate()->guid();
    }
    
    /**
     * \dref_QueueProducer_has_matching_shared_reader_queue
     */
    bool has_matching_reader_queue()
    {
        return this->delegate()->has_matching_reader_queue();
    }
    
    void close() 
    {
        this->delegate()->close();
    }
    
private:
    /* We need to pass a QueueProducer<T> object to the user so we are forced to
     * define the internal listener here instead of in the implementation */
    class ProducerInternalListener : public dds::pub::NoOpDataWriterListener<T> {
        public:

        void on_application_acknowledgment(
            dds::pub::DataWriter<T>&,
            const rti::pub::AcknowledgmentInfo& info) 
        {
            /* process function controls whether or not the user's listener
             * should be called */
            if (producer_impl.process_received_acknowledgment(info)) {
                Listener* listener = producer_impl.listener();
                if (listener != NULL) {
                    // Only obtain shared_ptr if calling user listener
                    QueueProducer producer(producer_impl.get_reference());
                    listener->on_sample_acknowledged(producer, info);
                }
            }
        }

        void on_publication_matched(
            dds::pub::DataWriter<T>&,
            const dds::core::status::PublicationMatchedStatus& status) 
        { 
                /* process function controls whether or not the user's listener 
                 * should be called */
                if (producer_impl.process_on_publication_matched(status)) {
                    Listener* listener = producer_impl.listener();
                    if (listener != NULL) {
                        // Only obtain shared_ptr if calling user listener
                        QueueProducer producer(producer_impl.get_reference());
                        listener->on_shared_reader_queue_matched(
                                producer,
                                status);
                    }
                }
        }
        
        ProducerInternalListener(detail::QueueProducerImpl<T>& producer)
            : producer_impl(producer)
        {
        }
        
    private:
        detail::QueueProducerImpl<T>& producer_impl;
    };
    
    /* This class should hold no state. */
};


} } // namespace rti::queuing

#endif // RTI_QUEUING_PRODUCER_HPP_
