#pragma once
#include "GameMedia.h"
#include <vector>
#include <SDL.h>

class LTexture;
struct LSprite;

class GameGraphics
{
private:
	GameGraphics();
	GameGraphics(const GameGraphics&) = delete;
	GameGraphics(GameGraphics&&) = delete;
	void operator=(const GameGraphics&) = delete;
	void operator=(GameGraphics&&) = delete;

	bool LoadFromFile(LTexture &Image, std::string path);

protected:
	const static int SCREEN_WIDTH = 1200;
	const static int SCREEN_HEIGHT = 700;
	static SDL_Window* Window;
	static SDL_Renderer* Renderer;
	static std::vector<LTexture> Textures;
	static std::vector<LSprite> Sprites;
	
	static bool GraphicSuccess;
	static bool GraphicReady;

public:
	
	~GameGraphics();
	static GameGraphics& Get();
	bool LoadGraphics();


};

