/*************************************************************************
                           Stockage  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---------- Réalisation du module <Stockage> (fichier Stockage.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Stockage.h"
#include <stdlib.h>
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int Search ( uint64_t cible, facteur ** feuille, facteur * racine )
{
	*feuille = racine;
	int retour = 42;
	do {
		if ( (*feuille)->nombre == cible )
		{
			retour = 0;
		}
		else
		{
			if ( cible < (*feuille)->nombre )
			{
				if ( (*feuille)->filsGauche != (*feuille) )
				{
					*feuille = (*feuille)->filsGauche;
				}
				else
				{
					retour = -1;
				}
			}
			else
			{
				if ( (*feuille)->filsDroit != (*feuille) )
				{
					*feuille = (*feuille)->filsDroit;
				}
				else
				{
					retour = -1;
				}
			}
		}
	} while( retour == 42 );

	return retour;
}



void Insert ( facteur * feuille, facteur * racine )
// Algorithme :
//	Algorithme récursif. On descend dans l'arbre jusqu'à ce qu'on trouve une
//	place pour la nouvelle feuille.
{
	facteur * parent = racine;
	int estPlace = 0;

	do {
		if ( feuille->nombre < parent->nombre)
		{
			if ( parent->filsGauche == parent )
			{
				parent->filsGauche = feuille;
				estPlace = 42;
			}
			else
			{
				parent = parent->filsGauche;
			}
		}
		else
		{
			if ( parent->filsDroit == parent )
			{
				parent->filsDroit = feuille;
				estPlace = 42;
			}
			else
			{
				parent = parent->filsDroit;
			}
		}
	} while ( estPlace == 0 );
}

facteur * Init ( )
{
	facteur * racine = malloc ( sizeof ( facteur ) );
	racine->facteur = racine;
	racine->diviseur = 2;
	racine->filsDroit = racine;
	racine->filsGauche = racine;
	racine->nombre = 2;

	return racine;
} //----- fin de Init

void End ( facteur * racine )
// Algorithme :
//	On utilise un algorithme récursif qui va détruire les fils (gauche et droit)
//	Avant de détruire 'racine'.
{
	if ( racine->filsGauche != racine )
	{
		End ( racine->filsGauche );
	}

	if ( racine->filsDroit != racine )
	{
		End ( racine->filsDroit );
	}

	free ( racine );
}
