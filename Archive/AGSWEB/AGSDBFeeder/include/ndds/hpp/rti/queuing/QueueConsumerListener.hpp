/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_CONSUMER_LISTENER_HPP_
#define RTI_QUEUING_CONSUMER_LISTENER_HPP_


namespace rti { namespace queuing {

template <typename T>
class QueueConsumer;
    
/**
 * \dref_QueueConsumerListener
 *
 * @headerfile rti/queuing/QueueConsumerListener.hpp
 */
template<typename T>
class QueueConsumerListener {
public:
    virtual ~QueueConsumerListener()
    {
    }

    /**
     * \dref_QueueConsumerListener_on_sample_available
     */
    virtual void on_sample_available(
        QueueConsumer<T>& consumer) = 0;

    /**
     * \dref_QueueConsumerListener_on_shared_reader_queue_matched
     */
    virtual void on_shared_reader_queue_matched(
        QueueConsumer<T>& consumer,
        const dds::core::status::SubscriptionMatchedStatus& status) = 0;
};

/**
 * @ingroup QueueConsumerModule
 * @brief A listener with an empty implementation of all methods
 *
 * You can derive your listener from this class so you don't
 * have to implement the methods you don't need.
 */
template<typename T>
class NoOpQueueConsumerListener: public virtual QueueConsumerListener<T> {
public:
    virtual ~NoOpQueueConsumerListener()
    {
    }

    /**
     * \dref_QueueConsumerListener_on_sample_available
     */
    virtual void on_sample_available(QueueConsumer<T>&)
    {
    }
        
    /**
     * \dref_QueueConsumerListener_on_shared_reader_queue_matched
     */
    virtual void on_shared_reader_queue_matched(
        QueueConsumer<T>&,
        const dds::core::status::SubscriptionMatchedStatus&)
    {
    }
};    
   

} } // namespace rti::queuing

#endif // RTI_QUEUING_CONSUMER_LISTENER_HPP_
