#ifndef ENTITEVOLANTE_H
#define ENTITEVOLANTE_H

<<<<<<< HEAD
enum categorie { joueur, ennemis_simple, tir_joueur, tir_tie};
=======
enum categorie { joueur, ennemis_simple, tir_joueur, tir_tie };
>>>>>>> 20508cb639d3284a706d98f80c30c99fc6d34863
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
	bool Deleted;
	


public:
	EntiteVolante(categorie, affiliation, int, int, int, int, int);
	virtual ~EntiteVolante();
	int getCoordX() { return coordX; }
	int getCoordY() { return coordY; }
	categorie getCategorie(){ return Categorie; }
	affiliation getAffiliation(){ return Affiliation; }
	int getHP() { return HP; }
	int getDamage() { return Damage; }
	int getVitesseDeplacment() { return VitesseDeplacment; }

	bool isAlive() { return HP >= 0; }
	bool isRemoved() { return Deleted; }

	void TakeDamage(int dmg) { HP -= dmg; }
	void Remove() { Deleted = true; }


	virtual void UpdateTrajet(int x, int y) { coordX = x; coordY = y; } //incremente la position, en ce 

};
#endif 