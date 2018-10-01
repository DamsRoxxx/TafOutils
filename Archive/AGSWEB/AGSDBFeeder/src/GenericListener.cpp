/* GenericListener.cpp */

#include <iostream>
#include <string>
#include <sstream>
#include "GenericListener.h"

GenericListener::GenericListener(std::string inTopicName, std::string inTypeName, DBHandler* inDBHandler) :
  topicName(inTopicName),
  typeName(inTypeName),
  dbHandler(inDBHandler) {
  ;
}

std::string DynamicDataToString(const DDS_DynamicData& dynamicData) {
  FILE* tmpFile = tmpfile();
  char* buffer;
  long length;

  dynamicData.print(tmpFile, 1);
  fseek(tmpFile, 0, SEEK_END);
  length = ftell(tmpFile);
  fseek(tmpFile, 0, SEEK_SET);
  buffer = (char*)malloc(length);
  if (buffer)
    fread (buffer, 1, length, tmpFile);
  fclose (tmpFile);

  std::string outString(buffer, length - 1);

  free(buffer);

  return outString;
}

void GenericListener::on_data_available(DDSDataReader* reader) {
  /* std::cerr << "GenericListener (" << topicName << ")" << std::endl; */
  DDSDynamicDataReader *dynamicDataReader = NULL;
  DDS_DynamicDataSeq dataSeq;
  DDS_SampleInfoSeq infoSeq;
  DDS_ReturnCode_t retcode;
  int i;

  dynamicDataReader = DDSDynamicDataReader::narrow(reader);
  if (dynamicDataReader == NULL) {
    std::cerr << "DataReader narrow error" << std::endl;
    return;
  }

  retcode = dynamicDataReader->take(dataSeq, infoSeq,
      DDS_LENGTH_UNLIMITED,
      DDS_ANY_SAMPLE_STATE,
      DDS_ANY_VIEW_STATE,
      DDS_ANY_INSTANCE_STATE);

  if (retcode == DDS_RETCODE_NO_DATA) {
    return;
  } else if (retcode != DDS_RETCODE_OK) {
    std::cerr << "take error " << retcode << std::endl;
    return;
  }

  for (i = 0; i < dataSeq.length(); ++i) {
    if (infoSeq[i].valid_data) {
      std::cout << infoSeq[i].source_timestamp.sec << "." << infoSeq[i].source_timestamp.nanosec << "\t" <<
      topicName << "\t" <<
      typeName << std::endl;

      std::string strData = DynamicDataToString(dataSeq[i]);
      std::cout << strData << std::endl;

      /* If it's a DescObjet */
      std::string topicNameStr = std::string(topicName);
      if (topicNameStr.find("DescObjet") != std::string::npos) {
        std::cout << "-ADD OBJET-" << std::endl;

        /* Extract nom */
        int startPos = strData.find('"') + 1;
        int endPos = strData.find('"', startPos);
        std::string name = strData.substr(startPos, endPos - startPos);

        /* Extract type */
        startPos = strData.find('"', endPos + 1) + 1;
        endPos = strData.find('"', startPos);
        std::string typeObjet = strData.substr(startPos, endPos - startPos);

        /* Extract libelle */
        startPos = strData.find('"', endPos + 1) + 1;
        endPos = strData.find('"', startPos);
        std::string libelle = strData.substr(startPos, endPos - startPos);

        /* Extract idGroupe */
        startPos = strData.find('"', endPos + 1) + 1;
        endPos = strData.find('"', startPos);
        std::string groupe = strData.substr(startPos, endPos - startPos);

        /* Extract idEspace */
        startPos = strData.find('"', endPos + 1) + 1;
        endPos = strData.find('"', startPos);
        std::string espace = strData.substr(startPos, endPos - startPos);

        dbHandler->InsertObjetEntry(name, libelle, typeObjet, groupe, espace);
      }

      /* Else if it's an Alarme, Etat, Mesure or InfoGen */
      /* Insert data into DB */
      else if (strData.find("idInfo") != std::string::npos){
        /* Extract idObjet */
        int startPos = strData.find('"') + 1;
        int endPos = strData.find('"', startPos);
        std::string idObjet = strData.substr(startPos, endPos - startPos);

        /* Extract idInfo */
        startPos = strData.find(':', endPos + 1);
        endPos = strData.find('\n', startPos);
        std::string idInfo = strData.substr(startPos + 2, endPos - startPos - 2);

        /* Remove old entry if exists */
        dbHandler->RemoveDDSEntryWithSameNameTypeAndIdInfo(idObjet, topicName, idInfo); /* topicName is the type ! */

        /* Add the new entry */
        dbHandler->InsertDDSEntry(idObjet, topicName, strData); /* topicName is the type */
      }
      /* --------------- */
    }
  }

  retcode = dynamicDataReader->return_loan(dataSeq, infoSeq);
  if (retcode != DDS_RETCODE_OK) {
    std::cerr << "return loan error " << retcode << std::endl;
  }
}
