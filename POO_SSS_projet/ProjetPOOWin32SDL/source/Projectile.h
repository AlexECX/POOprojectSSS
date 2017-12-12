#ifndef PROJECTILE_H
#define PROJECTILE_H

struct SDL_Thread;

class Projectile : public EntiteVolante
{
private:
	SDL_Thread* ProjectileThreadPtr;
	int ProjectileThreadReturnValue;

public:
	Projectile(categorie, affiliation, int, int, int, int, int);
	~Projectile();
	
	static int StartProjectileThread(void *pointer);
	//int ProjectileThread();
	void UpdateTrajet(int PosX, int PosY) override;

	int Projectile::ProjectileThread(int direction);
};
#endif 