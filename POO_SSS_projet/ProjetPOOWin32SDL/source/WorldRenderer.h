#pragma once

#include <vector>
#include <list>

class LTexture;
struct LSprite;
struct AnimationRequest;
struct SDL_Renderer;
struct SDL_Rect;
class Ennemis;
class Joueur;
class CEsquadronTie;
class Projectile;

struct AnimationRequest;

class WorldRenderer
{
private:
	static std::list<AnimationRequest> Animations;

public:
	static void Render(LTexture *TextureNum, int x, int y, SDL_Rect* Clip = NULL);

	static LTexture Textures[10];
	static LSprite Sprites[10];
	static SDL_Renderer* Renderer;
	

public:

	//static void SetupWorldRenderer();
	static void Render(Joueur*);
	static void Render(CEsquadronTie*);
	static void Render(Projectile*);
	static void RenderEventAnimations();
	static void RenderClear();
	static void RenderPresent();

	//Inutilisé
	static int StartExplosionThread(void* ptr);
	int RenderExplosion(void*);
};