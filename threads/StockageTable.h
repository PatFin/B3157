/*************************************************************************
                           StockageTable  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//------- Interface du module <StockageTable> (fichier StockageTable.h) --
#if ! defined ( Stockage_H )
#define Stockage_H

//------------------------------------------------------------------------
// Rôle du module <StockageTable>
//	Ce fichier décrit l'interface de la mémoisation des facteurs successifs
//	des nombre rencontrés.
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <inttypes.h>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
struct facteur;
struct facteur
{
	uint64_t nombre;
	uint64_t diviseur;
	uint64_t premier;
};
typedef struct facteur facteur;
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int Search ( uint64_t nombre, facteur ** resultat );
// Mode d'emploi :
//	Permet de rechercher la feuille contenant le nombre passé en paramètre dans
//	La structure de données 'racine'.
//	Si la feuille existe, le pointeur feuille passé en paramètre prend pour
//	valeur l'adresse de cette feuille et la fonction renvoie 0.
//	Sinon la méthode renvoie -1.
// Contrat :
//	Pas de contrat.

void Insert ( facteur * insert );
// Mode d'emploi :
//	Permet d'insérer une feuille dans le stockage.
// Contrat :
//	La feuille doit avoir ses deux fils égaux à elle-même, avoir une valeur de
//	nombre correcte et avoir facteur pointant sur une feuille de l'arbre déjà
//	existante (et ayant du sens :P). Bref c'est compliqué à expliquer.
//	Ah et il ne faut pas que le nombre soit déjà présent dans la structure. Ça
//	évitera des bogues.

void InitMemoire ( );
// Mode d'emploi :
//	Permet d'initialiser la mémoire. Renvoie une feuille qu'il faudra envoyer
//	dans l'arbre avec Insert.
// Contrat :
//	Pas de contrat

void DestructionMemoire ( );
// Mode d'emploi :
//	Permet de libérer l'espace mémoire
// Contrat :
//	La racine passée en paramètre ne doit avoir été manipulée que par des
//	fonctions du présent module et avoir été correctement intialisé avec la
//	fonction Init.


#endif // Stockage_H
