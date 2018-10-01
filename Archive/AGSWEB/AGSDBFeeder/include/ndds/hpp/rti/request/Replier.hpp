/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_REQUEST_REPLIER_HPP_
#define RTI_REQUEST_REPLIER_HPP_

#include <rti/request/detail/ReplierImpl.hpp>

namespace rti { namespace request {

/**
 * @ingroup ReplierModule
 * @headerfile rti/request/Replier.hpp
 * @brief @st_ref_type Allows receiving requests and sending replies
 *
 * @details \dref_details_Replier
 */
template <typename RequestType, typename ReplyType>
class Replier
    : public dds::core::Reference< detail::ReplierImpl<RequestType, ReplyType> > {
public:

    typedef detail::ReplierImpl<RequestType, ReplyType> Delegate;
    typedef dds::core::Reference<Delegate> Base;
    typedef ReplierListener<RequestType, ReplyType> Listener;
    typedef typename dds::core::smart_ptr_traits<Delegate >::ref_type ref_type;
    typedef typename dds::core::smart_ptr_traits<Delegate >::weak_ref_type weak_ref_type;


    OMG_DDS_REF_TYPE(Replier, dds::core::Reference, Delegate);

    /**
     * \dref_Replier_new
     */
    Replier(
        dds::domain::DomainParticipant participant,
        const std::string& service_name)
        : Base(new Delegate(
            ReplierParams(participant).service_name(service_name)))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * \dref_Replier_new_w_params
     */
    explicit Replier(const ReplierParams& params)
        : Base(new Delegate(params))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * @brief Creates a replier with additional parameters and a listener
     *
     * @param the_listener A ReplierListener that notifies when new requests
     * are available. Cannot be NULL.
     *
     * @note The listener must be reset with \p this->listener(NULL) before this
     * object can be destroyed. Alternatively, create the Replier and then use
     * rti::core::bind_listener() to have it automatically reset.
     */
    Replier(const ReplierParams& params, Listener *the_listener)
        : Base(new Delegate(params, the_listener))
    {
        // Two-phase initialization. The constructor (Base) partially initializes
        // the delegate, but to complete it we need to pass a ListenerAdapter
        // that requires a reference to delegate itself, which has just been
        // constructed.
        this->delegate()->initialize(
                params,
                new ListenerAdapter(this->delegate()));
        this->delegate()->remember_reference(this->delegate());
        this->delegate()->retain();
    }

    // For internal use only
    Replier(ref_type delegate_ref)
        : Base(delegate_ref)
    {
        this->delegate()->remember_reference(this->delegate());
    }

    /**
     * \dref_Replier_send_reply
     */
    void send_reply(
        const ReplyType& reply,
        const rti::core::SampleIdentity& related_request_id)
    {
        this->delegate()->send_reply(reply, related_request_id);
    }

    /**
     * @brief Sends a reply
     *
     * This operation obtains the related_request_id from a request SampleInfo,
     * that is, it's equivalent to send_reply(reply, related_request_info->original_publication_virtual_sample_identity())
     */
    void send_reply(
        const ReplyType& reply,
        const dds::sub::SampleInfo& related_request_info)
    {
        this->delegate()->send_reply(
                reply,
                related_request_info->original_publication_virtual_sample_identity());
    }

    /**
     * @brief Sends a reply with advanced parameters
     *
     * @param reply The reply to be sent
     * @param params (in-out) The parameters to write the reply (see ).
     *
     * @pre params.related_sample_identity() must be set with the related
     * request SampleIdentity.
     *
     * Other parameters to customize are discussed in \idref_FooDataWriter_write_w_params.
     * In particular, rti::pub::WriteParams::flag can be set to rti::core::SampleFlag::intermediate_reply_sequence
     * to inform the Requester application that this reply will be followed by
     * additional replies to the same request. The Requester can access
     * the flag in dds::sub::SampleInfo::flag() when it receives the reply.
     */
    void send_reply(
        const ReplyType& reply,
        rti::pub::WriteParams& params)
    {
        this->delegate()->send_reply(reply, params);
    }

    /**
     * \dref_Replier_wait_for_requests_simple
     */
    bool wait_for_requests(const dds::core::Duration& max_wait)
    {
        return this->delegate()->wait_for_requests(1, max_wait);
    }

    /**
     * \dref_Replier_wait_for_requests
     */
    bool wait_for_requests(int min_count, const dds::core::Duration& max_wait)
    {
        return this->delegate()->wait_for_requests(min_count, max_wait);
    }

    /**
     * \dref_Replier_receive_requests_simple
     */
    dds::sub::LoanedSamples<RequestType> receive_requests(
        const dds::core::Duration& max_wait)
    {
        return this->delegate()->receive_requests(1, max_wait);
    }

    /**
     * \dref_Replier_receive_requests
     */
    dds::sub::LoanedSamples<RequestType> receive_requests(
        int min_count,
        const dds::core::Duration& max_wait)
    {
        return this->delegate()->receive_requests(min_count, max_wait);
    }

    /**
     * @brief Takes all the requests
     *
     * @details \dref_details_Replier_take_requests
     */
    dds::sub::LoanedSamples<RequestType> take_requests()
    {
        return this->delegate()->take_requests();
    }

    /**
     * @brief Reads all the requests
     *
     * @details \dref_details_Replier_read_requests
     */
    dds::sub::LoanedSamples<RequestType> read_requests()
    {
        return this->delegate()->read_requests();
    }

    /**
     * @brief Sets a ReplierListener
     *
     * The listener will be called when new requests are available
     */
    Listener* listener() const
    {
        return this->delegate()->listener();
    }

    /**
     * @brief Sets a ReplierListener
     *
     * The listener will be called when new requests are available.
     *
     * @note rti::core::bind_listener() is recommended instead of this listener
     * setter. bind_listener() and bind_and_manage_listener() automatically
     * remove the listener, which allows the Replier to be automatically
     * destroyed.
     *
     * (The second parameter is ignored)
     */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask& = dds::core::status::StatusMask::none())
    {
        if (the_listener != NULL && !this->delegate()->has_listener_adapter()) {
            /* Before the ReplierImpl can hold a listener, it needs a listener
             * adapter. The listener base class definition needs to be here
             * because its callback takes a Replier as an argument.
             */
            this->delegate()->listener_adapter(new ListenerAdapter(this->delegate()));
        }
        this->delegate()->listener(the_listener);
    }

    /**
     * \dref_Replier_get_request_datareader
     */
    dds::sub::DataReader<RequestType> request_datareader() const
    {
        return this->delegate()->request_datareader();
    }

    /**
     * \dref_Replier_get_reply_datawriter
     */
    dds::pub::DataWriter<ReplyType> reply_datawriter() const
    {
        return this->delegate()->reply_datawriter();
    }

private:
    class ListenerAdapter : public dds::sub::NoOpDataReaderListener<RequestType> {
    public:
        void on_data_available(dds::sub::DataReader<RequestType>&) // override
        {
            ref_type delegate_ref = requester_weak_ref_.lock();
            if (delegate_ref) {
                Replier<RequestType, ReplyType> replier(delegate_ref);
                Listener* listener = replier.delegate()->listener();
                if (listener != NULL) {
                    listener->on_request_available(replier);
                }
            }
        }

        ListenerAdapter(ref_type requester)
            : requester_weak_ref_(requester)
        {
        }

    private:
        weak_ref_type requester_weak_ref_;
    };
};

/**
 * @brief Obtains the number of Requesters that match with a Replier
 *
 * @note This operation requires that the requesters' data writer and data reader
 * role name (in rti::core::policy::EntityName) has not been changed.
 */
template <typename RequestType, typename ReplyType>
size_t matched_requester_count(Replier<RequestType, ReplyType>& replier)
{
    return detail::matched_count(
            *replier.request_datareader().delegate(),
            *replier.reply_datawriter().delegate(),
            "Requester");
}

} } // namespace rti::request

#endif // RTI_REQUEST_REPLIER_HPP_
