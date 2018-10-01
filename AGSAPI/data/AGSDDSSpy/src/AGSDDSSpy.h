/* AGSDDSSpy.h */

#ifndef AGSDDSSPY_H_INCLUDED
#define AGSDDSSPY_H_INCLUDED

#include <string>


class AGSDDSSpy {
  typedef void (*ProcessDataFunction)(std::string topicName, std::string data, void* userData);
  typedef bool (*FilterTopicSubscriptionFunction)(std::string topicName, void* userData);

  public:
  AGSDDSSpy(int domainId=0);
  ~AGSDDSSpy(void);

  void SetProcessDataCallback(ProcessDataFunction callback);
  void SetFilterTopicSubscriptionCallback(FilterTopicSubscriptionFunction callback);
  void AttachUserData(void* userData);
  void SetDDSLoggingState(bool state);
  void SetRTILicensePath(std::string rtiLicensePath);

  void Start(void);
  void Stop(void);

  class Default {
    public:
    static void ProcessData(std::string topicName, std::string data, void* userData);
    static bool FilterTopicSubscription(std::string topicName, void* userData);
  };

  class Utility {
    public:
    static void Sleep(int sec);
    static void SetKeyboardInterruptCallback(void (*callback)(int));
  };


  private:
  int m_domainId;
  ProcessDataFunction m_ProcessData;
  FilterTopicSubscriptionFunction m_FilterTopicSubscription;
  void* m_userData;
  bool m_ddsLogging;
  bool m_running;
  char* m_rtiLicenseEnvVar;
  void* m_genericClient;
};

#endif /* AGSDDSSPY_H_INCLUDED */
