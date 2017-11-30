//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#include"initialise.h"

//----Main----------------------------------------------------------------------------

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background texture to screen
				gBackgroundTexture.render(0, 0);

				//Render Foo' to the screen
				gFooTexture.render(50, 250);

				gFooTexture2.render(500, 250);

				//Update screen
				SDL_RenderPresent(gRenderer);
				temp += 10;
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

//----Fonctions----------------------------------------------------------------------------

#include"loadFromFile.h"

#include"loadtexture.h"

#include"boolinit.h"

#include"loadmedia.h"

#include"close.h"