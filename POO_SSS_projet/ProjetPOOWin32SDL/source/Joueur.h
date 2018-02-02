#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur : public EntiteVolante
{
public:
	Joueur(affiliation, int, int);
	~Joueur();
	
	void UpdateTrajet(int x, int y) override;

	void MouvUp();
	void MouvDown();
	void MouvLeft();
	void MouvRight();

};
#endif 