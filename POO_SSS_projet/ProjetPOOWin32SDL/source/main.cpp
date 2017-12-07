//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
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
#include "Ennemis.h"

typedef struct {
	Joueur *PtrJoueur;
} ThreadData;

//----Thread Funct----------------------------------------------------------------------------

int TestThread(void *ptr)
{
	//On traduit le pointeur en GameWorld
	GameWorld *tdata = (GameWorld*)ptr; 
	//Initialise un Tie Fighter
	//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet
	Joueur *TieFighter = tdata->AddToGameWorld(Joueur(ennemis_simple, empire, 500, 250, 1, 0, 0));
	std::list<Joueur>* AccessKey;

	//trucs pour le timer et le deplacement
	auto interval = std::chrono::nanoseconds(10000000);
	auto before = std::chrono::high_resolution_clock::now();
	auto before2 = std::chrono::high_resolution_clock::now();
	int flying = 9000;
	int H = 1;
	////

	while (flying)
	{
		
		if (std::chrono::high_resolution_clock::now() - before > interval) {
			//Ici le thread vas Accede a sont objet dans la liste PlayerHolder the GameWorld

			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			TieFighter->UpdateTrajet(TieFighter->getCoordX() + H, TieFighter->getCoordY());
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)
			
			before = std::chrono::high_resolution_clock::now();
		}
		if (std::chrono::high_resolution_clock::now() - before2 > interval*50) {
			H *= -1;
			before2 = std::chrono::high_resolution_clock::now();
		}
	}

	return 1;
}

//----Main----------------------------------------------------------------------------

int main(int argc, char* args[])
{
	void SDL_SetWindowMinimumSize(SDL_Window* window, int min_w, int min_h);
	
	int X1 = 200;
	int Y1 = 200;
	auto Main_interval = std::chrono::nanoseconds(16666666); //16666666
	auto Main_Timestamp = std::chrono::high_resolution_clock::now();
	GameWorld Space;
	std::list<Joueur>* PlayerHolderAccessKey;
	
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

			//On initilise le Faucon.
			//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet
			Joueur *MilleniumFalcon = Space.AddToGameWorld(Joueur(joueur, republic, 50, 250, 1, 0, 0));

			/**/
			//printf("\nSimple SDL_CreateThread test:");

			//Simply create a thread 
			GameWorld *World_ptr = &Space; //On envoie GameWorld en parametre, on devra le traduire avec (GameWorld*)
			thread = SDL_CreateThread(TestThread, "TestThread", World_ptr);
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

					//Astuce: les methodes "Access_______()" the GameWorld retourne en fait l'adresse du conteneur, 
					//apres l'avoir locké. Tu peux donc itérer dessus si nécessaire

					PlayerHolderAccessKey = Space.AccessPlayerHolder();	//On reclame un acces au conteneur
					std::list<Joueur>::iterator S = PlayerHolderAccessKey->begin();

					//Ici on itere sur le conteneur PlayerHolder pour render tout les objets qu'il contient
					while (S != PlayerHolderAccessKey->end()) {
						texture[S->getCategorie()].render(S->getCoordX(), S->getCoordY());
						S++;
					}
					Space.ReleaseContainer(PlayerHolderAccessKey);	//Ne pas oublier de relacher le conteneur


					//texture[temp.getCategorie()].render(temp.getCoordX(), temp.getCoordY());

					texture[2].render(200, 300);

					texture[3].render(350, 300);

					//Update screen
					SDL_RenderPresent(gRenderer);
				//}

				//----Keyboard detect----

				const Uint8 *state = SDL_GetKeyboardState(NULL);

				if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
					MilleniumFalcon->UpdateTrajet( MilleniumFalcon->getCoordX()-1,
												   MilleniumFalcon->getCoordY()-1);
				}

				else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
					MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() - 1,
												  MilleniumFalcon->getCoordY() + 1);
			
				}

				else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
					MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1, 
												  MilleniumFalcon->getCoordY() - 1);
	
				}

				else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
					MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1, 
												  MilleniumFalcon->getCoordY() + 1);

				}
				
				else if (state[SDL_SCANCODE_DOWN]) {
					MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX(),
												  MilleniumFalcon->getCoordY() + 1);
				}
				else if (state[SDL_SCANCODE_UP]) {
					MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX(),
												  MilleniumFalcon->getCoordY() - 1);

				}
				else if (state[SDL_SCANCODE_RIGHT]) {
					MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1, 
												  MilleniumFalcon->getCoordY());

				}
				else if (state[SDL_SCANCODE_LEFT]) {
					MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() - 1,
												  MilleniumFalcon->getCoordY());

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