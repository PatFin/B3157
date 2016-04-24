/*************************************************************************
                           Question10.4  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---- Réalisation du module <Question10.4> (fichier Question10.4.c) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
//------------------------------------------------------ Include personnel
#include "Stockage.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef struct str_thdata					//Données associées à un thread
{
    int thread_no;
    pthread_mutex_t * mutexMemoire;
} thdata;
//---------------------------------------------------- Variables statiques
static FILE * lecture;						//Pointeur de lecture du fichier
static pthread_t thread1;					//Premier Thread
static pthread_t thread2;					//Second Thread
static pthread_mutex_t mutexLecture;		//Mutex pour la lecture du fichier

#ifndef NODISPLAY
static pthread_mutex_t mutexAffichage;		//Mutex pour affichage
#endif
static pthread_mutex_t mutexMemThr1;		//Mutex pour l'accès à la mémoire T1
static pthread_mutex_t mutexMemThr2;		//Mutex pour l'accès à la mémoire T2
//------------------------------------------------------ Fonctions privées
static void reserverMemoirePourEcriture ( )
{
	pthread_mutex_lock ( &mutexMemThr2 );
	pthread_mutex_lock ( &mutexMemThr1 );
}

static void libererMemoireApresEcriture ( )
{
	pthread_mutex_unlock ( &mutexMemThr2 );
	pthread_mutex_unlock ( &mutexMemThr1 );
}

static facteur * get_prime_factors ( uint64_t nombre, pthread_mutex_t * mutexLectureMemoire )
// Mode d'emploi :
//	Calcule les facteurs premiers du nombre passé en paramètre et les stocke
//	dans la structure de données.
// Algorithme :
//	Si le nombre demandé, aucun calcul n'est fait.
//	Si le nombre demandé n'est pas présent, on lui cherche un facteur. Dès qu'un
//	facteur est trouvé, on appelle cette fonction récursivement pour le nombre
//	divisé par ce diviseur. Au retour, on insère une nouvelle feuille dans
//	l'arbre.
{
	facteur * retour;

	pthread_mutex_lock ( mutexLectureMemoire );
	if ( Search ( nombre, &retour ) == 0 )
	{
		pthread_mutex_unlock ( mutexLectureMemoire );
		return retour;
	}
	else
	{
		pthread_mutex_unlock ( mutexLectureMemoire );

		//Il faut trouver un facteur au nombre
		facteur * nouvelleFeuille = malloc ( sizeof ( facteur ) );
		nouvelleFeuille->filsGauche = nouvelleFeuille;
		nouvelleFeuille->filsDroit = nouvelleFeuille;

		if ( nombre % 2 == 0 )
		{
			nouvelleFeuille->nombre = nombre;
			nouvelleFeuille->diviseur = 2;
			nouvelleFeuille->facteur = get_prime_factors ( nombre / 2, mutexLectureMemoire );

			reserverMemoirePourEcriture ( );
			Insert ( nouvelleFeuille, retour );
			libererMemoireApresEcriture ( );

			return nouvelleFeuille;
		}

		if ( nombre % 3 == 0 )
		{
			nouvelleFeuille->nombre = nombre;
			nouvelleFeuille->diviseur = 3;
			nouvelleFeuille->facteur = get_prime_factors ( nombre / 3, mutexLectureMemoire );

			reserverMemoirePourEcriture ( );
			Insert ( nouvelleFeuille, retour );
			libererMemoireApresEcriture ( );

			return nouvelleFeuille;
		}

		uint64_t i = 5;
		uint64_t inc = 4;
		while ( i * i < nombre )
		{
			if ( nombre % i == 0 )
			{
				nouvelleFeuille->facteur = get_prime_factors ( nombre / i, mutexLectureMemoire );	//Appel récursif;
				nouvelleFeuille->nombre = nombre;
				nouvelleFeuille->diviseur = i;
				reserverMemoirePourEcriture ( );
				Insert ( nouvelleFeuille, retour );
				libererMemoireApresEcriture ( );

				return nouvelleFeuille;
			}
			else
			{
				inc = 6 - inc;
				i+= inc;
			}
		}//-- fin while
		//On est sorti de la boucle -> nombre est nécessairement premier
		nouvelleFeuille->nombre = nombre;
		nouvelleFeuille->diviseur = nombre;
		nouvelleFeuille->facteur = nouvelleFeuille;
		reserverMemoirePourEcriture ( );
		Insert ( nouvelleFeuille, retour );
		libererMemoireApresEcriture ( );

		return nouvelleFeuille;
	}
}

#ifndef NODISPLAY
static void print_prime_factors ( facteur * feuille )
// Mode d'emploi :
//	Permet d'afficher les facteurs premiers du nombre  passé en paramètre.
// Contrat :
//	Les facteurs premiers de nombre doivent avoir été préalablement calculés.
{

	//On veut commencer à afficher, on protège la ressource
	pthread_mutex_lock ( &mutexAffichage );
	printf("%" PRIu64 ":", feuille->nombre);
	while( feuille->facteur != feuille )
	{
		printf( " %" PRIu64"", feuille->diviseur );
		feuille = feuille->facteur;
	}
	printf( " %" PRIu64 "\n", feuille->diviseur );
	//Fin de l'affichage, on en rends l'accès
	pthread_mutex_unlock ( &mutexAffichage );
} //----- print_prime_factors
#endif

void threadMain ( void * thrData )
{
	thdata * data = (thdata *) thrData;
	uint64_t nombre;
	facteur * nombreCalcule;

	//On veut lire, on protège
	pthread_mutex_lock ( &mutexLecture );
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", &nombre ) ) )
	{
		//Lecture effectuée, on rends l'accès
		pthread_mutex_unlock ( &mutexLecture );

		//Calcul des facteurs
		nombreCalcule = get_prime_factors ( nombre, data->mutexMemoire );
#ifndef NODISPLAY
		//Affichage
		print_prime_factors ( nombreCalcule );
#endif
	}
	pthread_mutex_unlock ( &mutexLecture );
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( void )
{
	//Initialisation de la mémoire
	InitMemoire ( );

	//Ouverture du fichier d'entrée en lecture
	lecture = fopen ( "input.txt" , "r");

	//Création des mutex pour la lecture du fichier et l'affichage
	pthread_mutex_init ( &mutexLecture, NULL );
#ifndef NODISPLAY
	pthread_mutex_init ( &mutexAffichage, NULL );
#endif
	pthread_mutex_init ( &mutexMemThr1, NULL );
	pthread_mutex_init ( &mutexMemThr2, NULL );

	//Création des paquest de données attachés aux threads
	thdata dataThread1;
	dataThread1.mutexMemoire = &mutexMemThr1;
	thdata dataThread2;
	dataThread2.mutexMemoire = &mutexMemThr2;

	//Création des threads
	pthread_create( &thread1, NULL, (void *) &threadMain, &dataThread1 );
	pthread_create( &thread2, NULL, (void *) &threadMain, &dataThread2 );

//------------------------------PHASE MOTEUR -----------------------------------

	//Attente de la fin des threads
	pthread_join( thread1, NULL );
	pthread_join( thread2, NULL );

	//Destruction des mutex pour lecture fichier et affichage
	pthread_mutex_destroy ( &mutexLecture );
#ifndef NODISPLAY
	pthread_mutex_destroy ( &mutexAffichage );
#endif
	pthread_mutex_destroy ( &mutexMemThr1 );
	pthread_mutex_destroy ( &mutexMemThr2 );

	//Fermeture du fichier
	fclose ( lecture );

	//Destruction de la mémoire
	End ( );
	return 0;
} //----- fin de Main
