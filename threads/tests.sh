DESTINATION="temps.csv"

echo "Version;Temps" > $DESTINATION
/usr/bin/time --format "question2;%E" -o $DESTINATION -a ./question2.exe > /dev/null
/usr/bin/time --format "question3;%E" -o $DESTINATION -a ./question3.exe > /dev/null
/usr/bin/time --format "question5;%E" -o $DESTINATION -a ./question5.exe > /dev/null
/usr/bin/time --format "question8;%E" -o $DESTINATION -a ./question8.exe > /dev/null

echo "Calculs des temps d'éxécution terminés, fichier $DESTINATION prêt."
