#include "EntiteVolante.h"
#include "Projectile.h"
#include "GameWorld.h"

#include <SDL.h>
#include <SDL_thread.h>
#include <chrono>

#define DURATION_IN_MS(Time_Interval) std::chrono::duration_cast<std::chrono::milliseconds>(Time_Interval)

Projectile::Projectile(affiliation AffiliationParam,
					   int			PosXParam,
					   int			PosYParam)
					  : EntiteVolante((AffiliationParam == republic) ? tir_joueur:tir_tie,
						AffiliationParam,
						PosXParam,
						PosYParam,
						1,
						10,
						0)
{
	Size = 1;
	ProjectileThreadPtr = SDL_CreateThread(StartProjectileThread, "StartProjectileThread", this);
}

Projectile::~Projectile()
{
	HP = 0;
	SDL_WaitThread(ProjectileThreadPtr, &ProjectileThreadReturnValue);
}

int Projectile::StartProjectileThread(void * pointer)
{
	Projectile* ptr = (Projectile*)pointer;
	if (ptr->Affiliation == republic)
		return ptr->ProjectileThread(-1);
	else
		if (ptr->Affiliation == empire)
			return ptr->ProjectileThread(1);
		else
			return 2;
}

void Projectile::UpdateTrajet(int PosX, int PosY)
{
	if (coordX < 1200 && coordX > -5) {
		coordX = PosX;
		coordY = PosY;
	}
	else
		HP = 0;
}

void Projectile::MakeFly()
{
	ProjectileThreadPtr = SDL_CreateThread(StartProjectileThread, "StartProjectileThread", this);
}

//int Projectile::ProjectileThread()
//{
//	if (Affiliation == republic)
//	{
//		Move(-1);
//	}
//
//	else if (Affiliation == empire)
//	{
//		Move(1);
//	}
//
//	ProjectileThreadReturnValue = true;
//
//	return ProjectileThreadReturnValue;
//}

int Projectile::ProjectileThread(int direction)
{
	auto interval = std::chrono::milliseconds(1);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (isAlive())
	{
		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
		{
			this->UpdateTrajet(this->coordX - direction, this->coordY);
			BeforeUpdate = std::chrono::high_resolution_clock::now();
		}
		else
		{
			SDL_Delay(1);
		}
		/*if (GameWorld::ColisionThread(this) == true)
			HP = 0;*/
	}
	return 0;
}

#undef DURATION_IN_MS