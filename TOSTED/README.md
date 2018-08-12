# Étape 1

./ExtractDriverNDSIFromTOSArchive.py [DIRECTORY]

# Étape 2

./MergeTOSLogsIntoCSV.py Extracted_DriverNDSI/ "2018-07-14 00:00:01" "2018-07-23 23:59:59"

# Étape 3

./MergeTEDLogsIntoCSV.py [TED_LOGS_DIRECTORY] "2018-07-14 00:00:01" "2018-07-23 23:59:59"

# Étape 4

./FilterEqptstestCas4.py TED.csv CAS4_FILTERED_TED.csv

# Étape 5

./FilterEqptstestCas4.py TOS.csv CAS4_FILTERED_TOS.csv

# Étape 6

./MergeAudaceTEDLogsIntoCSV.py [AUDACE_TED_LOGS_DIRECTORY] "2018-07-14 00:00:01" "2018-07-23 23:59:59"

# Étape 7

./MergeAudaceTOSLogsIntoCSV.py [AUDACE_TED_LOGS_DIRECTORY] "2018-07-14 00:00:01" "2018-07-23 23:59:59"

# Étape 8

./FilterEqptstestCas4.py Audace_TED.csv CAS4_FILTERED_Audace_TED.csv

# Étape 9

./FilterEqptstestCas4.py Audace_TOS.csv CAS4_FILTERED_Audace_TOS.csv

# Étape 10 et +

./MergeTOSTED.py [TED_FILE] [TOS_FILE] "2018-07-14 00:00:01" "2018-07-23 23:59:59" [OUTPUT_CSV]
