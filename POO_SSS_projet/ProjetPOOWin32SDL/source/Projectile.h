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
	
	void UpdateTrajet(int PosX, int PosY) override;
	void MakeFly();
	static int StartProjectileThread(void *pointer);
	int Projectile::ProjectileThread(int direction);
};
#endif 