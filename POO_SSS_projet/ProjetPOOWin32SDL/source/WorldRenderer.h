#pragma once

#include <vector>
#include <list>

class LTexture;
struct LSprite;
struct AnimationRequest;
struct SDL_Renderer;
class Ennemis;
class Joueur;
class EsquadronTie;
class Projectile;


class WorldRenderer
{
private:
	LTexture *GameTextures;
	LSprite *GameSprites;
	SDL_Thread* ExplosionThreadPtr;
	SDL_Renderer* Renderer;
	std::list<AnimationRequest> Animations;

public:
	WorldRenderer(LTexture gametextures[], LSprite gamesprites[], SDL_Renderer* renderer);
	~WorldRenderer();

	void Render(Joueur*);
	//void Render(std::list<Ennemis>);
	void Render(CEsquadronTie*);
	void Render(Projectile*);
	void RenderEventAnimations();
	static int StartExplosionThread(void* ptr);
	int RenderExplosion(void*);
	//void Render(std::list<categorie>);
};

