#include "GameWorld.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"
#include "WorldRenderer.h"
#include <SDL.h>
#include "..\ressources\LTexture.h"

int GameWorld::Score;

std::list<Joueur*>::iterator  GameWorld::P;
std::list<Joueur*>  GameWorld::PlayerHolder;
std::list<Ennemis*>::iterator  GameWorld::S;
std::list<Ennemis*>  GameWorld::EnnemieSimple;
std::list<CEsquadronTie*>::iterator GameWorld::F;
std::list<CEsquadronTie*> GameWorld::FormationEnnemie;
std::list<Projectile*>::iterator GameWorld::T;
std::list<Projectile*> GameWorld::TirsLaser;

std::mutex GameWorld::P_lock;
std::mutex GameWorld::S_lock;
std::mutex GameWorld::F_lock;
std::mutex GameWorld::T_lock;

//GameWorld::GameWorld()
//{
//}

//GameWorld::GameWorld(WorldRenderer* renderer_instance)
//					: RendererInstance(renderer_instance)
//{
//}

//GameWorld::~GameWorld()
//{
//	P_lock.lock();
//	for (P = PlayerHolder.begin(); P != PlayerHolder.end(); P++) 
//		delete (*P);
//	P_lock.unlock();
//
//	T_lock.lock();
//	for (T = TirsLaser.begin(); T != TirsLaser.end(); T++)
//		delete (*T);
//	T_lock.unlock();
//
//	F_lock.lock();
//	for (F = FormationEnnemie.begin();
//			F != FormationEnnemie.end(); F++)
//		delete (*F);
//	F_lock.unlock();
//}

void GameWorld::DeleteGameWorld()
{
	P_lock.lock();
	for (P = PlayerHolder.begin(); P != PlayerHolder.end(); P++)
		delete (*P);
	P_lock.unlock();

	T_lock.lock();
	for (T = TirsLaser.begin(); T != TirsLaser.end(); T++)
		delete (*T);
	T_lock.unlock();

	F_lock.lock();
	for (F = FormationEnnemie.begin();
		 F != FormationEnnemie.end(); F++)
		delete (*F);
	F_lock.unlock();
}

Joueur* GameWorld::AddToGameWorld(Joueur *entity)
{
	Joueur *PtrToSend;
	P_lock.lock();
	PlayerHolder.push_back(entity);
	PtrToSend = PlayerHolder.back();
	P_lock.unlock();
	return PtrToSend;
}

Ennemis* GameWorld::AddToGameWorld(Ennemis *entity) 
{
	Ennemis *PtrToSend;
	S_lock.lock();
	EnnemieSimple.push_back(entity);
	PtrToSend = EnnemieSimple.back();
	S_lock.unlock();
	return PtrToSend;
}


CEsquadronTie* GameWorld::AddToGameWorld(CEsquadronTie *entity)
{
	CEsquadronTie *PtrToSend;
	F_lock.lock();
	FormationEnnemie.push_back(entity);
	PtrToSend = FormationEnnemie.back();
	F_lock.unlock();
	return PtrToSend;
}

Projectile* GameWorld::AddToGameWorld(Projectile *entity)
{
	Projectile *PtrToSend;
	T_lock.lock();
	TirsLaser.push_back(entity);
	PtrToSend = TirsLaser.back();
	T_lock.unlock();
	return PtrToSend;
}

bool GameWorld::VerifierImpact(Projectile* Tir){
	bool Impact = false;
	if (Tir->getAffiliation() == republic) 
		F_lock.lock();
		F = FormationEnnemie.begin();
		while (F != FormationEnnemie.end()) {
			if ((*F)->isAlive()) {
				int i = 0;
				while (i < (*F)->getSquadronSize() && !Impact) {
					if ((*F)->getMember(i)->isAlive()) {
						int x1 = (*F)->getMember(i)->getCoordX() + 30 - Tir->getCoordX();
						int y1 = (*F)->getMember(i)->getCoordY() + 30 - Tir->getCoordY();
						if ((x1*x1) + (y1*y1) < (30 * 30)) {
							(*F)->getMember(i)->TakeDamage(Tir->getDamage());
							Impact = true;
							Score++;
						}
					}
					i++;
				}
			}
			F++;
		}
		F_lock.unlock();
	return Impact;
}

void GameWorld::RenderWorld()
{
	WorldRenderer::RenderClear();

	P_lock.lock();
	P = PlayerHolder.begin();
	while (P != PlayerHolder.end()) {
		if ((*P)->isAlive()) {
			WorldRenderer::Render(*P);
			P++;
		}
		else {
			(*P)->Remove();
			P = PlayerHolder.erase(P);
		}
	}
	P_lock.unlock();

	F_lock.lock();
	F = FormationEnnemie.begin();
	while (F != FormationEnnemie.end()) {
		if ((*F)->isAlive()) {
			WorldRenderer::Render(*F);
			F++;
		}
		else {
			(*F)->Remove();
			F = FormationEnnemie.erase(F);
		}
	}
	F_lock.unlock();

	T_lock.lock();
	T = TirsLaser.begin();
	while (T != TirsLaser.end()) {
		if ((*T)->isAlive()) {
			WorldRenderer::Render(*T);
			T++;
		}
		else {
			(*T)->Remove();
			T = TirsLaser.erase(T);
		}
	}
	T_lock.unlock();

	WorldRenderer::RenderEventAnimations();
}

std::list<Joueur*>* GameWorld::AccessPlayerHolder()
{
	P_lock.lock();
	return &PlayerHolder;
}

std::list<Ennemis*>* GameWorld::AccessEnnemieSimple()
{
	S_lock.lock();
	return &EnnemieSimple;
}


//void GameWorld::RemoveFromGameWorld(Joueur * entity)
//{
//	P_lock.lock();
//	PlayerHolder.remove(*entity);
//	P_lock.unlock();
//}
//
//void GameWorld::RemoveFromGameWorld(Ennemis * entity)
//{
//	S_lock.lock();
//	EnnemieSimple.remove(*entity);
//	S_lock.unlock();
//}

/**
CEsquadronTie* GameWorld::RemoveFromGameWorld(int member)
{
F_lock.lock();
std::list<CEsquadronTie*>::iterator it = FormationEnnemie.begin();
it->removeMember(member);
F_lock.unlock();
return F._Ptr->_Myval;
}
/**/