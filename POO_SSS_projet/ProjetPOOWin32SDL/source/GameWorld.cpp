#include "GameWorld.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"
#include "WorldRenderer.h"
#include <SDL.h>
#include "..\ressources\LTexture.h"

//GameWorld::GameWorld()
//{
//}

GameWorld::GameWorld(WorldRenderer* renderer_instance): RendererInstance(renderer_instance)
{
}

GameWorld::~GameWorld()
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
	for (F = FormationEnnemie.begin(); F != FormationEnnemie.end(); F++)
		delete (*F);
	F_lock.unlock();
}

Joueur* GameWorld::AddToGameWorld(Joueur &entity) {
	Joueur *PtrToSend;
	P_lock.lock();
	PlayerHolder.push_back(&entity);
	PtrToSend = PlayerHolder.back();
	P_lock.unlock();
	return PtrToSend;
}

Ennemis* GameWorld::AddToGameWorld(Ennemis &entity) {
	Ennemis *PtrToSend;
	S_lock.lock();
	EnnemieSimple.push_back(&entity);
	PtrToSend = EnnemieSimple.back();
	S_lock.unlock();
	return PtrToSend;
}

//std::vector<Ennemis>* GameWorld::AddToGameWorld(std::vector<Ennemis> &entity) {
//	std::vector<Ennemis> *PtrToSend;
//	M_lock.lock();
//	EnnemisMultiple.push_back(entity);
//	PtrToSend = &EnnemisMultiple.back();
//	M_lock.unlock();
//	return PtrToSend;
//}

CEsquadronTie* GameWorld::AddToGameWorld(CEsquadronTie &entity)
{
	CEsquadronTie *PtrToSend;
	F_lock.lock();
	FormationEnnemie.push_back(&entity);
	PtrToSend = FormationEnnemie.back();
	F_lock.unlock();
	return PtrToSend;
}

Projectile * GameWorld::AddToGameWorld(Projectile &entity)
{
	Projectile *PtrToSend;
	T_lock.lock();
	TirsLaser.push_back(&entity);
	PtrToSend = TirsLaser.back();
	T_lock.unlock();
	return PtrToSend;
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
//
//void GameWorld::RemoveFromGameWorld(std::vector<Ennemis>* entity)
//{
//	M_lock.lock();
//	EnnemisMultiple.remove(*entity);
//	M_lock.unlock();
//}

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

//std::list<std::vector<Ennemis>>* GameWorld::AccessEnnemisMultiple()
//{
//	M_lock.lock();
//	return &EnnemisMultiple;
//}

void GameWorld::RenderWorld()
{
	P_lock.lock();
	P = PlayerHolder.begin();
	while (P != PlayerHolder.end()) {
		if ((*P)->isAlive()) {
			RendererInstance->Render(*P);
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
	while (F != FormationEnnemie.end()){
		if ((*F)->isAlive()) {
			RendererInstance->Render(*F);
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
	while (T != TirsLaser.end()){
		if ((*T)->isAlive()) {
			RendererInstance->Render(*T);
			T++;
		}
		else {
			(*T)->Remove();
			T = TirsLaser.erase(T);
		}
	}
	T_lock.unlock();

	RendererInstance->RenderEventAnimations();
}



