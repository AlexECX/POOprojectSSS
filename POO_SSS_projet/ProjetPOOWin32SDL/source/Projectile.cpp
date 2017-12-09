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
	ProjectileThreadPtr = SDL_CreateThread(StartProjectileThread, "StartProjectileThread", this);
}

Projectile::~Projectile()
{
	if (isActive()) {
		Active += 2;
		SDL_WaitThread(ProjectileThreadPtr, &ProjectileThreadReturnValue);
	}
}

int Projectile::StartProjectileThread(void * pointer)
{
	return ((Projectile*)pointer)->ProjectileThread();
}

int Projectile::ProjectileThread()
{
	if (Affiliation == republic)
	{
		MoveRight();
	}

	else if (Affiliation == empire)
	{
		MoveLeft();
	}

	ProjectileThreadReturnValue = true;

	return ProjectileThreadReturnValue;
}

void Projectile::UpadteTrajet(int x, int y)
{
	if (coordX < 1200 && coordX > -5) {
		coordX = x;
		coordY = y;
	}
	else
		HP = 0;
}

int Projectile::MoveLeft()
{
	auto interval = std::chrono::milliseconds(1);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (isActive())
	{
		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
		{
			this->UpdateTrajet(this->coordX - 1, this->coordY);
			BeforeUpdate = std::chrono::high_resolution_clock::now();
		}
		else
		{
			SDL_Delay(1);
		}
	}
	if (Active == 1)
		delete this;
	return 0;
}

int Projectile::MoveRight()
{
	auto interval = std::chrono::milliseconds(1);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (isActive())
	{
		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
		{
 			Projectile::UpadteTrajet(coordX + 1, coordY);
			BeforeUpdate = std::chrono::high_resolution_clock::now();
		}
		else
		{
			SDL_Delay(1);
		}
	}
	if (Active == 1)
		delete this;
	return 0;
}

#undef DURATION_IN_MS