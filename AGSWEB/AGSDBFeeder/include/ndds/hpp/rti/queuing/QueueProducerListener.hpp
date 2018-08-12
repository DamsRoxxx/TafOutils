/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

*/

#ifndef RTI_QUEUING_PRODUCER_LISTENER_HPP_
#define RTI_QUEUING_PRODUCER_LISTENER_HPP_

#include <dds/core/status/Status.hpp>
#include <rti/pub/AcknowledgmentInfo.hpp>

namespace rti { namespace queuing {

template <typename T>
class QueueProducer;

/**
 * \dref_QueueProducerListener
 *
 * @headerfile rti/queuing/QueueProducerListener.hpp
 */
template<typename T>
class QueueProducerListener {
public:
    virtual ~QueueProducerListener()
    {
    }

    /**
     * \dref_QueueProducerListener_on_sample_acknowledged
     */
    virtual void on_sample_acknowledged(
        QueueProducer<T>& producer, 
        const rti::pub::AcknowledgmentInfo &info) = 0;

    /**
     * \dref_QueueProducerListener_on_shared_reader_queue_matched
     */
    virtual void on_shared_reader_queue_matched(
        QueueProducer<T>& producer,
        const dds::core::status::PublicationMatchedStatus& status) = 0;
};

/**
 * @ingroup QueueProducerModule
 * @brief A listener with an empty implementation of all methods
 *
 * You can derive your listener from this class so you don't
 * have to implement the methods you don't need.
 */
template<typename T>
class NoOpQueueProducerListener: public virtual QueueProducerListener<T> {
public:
    virtual ~NoOpQueueProducerListener()
    {
    }

    /**
     * \dref_QueueProducerListener_on_sample_acknowledged
     */
    virtual void on_sample_acknowledged(
        QueueProducer<T>&,
        const rti::pub::AcknowledgmentInfo&)
    {
    }
        
    /**
     * \dref_QueueProducerListener_on_shared_reader_queue_matched
     */
    virtual void on_shared_reader_queue_matched(
        QueueProducer<T>&,
        const dds::core::status::PublicationMatchedStatus&)
    {
    }
};

} } // namespace rti::queuing

#endif // RTI_QUEUING_PRODUCER_LISTENER_HPP_
