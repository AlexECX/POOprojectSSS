#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur : public EntiteVolante
{
public:
	Joueur(categorie, affiliation, int, int, int, int, int);
	~Joueur();
	
	void MouvUp();
	void MouvDown();
	void MouvLeft();
	void MouvRight();
	void MouvUpLeft();
	void MouvDownLeft();
	void MouvUpRight();
	void MouvDownRight();
};
#endif 