#ifndef PROJECTILE_H
#define PROJECTILE_H


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

	void MoveLeft();
	void MoveRight();
};
#endif 