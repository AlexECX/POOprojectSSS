#include "GameMedia.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "..\ressources\LTexture.h"
#include "..\ressources\LSprite.h"

LTexture WorldRenderer::Textures[10];
LSprite WorldRenderer::Sprites[10];
SDL_Renderer*  WorldRenderer::Renderer;
SDL_Window* GameMedia::Window;
Mix_Music* GameMedia::Music;
Mix_Chunk* GameMedia::SFX[10];

bool GameMedia::LoadFromFile(LTexture &Image, std::string path)
{
	//Get rid of preexisting texture
	Image.free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			//Set Texture
			Image.AssignTexture(newTexture, loadedSurface->w, loadedSurface->h);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	//Return success
	
	return newTexture != NULL;
}

bool GameMedia::Initialise()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		Window = SDL_CreateWindow("Empire strike back",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool GameMedia::LoadMedia()
{
	bool success = true;

	//----Load image----------------------------------------------------------

	if (!LoadFromFile(Textures[0], "./image/falcon.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!LoadFromFile(Textures[1], "./image/tiefighter.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!LoadFromFile(Textures[2], "./image/LaserFriend.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!LoadFromFile(Textures[3], "./image/LaserEnnemis.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!LoadFromFile(Textures[4], "./image/Asteroid.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	//Load background texture
	if (!LoadFromFile(Textures[5], "./image/background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	//Load background2 texture
	if (!LoadFromFile(Textures[6], "./image/background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	//----Load image end------------------------------------------------------
	
	//----Load sprite----------------------------------------------------------

	//Load sprite sheet texture
	if (!LoadFromFile(Sprites[0].SpriteTexture, "./image/Explosion.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips

		//This is a SDL_Rect
		/*typedef struct SDL_Rect
		{
		int x, y;
		int w, h;
		} SDL_Rect;*/
		//----------------

		//-Tie Explosion--
		Sprites[0].SpriteClips = {
			SDL_Rect{ 10,  10,  60, 60 },
			SDL_Rect{ 75,  10,  60, 60 },
			SDL_Rect{ 150, 10,  60, 60 },
			SDL_Rect{ 10,  75,  60, 60 },
			SDL_Rect{ 75,  75,  60, 60 },
			SDL_Rect{ 150, 75,  60, 60 },
			SDL_Rect{ 10,  150, 60, 60 },
			SDL_Rect{ 75,  150, 60, 60 },
			SDL_Rect{ 150, 150, 60, 60 },
		};
		Sprites[0].CurrentFrame = 0;
		Sprites[0].TotalFrames = 9;
		//-----------
	}
	//----Load sprite end------------------------------------------------------

	//----Load music and sound-------------------------------------------------

	Music = Mix_LoadMUS("./music/BackgroundAsteroidField.mp3");
	if (Music == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	SFX[0] = Mix_LoadWAV("./music/FalconFire.wav");
	if (SFX[0] == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	SFX[1] = Mix_LoadWAV("./music/TieFighterFire.wav");
	if (SFX[1] == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	SFX[2] = Mix_LoadWAV("./music/TieFighterExplosion.wav");
	if (SFX[2] == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//----Load music and end--------------------------------------------------

	return success;


}

void GameMedia::Close()
{
	Sprites[0].SpriteTexture.free();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Renderer = NULL;
	Window = NULL;

}


