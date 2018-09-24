#!/usr/bin/python
# coding: utf-8

from PyQt4.QtSql import QSqlDatabase, QSqlQuery
import random
import threading

class DBHandler:
    connection_id = 0

    def __init__(self, database_name):
        # Connection to the database

        # Increase connection_id for a thread-safe database access
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
            # print("Connected to the database ID->" + self.instance_connection_id)
            pass
        else:
            print("Cannot connect to the database")

    def close(self):
        # print("Closing connection to the database ID->" + self.instance_connection_id)
        self.db.close()
        del self.db
        QSqlDatabase.removeDatabase(self.instance_connection_id)
            
    # List all available names in the database
    def list_names(self):
        query = QSqlQuery(self.db)
        query.exec_("SELECT * FROM DescObjet")
        names_list = []
        while query.next():
            name = str(query.record().value(0).toString())
            names_list.append(name)
        return names_list

    # List all available names in the database
    def list_name_libelle_type(self):
        query = QSqlQuery(self.db)
        query.exec_("SELECT * FROM DescObjet")
        names_list = []
        while query.next():
            name = str(query.record().value(0).toString())
            libelle = str(query.record().value(1).toString())
            type_objet = str(query.record().value(2).toString())
            names_list.append('name: "{0}"\nlibelle: "{1}"\ntypeObjet: "{2}"'.format(name, libelle, type_objet))
        return names_list

    def make_objet_table(self):
        query = QSqlQuery(self.db)
        query.exec_("SELECT * FROM DescObjet")
        table = dict()
        while query.next():
            name = str(query.record().value(0).toString())
            libelle = unicode(query.record().value(1).toString(), "utf-8")
            type_objet = str(query.record().value(2).toString())
            table[name] = dict()
            table[name]["libelle"] = libelle
            table[name]["type"] = type_objet
        return table

    def make_descobjet_dict(self):
        query = QSqlQuery(self.db)
        query.exec_("SELECT * FROM DescObjet")
        objet_dict = dict()
        knownGroupe = []
        knownEsapce = []

        while query.next():
            nom = str(query.record().value(0).toString())
            libelle = unicode(query.record().value(1).toString(), "utf-8")
            type_objet = str(query.record().value(2).toString())
            groupe = str(query.record().value(3).toString())
            espace = str(query.record().value(4).toString())

            if not groupe in knownGroupe:
                objet_dict[groupe] = dict()
                knownGroupe.append(groupe)
            if not espace in knownEsapce:
                objet_dict[groupe][espace] = dict()
                knownEsapce.append(espace)

            objet_dict[groupe][espace][libelle] = dict()
            objet_dict[groupe][espace][libelle]["nom"] = nom
            objet_dict[groupe][espace][libelle]["type"] = type_objet

        return objet_dict

    # List data filtering by name and type
    def list_data(self, name="", type="", limit="", filter=""):
        data_list = []

        if name == "":
            return ""
        query = QSqlQuery(self.db)

        if limit != "":
           limit = " LIMIT " + limit

        if filter != "":
            try:
                filter_split = filter.split('=')
                filter = 'AND data LIKE "%{0}: {1}%"'.format(filter_split[0], filter_split[1])
            except:
                data_list.append("filter: BAD FILTER")
                filter = ""

        if type != "":
            query.exec_("SELECT * FROM DDS WHERE name = \"{0}\""
                        "AND type LIKE \"{1}%\"".format(name, type) + filter + limit)
        else:
            query.exec_("SELECT * FROM DDS WHERE name = \"{0}\"".format(name) + filter + limit)
        print query.lastQuery()

        while query.next():
            type = str(query.value(2).toString())
            data = str(query.value(3).toString())
            data_list.append("type: " + type + '\n' + data)
        return data_list

if __name__ == '__main__':
    db_path = "../../common/db/DDS.db"
    print db_path
    db = DBHandler(db_path)
    import json
    jstr = json.dumps(db.make_descobjet_dict(), sort_keys=True, indent=4)
    print(jstr)


