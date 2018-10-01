/* BuiltinPublicationListener.h */

#ifndef BUILTINPUBLICATIONLISTENER_H_INCLUDED
#define BUILTINPUBLICATIONLISTENER_H_INCLUDED

#include "ndds/ndds_cpp.h"
#include "AGSDDSSpyArgs.h"

class BuiltinPublicationListener : public DDSDataReaderListener {
  public:
    BuiltinPublicationListener(
        DDSDomainParticipant* inParticipant,
        DDSSubscriber* inSubscriber,
        AGSDDSSpyArgs inSpyArgs
    );

    /* Called when a topic is discovered */
    virtual void on_data_available(DDSDataReader *reader);

    DDSDomainParticipant* participant;
    DDSSubscriber* subscriber;
    AGSDDSSpyArgs spyArgs;
};

#endif /* BUILTINPUBLICATIONLISTENER_H_INCLUDED */
