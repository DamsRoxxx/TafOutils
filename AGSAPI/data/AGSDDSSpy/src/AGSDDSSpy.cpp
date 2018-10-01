/* AGSDDSSpy.cpp */

#include "AGSDDSSpy.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include "GenericClient.h"
#include <unistd.h>
#include <iomanip>
#include <locale>
#include <string>
#include <sstream>
#include "AGSDDSSpyArgs.h"
#include "ndds/ndds_cpp.h"

AGSDDSSpy::AGSDDSSpy(int domainId) {
  m_domainId = domainId;
  m_ProcessData = AGSDDSSpy::Default::ProcessData;
  m_FilterTopicSubscription = AGSDDSSpy::Default::FilterTopicSubscription;
  m_userData = NULL;
  m_ddsLogging = false;
  m_running = false;
  m_rtiLicenseEnvVar = NULL;
  m_genericClient = NULL;
}

AGSDDSSpy::~AGSDDSSpy(void) {
  if (m_rtiLicenseEnvVar != NULL) {
    delete m_rtiLicenseEnvVar;
  }
  if (m_running == true) {
    Stop();
    m_running = false;
  }
}

void AGSDDSSpy::Start(void) {
  if (m_running == true) {
    std::cout << "Error : Already running" << std::endl;
    return;
  }
  AGSDDSSpyArgs spyArgs(m_domainId, m_ProcessData, m_userData, m_FilterTopicSubscription, m_ddsLogging);
  m_running = true;
  std::cout << "AGSDDSSpy running..." << std::endl;
  m_genericClient = new GenericClient(spyArgs);
}

void AGSDDSSpy::Stop(void) {
  if (m_running) {
    std::cout << "AGSDDSSpy stopping..." << std::endl;
    delete (GenericClient*)m_genericClient;
    m_genericClient = NULL;
    m_running = false;
  } else  {
    std::cout << "Error : Not running" << std::endl;
  }
}

void AGSDDSSpy::SetRTILicensePath(std::string rtiLicensePath) {
  if (m_running) {
    std::cout << "Error : Can't modify AGSDDSSpy while running" << std::endl;
    return;
  }
  std::string rtiLicenseStr = std::string("RTI_LICENSE_FILE=") + rtiLicensePath;
  char* m_rtiLicenseEnvVar = new char[rtiLicenseStr.size() + 1];
  memcpy(m_rtiLicenseEnvVar, rtiLicenseStr.c_str(), rtiLicenseStr.size() + 1);
  putenv(m_rtiLicenseEnvVar);
}

void AGSDDSSpy::SetProcessDataCallback(ProcessDataFunction callback) {
  if (m_running) {
    std::cout << "Error : Can't modify AGSDDSSpy while running" << std::endl;
    return;
  }
  m_ProcessData = callback;
}

void AGSDDSSpy::SetFilterTopicSubscriptionCallback(FilterTopicSubscriptionFunction callback) {
  if (m_running) {
    std::cout << "Error : Can't modify AGSDDSSpy while running" << std::endl;
    return;
  }
  m_FilterTopicSubscription = callback;
}

void AGSDDSSpy::AttachUserData(void* userData) {
  if (m_running) {
    return;
    std::cout << "Error : Can't modify AGSDDSSpy while running" << std::endl;
  }
  m_userData = userData;
}

void AGSDDSSpy::SetDDSLoggingState(bool state) {
  if (m_running) {
    return;
    std::cout << "Error : Can't modify AGSDDSSpy while running" << std::endl;
  }
  m_ddsLogging = state;
}

void AGSDDSSpy::Default::ProcessData(std::string topicName, std::string data, void* userData) {
  std::cout << "-----Default data processing-----" << std::endl;
  std::cout << "[" << topicName << "]" << std::endl;
  std::cout << data << std::endl;
  std::cout << "---------------------------------" << std::endl;
}

bool AGSDDSSpy::Default::FilterTopicSubscription(std::string topicName, void* userData) {
  std::cout << "Default subscription: " << topicName << std::endl;
  return true;
}

void AGSDDSSpy::Utility::Sleep(int sec) {
    struct DDS_Duration_t waitTime = {sec, 0};
    NDDSUtility::sleep(waitTime);
}

void AGSDDSSpy::Utility::SetKeyboardInterruptCallback(void (*callback)(int)) {
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = callback;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);
}
