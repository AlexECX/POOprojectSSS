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


	Joueur* AddToGameWorld(Joueur &entity);
	Ennemis* AddToGameWorld(Ennemis &entity);
	std::vector<Ennemis>* AddToGameWorld(std::vector<Ennemis> &entity);

	std::list<Joueur>* AccessPlayerHolder();
	std::list<Ennemis>* AccessEnnemieSimple();
	std::list<std::vector<Ennemis>>* AccessEnnemisMultiple();

	void ReleaseContainer(std::list<Joueur>*) { P_lock.unlock(); }
	void ReleaseContainer(std::list<Ennemis>*) { S_lock.unlock(); }
	void ReleaseContainer(std::list<std::vector<Ennemis>>*) { M_lock.unlock(); }

};
#endif 