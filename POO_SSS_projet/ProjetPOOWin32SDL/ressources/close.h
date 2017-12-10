#pragma once

void close()
{
	//Free loaded images
	GameSprites[0].SpriteTexture.free();

	//Free loaded images
	texture[0].free();
	texture[1].free();
	texture[2].free();
	texture[3].free();
	gBackgroundTexture.free();
	gBackground2Texture.free();

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}