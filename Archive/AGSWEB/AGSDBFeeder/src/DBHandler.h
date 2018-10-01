/* DBHandler.h */

#ifndef DBHANDLER_H_INCLUDED
#define DBHANDLER_H_INCLUDED

#include <QtSql>
#include <string>

class DBHandler {
  public:

  /* Methods */
  DBHandler(std::string dbName);
  ~DBHandler(void);
  void DisplayTable(std::string table);
  void Query(std::string query);
  void RemoveDDSEntryWithSameNameTypeAndIdInfo(std::string name, std::string type, std::string idInfo);
  void InsertDDSEntry(std::string name, std::string type, std::string data);
  void InsertObjetEntry(std::string name, std::string libelle, std::string typeObjet,
                        std::string groupe, std::string espace);

  /* Attributs */
  QSqlDatabase db;

  private:
};

#endif /* DBHANDLER_H_INCLUDED */
