# TOSTEDCommand

Génération de fichiers de comparaison entre les log des systèmes T&D et TOSCANE.

## Génération automatique du fichier TOSTED.xlsx

### Étape 1

Créer un dossier de données ayant l'arborescence suivante:

[TREE]

TOS: Dossier contenant les log LIBA TOSCANE au format .tar.gz
HISTO\_TED: Dossier contenant les log HISTO TED par minutes au format csv
parc.csv: Fichier PARC
cas4.csv: Liste des équipements du CAS4

### Étape 2

Configurer les répertoire dans le fichier config.json.

data\_directory\_path: Chemin vers le répertoire de données créé à l'étape 1.
result\_directory\_path: Chemin vers le répertoire qui contiendra les fichiers qui
seront générés. Si le dossier n'existe pas, il sera créé.
start\_date: Début de la tranche horaire sur laquelle effectuer les comparaisons.
end\_date: Fin de la tranche horaire sur laquelle effectuer les comparaisons.

REMARQUE: Les dates doivent être au format YYYY-MM-DD HH:MM:SS

### Étape 3

Lancer le script run.py en double cliquant dessus depuis l'explorateur de
fichiers ou en ligne de commande depuis un terminal.
