#!/bin/bash
echo "--------------------------------------------------------------------------"
echo "----Calculs des temps d'éxécution des différentes version du programme----"

DEFAULT_OUTPUT="temps.csv"
OUTPUT=DEFAULT_OUTPUT

INPUT_FILE="input.txt"
INPUT_EXTENSION=".txt"
EXE_EXTENSION=".exe"

if [ $1 != "" ]
	echo "Pas de fichier de sortie fourni !"
	echo "utilisation du fichier par défaut: $DEFAULT_OUTPUT."
else
	OUTPUT=$1
fi

#On supprime le fichier d'input pour éviter l'itération sur ce fichier
rm $INPUT_FILE

for input in *$INPUT_EXTENSION
do
	echo `./tests $input Question10.2.exe`

done
