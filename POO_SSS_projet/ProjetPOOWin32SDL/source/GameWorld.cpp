#include "GameWorld.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"
#include "WorldRenderer.h"
#include <SDL.h>
#include "..\ressources\TConcurrent_queue.h"
#include "..\ressources\LTexture.h"



int GameWorld::Score;
//int* GameWorld::ReaperReturnValue;
//SDL_sem* GameWorld::RBuffer_semlock;

//std::list<std::shared_ptr<EntiteVolante>>::iterator GameWorld::A;
std::list<EntiteVolante*>::iterator GameWorld::A;
std::list<EntiteVolante*> GameWorld::AllGameEntities;
//std::list<std::shared_ptr<EntiteVolante>> GameWorld::AllGameEntities;

concurrent_queue<EntiteVolante*> GameWorld::RBuffer;
std::vector<SDL_Thread*> GameWorld::GameThreads;
SDL_Thread* GameWorld::ReaperPtr;
std::mutex GameWorld::R_lock;
bool GameWorld::SignalReaper;

//std::list<EntiteVolante*>::iterator  GameWorld::A;
//std::list<EntiteVolante*>  GameWorld::PlayerHolder;
//std::list<EntiteVolante*>::iterator  GameWorld::A;
//std::list<EntiteVolante*>  GameWorld::EnnemieSimple;
//std::list<CEsquadronTie*>::iterator GameWorld::F;
//std::list<CEsquadronTie*> GameWorld::FormationEnnemie;
//std::list<Projectile*>::iterator GameWorld::A;
//std::list<Projectile*> GameWorld::TirsLaser;

std::mutex GameWorld::A_lock;
//std::mutex GameWorld::A_lock;
//std::mutex GameWorld::A_lock;
//std::mutex GameWorld::F_lock;
//std::mutex GameWorld::A_lock;

//GameWorld::GameWorld()
//{
//}

//GameWorld::GameWorld(WorldRenderer* renderer_instance)
//					: RendererInstance(renderer_instance)
//{
//}

//GameWorld::~GameWorld()
//{
//	A_lock.lock();
//	for (A = PlayerHolder.begin(); A != PlayerHolder.end(); A++) 
//		delete (*A);
//	A_lock.unlock();
//
//	A_lock.lock();
//	for (T = TirsLaser.begin(); T != TirsLaser.end(); T++)
//		delete (*T);
//	A_lock.unlock();
//
//	F_lock.lock();
//	for (F = FormationEnnemie.begin();
//			F != FormationEnnemie.end(); F++)
//		delete (*F);
//	F_lock.unlock();
//}


int GameWorld::ReaperThread(void*)
{
	
	static SDL_sem* RBuffer_semlock = SDL_CreateSemaphore(20);
	//static std::vectorEntiteVolante* RBuffer[20] = { nullptr };
	while (!SignalReaper) {
		if (!RBuffer.empty()) {
			delete RBuffer.front();
			RBuffer.pop_front();
		}
		else {
			SDL_Delay(1);
		}
			
	}
	while (!RBuffer.empty())
		RBuffer.pop_front();
	A_lock.lock();
	while (!AllGameEntities.empty())
		AllGameEntities.pop_back();
	A_lock.unlock();
	return 0;
}

void GameWorld::Close()
{
	SignalReaper = true;
}


void GameWorld::DeleteGameWorld()
{
	static int* GameTHReturnValue;
	while (!GameThreads.empty()) {
		SDL_WaitThread(GameThreads.back(), GameTHReturnValue);
		GameThreads.pop_back();
	}

	/*A_lock.lock();
	for (A = PlayerHolder.begin(); A != PlayerHolder.end(); A++)
		delete (*A);
	A_lock.unlock();

	A_lock.lock();
	for (T = TirsLaser.begin(); T != TirsLaser.end(); T++)
		delete (*T);
	A_lock.unlock();*/

	/*A_lock.lock();
	for (A = AllGameEntities.begin(); A != AllGameEntities.end(); A++)
		delete (*A);
	A_lock.unlock();*/
}
//
//Joueur* GameWorld::AddToGameWorld(Joueur *entity)
//{
//	A_lock.lock();
//	AllGameEntities.push_back(entity);
//	/*AllGameEntities.push_back(std::make_shared<EntiteVolante>(*entity));
//	Joueur *PtrToSend = static_cast<Joueur*>(AllGameEntities.back().get());*/
//	Joueur* PtrToSend = (Joueur*)AllGameEntities.back();
//	A_lock.unlock();
//	return PtrToSend;
//}
//
//Ennemis* GameWorld::AddToGameWorld(Ennemis *entity) 
//{
//	Ennemis *PtrToSend;
//	A_lock.lock();
//	AllGameEntities.push_back(entity);
//	/*AllGameEntities.push_back(std::make_shared<EntiteVolante>(*entity));
//	PtrToSend = static_cast<Ennemis*>(AllGameEntities.back().get());*/
//	PtrToSend = (Ennemis*)AllGameEntities.back();
//	A_lock.unlock();
//	return PtrToSend;
//}
//
//
//CEsquadronTie* GameWorld::AddToGameWorld(CEsquadronTie *entity)
//{
//	/*CEsquadronTie *PtrToSend;
//	F_lock.lock();
//	FormationEnnemie.push_back(entity);
//	PtrToSend = FormationEnnemie.back();
//	F_lock.unlock();
//	return PtrToSend;*/
//	return entity;
//}
//
//Projectile* GameWorld::AddToGameWorld(Projectile *entity)
//{
//	Projectile *PtrToSend;
//	A_lock.lock();
//	AllGameEntities.push_back(entity);
//	//std::shared_ptr<EntiteVolante> p = std::make_shared<EntiteVolante>(*entity);
//	/*AllGameEntities.push_back(std::make_shared<EntiteVolante>(*entity));
//	PtrToSend = static_cast<Projectile*>(AllGameEntities.back().get());*/
//	PtrToSend = (Projectile*)AllGameEntities.back();
//	A_lock.unlock();
//	//PtrToSend->MakeFly();
//	return PtrToSend;
//}


bool GameWorld::VerifierImpact(Projectile* Tir){
	bool Impact = false;
	if (Tir->getAffiliation() == republic) 
		A_lock.lock();
		A = AllGameEntities.begin();
		while (A != AllGameEntities.end() && !Impact) {
			if ((*A)->getAffiliation() != Tir->getAffiliation())
			if ((*A)->isAlive()) {
				int x1 = (*A)->getCoordX() + 30 - Tir->getCoordX();
				int y1 = (*A)->getCoordY() + 30 - Tir->getCoordY();
				if ((x1*x1) + (y1*y1) < (30 * 30)) {
					(*A)->TakeDamage(Tir->getDamage());
					Impact = true;
					Score++;
				}
			}
			A++;
		}
	A_lock.unlock();
	return Impact;
}

void GameWorld::RenderWorld()
{
	WorldRenderer::RenderClear();
	WorldRenderer::Render(background, 0, 0);

	/*A_lock.lock();
	A = PlayerHolder.begin();
	while (A != PlayerHolder.end()) {
		if ((*A)->isAlive()) {
			WorldRenderer::Render(*A);
			A++;
		}
		else {
			(*A)->Remove();
			A = PlayerHolder.erase(A);
		}
	}
	A_lock.unlock();*/

	A_lock.lock();
	A = AllGameEntities.begin();
	while (A != AllGameEntities.end()) {
		if ((*A)->isAlive()) {
			if ((*A)->getCategorie() == tir_joueur)
				int p = 0;
			WorldRenderer::Render((*A)->getCategorie(),
									(*A)->getCoordX(),
									(*A)->getCoordY());
			A++;
		}
		else {
			WorldRenderer::MakeAnimationRequest((*A)->getCategorie(),
												(*A)->getCoordX(),
												(*A)->getCoordY());
			//EntiteVolante* ptr = *A;
			RBuffer.push_back(*A);
			A = AllGameEntities.erase(A);
			int g = 0;
		}
	}
	A_lock.unlock();

	/*A_lock.lock();
	T = TirsLaser.begin();
	while (T != TirsLaser.end()) {
		if ((*T)->isAlive()) {
			WorldRenderer::Render(*T);
			T++;
		}
		else {
			(*T)->Remove();
			T = TirsLaser.erase(T);
		}
	}
	A_lock.unlock();*/

	WorldRenderer::RenderScore(Score);

	WorldRenderer::RenderPresent();

}

//std::list<Joueur*>* GameWorld::AccessPlayerHolder()
//{
//	A_lock.lock();
//	return &PlayerHolder;
//}

//std::list<Ennemis*>* GameWorld::AccessEnnemieSimple()
//{
//	A_lock.lock();
//	return &EnnemieSimple;
//}


//void GameWorld::RemoveFromGameWorld(Joueur * entity)
//{
//	A_lock.lock();
//	PlayerHolder.remove(*entity);
//	A_lock.unlock();
//}
//
//void GameWorld::RemoveFromGameWorld(Ennemis * entity)
//{
//	A_lock.lock();
//	EnnemieSimple.remove(*entity);
//	A_lock.unlock();
//}

/**
CEsquadronTie* GameWorld::RemoveFromGameWorld(int member)
{
F_lock.lock();
std::list<CEsquadronTie*>::iterator it = FormationEnnemie.begin();
it->removeMember(member);
F_lock.unlock();
return F._Ptr->_Myval;
}
/**/