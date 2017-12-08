#pragma once
//#include <SDL.h>
#include <SDL_mixer.h>
//#include "LTexture.h"

//Texture wrapper class
class LTexture;



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

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Walking animation
LSprite GameSprites[10];


SDL_Rect gSpriteClips[9];
//LTexture gSpriteSheetTexture;


//Scene textures
LTexture texture[10];

LTexture gBackgroundTexture;



//The music that will be played
Mix_Music *gMusic = NULL;
