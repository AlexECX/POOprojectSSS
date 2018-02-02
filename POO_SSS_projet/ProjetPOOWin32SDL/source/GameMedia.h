#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_video.h>
#include <vector>

class LTexture;
struct LSprite;
enum SfxName { falcon_fire, tie_fire, tie_explosion };
enum MusicName { background_music };
enum FontName { arial };


//#include "GameAudio.h"
//#include "GameGraphics.h"
//#include "GameText.h"


class GameMedia
{
public:
	static std::vector<Mix_Music*> Music;
	static std::vector<Mix_Chunk*> SFX;

	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 700;
	static SDL_Window* Window;
	static SDL_Renderer* Renderer;
	static LTexture Textures[10];
	static std::vector<LSprite> Sprites;

	static std::vector<TTF_Font*> Fonts;

	static bool LoadFromFile(LTexture *Image, std::string path) ;

	
	

	static bool GraphicSuccess;
	static bool GraphicReady;

	static bool AudioSuccess;
	static bool AudioReady;

	static bool TextSuccess;
	static bool TextReady;

public:
	//GameMedia();
	/*GameMedia(const GameMedia&) = delete;
	GameMedia(GameMedia&&) = delete;
	void operator=(const GameMedia&) = delete;
	void operator=(GameMedia&&) = delete;*/

public:
	static bool Initialise();

	static bool LoadFonts() ;


	static bool LoadAudio() ;
	static void PlayMusic(MusicName) ;
	static void PlaySFX(int sound) ;

	static bool LoadGraphics() ;

	//static GameMedia& Get();
	
};

