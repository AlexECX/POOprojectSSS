#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <list>
#include <vector>
#include <mutex>
//#include "../ressources/LTexture.h"

class Joueur;
class EntiteVolante;
class Ennemis;
class LTexture;
class CEsquadronTie;
class Projectile;
class WorldRenderer;
enum categorie;



class GameWorld
{
private:
	WorldRenderer* RendererInstance;

	std::list<Joueur> PlayerHolder;
	std::list<Ennemis> EnnemieSimple;
	std::list<std::vector<Ennemis>> EnnemisMultiple;
	std::list<CEsquadronTie> FormationEnnemie;
	std::list<categorie> Explosion;
	std::list<Projectile> TirsLaser;
	std::list<Projectile>::iterator T;
	std::list<Joueur>::iterator P;
	std::list<Ennemis>::iterator S;
	std::list<std::vector<Ennemis>>::iterator M;
	std::list<CEsquadronTie>::iterator F;
	std::mutex P_lock;
	std::mutex S_lock;
	std::mutex M_lock;
	std::mutex E_lock;
	std::mutex T_lock;
	
public:
	GameWorld(WorldRenderer*);
	~GameWorld();


	Joueur* AddToGameWorld(Joueur &entity);
	Ennemis* AddToGameWorld(Ennemis &entity);
	std::vector<Ennemis>* AddToGameWorld(std::vector<Ennemis> &entity);
	CEsquadronTie* AddToGameWorld(CEsquadronTie &entity);
	Projectile* AddToGameWorld(Projectile &entity);

	/*void RemoveFromGameWorld(Joueur *entity);
	void RemoveFromGameWorld(Ennemis *entity);
	void RemoveFromGameWorld(std::vector<Ennemis> *entity);*/

	std::list<Joueur>* AccessPlayerHolder();
	std::list<Ennemis>* AccessEnnemieSimple();
	std::list<std::vector<Ennemis>>* AccessEnnemisMultiple();

	void RenderWorld(LTexture TtoRender[]);

	void ReleaseContainer(std::list<Joueur>*) { P_lock.unlock(); }
	void ReleaseContainer(std::list<Ennemis>*) { S_lock.unlock(); }
	void ReleaseContainer(std::list<std::vector<Ennemis>>*) { M_lock.unlock(); }

};
#endif 