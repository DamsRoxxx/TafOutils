/* AGSDDSSpyArgs.h */

#ifndef AGSDDSSPYARGS_H_INCLUDED
#define AGSDDSSPYARGS_H_INCLUDED


class AGSDDSSpyArgs {
  typedef void (*ProcessDataFunction)(std::string topicName, std::string data, void* userData);
  typedef bool (*FilterTopicSubscriptionFunction)(std::string topicName, void* userData);

  public:
  AGSDDSSpyArgs(int domainId,
                ProcessDataFunction ProcessData,
                void* userData,
                FilterTopicSubscriptionFunction FilterTopicSubscription,
                bool logging) :
    m_domainId(domainId),
    m_ProcessData(ProcessData),
    m_userData(userData),
    m_FilterTopicSubscription(FilterTopicSubscription),
    m_logging(logging) {};

  int m_domainId;
  ProcessDataFunction m_ProcessData;
  void* m_userData;
  FilterTopicSubscriptionFunction m_FilterTopicSubscription;
  bool m_logging;
};

#endif /* AGSDDSSPYARGS_H_INCLUDED */
