/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)connext_cpp_requester_template.h    generated by: makeheader    Fri Feb 16 13:52:56 2018
 *
 *		built from:	requester_template.ifcxx
 */

#ifndef connext_cpp_requester_template_h
#define connext_cpp_requester_template_h



namespace connext {

using namespace DDS;

template <typename TReq, typename TRep>
Requester<TReq, TRep>::Requester(DDSDomainParticipant * participant,
                                 const std::string& service_name) 
    : _pImpl(new details::RequesterImpl<TReq, TRep>(
             RequesterParams(participant).service_name(service_name)))
{
}

template <typename TReq, typename TRep>
Requester<TReq, TRep>::Requester(const RequesterParams& params) 
    : _pImpl(new details::RequesterImpl<TReq, TRep>(params))
{
}


template <typename TReq, typename TRep>
Requester<TReq, TRep>::~Requester() 
{
    if (_pImpl != NULL) {
        delete _pImpl;
    }
}

template <typename TReq, typename TRep>
template<typename UReq>
void Requester<TReq, TRep>::send_request(const UReq & request)
{
    const char * METHOD_NAME = "send_request";
    try {
        _pImpl->send_request_impl(request);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }
}

template <typename TReq, typename TRep>
template <typename UReq>
void Requester<TReq, TRep>::send_request(WriteSample<UReq>& request)
{
    const char * METHOD_NAME = "send_request";
    try {
        _pImpl->send_request_impl(request);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }
}

template <typename TReq, typename TRep>
template <typename UReq>
void Requester<TReq, TRep>::send_request(WriteSampleRef<UReq>& request)
{
    const char * METHOD_NAME = "send_request";
    try {
        _pImpl->send_request_impl(request);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::receive_reply(
    Sample<TRep>& reply,
    const DDS_Duration_t& timeout)
{
    const char * METHOD_NAME = "receive_reply";
    try {
        return _pImpl->receive_reply(reply, timeout);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::receive_reply(
    SampleRef<TRep> reply,
    const DDS_Duration_t& timeout)
{
    const char * METHOD_NAME = "receive_reply";
    try {
        return _pImpl->receive_reply(reply, timeout);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::receive_replies(
    const DDS_Duration_t& max_wait)
{
    const char * METHOD_NAME = "receive_replies";
    try {
        return _pImpl->receive_replies(max_wait);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return LoanedSamples<TRep>(); // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::receive_replies(
    int min_reply_count,
    int max_reply_count,
    const DDS_Duration_t& max_wait)
{
    const char * METHOD_NAME = "receive_replies";
    try {
        return _pImpl->receive_replies(
            min_reply_count, max_reply_count, max_wait);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return LoanedSamples<TRep>(); // unreachable -- appeasing compiler
}


template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::wait_for_replies(
    int min_reply_count,
    const DDS_Duration_t& max_wait)
{
    const char * METHOD_NAME = "wait_for_replies";
    try {
        return _pImpl->wait_for_replies(min_reply_count, max_wait);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::wait_for_replies(
    const DDS_Duration_t& max_wait)
{
    const char * METHOD_NAME = "wait_for_replies";
    try {
        return _pImpl->wait_for_replies(1, max_wait);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::wait_for_replies(
    int min_reply_count,
    const DDS_Duration_t& max_wait,
    const SampleIdentity_t& related_request_id)
{
    const char * METHOD_NAME = "wait_for_replies";
    try {
        return _pImpl->wait_for_replies(
            min_reply_count, max_wait, related_request_id);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

// --- get methods: -----------------------------------------------------------

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::take_reply(Sample<TRep>& reply)
{
    const char * METHOD_NAME = "take_reply";
    try {
        return _pImpl->get_reply(reply, true);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::take_reply(
    Sample<TRep>& reply,
    const SampleIdentity_t& related_request_id)
{
    const char * METHOD_NAME = "take_reply";
    try {
        return _pImpl->get_reply(reply, related_request_id, true);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::take_reply(SampleRef<TRep> reply)
{
    const char * METHOD_NAME = "take_reply";
    try {
        return _pImpl->get_reply(reply, true);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::take_reply(
    SampleRef<TRep> reply,
    const SampleIdentity_t& related_request_id)
{
    const char * METHOD_NAME = "take_reply";
    try {
        return _pImpl->get_reply(reply, related_request_id, true);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::take_replies(int max_samples)
{
    const char * METHOD_NAME = "take_replies";
    try {
        return _pImpl->get_replies(max_samples, true);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return LoanedSamples<TRep>(); // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::take_replies(
    const SampleIdentity_t& related_request_id)
{
    return take_replies(DDS_LENGTH_UNLIMITED, related_request_id);
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::take_replies(
    int max_samples,
    const SampleIdentity_t& related_request_id)
{
    const char * METHOD_NAME = "take_replies";
    try {
        return _pImpl->get_replies(max_samples, related_request_id, true);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return LoanedSamples<TRep>(); // unreachable -- appeasing compiler
}

// --- read methods: ----------------------------------------------------------


template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::read_reply(Sample<TRep>& reply)
{
    const char * METHOD_NAME = "read_reply";
    try {
        return _pImpl->get_reply(reply, false);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::read_reply(
    Sample<TRep>& reply,
    const SampleIdentity_t& related_request_id)
{
    const char * METHOD_NAME = "read_reply";
    try {
        return _pImpl->get_reply(reply, related_request_id, false);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::read_reply(SampleRef<TRep> reply)
{
    const char * METHOD_NAME = "read_reply";
    try {
        return _pImpl->get_reply(reply, false);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
bool Requester<TReq, TRep>::read_reply(
    SampleRef<TRep> reply,
    const SampleIdentity_t& related_request_id)
{
    const char * METHOD_NAME = "read_reply";
    try {
        return _pImpl->get_reply(reply, related_request_id, false);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return false; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::read_replies(int max_samples)
{
    const char * METHOD_NAME = "read_replies";
    try {
        return _pImpl->get_replies(max_samples, false);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return LoanedSamples<TRep>(); // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::read_replies(
    const SampleIdentity_t& related_request_id)
{
    return read_replies(DDS_LENGTH_UNLIMITED, related_request_id);
}

template <typename TReq, typename TRep>
LoanedSamples<TRep> Requester<TReq, TRep>::read_replies(
    int max_samples,
    const SampleIdentity_t& related_request_id)
{
    const char * METHOD_NAME = "read_replies";
    try {
        return _pImpl->get_replies(max_samples, related_request_id, false);
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return LoanedSamples<TRep>(); // unreachable -- appeasing compiler
}


// --- Get DR/DW: -------------------------------------------------------------


template <typename TReq, typename TRep>
typename Requester<TReq, TRep>::RequestDataWriter *
Requester<TReq, TRep>::get_request_datawriter()
{
    const char * METHOD_NAME = "get_request_datawriter";
    try {
        return _pImpl->get_datawriter();
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return NULL; // unreachable -- appeasing compiler
}

template <typename TReq, typename TRep>
typename Requester<TReq, TRep>::ReplyDataReader *
Requester<TReq, TRep>::get_reply_datareader()
{
    const char * METHOD_NAME = "get_reply_datareader";
    try {
        return _pImpl->get_datareader();
    } catch (const Rethrowable& ex) {
        _pImpl->log_and_rethrow(ex, METHOD_NAME);
    }

    return NULL; // unreachable -- appeasing compiler
}

} // namespace connext


#endif /* connext_cpp_requester_template_h */
