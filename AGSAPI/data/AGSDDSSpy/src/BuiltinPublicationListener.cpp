/* BuiltinPublicationListener.cpp */

#include <iostream>
#include "BuiltinPublicationListener.h"
#include "GenericListener.h"

BuiltinPublicationListener::BuiltinPublicationListener(
    DDSDomainParticipant* inParticipant,
    DDSSubscriber* inSubscriber,
    AGSDDSSpyArgs inSpyArgs) :
  participant(inParticipant),
  subscriber(inSubscriber),
  spyArgs(inSpyArgs) {
  ;
}

/* Called when a topic is discovered */
void BuiltinPublicationListener::on_data_available(DDSDataReader *reader) {
  DDSPublicationBuiltinTopicDataDataReader *builtinReader =
      (DDSPublicationBuiltinTopicDataDataReader*) reader;

  DDS_PublicationBuiltinTopicDataSeq dataSeq;
  DDS_SampleInfoSeq infoSeq;
  DDS_ReturnCode_t retcode;

  /* We only process newly seen participants */
  retcode = builtinReader->take(dataSeq, infoSeq, DDS_LENGTH_UNLIMITED,
      DDS_ANY_SAMPLE_STATE, DDS_NEW_VIEW_STATE,
      DDS_ANY_INSTANCE_STATE);

  if (retcode == DDS_RETCODE_NO_DATA)
    return;

  for(int i = 0; i < dataSeq.length(); ++i) {
    if (!infoSeq[i].valid_data)
      continue;

    /* Do nothing if we already created that topic */
    if (participant->lookup_topicdescription(dataSeq[i].topic_name))
      continue;

    bool mustSubscribe = true;
    std::string topicNameStr = std::string(dataSeq[i].topic_name);

    /* FILTER TOPIC SUBSCRIPTION */
    if (spyArgs.m_FilterTopicSubscription != NULL) {
      mustSubscribe = spyArgs.m_FilterTopicSubscription(topicNameStr, spyArgs.m_userData);
    }

    if (!mustSubscribe) {
      continue;
    }

    /* std::cout << "SUBSCRIBING TOPIC : " << dataSeq[i].topic_name << std::endl; */

    /* Create TypeSupport */
    struct DDS_DynamicDataTypeProperty_t props;
    DDSDynamicDataTypeSupport* type_support =
      new DDSDynamicDataTypeSupport(dataSeq[i].type_code, props); 
    if (type_support == NULL)
      std::cerr <<  "create type_support error" << std::endl;

    /* Resgister type */
    retcode = type_support->register_type(participant, dataSeq[i].type_name);
    if (retcode != DDS_RETCODE_OK)
      std::cerr << "register_type error " << retcode << std::endl;

    /* Apply a specific QoS profile for the Heartbeat topic */
    if (std::string(dataSeq[i].topic_name).find("Heartbeat") != std::string::npos) {
      /* Create topic */
      DDSTopic* topic = participant->create_topic_with_profile(
          dataSeq[i].topic_name, dataSeq[i].type_name,
          "libAGSCommunMiddlewareDDS",
          "Heartbeat",
          NULL, /* listener */
          DDS_STATUS_MASK_NONE
      );
      if (topic == NULL)
        std::cerr << "create_topic error" << std::endl;

      /* Set up a listener that will be called when a data appear on the
       * topic */
      GenericListener* readerListener = new GenericListener(
          dataSeq[i].topic_name,
          dataSeq[i].type_name,
          spyArgs
      );
      reader = subscriber->create_datareader_with_profile(
          topic,
          "libAGSCommunMiddlewareDDS",
          "Heartbeat",
          readerListener,
          DDS_STATUS_MASK_ALL
      );
    } else { /* And a common QoS profile for all other topics except the
                Heartbeat */
      /* Create topic */
      DDSTopic* topic = participant->create_topic(
          dataSeq[i].topic_name,
          dataSeq[i].type_name,
          DDS_TOPIC_QOS_DEFAULT,
          NULL, /* listener */
          DDS_STATUS_MASK_NONE);
      if (topic == NULL)
        std::cerr << "create_topic error" << std::endl;

      /* Set up a listener that will be called when a data appear on the
       * topic */
      GenericListener* readerListener = new GenericListener(
          dataSeq[i].topic_name,
          dataSeq[i].type_name,
          spyArgs
      );
      reader = subscriber->create_datareader(
          topic,
          DDS_DATAREADER_QOS_DEFAULT,
          readerListener,
          DDS_STATUS_MASK_ALL
      );
    }
  }
  builtinReader->return_loan(dataSeq, infoSeq);
}
