/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_CONSUMER_HPP_
#define RTI_QUEUING_CONSUMER_HPP_

#include <dds/sub/LoanedSamples.hpp>
#include <dds/core/status/Status.hpp>
#include <rti/queuing/QueueConsumerListener.hpp>
#include <rti/queuing/detail/QueueConsumerImpl.hpp>

namespace rti { namespace queuing {   
    
/**
 * \dref_QueueConsumer
 *
 * @headerfile rti/queuing/QueueConsumer.hpp
 */
template <typename T>
class QueueConsumer
    : public dds::core::Reference< detail::QueueConsumerImpl<T> > {
public:

    typedef detail::QueueConsumerImpl<T> Delegate;
    typedef dds::core::Reference<Delegate> Base;
    typedef QueueConsumerListener<T> Listener;
    typedef typename dds::core::smart_ptr_traits<Delegate >::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<Delegate >::weak_ref_type weak_ref_type;

    OMG_DDS_REF_TYPE(QueueConsumer, dds::core::Reference, Delegate);

    /**
     * \dref_QueueConsumer_new_w_params
     */
    explicit QueueConsumer(
        const QueueConsumerParams& params,
        bool is_enabled = true,    
        Listener* consumer_listener = NULL,        
        const rti::core::Guid& consumer_guid = rti::core::Guid::unknown())
            : Base(new Delegate(params, consumer_guid))
    {
        /* The listener cannot be passed to the base class constructor because 
         * the listener needs the base class to be constructed. We use the
         * following initialize method to set the listener and finish the base
         * class construction. */
        this->delegate()->initialize(
                new ConsumerInternalListener(*this->delegate()),
                consumer_listener,
                is_enabled);
        this->delegate()->remember_reference(this->delegate());
    }
    
    QueueConsumer(ref_type delegate_ref)
        : Base(delegate_ref)
    {
        this->delegate()->remember_reference(this->delegate());
    }
    
    /**
     * @brief Sets the listener associated with this consumer.
     *
     * @param the_listener The QueueConsumerListener to set
     * @param event_mask The dds::core::status::StatusMask associated with the listener  
     */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask& event_mask = dds::core::status::StatusMask::none())
    {
        this->delegate()->listener(the_listener, event_mask);
    }

    /**
     * @brief Returns the listener currently associated with this Consumer.
     *
     * If there is no listener it returns NULL.
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }


    /**
     * \dref_QueueConsumer_enable
     */ 
    void enable() 
    {
        this->delegate()->enable();
    }
    
    /**
     * \dref_QueueConsumer_acknowledge_sample
     */
    void acknowledge_sample(
        const dds::sub::SampleInfo& sample_info, 
        bool is_positive_acknowledgment = true) 
    { 
        this->delegate()->acknowledge_sample(sample_info, is_positive_acknowledgment);
    }
    
    /**
     * \dref_QueueConsumer_acknowledge_all
     */
    void acknowledge_all(bool is_positive_acknowledgment = true) 
    {
        this->delegate()->acknowledge_all(is_positive_acknowledgment);
    }
    
    /**
     * \dref_QueueConsumer_get_datareader
     */
    dds::sub::DataReader<T> reader() const
    {
        return this->delegate()->reader();
    }
    
    /**
     * \dref_QueueConsumer_get_guid
     */
    rti::core::Guid guid() const
    {
        return this->delegate()->guid();
    }
    
    /**
     * \dref_QueueConsumer_receive_samples_simple
     */
    dds::sub::LoanedSamples<T> receive_samples(const dds::core::Duration& max_wait) 
    {
        return this->delegate()->receive_samples(max_wait);
    }
    
    /**
     * \dref_QueueConsumer_receive_samples
     */
    dds::sub::LoanedSamples<T> receive_samples(
            int min_count, 
            int max_count,
            const dds::core::Duration& max_wait) 
    {
        return this->delegate()->receive_samples(min_count, max_count, max_wait);
    }
   
    /**
     * \dref_QueueConsumer_take_samples_simple
     */
    dds::sub::LoanedSamples<T> take_samples()
    {
        return this->delegate()->take_samples();
    }
    
    /**
     * \dref_QueueConsumer_take_samples
     */
    dds::sub::LoanedSamples<T> take_samples(int max_count)
    {
        return this->delegate()->take_samples(max_count);
    }
    
    /**
     * \dref_QueueConsumer_read_samples_simple
     */
    dds::sub::LoanedSamples<T> read_samples()
    {
        return this->delegate()->read_samples();
    }
    
    /**
     * \dref_QueueConsumer_read_samples
     */
    dds::sub::LoanedSamples<T> read_samples(int max_count)
    {
        return this->delegate()->read_samples(max_count);
    }
    
    /**
     * \dref_QueueConsumer_wait_for_samples_simple
     */
    bool wait_for_samples(const dds::core::Duration& max_wait)
    {
        return this->delegate()->wait_for_samples(max_wait);
    }
    
    /**
     * \dref_QueueConsumer_wait_for_samples
     */
    bool wait_for_samples(int min_count, const dds::core::Duration& max_wait)
    {
        return this->delegate()->wait_for_samples(min_count, max_wait);
    }
    
    /**
     * \dref_QueueConsumer_send_availability
     */
    void send_availability(ConsumerAvailabilityParams parameters) 
    {
        this->delegate()->send_availability(parameters);
    }
    
    /**
     * \dref_QueueConsumer_has_matching_shared_reader_queue
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

    /* We need to pass a QueueConsumer<T> object to the user so we are forced to
     * define the internal listener here instead of in the implementation */
    class ConsumerInternalListener : public dds::sub::NoOpDataReaderListener<T> {
    public:

        void on_data_available(dds::sub::DataReader<T>&)
        { 
            Listener* listener = consumer_impl.listener();
            if (listener != NULL) {
                QueueConsumer<T> consumer_(consumer_impl.get_reference());
                listener->on_sample_available(consumer_);
            }
        }

        void on_subscription_matched(
            dds::sub::DataReader<T>&,
            const dds::core::status::SubscriptionMatchedStatus& status) 
        { 
            /* process function controls whether or not the user's listener
             * should be called */
            if (consumer_impl.process_on_subscription_matched(status)) {
                Listener* listener = consumer_impl.listener();
                if (listener != NULL) {
                    QueueConsumer<T> consumer_(consumer_impl.get_reference());
                    listener->on_shared_reader_queue_matched(consumer_, status);
                }
            }
        }

        ConsumerInternalListener(detail::QueueConsumerImpl<T>& consumer)
            : consumer_impl(consumer)
        {
        }
        
    private:
        detail::QueueConsumerImpl<T>& consumer_impl;
    };

   /* This class should hold no state. */
};

} } // namespace rti::queuing

#endif // RTI_QUEUING_CONSUMER_HPP_
