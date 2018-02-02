#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <type_traits>
#include <list>
#include <vector>
#include <mutex>
#include <memory>
#include <SDL.h>
#include "..\ressources\TConcurrent_queue.h"

class EntiteVolante;

class GameWorld
{
private:
	GameWorld();
	GameWorld(const GameWorld&) = delete;
	GameWorld(GameWorld&&) = delete;
	void operator=(const GameWorld&) = delete;
	void operator=(GameWorld&&) = delete;


	static std::list<std::shared_ptr<EntiteVolante>> ColisionList;
	static std::vector<EntiteVolante*> ColisionLists[4][4];
	static std::mutex GameWorld::C_lock;

	static std::list<std::shared_ptr<EntiteVolante>>::iterator B;
	static std::list<std::shared_ptr<EntiteVolante>>::iterator C;

	static std::list<std::shared_ptr<EntiteVolante>>::iterator A;
	static std::list<std::shared_ptr<EntiteVolante>> AllGameEntities;
	static std::mutex A_lock;

	static std::vector<SDL_Thread*> GameThreads;
	static int Score;
    static bool ThreadSignal;
	

	static void RenderWorld();

	
public:
	~GameWorld();
	static GameWorld& Get();

	static int ColisionThread(void*);
	static int RenderingThread(void*);

	//static void DeleteGameWorld();

	//static bool AssignCadrant();

	//void RenderWorld();

	template<class T>
	std::shared_ptr<T> AddToGameWorld(T* entity) {
		static_assert(std::is_base_of<EntiteVolante, T>::value, "T must be derived from EntiteVolante");
		std::shared_ptr<EntiteVolante> SharedEntity(entity);
		std::lock_guard<std::mutex> lock(A_lock);
		AllGameEntities.push_back(SharedEntity);
		ColisionList.push_back(SharedEntity);
		return static_pointer_cast<T>(SharedEntity);
	}

	template<typename ToTH>
	void AddThread(SDL_ThreadFunction func, std::string func_name, ToTH param)
	{
		GameThreads.push_back(SDL_CreateThread(func, func_name.c_str(), (void*)param));
	}

	template<typename ToTH>
	void AddThread(SDL_ThreadFunction func, ToTH param)
	{
		GameThreads.push_back(SDL_CreateThread(func, ((std::string)("EMPTY")).c_str(), (void*)param));
	}

};
#endif 


