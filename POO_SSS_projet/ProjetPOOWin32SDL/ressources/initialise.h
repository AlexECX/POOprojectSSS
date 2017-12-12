#pragma once
//#include <SDL.h>
#include <SDL_mixer.h>
//#include "LTexture.h"

//Texture wrapper class
class LTexture;

<<<<<<< HEAD
//The window renderer
=======
>>>>>>> 3de359bda83a7b3584516189f4be5fb3b8429ab2
SDL_Renderer* gRenderer = NULL;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Event handler
SDL_Event e;

//Main loop flag
bool quit = false;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Walking animation
LSprite GameSprites[10];

SDL_Rect gSpriteClips[9];
/*LTexture gSpriteSheetTexture;*/

//Scene textures
LTexture texture[10];

LTexture gBackgroundTexture;
LTexture gBackground2Texture;

//Globally used font
TTF_Font *gFont = NULL;
TTF_Font* Arial = TTF_OpenFont("./style/Arial.ttf", 12);
//Scene Texte
LTexture gPromptTextTexture;

//The music that will be played
Mix_Music *gMusic = NULL;

//The bref song that will be played

Mix_Chunk *gMusicBref[10];