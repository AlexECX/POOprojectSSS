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
	int ProjectileThread();

	int MoveLeft();
	int MoveRight();
};
#endif 