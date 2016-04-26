/*************************************************************************
                           Question10.1  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---------- Réalisation du module <Question10.1> (fichier Question10.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//------------------------------------------------------ Include personnel
#include "Stockage.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static facteur * racine;
//------------------------------------------------------ Fonctions privées
static facteur * get_prime_factors ( uint64_t nombre )
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

	if ( Search ( nombre, &retour ) == 0 )
	{
		//Le nombre est connu !
		//printf( "Nombre Connu : %" PRIu64 "\n", nombre );
		return retour;
	}
	else
	{
		//Il faut trouver un facteur au nombre

		facteur * retour;
		facteur * nouvelleFeuille;

		if ( nombre % 2 == 0 )
		{
			retour = get_prime_factors ( nombre / 2 );
			nouvelleFeuille = Init ( );
			nouvelleFeuille->nombre = nombre;
			nouvelleFeuille->diviseur = 2;
			nouvelleFeuille->facteur = retour;
			Insert ( nouvelleFeuille, racine );
			return nouvelleFeuille;
		}

		if ( nombre % 3 == 0 )
		{
			retour = get_prime_factors ( nombre / 3 );
			nouvelleFeuille = Init ( );
			nouvelleFeuille->nombre = nombre;
			nouvelleFeuille->diviseur = 3;
			nouvelleFeuille->facteur = retour;
			Insert ( nouvelleFeuille, racine );
			return nouvelleFeuille;
		}

		uint64_t i = 5;
		uint64_t inc = 4;
		while ( i * i < nombre )
		{
			if ( nombre%i == 0 )
			{
				nouvelleFeuille = Init ( );
				retour = get_prime_factors ( nombre / i );	//Appel récursif
				nouvelleFeuille->facteur = retour;
				nouvelleFeuille->nombre = nombre;
				nouvelleFeuille->diviseur = i;
				Insert ( nouvelleFeuille, racine );
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
		Insert ( nouvelleFeuille, racine );
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
	Search ( nombre, &feuille );

	printf("%" PRIu64 ":", nombre);

	while( feuille->facteur != feuille )
	{
		printf( " %" PRIu64"", feuille->diviseur );
		feuille = feuille->facteur;
	}
	printf( " %" PRIu64 "\n", feuille->diviseur );

} //----- print_prime_factors

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( void )
{
	InitMemoire ( );
	racine = GetRoot ( );

	FILE * lecture = fopen ( "input.txt" , "r");

	uint64_t * nombre = malloc ( sizeof ( uint64_t ) );
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", nombre ) ) )
	{
		get_prime_factors ( * nombre );
		print_prime_factors ( * nombre );
	}

	End ( racine );
	return 0;
} //----- fin de Main
