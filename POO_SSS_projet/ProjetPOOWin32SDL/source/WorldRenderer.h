#pragma once

#include <vector>
#include <list>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

class LTexture;
struct LSprite;
enum categorie;
struct AnimationRequest;
class Ennemis;
class Joueur;
class CEsquadronTie;
class Projectile;
class EntiteVolante;

struct AnimationRequest;

class WorldRenderer
{
private:
	static std::list<AnimationRequest> Animations;
	static void Render(LTexture *TextureNum, int x, int y, SDL_Rect* Clip = NULL);
protected:
	const static int SCREEN_WIDTH = 1200;
	const static int SCREEN_HEIGHT = 700;
	static LTexture Textures[10];
	static LTexture ScoreMessage;
	static TTF_Font* Fonts[10];
	static LSprite Sprites[10];
	static SDL_Renderer* Renderer;
	static SDL_Window* Window;

public:

	//static void SetupWorldRenderer();
	static void Render(categorie TextureNum, int x, int y);
	static void Render(Joueur*);
	static void Render(CEsquadronTie*);
	static void Render(Projectile*);
	static void RenderScore(int score);
	static void MakeAnimationRequest(categorie TextureNum, int x, int y);
	static void RenderEventAnimations();
	static void RenderClear();
	static void RenderPresent();

	//Inutilisé
	static int StartExplosionThread(void* ptr);
	int RenderExplosion(void*);
};