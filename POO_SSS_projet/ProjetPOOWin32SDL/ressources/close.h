#pragma once

void close()
{
	//Free loaded images
	//GameSprites[0].SpriteTexture.free();

	////Free loaded images
	//texture[0].free();
	//texture[1].free();
	//texture[2].free();
	//texture[3].free();
	//gBackgroundTexture.free();
	//gBackground2Texture.free();

	//Free loaded images
	gPromptTextTexture.free();

	//Free global font
	TTF_CloseFont(Arial);
	gFont = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	Mix_FreeChunk(gMusicBref[0]);
	Mix_FreeChunk(gMusicBref[1]);
	Mix_FreeChunk(gMusicBref[2]);
	gMusicBref[0] = NULL;
	gMusicBref[1] = NULL;
	gMusicBref[2] = NULL;

	//Destroy window	
	/*SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;*/

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}