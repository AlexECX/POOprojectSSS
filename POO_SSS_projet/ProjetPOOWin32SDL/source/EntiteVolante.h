#ifndef ENTITEVOLANTE_H
#define ENTITEVOLANTE_H

enum categorie { joueur, ennemis_simple, tir };
enum affiliation { republic, empire, neutre, environnement };

class EntiteVolante
{
protected:
	categorie Categorie;
	affiliation Affiliation;
	int coordX; //Coordonné de l'objet pour affichage
	int coordY;	//et vérification de colision missile-OTI
	int HP;
	int Damage;
	int VitesseDeplacment;


public:
	EntiteVolante(/*categorie, affiliation, int, int, int, int, int*/);
	virtual ~EntiteVolante();
	int getCoordX() { return coordX; }
	int getCoordY() { return coordY; }
	categorie getCategorie(){ return Categorie; }
	affiliation getAffiliation(){ return Affiliation; }
	int getHP() { return HP; }
	int getDamage() { return Damage; }
	int getVitesseDeplacment() { return VitesseDeplacment; }
	bool isAlive() { return HP <= 0; }

	void DealDamage(int dmg) { HP -= dmg; }


	virtual void UpdateTrajet(int x, int y) { coordX = x; coordY = y; } //incremente la position, en ce 

};
#endif 