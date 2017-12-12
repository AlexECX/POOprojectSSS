#pragma once
//#include <SDL.h>
#include <SDL_mixer.h>
//#include "LTexture.h"

//Texture wrapper class
class LTexture;

<<<<<<< HEAD
//The window renderer
SDL_Renderer* gRenderer = NULL;

=======
>>>>>>> ef1159a9eedd87e31966cddae28bdcde19722d44
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

//The music that will be played
Mix_Music *gMusic = NULL;

//The bref song that will be played

Mix_Chunk *gMusicBref[10];