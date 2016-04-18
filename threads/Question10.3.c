/*************************************************************************
                           Question10.3  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---- Réalisation du module <Question10.3> (fichier Question10.3.cpp) ---

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
static facteur * racine;					//Racine de la mémoire partagée
static FILE * lecture;						//Pointeur de lecture du fichier
static pthread_t thread1;					//Premier Thread
static pthread_t thread2;					//Second Thread
static pthread_mutex_t mutexLecture;		//Mutex pour l'affichage
static pthread_mutex_t mutexAffichage;		//Mutex pour lecture du fichier
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
	if ( Search ( nombre, &retour, racine ) == 0 )
	{
		pthread_mutex_unlock ( mutexLectureMemoire );
		//Le nombre est connu !
		//printf( "Nombre Connu : %" PRIu64 "\n", nombre );
		return retour;
	}
	else
	{
		pthread_mutex_unlock ( mutexLectureMemoire );

		//Il faut trouver un facteur au nombre
		facteur * nouvelleFeuille;

		if ( nombre % 2 == 0 )
		{
			nouvelleFeuille = Init ( );
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
			nouvelleFeuille = Init ( );
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
			if ( nombre%i == 0 )
			{
				nouvelleFeuille = Init ( );
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
		nouvelleFeuille = Init ( );
		nouvelleFeuille->nombre = nombre;
		nouvelleFeuille->diviseur = nombre;
		reserverMemoirePourEcriture ( );
		Insert ( nouvelleFeuille, retour );
		libererMemoireApresEcriture ( );
		return nouvelleFeuille;
	}
}

static void print_prime_factors ( uint64_t nombre )
// Mode d'emploi :
//	Permet d'afficher les facteurs premiers du nombre  passé en paramètre.
// Contrat :
//	Les facteurs premiers de nombre doivent avoir été préalablement calculés.
{
	facteur * feuille;
	Search ( nombre, &feuille, racine );

	//On veut commencer à afficher, on protège la ressource
	pthread_mutex_lock ( &mutexAffichage );
	printf("%" PRIu64 ":", nombre);
	while( feuille->facteur != feuille )
	{
		printf( " %" PRIu64"", feuille->diviseur );
		feuille = feuille->facteur;
	}
	printf( " %" PRIu64 "\n", feuille->diviseur );
	//Fin de l'affichage, on en rends l'accès
	pthread_mutex_unlock ( &mutexAffichage );
} //----- print_prime_factors

void threadMain ( void * thrData )
{
	thdata * data = (thdata *) thrData;
	uint64_t nombre;
	//On veut lire, on protège
	pthread_mutex_lock ( &mutexLecture );
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", &nombre ) ) )
	{
		//Lecture effectuée, on rends l'accès
		pthread_mutex_unlock ( &mutexLecture );

		//Calcul des facteurs
		get_prime_factors ( nombre, data->mutexMemoire );

		//Affichage
		print_prime_factors ( nombre );
	}
	pthread_mutex_unlock ( &mutexLecture );
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( void )
{
	//Initialisation de la mémoire
	racine = Init ( );

	//Ouverture du fichier d'entrée en lecture
	lecture = fopen ( "input.txt" , "r");

	//Création des mutex pour la lecture du fichier et l'affichage
	pthread_mutex_init ( &mutexLecture, NULL );
	pthread_mutex_init ( &mutexAffichage, NULL );
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

	//Attente de la fin des threads
	pthread_join( thread1, NULL );

	//Destruction des mutex pour lecture fichier et affichage
	pthread_mutex_destroy ( &mutexLecture );
	pthread_mutex_destroy ( &mutexAffichage );
	pthread_mutex_destroy ( &mutexMemThr1 );
	pthread_mutex_destroy ( &mutexMemThr2 );

	//Destruction de la mémoire
	End ( racine );
	return 0;
} //----- fin de Main
