#!/usr/bin/python
# coding: utf-8

from subprocess import call

startDate = "2018-08-02 00:00:01"
endDate = "2018-08-05 23:59:59"

tosLogs = "RES/TOS"
tedLogs = "RES/TED"

audaceTosLogs = "RES/AUDACE_TOS"
audaceTedLogs = "RES/AUDACE_TED"

parc = "RES/parc.csv"

histoTed = "RES/HISTO_TED/HISTO_TED.csv"

# Formate les logs TOS en CSV
cmd = """
./MergeTOSLogsIntoCSV.py {} "{}" "{}"
""".format(tosLogs, startDate, endDate)
print(cmd)
call(cmd, shell=True)

# Filtre les equipements cas4 du fichier TOS.csv et genere le fichier CAS4_FILTERED_TOS.csv
cmd = """
./FilterEqptstestCas4.py TOS.csv CAS4_FILTERED_TOS.csv
"""
print(cmd)
call(cmd, shell=True)

# Formate les logs TED en CSV
cmd = """
./MergeTEDLogsIntoCSV.py {} "{}" "{}"
""".format(tedLogs, startDate, endDate)
print(cmd)
call(cmd, shell=True)

# Filtre les equipements cas4 du fichier TED.csv et genere le fichier CAS4_FILTERED_TED.csv
cmd = """
./FilterEqptstestCas4.py TED.csv CAS4_FILTERED_TED.csv
"""
print(cmd)
call(cmd, shell=True)

# Formate les logs Audace_TOS en Audace_TOS.csv
cmd = """
./MergeAudaceTOSLogsIntoCSV.py {} "{}" "{}"
""".format(audaceTosLogs, startDate, endDate)
print(cmd)
call(cmd, shell=True)

# Filtre les equipements cas4 du fichier Audace_TOS.csv et genere le fichier CAS4_FILTERED_Audace_TOS.csv
cmd = """
./FilterEqptstestCas4.py Audace_TOS.csv CAS4_FILTERED_Audace_TOS.csv
"""
print(cmd)
call(cmd, shell=True)

# Formate les logs Audace_TED en Audace_TED.csv
cmd = """
./MergeAudaceTEDLogsIntoCSV.py {} "{}" "{}"
""".format(audaceTedLogs, startDate, endDate)
print(cmd)
call(cmd, shell=True)

# Filtre les equipements cas4 du fichier Audace_TED.csv et genere le fichier CAS4_FILTERED_Audace_TED.csv
cmd = """
./FilterEqptstestCas4.py Audace_TED.csv CAS4_FILTERED_Audace_TED.csv
"""
print(cmd)
call(cmd, shell=True)

# Formate le fichier parc
cmd = """
./FilterParc.py {} {}
""".format(parc, "PARC.csv")
print(cmd)
call(cmd, shell=True)

# Formate le fichier HISTO_TED.csv
cmd = """
./FormatHistoTed.py {} {} "{}" "{}" {}
""".format(histoTed, "HISTO_TED.csv", startDate, endDate, parc)
print(cmd)
call(cmd, shell=True)

# Inutile ?
# Filtre les equipements cas4 du fichier HISTO_TED.csv et genere le fichier CAS4_FILTERED_HISTO_TED.csv
cmd = """
./FilterEqptstestCas4.py HISTO_TED.csv CAS4_FILTERED_HISTO_TED.csv
"""
print(cmd)
call(cmd, shell=True)

# Tout mettre dans un dossier results
resultsDir = "results"
cmd = """
mkdir -p {0}
mv CAS4_FILTERED_TED.csv {0}/TED.csv
mv CAS4_FILTERED_TOS.csv {0}/TOS.csv
mv CAS4_FILTERED_Audace_TED.csv {0}/Audace_TED.csv
mv CAS4_FILTERED_Audace_TOS.csv {0}/Audace_TOS.csv
mv CAS4_FILTERED_HISTO_TED.csv {0}/HISTO_TED.csv

rm TED.csv
rm TOS.csv
rm Audace_TED.csv
rm Audace_TOS.csv
rm HISTO_TED.csv
""".format(resultsDir)
print(cmd)
call(cmd, shell=True)
