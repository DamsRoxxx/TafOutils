/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_REQUEST_DETAIL_REPLIERIMPL_HPP_
#define RTI_REQUEST_DETAIL_REPLIERIMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <rti/request/detail/macros.hpp>

#include <rti/core/detail/SelfReference.hpp>
#include <rti/request/detail/GenericSender.hpp>
#include <rti/request/detail/GenericReceiver.hpp>
#include <rti/request/ReplierParams.hpp>
#include <rti/request/ReplierListener.hpp>

namespace rti { namespace request {

namespace detail {

template <typename T>
dds::topic::TopicDescription<T> get_replier_request_topic(
    const rti::request::ReplierParams& params);

template <typename T>
dds::topic::Topic<T> get_replier_reply_topic(
    const rti::request::ReplierParams& params);

XMQCPP2DllExport
void validate_related_request_id(
    const rti::core::SampleIdentity& related_request_id);

XMQCPP2DllExport
rti::pub::WriteParams get_write_params_for_related_request(
    const rti::core::SampleIdentity& related_request_id);


template <typename RequestType>
class ReplierDataReaderListenerAdapter
        : public dds::sub::NoOpDataReaderListener<RequestType> {

    void on_data_available(dds::sub::DataReader<RequestType>& reader)
    {

    }
};

/**
 */
template <typename RequestType, typename ReplyType>
class ReplierImpl
    : public rti::core::detail::RetainableType<ReplierImpl<RequestType, ReplyType> >,
      private ParamsValidator {
public:

    explicit ReplierImpl(const rti::request::ReplierParams& params)
        : ParamsValidator(params),
          listener_adapter_(NULL),
          listener_(NULL),
          sender_(params, get_replier_reply_topic<ReplyType>(params), "Replier"),
          receiver_(params, get_replier_request_topic<RequestType>(params), "Replier")
    {
    }


    // Constructor with listener.
    //
    // IMPORTANT: this constructor is for two-phase initialization only.
    // initialize() must be called after this.
    ReplierImpl(
            const rti::request::ReplierParams& params,
            rti::request::ReplierListener<RequestType, ReplyType>* the_listener)
        : ParamsValidator(params, the_listener),
          listener_adapter_(NULL),
          listener_(the_listener),
          sender_(params, get_replier_reply_topic<ReplyType>(params), "Replier")
          // receiver_ default-constructed, awaiting initialize
    {
    }

    // To be called after the constructor with a listener. See rationale in
    // Replier.hpp
    void initialize(
            const rti::request::ReplierParams& params,
            dds::sub::DataReaderListener<RequestType> *the_listener_adapter)
    {
        receiver_.initialize(
                params,
                get_replier_request_topic<RequestType>(params),
                "Replier",
                the_listener_adapter,
                dds::core::status::StatusMask::data_available());
    }

    ~ReplierImpl()
    {
        // Listener can only be non-null here if this object was not retained
        // when the listener was set; otherwise the object can't be destroyed
        // while it holds a listener
        listener(NULL);
        if (listener_adapter_ != NULL) {
            delete listener_adapter_;
        }
    }

    void send_reply(
        const ReplyType& data,
        const rti::core::SampleIdentity& related_request_id)
    {
        rti::pub::WriteParams write_params =
            get_write_params_for_related_request(related_request_id);
        sender_.write(data, write_params);
    }

    void send_reply(
        const ReplyType& data,
        rti::pub::WriteParams& write_params)
    {
        validate_related_request_id(write_params.related_sample_identity());
        sender_.write(data, write_params);
    }

    bool wait_for_requests(int min_count, const dds::core::Duration& max_wait)
    {
        return receiver_.wait_for_any_sample(min_count, max_wait);
    }

    dds::sub::LoanedSamples<RequestType> receive_requests(
        int min_count, const dds::core::Duration& max_wait)
    {
        return receiver_.receive_samples(min_count, max_wait);
    }

    dds::sub::LoanedSamples<RequestType> take_requests()
    {
        return receiver_.take_samples();
    }

    dds::sub::LoanedSamples<RequestType> read_requests()
    {
        return receiver_.read_samples();
    }

    dds::pub::DataWriter<ReplyType> reply_datawriter() const
    {
        return sender_.writer();
    }

    dds::sub::DataReader<RequestType> request_datareader() const
    {
        return receiver_.reader();
    }

    void listener(
            rti::request::ReplierListener<RequestType, ReplyType>* the_listener,
            bool retain = true)
    {
        if (the_listener == NULL) {
            receiver_.listener(NULL);
            this->unretain();
        } else {
            listener_ = the_listener;

            // the listener_adapter must be set before calling this function
            receiver_.listener(listener_adapter_);
            if (retain) {
                // When the user sets the listener (Replier) we need
                // to retain this object while the listener is set; when
                // the listener is internal (SimpleReplier) we don't retain.
                this->retain();
            }
        }
    }

    rti::request::ReplierListener<RequestType, ReplyType>* listener()
    {
        return listener_;
    }

    // for internal use only:
    void listener_adapter(
            dds::sub::DataReaderListener<RequestType> *the_listener_adapter)
    {
        listener_adapter_ = the_listener_adapter;
    }

    bool has_listener_adapter() const
    {
        return listener_adapter_ != NULL;
    }

    bool closed() const
    {
        // close() not supported yet, therfore the object can never be in
        // closed state--it can be destroyed, but not closed.
        return false;
    }

private:
    dds::sub::DataReaderListener<RequestType>* listener_adapter_;
    rti::request::ReplierListener<RequestType, ReplyType>* listener_;
    detail::GenericSender<ReplyType> sender_;
    detail::GenericReceiver<RequestType> receiver_;
};


template <typename T>
dds::topic::TopicDescription<T> get_replier_request_topic(
    const rti::request::ReplierParams& params)
{
    return get_or_create_topic<T>(
        params.participant(),
        get_request_topic_name(params),
        params.request_type(),
        true);
}

template <typename T>
dds::topic::Topic<T> get_replier_reply_topic(
    const rti::request::ReplierParams& params)
{
    dds::topic::TopicDescription<T> topic_desc = get_or_create_topic<T>(
        params.participant(),
        get_reply_topic_name(params),
        params.reply_type(),
        false);

    return dds::core::polymorphic_cast<dds::topic::Topic<T> >(topic_desc);
}

} } } // namespace rti::request::detail

#endif // RTI_REQUEST_DETAIL_REPLIERIMPL_HPP_
