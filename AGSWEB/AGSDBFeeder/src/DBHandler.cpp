/* DBHandler.cpp */

#include <DBHandler.h>
#include <iostream>

DBHandler::DBHandler(std::string dbName) {
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(QString::fromStdString(dbName));
  if(db.open()) {
    std::cout << "Connected to " <<
    db.databaseName().toStdString() << std::endl;
  } else {
    std::cout << "Connection to the db failed failed" << std::endl;
    qDebug() << "ERROR: " << db.lastError().text();
  }
}

DBHandler::~DBHandler(void) {
  std::cout << "Closing DB" << std::endl;
  db.close();
}

void DBHandler::DisplayTable(std::string table) {
  QSqlQuery query;
  if(query.exec("SELECT * FROM " + QString::fromStdString(table))) {
    while(query.next()) {
      std::cout << "NEW ENTRY" << std::endl;
      for(int x = 0; x < query.record().count(); ++x) {
        std::cout << "\t" <<
        query.record().fieldName(x).toStdString() << " = " <<
        query.value(x).toString().toStdString() << std::endl;
      }
    }
  }
}

void DBHandler::Query(std::string queryStr) {
  QSqlQuery query;
  query.exec(QString::fromStdString(queryStr));
}

void DBHandler::RemoveDDSEntryWithSameNameTypeAndIdInfo(std::string name,
                                                        std::string type,
                                                        std::string idInfo) {
  QSqlQuery query;

  /* DELETE FROM DDS WHERE name=":name" AND type=":type" AND data LIKE "%idInfo: :idInfo%" */
  query.prepare(QString::fromStdString("DELETE FROM DDS WHERE name=\"" + name + "\" AND type=\"" + type + "\" AND data LIKE \"%idInfo: " + idInfo +"%\""));
  if (query.exec()) {
    /* std::cout << "EXECUTED : " << query.executedQuery().toStdString() << std::endl; */
    /* qDebug() << "AFFECTED_ROWS : " << query.numRowsAffected(); */
    return;
  } else {
    /* std::cerr << "RemoveDDSEntryWithSameNameTypeAndIdInfo failed" << std::endl; */
    /* qDebug() << "ERROR: " << query.lastError().text(); */
  }
}

void DBHandler::InsertDDSEntry(std::string name,
                               std::string type,
                               std::string data) {
  QSqlQuery query;

  query.prepare("INSERT INTO DDS (id, name, type, data)"
                " VALUES (NULL, :name, :type, :data)");
  query.bindValue(":name", QString::fromStdString(name));
  query.bindValue(":type", QString::fromStdString(type));
  query.bindValue(":data", QString::fromStdString(data));

  if (query.exec()) {
    return;
  } else {
    std::cerr << "InsertDDSEntry failed" << std::endl;
    qDebug() << "ERROR: " << query.lastError().text();
  }
}

void DBHandler::InsertObjetEntry(std::string name, std::string libelle, std::string typeObjet,
                                 std::string groupe, std::string espace) {
  QSqlQuery query;

  query.prepare("INSERT INTO DescObjet (name, libelle, typeObjet, groupe, espace)"
                " VALUES (:name, :libelle, :typeObjet, :groupe, :espace)");
  query.bindValue(":name", QString::fromStdString(name));
  query.bindValue(":libelle", QString::fromStdString(libelle));
  query.bindValue(":typeObjet", QString::fromStdString(typeObjet));
  query.bindValue(":groupe", QString::fromStdString(groupe));
  query.bindValue(":espace", QString::fromStdString(espace));

  if (query.exec()) {
    return;
  } else {
    std::cerr << "InsertNameLibelleTypeEntry failed" << std::endl;
    qDebug() << "ERROR: " << query.lastError().text();
  }
}
