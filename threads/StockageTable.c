/*************************************************************************
                           StockageTable  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---- Réalisation du module <StockageTable> (fichier StockageTable.c) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------ Include personnel
#include "StockageTable.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
#define TAILLE_TABLEAU	64
//------------------------------------------------------------------ Types
struct feuille;
struct feuille
{
	struct feuille * filsGauche;
	struct feuille * filsDroit;
	struct facteur * nombre;
};
typedef struct feuille feuille;
//---------------------------------------------------- Variables statiques
feuille racine [ TAILLE_TABLEAU ];
//------------------------------------------------------ Fonctions privées
static void destructionArbre ( feuille * root )
{
	free ( root->nombre );

	if ( root->filsGauche != NULL )
	{
		destructionArbre ( root->filsGauche );
	}
	if ( root->filsDroit != NULL )
	{
		destructionArbre ( root->filsDroit );
	}
	free ( root );
}

static void insertArbre ( facteur * resultat, feuille * ptrRacine )
{
	feuille * nouvelleFeuille = malloc ( sizeof ( feuille ) );
	nouvelleFeuille->filsGauche = NULL;
	nouvelleFeuille->filsDroit = NULL;
	nouvelleFeuille->nombre = resultat;

	for ( ; ; )
	{
		if ( resultat->nombre < ptrRacine->nombre->nombre )
		{
			if ( ptrRacine->filsGauche == NULL )
			{
				//Allocation
				ptrRacine->filsGauche = nouvelleFeuille;
				return;
			}
			else
			{
				ptrRacine = ptrRacine->filsGauche;
				continue;
			}
		}
		else
		{
			if ( ptrRacine->filsDroit == NULL )
			{
				//Allocation
				ptrRacine->filsDroit = nouvelleFeuille;
				return;
			}
			else
			{
				ptrRacine = ptrRacine->filsDroit;
				continue;
			}
		}
	}
}

static int searchArbre ( uint64_t nombre, facteur ** resultat, feuille * root )
{
	for ( ; ; )
	{
		if ( root->nombre->nombre == nombre )
		{
			resultat = &root->nombre;
			return 0;
		}
		else
		{
			if ( root->nombre->nombre < nombre )
			{
				if ( root->filsGauche != NULL )
				{
					root = root -> filsGauche;
					continue;
				}
				return -1;
			}
			else
			{
				if ( root->filsDroit != NULL )
				{
					root = root -> filsDroit;
					continue;
				}
				return -1;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void InitMemoire ( )
{
	unsigned int i;
	for ( i = 0; i < TAILLE_TABLEAU ; i++ )
	{
		racine [ i ].nombre = NULL;
		racine [ i ].filsGauche = NULL;
		racine [ i ].filsDroit = NULL;
	}
}

void Insert ( facteur * resultat )
{
	//printf ( "----- %" PRIu64 " = %" PRIu64 " * %" PRIu64 " -----\n", resultat->nombre, resultat->premier, resultat->diviseur );
	feuille * ptrRacine = &( racine [ __builtin_clzll (resultat->nombre) ] );
	if ( ptrRacine->nombre == NULL )
	{
		ptrRacine->nombre = resultat;
	}
	else
	{
		insertArbre ( resultat, ptrRacine );
	}
}

void DestructionMemoire ( )
{
	unsigned int i;
	for ( i = 0; i < TAILLE_TABLEAU ; i++ )
	{
		if ( racine [ i ].nombre != NULL )
		{
			free(racine[i].nombre);

			if ( racine [ i ].filsGauche != NULL )
			{
				destructionArbre(racine[i].filsGauche);
			}

			if ( racine [ i ].filsDroit != NULL )
			{
				destructionArbre(racine[i].filsDroit);
			}
		}
	}
}

int Search ( uint64_t nombre, facteur ** resultat )
{
	//printf ( "On cherche %" PRIu64 "\n", nombre );
	feuille * root = &( racine [ __builtin_clzll ( nombre ) ] );
	if ( root->nombre != NULL )
	{
		//ie il existe un arbre, on cherche dedans
		return searchArbre ( nombre, resultat, root );
	}
	return -1;
}
