/* BuiltinPublicationListener.h */

#ifndef BUILTINPUBLICATIONLISTENER_H_INCLUDED
#define BUILTINPUBLICATIONLISTENER_H_INCLUDED

#include "ndds/ndds_cpp.h"
#include "DBHandler.h"

class BuiltinPublicationListener : public DDSDataReaderListener {
  public:
    BuiltinPublicationListener(
        DDSDomainParticipant* inParticipant,
        DDSSubscriber* inSubscriber,
        DBHandler* inDBHandler
    );

    /* Called when a topic is discovered */
    virtual void on_data_available(DDSDataReader *reader);

    DDSDomainParticipant* participant;
    DDSSubscriber* subscriber;
    DBHandler* dbHandler;
};

#endif /* BUILTINPUBLICATIONLISTENER_H_INCLUDED */
