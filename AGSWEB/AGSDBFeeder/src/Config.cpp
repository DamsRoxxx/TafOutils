/* Config.cpp */

#include "Config.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstdlib>

/* Check if a file exists */
static bool FileExists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

/* Return the executable path */
/* static std::string GetExecutablePath(void) { */
/*   const int buffSize = 2000; */
/*   std::string linkPath = "/proc/" + std::to_string(getpid()) + "/exe"; */
/*   char* buff = (char*)malloc(sizeof(char) * buffSize); */
/*   readlink((const char*)linkPath.c_str(), buff, buffSize * sizeof(char)); */
/*   std::string executablePath(buff); */
/*   free(buff); */
/*   return executablePath; */
/* } */

Config::Config(void) : 
  domainId(0) {
}

int Config::Load(int argc, char** argv) {
  /* To specify the path of the QoS profile XML file */

  if (argc != 3) {
    std::cout << "Usage : AGSDBFeeder [DomainID] [QoSProfile]"
              << std::endl;
    return -1;
  }

  domainId = atoi(argv[1]);

  /* Check for the QoS profile XML file */
  if (FileExists("USER_QOS_PROFILES.xml")) {
    std::cout << "USER_QOS_PROFILES.xml will be use istead of the specified file" << std::endl;
  } else {
    std::string qosProfileFilePath = argv[2];
    if (!FileExists(qosProfileFilePath)) {
      std::cerr << "Can't reach " << qosProfileFilePath << std::endl;
      return -1;
    }
    nddsQosProfiles = "NDDS_QOS_PROFILES=" + qosProfileFilePath;
    putenv((char*)nddsQosProfiles.c_str());
  }

  const char* dbNameTmp = std::getenv("AGSAPI_DB");
  if (dbNameTmp == NULL) {
    return -1;
  } else {
    dbName = std::string(dbNameTmp);
  }

  const char* agsapiDirPathTmp = std::getenv("AGSAPI_PATH");
  if (agsapiDirPathTmp == NULL) {
    return -1;
  } else {
    agsapiDirPath = std::string(agsapiDirPathTmp);
  }

  return 1;
}
