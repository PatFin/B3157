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
//------------------------------------------------------ Include personnel
#include "StockageTable.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static FILE * lecture;
//------------------------------------------------------ Fonctions privées
static void print_prime_factors ( uint64_t nombre )
{
	facteur * retour;
	Search ( nombre, &retour );

	printf("%" PRIu64 " :", retour->nombre );
	while ( retour->diviseur != 1 )
	{
		printf(" %" PRIu64 "", retour->diviseur );
		Search ( retour->diviseur, &retour );
	}
	printf ( " %" PRIu64 "\n", retour->premier );
}

static void get_prime_factors ( uint64_t nombre )
// Mode d'emploi :
//	Fait moi confiance
// Contrat :
//	Fait moi confiance
// Algorithme :
//	Trust me, I'm an engineer
{
	//printf( "%" PRIu64 " :", nombre );

	facteur * retour;
	if ( Search ( nombre, &retour ) == 0 )
	{
		//Le nombre est déjà connu. Pas la peine de continuer
		return;
	}

	//Le nombre n'a pas encore été factorisé.

	//On prépare le stockage en mémoire de la factorisation
	retour = malloc ( sizeof ( facteur ) );
	retour->nombre = nombre;
	//Restent diviseur et premier à renseigner

	while ( nombre % 2 == 0 )		//Boucle où on essaye de diviser par deux
	{
		nombre = nombre / 2;
		retour->diviseur = nombre;
		retour->premier = 2;

		Insert ( retour );

		//Maintenant on regarde si nombre (qui a changé) n'est pas déjà connu
		if ( Search ( nombre, &retour ) == 0 )
		{
			//On a terminé
			return;
		}
		//Il faut continuer de factoriser
		//On prépare de nouveau la mémoire pour le prochain facteur
		retour = malloc ( sizeof ( facteur ) );
		retour->nombre = nombre;
	}

	while ( nombre % 3 == 0 )		//Boucle où on essaye de diviser par trois
	{
		nombre = nombre / 3;

		retour->diviseur = nombre;
		retour->premier = 3;

		Insert ( retour );

		//Maintenant on regarde si nombre (qui a changé) n'est pas déjà connu
		if ( Search ( nombre, &retour ) == 0 )
		{
			//On a terminé
			return;
		}
		//Il faut continuer de factoriser
		//On prépare de nouveau la mémoire pour le prochain facteur
		retour = malloc ( sizeof ( facteur ) );
		retour->nombre = nombre;
	}

	uint64_t i = 5;
	uint64_t inc = 4;
	while ( i * i < nombre )
	{
		if ( nombre%i == 0 )
		{
			nombre = nombre / i;

			retour->diviseur = nombre;
			retour->premier = i;

			Insert ( retour );

			//Maintenant on regarde si nombre (qui a changé) n'est pas déjà connu
			if ( Search ( nombre, &retour ) == 0 )
			{
				//On a terminé
				return;
			}
			//Il faut continuer de factoriser
			//On prépare de nouveau la mémoire pour le prochain facteur
			retour = malloc ( sizeof ( facteur ) );
			retour->nombre = nombre;
		}
		else
		{
			inc = 6 - inc;
			i+= inc;
		}
	}//-- fin while
	//On est sorti de la boucle -> nombre est nécessairement premier

	retour->diviseur = 1;
	retour->premier = nombre;

	Insert ( retour );

} //----- fin de get_prime_factors

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( )
// Algorithme :
//
{
	InitMemoire ( );

	lecture = fopen ( "input.txt" , "r");

	uint64_t nombre;
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", & nombre ) ) )
	{
		get_prime_factors ( nombre );
		//print_prime_factors ( nombre );
	}

	fclose ( lecture );

	DestructionMemoire ( );

	return 0;
} //----- fin de main
