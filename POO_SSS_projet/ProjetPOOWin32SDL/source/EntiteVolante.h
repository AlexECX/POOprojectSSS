#ifndef ENTITEVOLANTE_H
#define ENTITEVOLANTE_H

enum categorie { joueur, ennemis_simple, tir_joueur, tir_tie };

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
	int Active;
	


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

	bool isAlive() { return HP > 0; }
	bool isActive() { return Active == 0; }

	void TakeDamage(int dmg) { HP -= dmg; }
	void Remove() { Active++; }


	virtual void UpdateTrajet(int x, int y);

};
#endif 