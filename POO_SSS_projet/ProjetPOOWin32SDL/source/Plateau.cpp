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



