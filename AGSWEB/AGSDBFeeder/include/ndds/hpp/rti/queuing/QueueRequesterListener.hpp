/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_REQUESTER_LISTENER_HPP_
#define RTI_QUEUING_REQUESTER_LISTENER_HPP_


namespace rti { namespace queuing {

template <typename TReq, typename TRep >
class QueueRequester;
    
/**
 * \dref_QueueRequesterListener
 *
 * @headerfile rti/queuing/QueueRequesterListener.hpp
 */
template<typename TReq, typename TRep >
class QueueRequesterListener {
public:
    virtual ~QueueRequesterListener()
    {
    }

    /**
     * \dref_QueueRequesterListener_on_request_acknowledged
     */
    virtual void on_request_acknowledged(
        QueueRequester<TReq,TRep>& requester, 
        const rti::pub::AcknowledgmentInfo &info) = 0;
    
    /**
     * \dref_QueueRequesterListener_on_reply_available
     */
    virtual void on_reply_available(
        QueueRequester<TReq,TRep>& requester) = 0;

    /**
     * \dref_QueueRequesterListener_on_request_shared_reader_queue_matched
     */
    virtual void on_request_shared_reader_queue_matched(
        QueueRequester<TReq,TRep>& requester,
        const dds::core::status::PublicationMatchedStatus& status) = 0;
    
    /**
     * \dref_QueueRequesterListener_on_reply_shared_reader_queue_matched
     */
    virtual void on_reply_shared_reader_queue_matched(
        QueueRequester<TReq,TRep>& requester,
        const dds::core::status::SubscriptionMatchedStatus& status) = 0;
};

/**
 * @ingroup QueueRequesterModule
 * @headerfile rti/queuing/QueueRequesterListener.hpp
 * @brief A listener with an empty implementation of all methods
 *
 * You can derive your listener from this class so you don't
 * have to implement the methods you don't need.
 */
template<typename TReq, typename TRep >
class NoOpQueueRequesterListener: public virtual QueueRequesterListener<TReq, TRep> {
public:
    virtual ~NoOpQueueRequesterListener()
    {
    }

    /**
     * \dref_QueueRequesterListener_on_request_acknowledged
     */
    virtual void on_request_acknowledged(
        QueueRequester<TReq,TRep>&,
        const rti::pub::AcknowledgmentInfo&)
    {
    }
    
    /**
     * \dref_QueueRequesterListener_on_reply_available
     */
    virtual void on_reply_available(QueueRequester<TReq,TRep>&)
    {
    }

    /**
     * \dref_QueueRequesterListener_on_request_shared_reader_queue_matched
     */
    virtual void on_request_shared_reader_queue_matched(
        QueueRequester<TReq,TRep>&,
        const dds::core::status::PublicationMatchedStatus&)
    {
    }
    
    /**
     * \dref_QueueRequesterListener_on_reply_shared_reader_queue_matched
     */
    virtual void on_reply_shared_reader_queue_matched(
        QueueRequester<TReq,TRep>&,
        const dds::core::status::SubscriptionMatchedStatus&)
    {
    }
};    
   

} } // namespace rti::queuing

#endif // RTI_QUEUING_REQUESTER_LISTENER_HPP_
