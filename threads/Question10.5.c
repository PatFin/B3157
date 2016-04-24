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
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static void print_prime_factors ( uint64_t nombre )
// Mode d'emploi :
//	Fait confiance
// Contrat :
//	Fait confiance
// Algorithme :
//	Trust me, I'm an engineer
{
	printf( "%" PRIu64 " :", nombre );
	for ( ; ; )		//Boucle infinie où on essaye de diviser par deux
	{
		if ( nombre % 2 == 0 )
		{
			nombre = nombre / 2;
			printf ( " 2");

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
			printf ( " 3");

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

			printf(" %" PRIu64 "", i );
		}
		else
		{
			inc = 6 - inc;
			i+= inc;
		}
	}//-- fin while
	//On est sorti de la boucle -> nombre est nécessairement premier

	printf(" %" PRIu64 "\n", nombre );

} //----- fin de get_prime_factors

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( )
// Algorithme :
//
{
	FILE * lecture = fopen ( "input.txt" , "r");

	uint64_t * nombre = malloc ( sizeof ( uint64_t ) );
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", nombre ) ) )
	{
		print_prime_factors ( * nombre );
	}
	return 0;
} //----- fin de main
