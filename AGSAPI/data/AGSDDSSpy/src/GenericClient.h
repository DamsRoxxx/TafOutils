/* GenericClient.h */

#ifndef GENERICCLIENT_H_INCLUDED
#define GENERICCLIENT_H_INCLUDED

#include "ndds/ndds_cpp.h"
#include <string>
#include "AGSDDSSpyArgs.h"

class GenericClient {
  public:
  /* Methods */

  /* A generic DDS "client" that connects to a DDS domain and set up a listener
   * on all discovered topics */
  GenericClient(AGSDDSSpyArgs spyArgs);

  /* Properly destroy DDS and database "connections" */
  ~GenericClient(void);

  /* Attributs */
  DDSDomainParticipant* participant; 
  DDSDomainParticipantFactory* factory; 

  private:
  /* Called in the destructor to properly close DDS and database connections */
  void Shutdown(void);
  
};

#endif /* GENERICCLIENT_H_INCLUDED */
