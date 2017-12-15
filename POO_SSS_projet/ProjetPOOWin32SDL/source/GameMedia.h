#pragma once
#include "WorldRenderer.h"

class LTexture;
struct SDL_Window;
typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

class GameMedia : public WorldRenderer
{
private:

	static bool LoadFromFile(LTexture&, std::string path);
	const static int SCREEN_WIDTH = 1200;
	const static int SCREEN_HEIGHT = 700;
public:
	static Mix_Music* Music;
	static Mix_Chunk* SFX[10];
	static SDL_Window* Window;
	//static SDL_Renderer* Renderer;

	static void SetWindowsSize();
	static bool Initialise();
	static bool LoadMedia();
	static void Close();

};

