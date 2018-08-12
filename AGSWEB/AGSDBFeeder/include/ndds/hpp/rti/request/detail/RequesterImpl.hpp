/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_REQUEST_DETAIL_REQUESTERIMPL_HPP_
#define RTI_REQUEST_DETAIL_REQUESTERIMPL_HPP_

#include <rti/request/detail/macros.hpp>
#include <rti/core/detail/SelfReference.hpp>
#include <rti/request/detail/GenericSender.hpp>
#include <rti/request/detail/GenericReceiver.hpp>
#include <rti/request/RequesterParams.hpp>

namespace rti { namespace request { namespace detail {


template <typename T>
dds::topic::Topic<T> get_requester_request_topic(
    const rti::request::RequesterParams& params);

template <typename T>
dds::topic::ContentFilteredTopic<T> create_correlation_cft(
    dds::topic::Topic<T> topic,
    const rti::core::Guid& correlation_guid);

template <typename T>
dds::topic::ContentFilteredTopic<T> get_requester_reply_topic(
    const rti::request::RequesterParams& params,
    const rti::core::Guid& correlation_guid)
{
    dds::topic::TopicDescription<T> topic_desc = get_or_create_topic<T>(
        params.participant(),
        get_reply_topic_name(params),
        params.reply_type(),
        false);

    return create_correlation_cft(
        dds::core::polymorphic_cast<dds::topic::Topic<T> >(topic_desc),
        correlation_guid);
}

XMQCPP2DllExport
std::string create_correlation_filter_name(
    const std::string& related_topic_name,
    const rti::core::Guid& correlation_guid);

XMQCPP2DllExport
std::string create_correlation_filter_expression(
    const rti::core::Guid& correlation_guid);

template <typename T>
dds::topic::ContentFilteredTopic<T> create_correlation_cft(
    dds::topic::Topic<T> topic,
    const rti::core::Guid& correlation_guid);

XMQCPP2DllExport
dds::sub::cond::ReadCondition create_correlation_condition(
    dds::sub::AnyDataReader reader,
    dds::sub::status::SampleState sample_state,
    const rti::core::SequenceNumber& related_request_sn);

template <typename T>
rti::core::Guid get_guid_from_writer(const dds::pub::DataWriter<T>& writer);

XMQCPP2DllExport
void create_correlation_index(DDS_DataReader *reader);

/**
 */
template <typename RequestType, typename ReplyType>
class RequesterImpl
    : public rti::core::detail::RetainableType<RequesterImpl<RequestType, ReplyType> >,
      private ParamsValidator {
public:

    // Creates the sender and receiver with the appropriate topics that make
    // a Requester.
    explicit RequesterImpl(const rti::request::RequesterParams& params)
        : ParamsValidator(params),
          sender_(
              params,
              get_requester_request_topic<RequestType>(params),
              "Requester"),
          receiver_(
              params,
              // The receiver's topic is a CFT that filter replies based on the
              // correlation with requests
              get_requester_reply_topic<ReplyType>(
                  params,
                  get_guid_from_writer(sender_.writer())), // correlation guid
              "Requester")
    {
        create_correlation_index(receiver_.reader()->native_reader());
    }

    rti::core::SampleIdentity send_request(const RequestType& data)
    {
        rti::pub::WriteParams params;
        params.replace_automatic_values(true); // to obtain the actual identity

        sender_.write(data, params); // params is an in-out parameter

        // return the request identity; this is what the application can
        // pass to wait_for_replies to wait for a reply to this request.
        return params.identity();
    }

    void send_request(const RequestType& data, rti::pub::WriteParams& params)
    {
        sender_.write(data, params);
    }

    dds::sub::LoanedSamples<ReplyType> receive_replies(
        int min_count,
        const dds::core::Duration& max_wait)
    {
        return receiver_.receive_samples(min_count, max_wait);
    }

    dds::sub::LoanedSamples<ReplyType> take_replies(
            const rti::core::SampleIdentity& related_request_id)
    {
        using dds::sub::cond::ReadCondition;
        using namespace dds::sub::status;

        dds::sub::AnyDataReader reader(receiver_.reader());
        ReadCondition condition = create_correlation_condition(
            reader,
            SampleState::any(),
            related_request_id.sequence_number());

        return receiver_.take_samples(condition);
    }

    dds::sub::LoanedSamples<ReplyType> read_replies(
            const rti::core::SampleIdentity& related_request_id)
    {
        using dds::sub::cond::ReadCondition;
        using namespace dds::sub::status;

        dds::sub::AnyDataReader reader(receiver_.reader());
        ReadCondition condition = create_correlation_condition(
            reader,
            SampleState::any(),
            related_request_id.sequence_number());

        return receiver_.read_samples(condition);
    }

    dds::sub::LoanedSamples<ReplyType> take_replies()
    {
        return receiver_.take_samples();
    }

    dds::sub::LoanedSamples<ReplyType> read_replies()
    {
        return receiver_.read_samples();
    }

    dds::pub::DataWriter<RequestType> request_datawriter() const
    {
        return sender_.writer();
    }

    dds::sub::DataReader<ReplyType> reply_datareader() const
    {
        return receiver_.reader();
    }

    bool wait_for_replies(int min_count, const dds::core::Duration& max_wait)
    {
        return receiver_.wait_for_any_sample(min_count, max_wait);
    }

    bool wait_for_replies(
        int min_count,
        const dds::core::Duration& max_wait,
        const rti::core::SampleIdentity& related_request_id)
    {
        using dds::sub::cond::ReadCondition;
        using namespace dds::sub::status;

        dds::sub::AnyDataReader reader(receiver_.reader());
        ReadCondition correlation_condition = create_correlation_condition(
            reader,
            SampleState::not_read(),
            related_request_id.sequence_number());

        dds::core::cond::WaitSet waitset;
        waitset.attach_condition(correlation_condition);

        ReadCondition initial_condition = create_correlation_condition(
            reader,
            SampleState::any(),
            related_request_id.sequence_number());

        return receiver_.wait_for_samples(
            min_count,
            max_wait,
            waitset,
            initial_condition,
            correlation_condition);
    }

private:
    detail::GenericSender<RequestType> sender_;
    detail::GenericReceiver<ReplyType> receiver_;
};


template <typename T>
dds::topic::Topic<T> get_requester_request_topic(
    const rti::request::RequesterParams& params)
{
    dds::topic::TopicDescription<T> topic_desc = get_or_create_topic<T>(
        params.participant(),
        get_request_topic_name(params),
        params.request_type(),
        false);

    return dds::core::polymorphic_cast<dds::topic::Topic<T> >(topic_desc);
}

template <typename T>
dds::topic::ContentFilteredTopic<T> create_correlation_cft(
    dds::topic::Topic<T> topic,
    const rti::core::Guid& correlation_guid)
{
    std::string cft_name =
        create_correlation_filter_name(topic.name(), correlation_guid);
    std::string cft_expression =
        create_correlation_filter_expression(correlation_guid);

    return dds::topic::ContentFilteredTopic<T>(
        topic,
        cft_name,
        dds::topic::Filter(cft_expression));
}

template <typename T>
rti::core::Guid get_guid_from_writer(const dds::pub::DataWriter<T>& writer)
{
    using rti::core::policy::DataWriterProtocol;

    return writer.qos().template policy<DataWriterProtocol>().virtual_guid();
}

} } } // namespace rti::request::detail

#endif // RTI_REQUEST_DETAIL_REQUESTERIMPL_HPP_
