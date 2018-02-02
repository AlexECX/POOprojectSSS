#include "GameWorld.h"
#include "EntiteVolante.h"
#include "WorldRenderer.h"
#include <SDL.h>
#include <cmath>
#include "..\ressources\TConcurrent_queue.h"
#include "..\ressources\LTexture.h"

#include <string>


//SDL_Thread* GameWorld::ReaperPtr;
//concurrent_queue<EntiteVolante*> GameWorld::RBuffer;


std::list<std::shared_ptr<EntiteVolante>> GameWorld::AllGameEntities;
std::list<std::shared_ptr<EntiteVolante>>::iterator GameWorld::A;
std::mutex GameWorld::A_lock;

 std::vector<EntiteVolante*> GameWorld::ColisionLists[4][4];
 std::list<std::shared_ptr<EntiteVolante>> GameWorld::ColisionList;
 std::mutex GameWorld::C_lock;

 std::list<std::shared_ptr<EntiteVolante>>::iterator GameWorld::B;
 std::list<std::shared_ptr<EntiteVolante>>::iterator GameWorld::C;

std::vector<SDL_Thread*> GameWorld::GameThreads;
int GameWorld::Score;
bool GameWorld::ThreadSignal;


//int GameWorld::ReaperThread(void*)
//{
//	while (!SignalReaper) {
//		if (!RBuffer.empty()) {
//			delete RBuffer.front();
//			RBuffer.pop_front();
//		}
//		else 
//			SDL_Delay(3);
//	}
//	while (!RBuffer.empty())
//		RBuffer.pop_front();
//
//	std::lock_guard<std::mutex> lock(A_lock);
//	while (!AllGameEntities.empty())
//		AllGameEntities.pop_back();
//
//	return 0;
//}
//
//void GameWorld::Close()
//{
//	SignalReaper = true;
//}

GameWorld::GameWorld() {
	GameThreads.push_back(SDL_CreateThread(ColisionThread, "ColisionThread", (void*)1));
	GameThreads.push_back(SDL_CreateThread(RenderingThread, "RenderingThread", (void*)1));
}

GameWorld::~GameWorld() {
	ThreadSignal = true;
	static int* GameTHReturnValue;
	while (!GameThreads.empty()) {
		SDL_WaitThread(GameThreads.back(), GameTHReturnValue);
		GameThreads.pop_back();
	}
}

GameWorld & GameWorld::Get()
{
	static GameWorld game;
	return game;
}

//void GameWorld::DeleteGameWorld()
//{
//	ThreadSignal = true;
//	static int* GameTHReturnValue;
//	while (!GameThreads.empty()) {
//		SDL_WaitThread(GameThreads.back(), GameTHReturnValue);
//		GameThreads.pop_back();
//	}
//
//}


int GameWorld::ColisionThread(void* ptr){	
	while (ThreadSignal == false) {
		SDL_Delay(6);
		std::lock_guard<std::mutex> lock(A_lock);
		C = ColisionList.begin();
		while (C != ColisionList.end()) {
			if (!C->get()->isAlive()) 
				C = ColisionList.erase(C);
			else {
				B = C;
				B++;
				while (B != ColisionList.end()) {
					if (!B->get()->isAlive())
						B = ColisionList.erase(B);
					else{
						if (C->get()->getAffiliation() !=
							B->get()->getAffiliation()) {
							int x1 = C->get()->getCoordX() - B->get()->getCoordX();
							int y1 = C->get()->getCoordY() - B->get()->getCoordY();
							if ((x1*x1) + (y1*y1) < (30 * 30)) {
								C->get()->TakeDamage(B->get()->getDamage());
								B->get()->TakeDamage(C->get()->getDamage());
							}
						}
						B++;
					}
				}
				C++;
			}
		}
	}
		/*AssignCadrant();
		for (int ligne = 0; ligne < 4; ligne++) {
			for (int col = 0; col < 4; col++) {
				std::vector<EntiteVolante*> Vptr = ColisionLists[ligne][col];
				for (int ptr = 0; ptr < Vptr.size() && !(Vptr.size() <= 1); ptr++) {
					if (Vptr[ptr]->isAlive())
						for (int next = ptr + 1; next < Vptr.size(); next++) {
							if (Vptr[next]->isAlive())
								if (Vptr[ptr]->getAffiliation() !=
									Vptr[next]->getAffiliation()) {
									int x1 = Vptr[ptr]->getCoordX() - Vptr[next]->getCoordX();
									int y1 = Vptr[ptr]->getCoordY() - Vptr[next]->getCoordY();
									if ((x1*x1) + (y1*y1) < (30 * 30)) {
										Vptr[ptr]->TakeDamage(Vptr[next]->getDamage());
										Vptr[next]->TakeDamage(Vptr[ptr]->getDamage());
									}
								}
						}
				}

			}
		}
		SDL_Delay(6);
	}*/
	return 0;
}

/**
bool GameWorld::AssignCadrant()
{
	for (int ligne = 0; ligne < 4; ligne++)
		for (int col = 0; col < 4; col++)
			ColisionLists[ligne][col].clear();
	//A_lock.lock();
	//
	//int ListLenght = ColisionList.size();
	//A_lock.unlock();
	//int index = 0;
	std::lock_guard<std::mutex> lock(A_lock);
	C = ColisionList.begin();
	while (C != ColisionList.end()) {
		
		if (C->get()->isAlive() == false)
			C = ColisionList.erase(C);
		else {

			int y = ceil((double)C->get()->getCoordY() / (double)175);
			for (int i = 0; i < 4; i++) {
				if (C->get()->getCoordX() - 30 <= (i + 1) * 300 ||
					C->get()->getCoordX() <= (i + 1) * 300 ||
					C->get()->getCoordX() + 30 <= (i + 1) * 300) 
				{
					ColisionLists[i][y].push_back(C->get());
				}
			}
			int x = ceil((double)C->get()->getCoordX() / (double)175);
			for (int j = 0; j < 4; j++) {
				if (C->get()->getCoordY() - 30 <= (j + 1) * 175 ||
					C->get()->getCoordY() <= (j + 1) * 175 ||
					C->get()->getCoordY() + 30 <= (j + 1) * 175)
				{
					ColisionLists[x][j].push_back(C->get());
				}
			}
			C++;
		}
			
	}	
	return false;
}
/**/

int GameWorld::RenderingThread(void *)
{
	while (ThreadSignal == false) {
		RenderWorld();
		SDL_Delay(1);
	}
	return 0;
}

void GameWorld::RenderWorld()
{
	WorldRenderer::RenderClear();
	{
		std::lock_guard<std::mutex> lock(A_lock);
		A = AllGameEntities.begin();
		while (A != AllGameEntities.end()) {
			if ((*A)->isAlive()) {
				if ((*A)->getCategorie() == 4)
					int u = 0;
				WorldRenderer::RenderEntity(
					(*A)->getCategorie(),
					(*A)->getCoordX(),
					(*A)->getCoordY());
				A++;
			}
			else {
				WorldRenderer::MakeAnimationRequest(
					(*A)->getCategorie(),
					(*A)->getCoordX(),
					(*A)->getCoordY());
				A = AllGameEntities.erase(A);
			}
		}
	}

	WorldRenderer::RenderEventAnimations();
	WorldRenderer::RenderScore(Score);
	WorldRenderer::RenderPresent();
}