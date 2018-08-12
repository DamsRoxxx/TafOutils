/* GenericClient.h */

#ifndef GENERICCLIENT_H_INCLUDED
#define GENERICCLIENT_H_INCLUDED

#include "ndds/ndds_cpp.h"
#include "DBHandler.h"
#include <string>
#include "Config.h"

class GenericClient {
  public:
  /* Methods */

  /* A generic DDS "client" that connects to a DDS domain and set up a listener
   * on all discovered topics */
  GenericClient(Config& cfg);

  /* Properly destroy DDS and database "connections" */
  ~GenericClient(void);

  /* Attributs */
  DDSDomainParticipant* participant; 
  DDSDomainParticipantFactory* factory; 
  DBHandler* dbHandler;

  private:
  /* Called in the destructor to properly close DDS and database connections */
  void Shutdown(void);
  
};

#endif /* GENERICCLIENT_H_INCLUDED */
