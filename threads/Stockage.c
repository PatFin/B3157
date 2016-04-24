/*************************************************************************
                           Stockage  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---------- Réalisation du module <Stockage> (fichier Stockage.c) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
//------------------------------------------------------ Include personnel
#include "Stockage.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static facteur * racine;					//Racine de la mémoire partagée
//------------------------------------------------------ Fonctions privées
static void end ( facteur * racine )
// Algorithme :
//	On utilise un algorithme récursif qui va détruire les fils (gauche et droit)
//	Avant de détruire 'racine'.
{
	if ( racine->filsGauche != racine )
	{
		end ( racine->filsGauche );
	}

	if ( racine->filsDroit != racine )
	{
		end ( racine->filsDroit );
	}

	free ( racine );
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int Search ( uint64_t cible, facteur ** feuille )
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

	for ( ; ; )
	{
		if ( feuille->nombre <= parent->nombre )
		{
			if ( parent->filsGauche == parent )
			{
				parent->filsGauche = feuille;
				return;
			}
			else
			{
				parent = parent->filsGauche;
				continue;
			}
		}
		else
		{
			if ( parent->filsDroit == parent )
			{
				parent->filsDroit = feuille;
				return;
			}
			else
			{
				parent = parent->filsDroit;
				continue;
			}
		}
	}
}

facteur * Init ( )
{
	facteur * feuille = malloc ( sizeof ( facteur ) );
	feuille->facteur = feuille;
	feuille->diviseur = 2;
	feuille->filsDroit = feuille;
	feuille->filsGauche = feuille;
	feuille->nombre = 2;

	return feuille;
} //----- fin de InitMemoire

void InitMemoire ( )
{
	racine = malloc ( sizeof ( facteur ) );
	racine->facteur = racine;
	//racine->diviseur = 4006319;
	//racine->diviseur = 2662183033;
	racine->diviseur = 2281211;
	racine->filsDroit = racine;
	racine->filsGauche = racine;
	racine->nombre = 2281211;
} //----- fin de InitMemoire

facteur * GetRoot ( )
{
	return racine;
}

void End ( )
// Algorithme :
//	On utilise un algorithme récursif qui va détruire les fils (gauche et droit)
//	Avant de détruire 'racine'.
{
	if ( racine->filsGauche != racine )
	{
		end ( racine->filsGauche );
	}

	if ( racine->filsDroit != racine )
	{
		end ( racine->filsDroit );
	}

	free ( racine );
}
