#include <vector>
#include <chrono>
#include <SDL.h>
#include <SDL_thread.h>

#include "EsquadronTie.h"
#include "EntiteVolante.h"
#include "Ennemis.h"

#define DURATION_IN_MS(Time_Interval)\
std::chrono::duration_cast<std::chrono::milliseconds>(Time_Interval)\

CEsquadronTie::CEsquadronTie(std::vector<std::shared_ptr<Ennemis>> &Vect)
{
	Squad = std::move(Vect);
	SquadCount = Squad.size();
	SquadThreadPtr = nullptr;
}

CEsquadronTie::CEsquadronTie(CEsquadronTie const & E)
{
	Squad = std::move(E.Squad);
	SquadCount = E.SquadCount;
}

CEsquadronTie::~CEsquadronTie()
{
	if (SquadThreadPtr != nullptr) {
		SquadCount = 0;
		SDL_WaitThread(SquadThreadPtr, &SquadThreadReturnValue);
	}
	
}


void CEsquadronTie::Update()
{
	Squad_lock.lock();
	for (int i = 0; i < Squad.size(); i++) {
		if (Squad[i]->isAlive())
			Squad[i]->UpdateTrajet(Squad[i]->getCoordX() - 1,
								  Squad[i]->getCoordY());
		else {
			Squad.erase(Squad.begin()+i);
			SquadCount--;
		}
	}
	Squad_lock.unlock();
}


void CEsquadronTie::RemoveMember(int member)
{
	Squad_lock.lock();
	Squad[member] = nullptr;
	SquadCount--;
	Squad_lock.unlock();
}

void CEsquadronTie::MakeFly()
{
	SquadThreadPtr = SDL_CreateThread(StartSquadThread, "SquadThread", this);
}


int CEsquadronTie::StartSquadThread(void *pointer)
{
	return ((CEsquadronTie*)pointer)->SquadThread();
}

int CEsquadronTie::SquadThread()
{
	//trucs pour le timer et le deplacement
	auto interval = std::chrono::milliseconds(5);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (this->isAlive())
	{
		//int SquadronMembers = TieFighter->size();
		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() 
										- BeforeUpdate) >= interval) 
		{
			this->Update();
			BeforeUpdate = std::chrono::high_resolution_clock::now();
		}
		else
			SDL_Delay(1);

	}
	return 1;
}

#undef DURATION_IN_MS