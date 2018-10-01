/* Main.cpp */

#include "AGSDDSSpy.h"
#include "DBHandler.h"
#include "Config.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool _loop = true;

void Quit(int s) {
  std::cout << "Catch keyboard interruption" << std::endl;
  _loop = false;
}

// Subscribe to DescObjet, Alarme, Mesure, Etat, InfoGen and Heartbeat topics
bool FilterTopicSubscriptionFunction(std::string topicName, void* userData) {
  std::string topicsTopSubscribe[] = {"DescObjet", "Alarme", "Mesure", "Etat", "InfoGen", "Heartbeat", "END"};
  for (int i = 0; topicsTopSubscribe[i] != "END"; ++i) {
    if (topicName.find(topicsTopSubscribe[i], 0) != std::string::npos && topicName.find("Cmd") ==std::string::npos) { 
      std::cout << "INFO :: FilterTopicSubscriptionFunction :: Subscribing to " << topicName << std::endl;
      return true;
    }
  }
  return false;
}

void ProcessDataFunction(std::string topicName, std::string data, void* userData) {
  static int insertCounter = 0;

  DBHandler* dbHandler = (DBHandler*)userData;
  /* AGSDDSSpy::Default::ProcessData(topicName, data, userData); */
  if (topicName.find("DescObjet") != std::string::npos) { // If it's a DescObjet
    dbHandler->InsertDescObjetEntry(data);
  } else if (topicName.find("Heartbeat") == std::string::npos) { // Else if it's not a Heartbeat

    // Extract idObjet from DDS data
    int begin = data.find("idObjet") + 10;
    int end = data.find('"', begin);
    std::string idObjet = data.substr(begin, end - begin);

    // Extract idInfo from DDS data
    begin = data.find("idInfo") + 8;
    end = data.find('\n', begin);
    std::string idInfo = data.substr(begin, end - begin);

    dbHandler->ReplaceDDSEntry(idInfo, idObjet, topicName, data);
    ++insertCounter;
    std::cout << "insertCounter: " << insertCounter << std::endl;
  } else { // Else if it's a Heartbeat
    std::cout << "TRANSACTION" << std::endl;
    dbHandler->ExecQuery("END TRANSACTION");
    dbHandler->ExecQuery("BEGIN TRANSACTION");
  }
}

int main(int argc, char** argv) {
  Config cfg;

  // Init
  if (cfg.Load(argc, argv) == -1) {
    std::cerr << "Config::Load failed make sure your starting "
                 "the program from the top-level start script." << std::endl;
    return 0;
  }

  /* Save PID for stop script */
  std::string pidStr;
  std::ostringstream convert;
  convert << getpid();
  pidStr = convert.str();
  std::string pidFilePath = cfg.agsapiPidDirPath + '/' + pidStr;
  std::cout << pidFilePath << std::endl;
  std::ofstream pidsFile(pidFilePath.c_str());
  // -------------------------------------------------------------------------

  DBHandler dbHandler(cfg.dbName);
  dbHandler.ExecQuery("BEGIN TRANSACTION");

  AGSDDSSpy::Utility::SetKeyboardInterruptCallback(Quit);

  AGSDDSSpy spy = AGSDDSSpy(cfg.domainId);
  spy.SetRTILicensePath("../rti_license/rti_license.dat");
  spy.AttachUserData((void*)&dbHandler);
  spy.SetFilterTopicSubscriptionCallback(FilterTopicSubscriptionFunction);
  spy.SetProcessDataCallback(ProcessDataFunction);
  spy.Start();

  /* Loop to avoid killing listeners */
  while (_loop) {
    AGSDDSSpy::Utility::Sleep(1);
  }

  spy.Stop();

  return 0;
}
