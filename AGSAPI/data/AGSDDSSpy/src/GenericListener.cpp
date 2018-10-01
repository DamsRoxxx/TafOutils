/* GenericListener.cpp */

#include <iostream>
#include <string>
#include <sstream>
#include "GenericListener.h"

GenericListener::GenericListener(std::string inTopicName, std::string inTypeName, AGSDDSSpyArgs inSpyArgs) :
  topicName(inTopicName),
  typeName(inTypeName),
  spyArgs(inSpyArgs) {
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
      /* std::cout << infoSeq[i].source_timestamp.sec << "." << infoSeq[i].source_timestamp.nanosec << "\t" << */
      /* topicName << "\t" << */
      /* typeName << std::endl; */

      std::string strData = DynamicDataToString(dataSeq[i]);
      if (spyArgs.m_ProcessData != NULL) {
        spyArgs.m_ProcessData(topicName, strData, spyArgs.m_userData);
      }
    }
  }

  retcode = dynamicDataReader->return_loan(dataSeq, infoSeq);
  if (retcode != DDS_RETCODE_OK) {
    std::cerr << "return loan error " << retcode << std::endl;
  }
}
