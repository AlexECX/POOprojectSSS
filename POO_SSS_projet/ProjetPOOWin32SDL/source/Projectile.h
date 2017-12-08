#ifndef PROJECTILE_H
#define PROJECTILE_H


class Projectile : public EntiteVolante
{
public:
	Projectile(categorie, affiliation, int, int, int, int, int);
	~Projectile();
	
	int StartProjectileThread(void *pointer);
	void ProjectileThread();

	void MoveLeft();
	void MoveRight();
};
#endif 