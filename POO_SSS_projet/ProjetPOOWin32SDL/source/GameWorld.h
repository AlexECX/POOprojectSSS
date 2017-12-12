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
	static WorldRenderer* RendererInstance;

	static std::list<Joueur*>::iterator P;
	static std::list<Joueur*> PlayerHolder;
	static std::list<Ennemis*>::iterator S;
	static std::list<Ennemis*> EnnemieSimple;
	static std::list<CEsquadronTie*> FormationEnnemie;
	static std::list<CEsquadronTie*>::iterator F;
	static std::list<Projectile*>::iterator T;
	static std::list<Projectile*> TirsLaser;
	static std::mutex P_lock;
	static std::mutex S_lock;
	static std::mutex F_lock;
	static std::mutex T_lock;
	
public:
	//GameWorld();
	//GameWorld(WorldRenderer*);
	~GameWorld();
	static void SetupGameWorld(WorldRenderer* renderer_instance) {
		RendererInstance = renderer_instance;
	}

<<<<<<< HEAD

	static Joueur* AddToGameWorld(Joueur &entity);
	static Ennemis* AddToGameWorld(Ennemis &entity);
	static CEsquadronTie* AddToGameWorld(CEsquadronTie &entity);
	static Projectile* AddToGameWorld(Projectile &entity);
=======
	Joueur* AddToGameWorld(Joueur &entity);
	Ennemis* AddToGameWorld(Ennemis &entity);
	//std::vector<Ennemis>* AddToGameWorld(std::vector<Ennemis> &entity);
	CEsquadronTie* AddToGameWorld(CEsquadronTie &entity);
	//CEsquadronTie* RemoveFromGameWorld(int member);
	Projectile* AddToGameWorld(Projectile &entity);
>>>>>>> 8d82f0958ebe79d8dbabeb2bbefe194033d3b862

	/*void RemoveFromGameWorld(Joueur *entity);
	void RemoveFromGameWorld(Ennemis *entity);
	void RemoveFromGameWorld(std::vector<Ennemis> *entity);*/

	static std::list<Joueur*>* AccessPlayerHolder();
	static std::list<Ennemis*>* AccessEnnemieSimple();
	static bool VerifierImpact(Projectile*);

	static void RenderWorld();

	static void ReleaseContainer(std::list<Joueur>*) { P_lock.unlock(); }
	static void ReleaseContainer(std::list<Ennemis>*) { S_lock.unlock(); }
	//void ReleaseContainer(std::list<std::vector<Ennemis>>*) { M_lock.unlock(); }
};
#endif 