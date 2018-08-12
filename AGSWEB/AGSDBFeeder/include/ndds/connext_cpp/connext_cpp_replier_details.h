/* (c) Copyright 2003-2015, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)connext_cpp_replier_details.h    generated by: makeheader    Fri Feb 16 13:52:56 2018
 *
 *		built from:	replier_details.ifcxx
 */

#ifndef connext_cpp_replier_details_h
#define connext_cpp_replier_details_h



#include <memory>

#include "ndds/ndds_namespace_cpp.h"
#include "log/log_makeheader.h"
#include "log/log_common.h"
#include "dds_c/dds_c_log_impl.h"

#ifndef xmq_cpp_replier_listener_h
  #include "connext_cpp/connext_cpp_replier_listener.h"
#endif

#ifndef xmq_cpp_replier_params_h
  #include "connext_cpp/connext_cpp_replier_params.h"
#endif

#ifndef xmq_cpp_general_replier_h
  #include "connext_cpp/connext_cpp_replier.h"
#endif

#ifndef xmq_cpp_exception_h
  #include "connext_cpp/connext_cpp_exception.h"
#endif

#ifndef xmq_cpp_dll_h
  #include "connext_cpp/connext_cpp_dll.h"
#endif

#ifndef xmq_cpp_replier_untyped_h
  #include "connext_cpp/connext_cpp_replier_untyped.h"
#endif

// TODO: use the right submodule
#define DDS_CURRENT_SUBMODULE DDS_SUBMODULE_MASK_DATA

namespace connext {
namespace details {

// --- RequesterImpl: ---------------------------------------------------------

template <typename TReq, typename TRep>
class XMQCPPDllExport SimpleReplierImpl {
private:
    class InnerRequestListener : public ReplierListener<TReq, TRep> 
    {
    private:
        SimpleReplierListener<TReq, TRep> * _user_listener;

    public:                                        
        InnerRequestListener(SimpleReplierListener<TReq, TRep> * user_listener);
        virtual void on_request_available(Replier<TReq, TRep> & replier);
    };   

public:

    // --- types: -------------------------------------------------------------

    typedef TReq Request;
    typedef TRep Reply;
    typedef typename dds_type_traits<TReq>::DataReader RequestDataReader;
    typedef typename dds_type_traits<TRep>::DataWriter ReplyDataWriter;

    // --- ctors: -------------------------------------------------------------

    SimpleReplierImpl(DDS::DomainParticipant * participant,
                      const std::string& service_name,
                      SimpleReplierListener<TReq, TRep> * listener);
    SimpleReplierImpl(const SimpleReplierParams<TReq, TRep> & params);
    virtual ~SimpleReplierImpl();

    void swap(SimpleReplierImpl& other);

    // --- query methods: -----------------------------------------------------

    inline RequestDataReader * get_request_datareader() const;
    inline ReplyDataWriter * get_reply_datawriter() const;

private:

    InnerRequestListener _request_listener;
    Replier<TReq, TRep> _general_replier;
};



// --- RequesterImpl implementation: ------------------------------------------

template <typename TReq, typename TRep>
SimpleReplierImpl<TReq, TRep>::
SimpleReplierImpl(DDS::DomainParticipant * participant,
                  const std::string& service_name,
                  SimpleReplierListener<TReq, TRep> * user_listener)
    :  _request_listener(user_listener),
       _general_replier(ReplierParams<TReq, TRep>(participant)
                        .service_name(service_name)
                        .replier_listener(_request_listener))
{}

template <typename TReq, typename TRep>
SimpleReplierImpl<TReq, TRep>::
SimpleReplierImpl(const SimpleReplierParams<TReq, TRep> & params) 
    : _request_listener(params.simple_replier_listener()),
      _general_replier(ReplierParams<TReq, TRep>(params)
                       .replier_listener(_request_listener))
{}

template <typename TReq, typename TRep>
SimpleReplierImpl<TReq, TRep>::~SimpleReplierImpl() 
{
    if (_general_replier.get_request_datareader() != NULL) {
        _general_replier.get_request_datareader()->set_listener(NULL, DDS_STATUS_MASK_NONE);
    }
}

template <typename TReq, typename TRep>
void SimpleReplierImpl<TReq, TRep>::swap(SimpleReplierImpl& other)
{
    using std::swap;
    swap(_request_listener, other._request_listener);
    swap(_general_replier, other._general_replier);
}

template <typename TReq, typename TRep>
inline typename SimpleReplierImpl<TReq, TRep>::ReplyDataWriter * 
SimpleReplierImpl<TReq, TRep>::get_reply_datawriter() const
{
    return _general_replier.get_reply_datawriter();
}

template <typename TReq, typename TRep>
inline typename SimpleReplierImpl<TReq, TRep>::RequestDataReader * 
SimpleReplierImpl<TReq, TRep>::get_request_datareader() const
{
    return _general_replier.get_request_datareader();
}

template<class TReq, class TRep>
SimpleReplierImpl<TReq, TRep>::InnerRequestListener::
InnerRequestListener(SimpleReplierListener<TReq, TRep> * user_listener)
    : _user_listener(user_listener)
{
    const char * METHOD_NAME =
        "SimpleReplierImpl::InnerRequestListener::InnerRequestListener";
    if(!user_listener) {
        check_retcode(DDS_RETCODE_BAD_PARAMETER, METHOD_NAME,
                      DDS_LOG_BAD_PARAMETER_s, "user_listener");
    }
}

template<class TReq, class TRep>
void SimpleReplierImpl<TReq, TRep>::InnerRequestListener::
on_request_available(Replier<TReq, TRep> & replier)
{
    using namespace connext;
    const char * CLASS_NAME = "SimpleReplierImpl::InnerRequestListener";
    const char * METHOD_NAME = "on_request_available";

    try {
        typedef typename dds_type_traits<TReq>::LoanedSamplesType LoanedSamplesType;
        LoanedSamplesType ls = replier.take_requests(DDS_LENGTH_UNLIMITED);

        for (typename LoanedSamplesType::iterator iter = ls.begin();
             iter != ls.end();
             ++iter) 
        {
            TRep * reply = _user_listener->on_request_available(*iter);

            if (reply != NULL) {
                try {
                    replier.send_reply(*reply, 
                                       get_sample_identity_from_sample_info(iter->info()));
                }
                catch (const Rethrowable& ex) {
                    log_and_rethrow_conditional(replier.get_reply_datawriter(),
                                                replier.get_request_datareader(),
                                                ex, CLASS_NAME, METHOD_NAME, false /* Don't throw again */);
                }
                _user_listener->return_loan(reply);
            }
        }   
    }
    catch (const Rethrowable& ex) {
        log_and_rethrow_conditional(replier.get_reply_datawriter(),
                                    replier.get_request_datareader(),
                                    ex, CLASS_NAME, METHOD_NAME, false /* Don't throw again */);
    }
}

} // namespace details
} // namespace connext

#undef DDS_CURRENT_SUBMODULE


#endif /* connext_cpp_replier_details_h */
