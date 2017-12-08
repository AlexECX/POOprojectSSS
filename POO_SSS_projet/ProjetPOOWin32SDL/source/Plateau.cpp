#include "Plateau.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"
//#include "WorldRenderer.h"
#include <SDL.h>
#include "..\ressources\LTexture.h"

GameWorld::GameWorld()
{
}

//GameWorld::GameWorld(WorldRenderer* renderer_instance): RendererInstance(renderer_instance)
//{
//}

GameWorld::~GameWorld()
{
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
	M_lock.lock();
	FormationEnnemie.push_back(&entity);
	PtrToSend = FormationEnnemie.back();
	M_lock.unlock();
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

void GameWorld::RenderWorld(LTexture TtoRender[])
{
	P_lock.lock();
	for (P = PlayerHolder.begin(); P != PlayerHolder.end(); P++) {
		if ((*P)->isAlive())
			TtoRender[(*P)->getCategorie()].render((*P)->getCoordX(), (*P)->getCoordY());

	}
	//RendererInstance->Render()
	P_lock.unlock();

	S_lock.lock();
	for (S = EnnemieSimple.begin(); S != EnnemieSimple.end(); S++)
		if ((*S)->isAlive())
			TtoRender[(*S)->getCategorie()].render((*S)->getCoordX(), (*S)->getCoordY());
	S_lock.unlock();
	
	M_lock.lock();
	for (F = FormationEnnemie.begin(); F != FormationEnnemie.end(); F++) {
		if ((*F)->isAlive()) {
			int Members = (*F)->getSquadronSize();
			for (int i = 0; i < (*F)->getSquadronSize(); i++) {
				if ((*F)->getMember(i)->isAlive())
					TtoRender[(*F)->getMember(i)->getCategorie()].render((*F)->getMember(i)->getCoordX(), (*F)->getMember(i)->getCoordY());
				/*else {
					Members--;
					if (!F->getMember(i)->isRemoved()) {
						Explosion.push_back(F->getMember(i)->getCategorie());
						F->getMember(i)->Remove();
					}
				}*/
			}
			if (Members == 0)
				F = FormationEnnemie.erase(F);
		}
			
	}
	M_lock.unlock();

	T_lock.lock();
	for (T = TirsLaser.begin(); T != TirsLaser.end(); T++) {
		if ((*T)->isAlive())
			TtoRender[(*T)->getCategorie()].render((*T)->getCoordX(), (*T)->getCoordY());

	}
	T_lock.unlock();



	//for (M = EnnemisMultiple.begin(); M != EnnemisMultiple.end(); M++) {
	//	for (int i = 0; i < M->size(); i++)
	//		if ((*M)[i].isAlive())
	//			TtoRender[(*M)[i].getCategorie()].render((*M)[i].getCoordX(), (*M)[i].getCoordY());
	//}
}



