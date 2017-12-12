#include <vector>
#include <chrono>
#include <SDL.h>
#include <SDL_thread.h>

#include "EsquadronTie.h"
#include "EntiteVolante.h"
#include "Ennemis.h"

#define DURATION_IN_MS(Time_Interval) std::chrono::duration_cast<std::chrono::milliseconds>(Time_Interval)

CEsquadronTie::CEsquadronTie(std::vector<Ennemis> Ptr) : Squad(Ptr)
{
	Active = 0;
	SquadCount = Squad.size();
	SquadThreadPtr = SDL_CreateThread(StartSquadThread, "SquadThread", this);
}

CEsquadronTie::~CEsquadronTie()
{
	if (isActive()) {
		Active += 2;
		SDL_WaitThread(SquadThreadPtr, &SquadThreadReturnValue);
	}
}

void CEsquadronTie::Update()
{
	for (int i = 0; i < Squad.size(); i++) {
		if (Squad[i].isAlive())
			Squad[i].UpdateTrajet(Squad[i].getCoordX() - 1, Squad[i].getCoordY());
	}
}

void CEsquadronTie::RemoveMember(int member)
{
	Squad[member].Remove();
	SquadCount--;
}

int CEsquadronTie::StartSquadThread(void *pointer)
{
	return ((CEsquadronTie*)pointer)->SquadThread();
}

int CEsquadronTie::SquadThread()
{
	//trucs pour le timer et le deplacement
	auto interval = std::chrono::milliseconds(5);
	std::chrono::milliseconds TieFighterFlightTime;
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (this->isActive())
	{
		//int SquadronMembers = TieFighter->size();
		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval) 
		{
			this->Update();
			BeforeUpdate = std::chrono::high_resolution_clock::now();
		}
		else
			SDL_Delay(1);

	}
	if (Active == 1)
		delete this;
	return 1;
}

#undef DURATION_IN_MS