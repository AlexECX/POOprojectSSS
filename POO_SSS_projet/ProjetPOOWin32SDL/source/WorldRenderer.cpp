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
#include "GameMedia.h"

std::list<AnimationRequest> WorldRenderer::Animations;

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


void WorldRenderer::Render(LTexture &TextureNum, int x, int y, SDL_Rect* Clip)
{

	SDL_Rect renderQuad = { x, y, 
							TextureNum.getWidth(),
							TextureNum.getWidth()
						  };
	if (Clip != NULL)
	{
		renderQuad.w = Clip->w;
		renderQuad.h = Clip->h;
	}
	SDL_RenderCopy(Renderer, TextureNum.getTexture(), Clip, &renderQuad);
}

void WorldRenderer::Render(Joueur* PlayerRender)
{
	Render(Textures[PlayerRender->getCategorie()],
		   PlayerRender->getCoordX(),
		   PlayerRender->getCoordY());
}

void WorldRenderer::Render(CEsquadronTie *SquadRender)
{
	for (int i = 0; i < SquadRender->getSquadronSize(); i++)
		if (SquadRender->getMember(i)->isAlive())
			Render(Textures[SquadRender->getMember(i)->getCategorie()],
				   SquadRender->getMember(i)->getCoordX(),
				   SquadRender->getMember(i)->getCoordY());
		else
			if (SquadRender->getMember(i)->isActive()) {
				//Pour l'instant, seulement une animation d'explosion
				Animations.push_back(AnimationRequest{ 
					0,	//Sprite Number
					Sprites[0].TotalFrames,
					SquadRender->getMember(i)->getCoordX(),
					SquadRender->getMember(i)->getCoordY(),
					0	//Starting frame
					} );
				SquadRender->RemoveMember(i);
			}
}
void WorldRenderer::Render(Projectile *ProjectileRender)
{
	Render(Textures[ProjectileRender->getCategorie()],
		   ProjectileRender->getCoordX(),
		   ProjectileRender->getCoordY());
}


void WorldRenderer::RenderEventAnimations()
{
	if (!Animations.empty()) {
		std::list<AnimationRequest>::iterator Animator = Animations.begin();
		while (Animator != Animations.end()) {
			if (Animator->CurrentFrame < Animator->TotalFrames) {
				Render(Sprites[Animator->SpriteNum].SpriteTexture,
					   Animator->X, 
					   Animator->Y,
					   &Sprites[Animator->SpriteNum].SpriteClips[Animator->CurrentFrame / 6]);
				Animator->CurrentFrame++;
				Animator++;
			}
			else
				Animator = Animations.erase(Animator);
		}
	}
}

void WorldRenderer::RenderClear()
{
	//Clear screen
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF,
		0xFF, 0xFF);
	SDL_RenderClear(Renderer);
}

void WorldRenderer::RenderPresent()
{
	SDL_RenderPresent(Renderer);
}



//int WorldRenderer::StartExplosionThread(void * ptr)
//{
//	ThreadData* pointer = (ThreadData*)ptr;
//	return ((WorldRenderer*)pointer->data1)->RenderExplosion(ptr);
//}
//
//int WorldRenderer::RenderExplosion(void* explose)
//{
//	ThreadData* Data = (ThreadData*)explose;
//	WorldRenderer* Intermediaire = (WorldRenderer*)Data->data1;
//	
//	int x = (int)Data->data2, y = (int)Data->data3;
//	SDL_Rect* Boom = this->GameSprites[0].SpriteClips;
//	SDL_Rect* NextBoom;
//	int frame = 0;
//	while (frame < 9) {
//		NextBoom = &Boom[frame / 7];
//		this->GameSprites[0].SpriteTexture.renderSprite(x, y, NextBoom);
//		frame++;
//		//SDL_RenderPresent(this->Renderer);
//		SDL_Delay(16);
//	}
//	return 0;
//}