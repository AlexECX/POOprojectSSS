
#include "GameWorld.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"
#include "WorldRenderer.h"
#include <SDL.h>
#include "..\ressources\LTexture.h"
#include "..\ressources\LSprite.h"

typedef struct {
	void *data1;
	void *data2;
	void *data3;
} ThreadData;

struct AnimationRequest {
	int SpriteNum;
	int TotalFrames;
	int X;
	int Y;
	int CurrentFrame;
};



WorldRenderer::WorldRenderer(LTexture gametextures[], LSprite gamesprites[], SDL_Renderer* renderer)
		: GameTextures(gametextures), GameSprites(gamesprites), Renderer(renderer)
{
}

WorldRenderer::~WorldRenderer()
{
}

//void WorldRenderer::SetupWorldRenderer(LTexture gametextures[], LSprite gamesprites[], SDL_Renderer * renderer)
//{
//	GameTextures = gametextures;
//	GameSprites = gamesprites;
//	Renderer = renderer;
//}

void WorldRenderer::Render(Joueur *PlayerRender)
{
	GameTextures[PlayerRender->getCategorie()].render(PlayerRender->getCoordX(),
													  PlayerRender->getCoordY());
}

void WorldRenderer::Render(CEsquadronTie *SquadRender)
{
	for (int i = 0; i < SquadRender->getSquadronSize(); i++)
		if (SquadRender->getMember(i)->isAlive())
			GameTextures[SquadRender->getMember(i)->getCategorie()].render(SquadRender->getMember(i)->getCoordX(),
																		   SquadRender->getMember(i)->getCoordY());
		else
			if (SquadRender->getMember(i)->isActive()) {
				//Pour l'instant, seulement une animation d'explosion
				Animations.push_back(AnimationRequest{ 0,	//Sprite Number
													   GameSprites[0].TotalFrames,
													   SquadRender->getMember(i)->getCoordX(),
													   SquadRender->getMember(i)->getCoordY(),
													   0	//Starting frame
													  } );
				/*ThreadData* ExplosionData = new ThreadData{ this, 
															(void*)SquadRender->getMember(i)->getCoordX(),
															(void*)SquadRender->getMember(i)->getCoordY() };
				ExplosionThreadPtr = SDL_CreateThread(StartExplosionThread, "Explosion", ExplosionData);*/
				SquadRender->RemoveMember(i);
			}
}
void WorldRenderer::Render(Projectile *ProjectileRender)
{
	GameTextures[ProjectileRender->getCategorie()].render(ProjectileRender->getCoordX(), 
														  ProjectileRender->getCoordY());
}

void WorldRenderer::RenderEventAnimations()
{
	if (!Animations.empty()) {
		std::list<AnimationRequest>::iterator Animator = Animations.begin();
		while (Animator != Animations.end()) {
			if (Animator->CurrentFrame < Animator->TotalFrames) {
				SDL_Rect* currentClip = &GameSprites[Animator->SpriteNum].SpriteClips[Animator->CurrentFrame / 6];
				GameSprites[Animator->SpriteNum].SpriteTexture.renderSprite(Animator->X, Animator->Y, currentClip);
				Animator->CurrentFrame++;
				Animator++;
			}
			else
				Animator = Animations.erase(Animator);
		}
	}
}



int WorldRenderer::StartExplosionThread(void * ptr)
{

	return ((WorldRenderer*)((ThreadData*)ptr)->data1)->RenderExplosion(ptr);
}



int WorldRenderer::RenderExplosion(void* explose)
{
	ThreadData* Data = (ThreadData*)explose;
	WorldRenderer* Intermediaire = (WorldRenderer*)Data->data1;
	
	int x = (int)Data->data2, y = (int)Data->data3;
	SDL_Rect* Boom = this->GameSprites[0].SpriteClips;
	SDL_Rect* NextBoom;
	int frame = 0;
	while (frame < 9) {
		NextBoom = &Boom[frame / 7];
		this->GameSprites[0].SpriteTexture.renderSprite(x, y, NextBoom);
		frame++;
		//SDL_RenderPresent(this->Renderer);
		SDL_Delay(16);
	}
	return 0;
}
