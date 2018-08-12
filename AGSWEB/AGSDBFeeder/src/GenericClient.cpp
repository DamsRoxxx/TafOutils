/* GenericClient.cpp */

#include <iostream>
#include <sstream>
#include <fstream>
#include "BuiltinPublicationListener.h"
#include "GenericClient.h"

/* Properly destroy DDS and database "connections" */
GenericClient::~GenericClient(void) {
  Shutdown();
  delete dbHandler; /* Deleted here because the program may stop with Ctrl-C */
}

/* A generic DDS "client" that connects to a DDS domain and set up a listener
 * on all discovered topics */
GenericClient::GenericClient(Config& cfg) :
  participant(NULL), factory(NULL) {
  std::cout << "GenericClient" << std::endl;

  DDS_ReturnCode_t retcode;

  /* For database operations */
  dbHandler = new DBHandler(cfg.dbName);

  /* DISABLE WHEN DEBUGING WITH ALREADY FEEDED DB */
  /* Create tables if they do not exists and clean all the tables */
  /* dbHandler->Query("DROP TABLE DDS;"); */
  /* dbHandler->Query("DROP TABLE DescObjet;"); */
  /* dbHandler->Query("CREATE TABLE DDS (id NULL, name TEXT, type TEXT, data TEXT);"); */
  /* dbHandler->Query("CREATE TABLE DescObjet (name TEXT, libelle TEXT, typeObjet TEXT, groupe Text, espace TEXT);"); */

  /* Get the participant factory */
  DDS_DomainParticipantFactoryQos factoryQos;
  retcode = DDSTheParticipantFactory->get_qos(factoryQos);
  if (retcode != DDS_RETCODE_OK)
    std::cerr << "DDSTheParticipantFactory->get_qos error" << std::endl;

  /* Participant are created disabled */
  factoryQos.entity_factory.autoenable_created_entities = DDS_BOOLEAN_FALSE;
  retcode = DDSTheParticipantFactory->set_qos(factoryQos);
  if (retcode != DDS_RETCODE_OK)
    std::cerr << "DDSTheParticipantFactory->set_qos error" << std::endl;

  /* This factory will create disabled participants */
  factory = DDSDomainParticipantFactory::get_instance();
  if (!factory)
    std::cerr << "DDSDomainParticipantFactory::get_instance" << std::endl;
  
  /* Create a participant disabled by default */
  participant = factory->create_participant(
      cfg.domainId,
      DDS_PARTICIPANT_QOS_DEFAULT,
      NULL /* listener */,
      DDS_STATUS_MASK_NONE);
  if (!participant)
    std::cerr << "create_participant error" << std::endl;

  /* Get the built-in subscriber */
  DDSSubscriber *builtinSubscriber = participant->get_builtin_subscriber();
  if (!builtinSubscriber)
    std::cerr << "get_builtin_subscriber error" << std::endl;

  /* Get the publication built-in data reader */
  DDSPublicationBuiltinTopicDataDataReader *builtinPublicationDatareader =
      (DDSPublicationBuiltinTopicDataDataReader*)
      builtinSubscriber->lookup_datareader(DDS_PUBLICATION_TOPIC_NAME);
  if (!builtinPublicationDatareader)
    std::cerr << "lookup_datareader error" << std::endl;

  /* Create our generic subscriber */
  DDS_SubscriberQos subscriberQos;
  retcode = participant->get_default_subscriber_qos(subscriberQos);
  if (retcode != DDS_RETCODE_OK) {
    printf("get_default_subscriberQos error\n");
  }
  /* To match all partitions */
  subscriberQos.partition.name.ensure_length(1, 1);
  subscriberQos.partition.name[0] = DDS_String_dup("*");

  DDSSubscriber* subscriber = participant->create_subscriber(
      subscriberQos,
      NULL /* listener */,
      DDS_STATUS_MASK_NONE);

  /* Set up the publication listener that will be called when a topic is 
   * discovered */
  BuiltinPublicationListener *builtinPublicationListener =
    new BuiltinPublicationListener(participant, subscriber, dbHandler);

  builtinPublicationDatareader->set_listener(
    builtinPublicationListener,
    DDS_DATA_AVAILABLE_STATUS
  );

  /* Enable participant */
  retcode = participant->enable();
  if (retcode != DDS_RETCODE_OK)
    std::cerr << "participant enable error" << std::endl;
}

/* Properly close the DDS "connection" */
void GenericClient::Shutdown(void) {
  DDS_ReturnCode_t retcode;

  std::cerr << "Shutdown" << std::endl;
  if (participant != NULL) {
    retcode = participant->delete_contained_entities();
    if (retcode != DDS_RETCODE_OK) {
      std::cerr << "delete_contained_entities error " << retcode << std::endl;
    }

    retcode = factory->delete_participant(participant);
    if (retcode != DDS_RETCODE_OK) {
      std::cerr << "delete_participant error " << retcode << std::endl;
    }
  }
}
