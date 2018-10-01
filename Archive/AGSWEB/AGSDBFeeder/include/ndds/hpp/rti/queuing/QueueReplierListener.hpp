/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_REPLIER_LISTENER_HPP_
#define RTI_QUEUING_REPLIER_LISTENER_HPP_


namespace rti { namespace queuing {

template <typename TReq, typename TRep >
class QueueReplier;
    
/**
 * \dref_QueueReplierListener
 *
 * @headerfile rti/queuing/QueueReplierListener.hpp
 */
template<typename TReq, typename TRep >
class QueueReplierListener {
public:
    virtual ~QueueReplierListener()
    {
    }

    /**
     * \dref_QueueReplierListener_on_reply_acknowledged
     */
    virtual void on_reply_acknowledged(
        QueueReplier<TReq,TRep>& producer, 
        const rti::pub::AcknowledgmentInfo &info) = 0;
    
    /**
     * \dref_QueueReplierListener_on_request_available
     */
    virtual void on_request_available(
        QueueReplier<TReq,TRep>& requester) = 0;

    /**
     * \dref_QueueReplierListener_on_request_shared_reader_queue_matched
     */
    virtual void on_request_shared_reader_queue_matched(
        QueueReplier<TReq,TRep>& requester,
        const dds::core::status::SubscriptionMatchedStatus& status) = 0;
    
    /**
     * \dref_QueueReplierListener_on_reply_shared_reader_queue_matched
     */
    virtual void on_reply_shared_reader_queue_matched(
        QueueReplier<TReq,TRep>& requester,
        const dds::core::status::PublicationMatchedStatus& status) = 0;
};

/**
 * @ingroup QueueReplierModule
 * @headerfile rti/queuing/QueueReplierListener.hpp
 * @brief A listener with an empty implementation of all methods
 *
 *
 * You can derive your listener from this class so you don't
 * have to implement the methods you don't need.
 */
template<typename TReq, typename TRep >
class NoOpQueueReplierListener: public virtual QueueReplierListener<TReq, TRep> {
public:
    virtual ~NoOpQueueReplierListener()
    {
    }

    /**
     * @brief 
     *
     * @details 
     */
    virtual void on_reply_acknowledged(
        QueueReplier<TReq,TRep>&,
        const rti::pub::AcknowledgmentInfo&)
    {
    }
    
    /**
     * @brief 
     *
     * @details 
     */
    virtual void on_request_available(QueueReplier<TReq,TRep>&)
    {
    }

    /**
     * @brief 
     *
     * @details 
     */
    virtual void on_request_shared_reader_queue_matched(
        QueueReplier<TReq,TRep>&,
        const dds::core::status::SubscriptionMatchedStatus&)
    {
    }
    
    /**
     * @brief 
     *
     * @details 
     */
    virtual void on_reply_shared_reader_queue_matched(
        QueueReplier<TReq,TRep>&,
        const dds::core::status::PublicationMatchedStatus&)
    {
    }
};    
   

} } // namespace rti::queuing

#endif // RTI_QUEUING_REPLIER_LISTENER_HPP_
