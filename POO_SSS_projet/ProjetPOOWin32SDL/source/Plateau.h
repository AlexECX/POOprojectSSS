#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <list>
#include <vector>
#include <mutex>

class Joueur;
class EntiteVolante;
class Ennemis;

class GameWorld
{
private:
	std::list<Joueur> PlayerHolder;
	std::list<std::vector<Ennemis>> EnnemisMultiple;
	std::list<Ennemis> EnnemieSimple;
	std::mutex M_lock;
	std::mutex S_lock;
	std::mutex P_lock;

public:
	GameWorld();
	~GameWorld();


	Joueur* AddToGameWorld(Joueur &entity) { 
		PlayerHolder.push_back(entity); 
		return &PlayerHolder.back();
	}

	Ennemis* AddToGameWorld(Ennemis &entity) {
		EnnemieSimple.push_back(entity);
		return &EnnemieSimple.back();
	}

	std::vector<Ennemis>* AddToGameWorld(std::vector<Ennemis> &entity){ 
		EnnemisMultiple.push_back(entity); 
		return &EnnemisMultiple.back();
	}

	std::list<Joueur>* AccessPlayerHolder();
	std::list<Ennemis>* AccessEnnemieSimple();
	std::list<std::vector<Ennemis>>* AccessEnnemisMultiple();

	void ReleaseContainer(std::list<Joueur>*) { P_lock.unlock(); }
	void ReleaseContainer(std::list<Ennemis>*) { S_lock.unlock(); }
	void ReleaseContainer(std::list<std::vector<Ennemis>>*) { M_lock.unlock(); }

};
#endif 