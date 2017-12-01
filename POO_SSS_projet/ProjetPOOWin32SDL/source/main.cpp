//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>

//Screen dimension constants
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;


#include"initialise.h"
#include "Plateau.h"
#include "EntiteVolante.h"
#include "Joueur.h"


typedef struct {
	Joueur *PtrJoueur;
} ThreadData;




//----Thread Funct----------------------------------------------------------------------------

int TestThread(void *ptr)
{
	ThreadData *tdata = (ThreadData*)ptr;
	auto interval = std::chrono::nanoseconds(10000000);
	auto before = std::chrono::high_resolution_clock::now();
	auto before2 = std::chrono::high_resolution_clock::now();
	int flying = 9000;
	int H = 1;
	while (flying)
	{
		
		if (std::chrono::high_resolution_clock::now() - before > interval) {
			tdata->PtrJoueur->UpdateTrajet(tdata->PtrJoueur->getCoordX() + H, tdata->PtrJoueur->getCoordY());
			before = std::chrono::high_resolution_clock::now();
		}
		if (std::chrono::high_resolution_clock::now() - before2 > interval*50) {
			H *= -1;
			before2 = std::chrono::high_resolution_clock::now();
		}
	}

	return 2;
}


//----Main----------------------------------------------------------------------------


int main(int argc, char* args[])
{
	void SDL_SetWindowMinimumSize(SDL_Window* window, int min_w, int min_h);
	
	int X1 = 200;
	int Y1 = 200;
	auto Main_interval = std::chrono::nanoseconds(16666666); //16666666
	auto Main_Timestamp = std::chrono::high_resolution_clock::now();
	
	//Thread initialise

	SDL_Thread *thread;
	int         threadReturnValue;



	/*if (NULL == thread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}*/


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
			Joueur temp(joueur, republic, 50, 250, 1, 0, 0);
			Joueur temp2(ennemis_simple, empire, 500, 250, 1, 0, 0);
			ThreadData *message = (ThreadData*)malloc(sizeof(ThreadData));
			message->PtrJoueur = &temp2;

			/**/
			//printf("\nSimple SDL_CreateThread test:");

			//Simply create a thread 
			thread = SDL_CreateThread(TestThread, "TestThread", message);
			/////////////////////////////////

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

			/*	auto tempTime = std::chrono::high_resolution_clock::now();
				auto tempResult = tempTime - Main_Timestamp;
				if (tempTime - Main_Timestamp < Main_interval) {
					SDL_Delay(30);
					Main_Timestamp = std::chrono::high_resolution_clock::now();
				}
				else {*/


					SDL_Delay(16);

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					//Render background texture to screen
					gBackgroundTexture.render(0, 0);

					//Render Foo' to the screen

					texture[temp.getCategorie()].render(temp.getCoordX(), temp.getCoordY());

					texture[2].render(200, 300);

					texture[temp2.getCategorie()].render(temp2.getCoordX(), temp2.getCoordY());

					texture[3].render(350, 300);

					//Update screen
					SDL_RenderPresent(gRenderer);
				//}
				

				//----Keyboard detect----

				const Uint8 *state = SDL_GetKeyboardState(NULL);

				if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
					temp.UpdateTrajet( temp.getCoordX()-1, temp.getCoordY()-1);
				}

				else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
					temp.UpdateTrajet(temp.getCoordX() - 1, temp.getCoordY() + 1);
			
				}

				else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
					temp.UpdateTrajet(temp.getCoordX() + 1, temp.getCoordY() - 1);
	
				}

				else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
					temp.UpdateTrajet(temp.getCoordX() + 1, temp.getCoordY() + 1);

				}
				
				else if (state[SDL_SCANCODE_DOWN]) {
					temp.UpdateTrajet(temp.getCoordX(), temp.getCoordY() + 1);
				}
				else if (state[SDL_SCANCODE_UP]) {
					temp.UpdateTrajet(temp.getCoordX(), temp.getCoordY() - 1);

				}
				else if (state[SDL_SCANCODE_RIGHT]) {
					temp.UpdateTrajet(temp.getCoordX() + 1, temp.getCoordY());

				}
				else if (state[SDL_SCANCODE_LEFT]) {
					temp.UpdateTrajet(temp.getCoordX() - 1, temp.getCoordY());

				}
			}
			SDL_WaitThread(thread, &threadReturnValue); //Wait for the thread to complete.
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