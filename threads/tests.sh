#!/bin/bash
OUTPUT=temps
TIME=/usr/bin/time
FICHIER_ENTREE=input.txt

#On va tester les algorithmes pour différents fichiers d'input
echo "##### TESTS DES ALGORITHMES #############" > $OUTPUT
echo -n "Compilation ..." >> $OUTPUT
make >> /dev/null 2>&1 && echo "Succès" >> $OUTPUT || echo "Échec" >> $OUTPUT

for fichier in tiny.txt small.txt stdinput.txt
do
	cp $fichier $FICHIER_ENTREE
	echo "##### nb Lignes :`wc -l $fichier` #########" >> $OUTPUT
	$TIME -o $OUTPUT -a -f "v2 ------------------------ %E" ./question2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v3 ------------------------ %E" ./question3.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v5 ------------------------ %E" ./question5.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v8 ------------------------ %E" ./question8.exe >> /dev/null

	$TIME -o $OUTPUT -a -f "v2.1 ---------------------- %E" ./question2.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v3.1 ---------------------- %E" ./question3.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v5.1 ---------------------- %E" ./question5.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v8.1 ---------------------- %E" ./question8.1.exe >> /dev/null

	$TIME -o $OUTPUT -a -f "v2.2 ---------------------- %E" ./question2.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v3.2 ---------------------- %E" ./question3.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v5.2 ---------------------- %E" ./question5.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v8.2 ---------------------- %E" ./question8.2.exe >> /dev/null

	$TIME -o $OUTPUT -a -f "v10.1 (Mem Mono-thread) --- %E" ./Question10.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.2 (Mem Mono-thread) --- %E" ./Question10.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.3 (Mem Bi-thread) ----- %E" ./Question10.3.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.4 (Mem Bi-thread) ----- %E" ./Question10.4.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.6 (XMem, Mono-thread) - %E" ./Question10.6.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.7 (XMem, Bi-thread) --- %E" ./Question10.7.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.8 (Mem, Bi-thread) ---- %E" ./Question10.8.exe >> /dev/null
done

for fichier in medium.txt
do
	cp $fichier $FICHIER_ENTREE
	echo "##### nb Lignes :`wc -l $fichier` #########" >> $OUTPUT
	$TIME -o $OUTPUT -a -f "v2.1 ---------------------- %E" ./question2.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v3.1 ---------------------- %E" ./question3.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v5.1 ---------------------- %E" ./question5.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v8.1 ---------------------- %E" ./question8.1.exe >> /dev/null

	$TIME -o $OUTPUT -a -f "v2.2 ---------------------- %E" ./question2.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v3.2 ---------------------- %E" ./question3.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v5.2 ---------------------- %E" ./question5.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v8.2 ---------------------- %E" ./question8.2.exe >> /dev/null

	$TIME -o $OUTPUT -a -f "v10.1 (Mem Mono-thread) --- %E" ./Question10.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.2 (Mem Mono-thread) --- %E" ./Question10.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.3 (Mem Bi-thread) ----- %E" ./Question10.3.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.4 (Mem Bi-thread) ----- %E" ./Question10.4.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.6 (XMem, Mono-thread) - %E" ./Question10.6.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.7 (XMem, Bi-thread) --- %E" ./Question10.7.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.8 (Mem, Bi-thread) ---- %E" ./Question10.8.exe >> /dev/null
done

for fichier in large.txt fat.txt huge.txt
do
	cp $fichier $FICHIER_ENTREE
	echo "##### nb Lignes :`wc -l $fichier` #########" >> $OUTPUT
	$TIME -o $OUTPUT -a -f "v2.2 ---------------------- %E" ./question2.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v3.2 ---------------------- %E" ./question3.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v5.2 ---------------------- %E" ./question5.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v8.2 ---------------------- %E" ./question8.2.exe >> /dev/null

	$TIME -o $OUTPUT -a -f "v10.1 (Mem Mono-thread) --- %E" ./Question10.1.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.2 (Mem Mono-thread) --- %E" ./Question10.2.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.3 (Mem Bi-thread) ----- %E" ./Question10.3.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.4 (Mem Bi-thread) ----- %E" ./Question10.4.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.6 (XMem, Mono-thread) - %E" ./Question10.6.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.7 (XMem, Bi-thread) --- %E" ./Question10.7.exe >> /dev/null
	$TIME -o $OUTPUT -a -f "v10.8 (Mem, Bi-thread) ---- %E" ./Question10.8.exe >> /dev/null
done

cp race2.txt $FICHIER_ENTREE
echo "##### nb Lignes :`wc -l $fichier` #########" >> $OUTPUT

$TIME -o $OUTPUT -a -f "v2.2 ---------------------- %E" ./question2.2.exe >> /dev/null
$TIME -o $OUTPUT -a -f "v3.2 ---------------------- %E" ./question3.2.exe >> /dev/null
$TIME -o $OUTPUT -a -f "v8.2 ---------------------- %E" ./question8.2.exe >> /dev/null

$TIME -o $OUTPUT -a -f "v10.3 (Mem Bi-thread) ----- %E" ./Question10.3.exe >> /dev/null
$TIME -o $OUTPUT -a -f "v10.4 (Mem Bi-thread) ----- %E" ./Question10.4.exe >> /dev/null
$TIME -o $OUTPUT -a -f "v10.8 (Mem, Bi-thread) ---- %E" ./Question10.8.exe >> /dev/null
