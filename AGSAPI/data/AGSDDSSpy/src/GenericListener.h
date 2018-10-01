/* GenericListener.h */

#ifndef GENERICLISTENER_H_INCLUDED
#define GENERICLISTENER_H_INCLUDED

#include <string>
#include "ndds/ndds_cpp.h"
#include "AGSDDSSpyArgs.h"

class GenericListener : public DDSDataReaderListener {
  public:
    GenericListener(std::string inTopicName, std::string inTypeName, AGSDDSSpyArgs inSpyArgs);
    virtual void on_requested_deadline_missed(
        DDSDataReader* /*reader*/,
        const DDS_RequestedDeadlineMissedStatus& /*status*/) {}

    virtual void on_requested_incompatible_qos(
        DDSDataReader* /*reader*/,
        const DDS_RequestedIncompatibleQosStatus& /*status*/) {}

    virtual void on_sample_rejected(
        DDSDataReader* /*reader*/,
        const DDS_SampleRejectedStatus& /*status*/) {}

    virtual void on_liveliness_changed(
        DDSDataReader* /*reader*/,
        const DDS_LivelinessChangedStatus& /*status*/) {}

    virtual void on_sample_lost(
        DDSDataReader* /*reader*/,
        const DDS_SampleLostStatus& /*status*/) {}

    virtual void on_subscription_matched(
        DDSDataReader* /*reader*/,
        const DDS_SubscriptionMatchedStatus& /*status*/) {}

    virtual void on_data_available(DDSDataReader* reader);

    std::string topicName;
    std::string typeName;
    AGSDDSSpyArgs spyArgs;
};

#endif /* GENERICLISTENER_H_INCLUDED */
