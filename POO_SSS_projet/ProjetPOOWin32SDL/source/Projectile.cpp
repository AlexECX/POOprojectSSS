#include "EntiteVolante.h"
#include "Projectile.h"

#include <SDL.h>
#include <SDL_thread.h>
#include <chrono>

#define DURATION_IN_MS(Time_Interval) std::chrono::duration_cast<std::chrono::milliseconds>(Time_Interval)

Projectile::Projectile(	categorie CategorieParam,
						affiliation AffiliationParam,
						int			PosXParam,
						int			PosYParam,
						int			HP_Param,
						int			DamageParam,
						int			SpeedParam) : EntiteVolante(CategorieParam,
																AffiliationParam,
																PosXParam,
																PosYParam,
																HP_Param,
																DamageParam,
																SpeedParam)
{
	SquadThreadPtr = SDL_CreateThread(StartProjectileThread, "SquadThread", this);
}

Projectile::~Projectile()
{
	SDL_WaitThread(SquadThreadPtr, &SquadThreadReturnValue);
}

int Projectile::StartProjectileThread(void * pointer)
{
	return ((Projectile*)pointer)->ProjectileThread();
}

void Projectile::ProjectileThread()
{
	if (Affiliation == republic)
	{
		MoveRight();
	}
	else if (Affiliation == empire)
	{
		MoveLeft();
	}
}

void Projectile::MoveLeft()
{
	auto interval = std::chrono::milliseconds(2);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (coordX > 0)
	{
		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
		{
			coordX--;
			BeforeUpdate = std::chrono::high_resolution_clock::now();
		}
		else
		{
			SDL_Delay(1);
		}
	}
}

void Projectile::MoveRight()
{
	auto interval = std::chrono::milliseconds(2);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (coordX < 1200)
	{
		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
		{
			coordX++;
			BeforeUpdate = std::chrono::high_resolution_clock::now();
		}
		else
		{
			SDL_Delay(1);
		}
	}
}

#undef DURATION_IN_MS