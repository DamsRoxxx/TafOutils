/* Main.cpp */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include "GenericClient.h"
#include "DBHandler.h"
#include "Config.h"
#include <unistd.h>
#include <iomanip>
#include <locale>
#include <string>
#include <sstream>

/* To be able to destroy the GenericClient properly when Ctrl-C is pressed */
GenericClient* _genericClientPtr;

/* Executed when Ctrl-C is pressed to properly destroy the GenericClient */
void Quit(int s) {
  std::cout << std::endl << "Quit" << std::endl;
  _genericClientPtr->~GenericClient();
  exit(0);
}

/* Main function */
void GenericClientMain(Config& cfg) {
  GenericClient genericClient(cfg);

  /* Execute Quit function when Ctrl-C is pressed */
  _genericClientPtr = &genericClient;
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = Quit;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  /* Loop to avoid killing listeners */
  struct DDS_Duration_t waitTime = {1, 0};
  for (;;) {
    NDDSUtility::sleep(waitTime);
  }
}

int main(int argc, char** argv) {
  Config cfg;

  if (cfg.Load(argc, argv) == -1) {
    std::cerr << "Config::Load failed make sure your starting "
                 "the program from the top-level start script." << std::endl;
    return 0;
  }

  std::string pidStr;
  std::ostringstream convert;
  convert << getpid();
  pidStr = convert.str();

  std::string pidFilePath = cfg.agsapiDirPath + "/common/pids/" + pidStr;
  std::cout << pidFilePath << std::endl;
  std::ofstream pidsFile(pidFilePath.c_str());

  /* Main function */
  GenericClientMain(cfg);

  return 1;
}
