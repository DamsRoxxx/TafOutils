#!/usr/bin/python
# coding: utf-8

from PyQt4.QtSql import QSqlDatabase, QSqlQuery
from Logger import *
import threading

class DBHandler:
    connection_id = 0

    def __init__(self, database_name):
        # Connection to the database

        # Increase connection_id for a thread-safe database access (Dirty)
        connection_id_lock = threading.Lock()
        connection_id_lock.acquire()
        self.__class__.connection_id += 1
        if self.__class__.connection_id > 1000000:
            self.__class__.connection_id = 0
        self.instance_connection_id = str(self.__class__.connection_id)
        connection_id_lock.release()

        self.db = QSqlDatabase.addDatabase("QSQLITE", str(self.instance_connection_id))

        self.db.setDatabaseName(database_name)
        if self.db.open():
            print("Connected to the database ID->" + self.instance_connection_id)
            pass
        else:
            print("Cannot connect to the database")

    def close(self):
        print("Closing connection to the database ID->" + self.instance_connection_id)
        self.db.close()
        del self.db
        QSqlDatabase.removeDatabase(self.instance_connection_id)

    def get_descobjet_list(self):
        query = QSqlQuery(self.db)
        if not query.exec_("SELECT * FROM DescObjet"):
            logging.error("%s", query.lastError().text())

        descobjet_list = []
        while query.next():
            dds_data = unicode(query.record().value(0).toString())
            descobjet_list.append(dds_data)

        return descobjet_list

    def get_dds_data_list(self, id_objet, topic_name):
        query = QSqlQuery(self.db)
        
        # "DATA LIKE" to match things like AlarmeV2 even when the topic_name passed is Alarme
        query.prepare('SELECT * FROM DDS WHERE idObjet = :idObjet AND topicName LIKE "{0}%"'.format(topic_name))
        query.bindValue(":idObjet", id_objet)
        # query.bindValue(":topicName", topic_name)

        if not query.exec_():
            logging.error("%s", query.lastError().text())

        dds_data_list = []
        while query.next():
            dds_data = unicode(query.record().value(3).toString())
            dds_data_list.append(dds_data)

        return dds_data_list
