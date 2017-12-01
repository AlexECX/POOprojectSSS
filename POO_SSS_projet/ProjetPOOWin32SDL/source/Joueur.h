#ifndef JOUEUR_H
#define JOUEUR_H

#include "Vaisseau.h"
class Joueur : public Vaisseau
{
public:
	Joueur(categorie, affiliation, int, int, int, int, int);
	~Joueur();
};
#endif 