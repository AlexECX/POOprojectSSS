#pragma once

void close()
{
	//Free loaded images
	texture[0].free();
	texture[1].free();
	texture[2].free();
	texture[3].free();
	gBackgroundTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}