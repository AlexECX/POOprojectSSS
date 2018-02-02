#pragma once
#include "GameGraphics.h"
#include "GameText.h"
#include <mutex>
#include <vector>
#include <list>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

class LTexture;
enum categorie;
struct AnimationRequest;

class WorldRenderer : public GameMedia
{
private:
	static std::list<AnimationRequest> Animations;
	static void Render(LTexture *TextureNum, int x, int y, SDL_Rect* Clip = NULL);
	static std::mutex Renderer_lock;

public:
	//static WorldRenderer& Get();
	static void RenderEntity(categorie TextureNum, int x, int y);
	static void RenderScore(int score);
	static void MakeAnimationRequest(categorie TextureNum, int x, int y);
	static void RenderEventAnimations();
	static void RenderClear();
	static void RenderPresent();
};