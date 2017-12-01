//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;


#include"initialise.h"
#include "Plateau.h"
#include "EntiteVolante.h"
#include "Joueur.h"

//----Main----------------------------------------------------------------------------

int main(int argc, char* args[])
{
	int X1 = 200;
	int Y1 = 200;
	
	//Thread initialise

	SDL_Thread *thread;
	int         threadReturnValue;

	/**
	printf("\nSimple SDL_CreateThread test:");

	//Simply create a thread 
	thread = SDL_CreateThread(TestThread, "TestThread", (void *)NULL);

	if (NULL == thread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
	else {
		SDL_WaitThread(thread, &threadReturnValue); //Wait for the thread to complete.
		printf("\nThread returned value: %d", threadReturnValue);
	}

	static int TestThread(void *ptr)
	{
	int cnt;

	for (cnt = 0; cnt < 10; ++cnt) {
	printf("\nThread counter: %d", cnt);
	SDL_Delay(50);
	}

	return cnt;
	}

	/**/

	Joueur temp(joueur, republic, 50, 250, 1, 0, 0);

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

			//////////////////////////

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
<<<<<<< HEAD
				texture[temp.getCategorie()].render(temp.getCoordX(), temp.getCoordY());
=======
				texture[0].render(X1,Y1);
>>>>>>> 51dd08e02ede2172f31043af855a32135442a707

				texture[2].render(200, 300);

				texture[1].render(500, 250);

				texture[3].render(350, 300);

				//Update screen
				SDL_RenderPresent(gRenderer);

				//----Keyboard detect----

				const Uint8 *state = SDL_GetKeyboardState(NULL);

				if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
					Y1--;
					X1--;
				}

				else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
					Y1++;
					X1--;
				}

				else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
					Y1--;
					X1++;
				}

				else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
					Y1++;
					X1++;
				}
				
				else if (state[SDL_SCANCODE_DOWN]) {
					Y1++;
				}
				else if (state[SDL_SCANCODE_UP]) {
					Y1--;
				}
				else if (state[SDL_SCANCODE_RIGHT]) {
					X1++;
				}
				else if (state[SDL_SCANCODE_LEFT]) {
					X1--;
				}
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