#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <list>
#include <vector>
#include <mutex>
#include <memory>
#include <SDL.h>
#include "..\ressources\TConcurrent_queue.h"

class Joueur;
class EntiteVolante;
class Ennemis;
class CEsquadronTie;
class Projectile;
enum categorie;

class GameWorld
{
private:
	static int Score;
	

	static std::list<EntiteVolante*>::iterator A;
	//static std::list<std::shared_ptr<EntiteVolante>>::iterator A;
	//static std::list<std::shared_ptr<EntiteVolante>> AllGameEntities;
	static std::list<EntiteVolante*> AllGameEntities;
	static std::mutex A_lock;
	static concurrent_queue<EntiteVolante*> RBuffer;
	static std::vector<SDL_Thread*> GameThreads;
	static SDL_Thread* ReaperPtr;
	static std::mutex R_lock;
	static bool SignalReaper;
	

	//static std::list<EntiteVolante*>::iterator P;
	//static std::list<EntiteVolante*> PlayerHolder;
	//static std::list<EntiteVolante*>::iterator S;
	//static std::list<EntiteVolante*> EnnemieSimple;
	//static std::list<CEsquadronTie*> FormationEnnemie;
	//static std::list<CEsquadronTie*>::iterator F;
	//static std::list<Projectile*>::iterator T;
	//static std::list<Projectile*> TirsLaser;
	//static std::mutex P_lock;
	//static std::mutex S_lock;
	//static std::mutex F_lock;
	//static std::mutex T_lock;

	
public:
	static int ReaperThread(void*);
	static void Close();
	static void DeleteGameWorld();

	template<typename T>
	static T* AddToGameWorld(T* entity) {
		std::lock_guard<std::mutex> lock(A_lock);
		AllGameEntities.push_back(entity);
		/*AllGameEntities.push_back(std::make_shared<EntiteVolante>(*entity));
		Joueur *PtrToSend = static_cast<Joueur*>(AllGameEntities.back().get());*/
		T* PtrToSend = static_cast<T*>(AllGameEntities.back());
		return PtrToSend;
	}

	/*static Joueur* AddToGameWorld(Joueur* entity);
	static Ennemis* AddToGameWorld(Ennemis* entity);
	static CEsquadronTie* AddToGameWorld(CEsquadronTie* entity);
	static Projectile* AddToGameWorld(Projectile* entity);*/

	static bool VerifierImpact(Projectile*);

	static void RenderWorld();


	template<typename ToTH>
	static void GameWorld::AddThread(SDL_ThreadFunction func, std::string func_name, ToTH param)
	{
		GameThreads.push_back(SDL_CreateThread(func, func_name.c_str(), (void*)param));
	}

	template<typename ToTH>
	static void AddThread(SDL_ThreadFunction func, ToTH param)
	{
		GameThreads.push_back(SDL_CreateThread(func, ((std::string)("EMPTY")).c_str(), (void*)param));
	}


	static std::list<Joueur*>* AccessPlayerHolder();
	static std::list<Ennemis*>* AccessEnnemieSimple();

	//static void ReleaseContainer(std::list<Joueur>*) { P_lock.unlock(); }
	//static void ReleaseContainer(std::list<Ennemis>*) { S_lock.unlock(); }

	/*void RemoveFromGameWorld(Joueur *entity);
	void RemoveFromGameWorld(Ennemis *entity);
	void RemoveFromGameWorld(std::vector<Ennemis> *entity);*/

};
#endif 


