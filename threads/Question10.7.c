/*************************************************************************
                           XXX  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---------- Réalisation du module <XXX> (fichier XXX.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
//------------------------------------------------------ Include personnel
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static FILE * lecture;
static pthread_mutex_t mutexAffichage;
static pthread_mutex_t mutexLecture;
//------------------------------------------------------ Fonctions privées
static void print_prime_factors ( unsigned int nombre, uint64_t * tableau )
{
	unsigned int i = 1;
	pthread_mutex_lock ( &mutexAffichage );
	printf ( "%" PRIu64 " :", *tableau );
	for ( ; i < nombre; i ++ )
	{
		printf(" %" PRIu64 "", tableau [ i ] );
	}
	printf("\n");
	pthread_mutex_unlock ( &mutexAffichage );
}

static unsigned int get_prime_factors ( uint64_t * resultat )
// Mode d'emploi :
//	Fait confiance
// Contrat :
//	Fait confiance
// Algorithme :
//	Trust me, I'm an engineer
{
	unsigned int compteur = 1;
	uint64_t nombre = resultat [ 0 ];
	for ( ; ; )		//Boucle infinie où on essaye de diviser par deux
	{
		if ( nombre % 2 == 0 )
		{
			nombre = nombre / 2;
			//printf ( " 2");
			resultat [ compteur ++ ] = 2;

			continue;
		}
		else
		{
			break;
		}
	}

	for ( ; ; )		//Boucle infinie où on essaye de diviser par trois
	{
		if ( nombre % 3 == 0 )
		{
			nombre = nombre / 3;
			//printf ( " 3");
			resultat [ compteur ++ ] = 3;

			continue;
		}
		else
		{
			break;
		}
	}

	uint64_t i = 5;
	uint64_t inc = 4;
	while ( i * i < nombre )
	{
		if ( nombre%i == 0 )
		{
			nombre = nombre / i;

			//printf(" %" PRIu64 "", i );
			resultat [ compteur ++ ] = i;
		}
		else
		{
			inc = 6 - inc;
			i+= inc;
		}
	}//-- fin while
	//On est sorti de la boucle -> nombre est nécessairement premier

	//printf(" %" PRIu64 "\n", nombre );
	resultat [ compteur ++ ] = nombre;

	return compteur;
} //----- fin de get_prime_factors

void threadMain ( )
{
	uint64_t * nombre = malloc ( 20 * sizeof ( uint64_t ));
	unsigned int nbre;
	pthread_mutex_lock ( &mutexLecture );
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", nombre ) ) )
	{
		//Lecture effectuée, on rends l'accès
		pthread_mutex_unlock ( &mutexLecture );

		nbre = get_prime_factors ( nombre );
		print_prime_factors ( nbre, nombre );
	}
	pthread_mutex_unlock ( &mutexLecture );

	free ( nombre );
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( )
// Algorithme :
//
{
	lecture = fopen ( "input.txt" , "r");

	pthread_mutex_init ( &mutexLecture, NULL );
	pthread_mutex_init ( &mutexAffichage, NULL );

	pthread_t thread1, thread2;

	pthread_create ( &thread1, NULL, (void *) &threadMain, NULL );
	pthread_create ( &thread2, NULL, (void *) &threadMain, NULL );
//-------------------------PHASE MOTEUR ------------------------
	pthread_join( thread1, NULL );
	pthread_join( thread2, NULL );

	pthread_mutex_destroy ( &mutexAffichage );
	pthread_mutex_destroy ( &mutexLecture );

	fclose ( lecture );

	return 0;
} //----- fin de main
