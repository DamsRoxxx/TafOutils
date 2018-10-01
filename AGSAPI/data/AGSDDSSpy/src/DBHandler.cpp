/* DBHandler.cpp */

#include <stdio.h>
#include <iostream>
#include <string>
#include "DBHandler.h"

DBHandler::DBHandler(std::string dbFilePath) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");
  m_db.setDatabaseName(QString::fromStdString(dbFilePath));
  if (m_db.open()) {
    std::cout << "INFO :: DBHandler :: Connected to " << m_db.databaseName().toStdString() << std::endl;

    ExecQuery("PRAGMA journal_mode=WAL"); // Enables WAL mode for concurrent access to the database
    ExecQuery("DROP TABLE IF EXISTS DescObjet");
    ExecQuery("DROP TABLE IF EXISTS DDS");
    ExecQuery("CREATE TABLE DescObjet (ddsData TEXT)");
    /* ExecQuery("CREATE TABLE IF NOT EXISTS DDS (idInfo TEXT, idObjet TEXT, topicName TEXT, ddsData TEXT)"); */
    ExecQuery("CREATE TABLE DDS (pKey TEXT PRIMARY KEY, idObjet TEXT, topicName TEXT, ddsData TEXT)");

  } else {
    std::cout << "ERROR :: DBHandler :: Connection to " << m_db.databaseName().toStdString() << " failed" << std::endl;
    qDebug() << "ERROR :: DBHandler :: " << m_db.lastError().text();
  }
}

DBHandler::~DBHandler(void) {
  std::cout << "INFO :: ~DBHandler :: Closing " << m_db.databaseName().toStdString() << std::endl;
  m_db.close();
}

void DBHandler::ExecQuery(std::string queryStr) {
  QSqlQuery query;
  if (!query.exec(QString::fromStdString(queryStr))) {
    qDebug() << "ERROR :: ExecQuery :: " << query.lastError().text();
  }
}

void DBHandler::InsertDescObjetEntry(std::string ddsData) {
  QSqlQuery query;

  query.prepare("INSERT INTO DescObjet (ddsData) VALUES (:ddsData)");
  query.bindValue(":ddsData", QString::fromStdString(ddsData));

  if (!query.exec()) {
    qDebug() << "ERROR :: InsertDescObjetEntry :: " << query.lastError().text();
  }
}

void DBHandler::InsertDDSEntry(std::string idInfo, std::string idObjet, std::string topicName, std::string ddsData) {
  QSqlQuery query;

  /* DELETE */
  query.prepare("DELETE FROM DDS WHERE idInfo = :idInfo AND idObjet = :idObjet AND topicName = :topicName");
  query.bindValue(":idInfo", QString::fromStdString(idInfo));
  query.bindValue(":idObjet", QString::fromStdString(idObjet));
  query.bindValue(":topicName", QString::fromStdString(topicName));

  if (!query.exec()) {
    qDebug() << "ERROR :: InsertDDSEntry :: " << query.lastError().text();
  }

  /* INSERT */
  query.prepare("INSERT INTO DDS (idInfo, idObjet, topicName, ddsData) VALUES (:idInfo, :idObjet, :topicName, :ddsData)");
  query.bindValue(":idInfo", QString::fromStdString(idInfo));
  query.bindValue(":idObjet", QString::fromStdString(idObjet));
  query.bindValue(":topicName", QString::fromStdString(topicName));
  query.bindValue(":ddsData", QString::fromStdString(ddsData));

  if (!query.exec()) {
    qDebug() << "ERROR :: InsertDDSEntry :: " << query.lastError().text();
  }

}

void DBHandler::ReplaceDDSEntry(std::string idInfo, std::string idObjet, std::string topicName, std::string ddsData) {
  QSqlQuery query;

  /* REPLACE */
  std::string pKeySeparator = "/////";
  query.prepare("REPLACE INTO DDS (pKey, idObjet, topicName, ddsData) VALUES (:pKey, :idObjet, :topicName, :ddsData)");
  query.bindValue(":pKey", QString::fromStdString(idInfo + pKeySeparator + idObjet + pKeySeparator + topicName));
  query.bindValue(":idObjet", QString::fromStdString(idObjet));
  query.bindValue(":topicName", QString::fromStdString(topicName));
  query.bindValue(":ddsData", QString::fromStdString(ddsData));

  if (!query.exec()) {
    qDebug() << "ERROR :: ReplaceDDSEntry :: " << query.lastError().text();
  }
}
