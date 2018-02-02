#include "GameGraphics.h"
#include <SDL_image.h>
#include <SDL_video.h>
#include "..\ressources\LTexture.h"
#include "..\ressources\LSprite.h"
#include <string>
#include <iostream>
#include <fstream>

SDL_Window* GameGraphics::Window;
SDL_Renderer* GameGraphics::Renderer;
std::vector<LTexture> GameGraphics::Textures;
std::vector<LSprite> GameGraphics::Sprites;

bool GameGraphics::GraphicSuccess;
bool GameGraphics::GraphicReady;

GameGraphics::GameGraphics()
{
	//Initialization flag
	GraphicSuccess = true;
	GraphicReady = false;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize graphics! SDL Error: %s\n", SDL_GetError());
		GraphicSuccess = false;
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
			GraphicSuccess = false;
		}
		else
		{
			//Create renderer for window
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				GraphicSuccess = false;
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
					GraphicSuccess = false;
				}
			}
		}
	}
}

bool GameGraphics::LoadGraphics() {
	if (!GraphicReady)
	{
		std::ifstream File;
		std::string FileName;

		//----Load image----------------------------------------------------------

		FileName = ".\image\Textures_List.txt";
		File.open(FileName.c_str());
		if (File.fail())
			printf("Failed to open %s", FileName.c_str());
		else
			while (!File.eof()) {
				std::getline(File, FileName);
				Textures.push_back(LTexture());
				if (!LoadFromFile(Textures.back(), FileName.c_str()))
				{
					printf("Failed to load %s texture image!\n", FileName.c_str());
					GraphicSuccess = false;
				}
			}
		File.close();
		//----Load image end------------------------------------------------------
		//----Load sprite----------------------------------------------------------

		FileName = ".\image\Sprites_List.txt";
		File.open(FileName.c_str());
		if (File.fail())
			printf("Failed to open %s", FileName.c_str());
		else
			while (!File.eof()) {
				std::getline(File, FileName);
				Sprites.push_back(LSprite());
				if (!LoadFromFile(Sprites.back().SpriteTexture, FileName.c_str()))
				{
					printf("Failed to load %s sprite image!\n", FileName.c_str());
					GraphicSuccess = false;
				}
				else
				{
					Sprites.back().SpriteClips = {
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
					Sprites.back().CurrentFrame = 0;
					Sprites.back().TotalFrames = 9;
				}
			}
		File.close();
		//----Load sprite end------------------------------------------------------
		if (GraphicSuccess)
			GraphicReady = true;
	}

	return GraphicSuccess;
}

bool GameGraphics::LoadFromFile(LTexture &Image, std::string path) {
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


GameGraphics::~GameGraphics()
{
	SDL_DestroyWindow(Window);
	Window = nullptr;
	SDL_DestroyRenderer(Renderer);
	Renderer = nullptr;

	IMG_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}




GameGraphics& GameGraphics::Get() {
	static GameGraphics *video = &GameMedia::Get();
	return *video;
}