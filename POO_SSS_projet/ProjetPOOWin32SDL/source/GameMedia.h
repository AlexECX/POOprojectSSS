#pragma once
#include "WorldRenderer.h"
#include <SDL_mixer.h>

class LTexture;

class GameMedia : private WorldRenderer
{
private:
	static bool LoadFromFile(LTexture&, std::string path);

public:
	static Mix_Music* Music;
	static Mix_Chunk* SFX[10];
	//static SDL_Renderer* Renderer;

	static bool Initialise();
	static bool LoadMedia();
	static void PlayMusic();
	static void PlaySFX(int sound){ Mix_PlayChannel(-1, SFX[sound], 0); }
	static void Close();

};

