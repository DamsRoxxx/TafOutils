/* DBHandler.h */

#ifndef DBHANDLER_H_INCLUDED
#define DBHANDLER_H_INCLUDED

#include <string>
#include "QtSql"

class DBHandler {
  public:
  DBHandler(std::string dbFilePath);
  ~DBHandler(void);
  void InsertDescObjetEntry(std::string ddsData);
  void InsertDDSEntry(std::string idInfo, std::string idObjet, std::string topicName, std::string ddsData);
  void ReplaceDDSEntry(std::string idInfo, std::string idObjet, std::string topicName, std::string ddsData);
  void ExecQuery(std::string query);

  private:
  QSqlDatabase m_db;
};

#endif /* DBHANDLER_H_INCLUDED */
