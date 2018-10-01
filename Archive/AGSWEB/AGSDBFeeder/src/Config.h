/* Config.h */

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <string>

class Config {
  public:
  Config();
  int Load(int argc, char** argv);

  int domainId;
  std::string nddsQosProfiles; /* In class scope for putenv */

  std::string dbName;
  std::string agsapiDirPath;

  private:
  
};

#endif /* CONFIG_H_INCLUDED */

