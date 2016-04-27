/*************************************************************************
                           Stockage  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---------- Interface du module <Stockage> (fichier Stockage.h) ---------
#if ! defined ( Stockage_H )
#define Stockage_H

//------------------------------------------------------------------------
// Rôle du module <Stockage>
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
	struct facteur * facteur;
	struct facteur * filsGauche;
	struct facteur * filsDroit;
	uint64_t nombre;
	uint64_t diviseur;
};
typedef struct facteur facteur;
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int Search ( uint64_t cible, facteur ** feuille );
// Mode d'emploi :
//	Permet de rechercher la feuille contenant le nombre passé en paramètre dans
//	La structure de données 'racine'.
//	Si la feuille existe, le pointeur feuille passé en paramètre prend pour
//	valeur l'adresse de cette feuille et la fonction renvoie 0.
//	Sinon la méthode renvoie -1.
// Contrat :
//	'racine' reste inchangé.
//	'feuille' en revanche sera modifié par cette fonction et ne doit donc pas
//	(plus) avoir de sens pour la fonction appellante.
//	'racine' doit être un Stockage valide.

void Insert ( facteur * feuille, facteur * racine );
// Mode d'emploi :
//	Permet d'insérer une feuille dans le stockage.
// Contrat :
//	La feuille doit avoir ses deux fils égaux à elle-même, avoir une valeur de
//	nombre correcte et avoir facteur pointant sur une feuille de l'arbre déjà
//	existante (et ayant du sens :P). Bref c'est compliqué à expliquer.
//	Ah et il ne faut pas que le nombre soit déjà présent dans la structure. Ça
//	évitera des bogues.

facteur * GetRoot ( );

facteur * Init ( );
// Mode d'emploi :
//	Permet d'initialiser la mémoire. Renvoie une feuille qu'il faudra envoyer
//	dans l'arbre avec Insert.
// Contrat :
//	Pas de contrat

void InitMemoire ( );

void DestructionMemoire ( );
// Mode d'emploi :
//	Permet de libérer l'espace mémoire dynamiquement alloué.
// Contrat :
//	La racine passée en paramètre ne doit avoir été manipulée que par des
//	fonctions du présent module et avoir été correctement intialisé avec la
//	fonction Init.


#endif // Stockage_H
