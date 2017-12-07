#include "Plateau.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"


//#include "initialise.h"

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

Joueur* GameWorld::AddToGameWorld(Joueur &entity) {
	Joueur *PtrToSend;
	P_lock.lock();
	PlayerHolder.push_back(entity);
	PtrToSend = &PlayerHolder.back();
	P_lock.unlock();
	return PtrToSend;
}

Ennemis* GameWorld::AddToGameWorld(Ennemis &entity) {
	Ennemis *PtrToSend;
	S_lock.lock();
	EnnemieSimple.push_back(entity);
	PtrToSend = &EnnemieSimple.back();
	S_lock.unlock();
	return PtrToSend;
}

std::vector<Ennemis>* GameWorld::AddToGameWorld(std::vector<Ennemis> &entity) {
	std::vector<Ennemis> *PtrToSend;
	M_lock.lock();
	EnnemisMultiple.push_back(entity);
	PtrToSend = &EnnemisMultiple.back();
	M_lock.unlock();
	return PtrToSend;
}

std::list<Joueur>* GameWorld::AccessPlayerHolder()
{
P_lock.lock(); 
return &PlayerHolder;
		
}

std::list<Ennemis>* GameWorld::AccessEnnemieSimple()
{
	S_lock.lock();
	return &EnnemieSimple;
}

std::list<std::vector<Ennemis>>* GameWorld::AccessEnnemisMultiple()
{
	M_lock.lock();
	return &EnnemisMultiple;
}



