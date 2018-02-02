#include "GameWorld.h"
#include <vector>
#include "EntiteVolante.h"
#include "WorldRenderer.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "..\ressources\LTexture.h"
#include "..\ressources\LSprite.h"
#include <string>

std::list<AnimationRequest> WorldRenderer::Animations;
std::mutex WorldRenderer::Renderer_lock;


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



//WorldRenderer & WorldRenderer::Get()
//{
//	static WorldRenderer renderer;
//	return renderer;
//}


void WorldRenderer::Render(LTexture *TextureNum, int x, int y, SDL_Rect* Clip)
{
	static SDL_Rect renderQuad;
	if (Clip == NULL) {
		renderQuad.x = x - TextureNum->getWidth() / 2;
		renderQuad.y = y - TextureNum->getHeight() / 2;
		renderQuad.w = TextureNum->getWidth();
		renderQuad.h = TextureNum->getHeight();
	}
	else
	{
		renderQuad.x = x - Clip->w / 2;
		renderQuad.y = y - Clip->h / 2;
		renderQuad.w = Clip->w;
		renderQuad.h = Clip->h;
	}
	//std::lock_guard<std::mutex> lock(Renderer_lock);
	SDL_RenderCopy(Renderer, TextureNum->getTexture(), Clip, &renderQuad);
}


void WorldRenderer::RenderEntity(categorie TextureNum, int x, int y)
{
	Render(&Textures[TextureNum], x, y);
}

void WorldRenderer::RenderScore(int score)
{
	static LTexture ScoreMessage;
	static int PrevScore = -1;
	static SDL_Color White = { 255, 255, 255 };
	static LTexture ScorePoints;
	if (PrevScore != score) {
		ScorePoints.free();
		PrevScore = score;
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Fonts[arial], std::to_string(score).c_str(), White);
		ScorePoints.AssignTexture(SDL_CreateTextureFromSurface(Renderer, surfaceMessage),
								  std::to_string(score).size()*15,
								  24);
	}
	Render(&ScorePoints, 215, 650);
	Render(&ScoreMessage, 125, 650);

}

void WorldRenderer::MakeAnimationRequest(categorie TextureNum, int x, int y)
{
	if (TextureNum != tir_joueur && TextureNum != tir_tie)
		Animations.push_back(AnimationRequest{
			0,	//Sprite Number
			Sprites[0].TotalFrames,
			x, y,
			0	//Starting frame
		});
}


void WorldRenderer::RenderEventAnimations()
{
	if (!Animations.empty()) {
		std::list<AnimationRequest>::iterator Animator = Animations.begin();
		while (Animator != Animations.end()) {
			if (Animator->CurrentFrame < Animator->TotalFrames) {
				Render(&Sprites[Animator->SpriteNum].SpriteTexture,
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
	//Render Background
	static SDL_Rect renderQuad;
	renderQuad.x = 0;
	renderQuad.y = 0;
	renderQuad.w = Textures[background].getWidth();
	renderQuad.h = Textures[background].getHeight();

	//Clear screen
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(Renderer);

	//std::lock_guard<std::mutex> lock(Renderer_lock);

	SDL_RenderCopy(Renderer, Textures[background].getTexture(), NULL, &renderQuad);
}

void WorldRenderer::RenderPresent()
{
	//std::lock_guard<std::mutex> lock(Renderer_lock);
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