//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

#include "../ressources/LTexture.h"
#include "..\ressources\LSprite.h"
#include "initialise.h"
#include "GameWorld.h"
#include "WorldRenderer.h"

#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"

#define DURATION_IN_MS(Time_Interval) std::chrono::\
        duration_cast<std::chrono::milliseconds>(Time_Interval)\

typedef struct {
	void *data1;
	void *data2;
	void *data3;
} ThreadData;

<<<<<<< HEAD
int CircleCollision(int x1, int y1, int radius1, int x2, int y2, int radius2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int radius3 = radius1 + radius2;

	if (((dx ^ 2) + (dy ^ 2)) < (radius3 ^ 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//----Thread Funtions----------------------------------------------------------------------------

//int TieThread(void *ptr)
//{
//	//On traduit le pointeur en GameWorld
//	ThreadData* FactoryData = (ThreadData*)ptr;
//
//	vector<Ennemis>* TieFighter = (vector<Ennemis>*)FactoryData->data1;
//	//GameWorld *WorldData = (GameWorld*)FactoryData->data2;
//
//	//trucs pour le timer et le deplacement
//	auto interval = std::chrono::milliseconds(5);
////	std::chrono::milliseconds TieFighterFlightTime;
//	auto BeforeUpdate = std::chrono::high_resolution_clock::now();
//
//	while (!TieFighter->empty() && !quit)
//	{
//		int SquadronMembers = TieFighter->size();
//		if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval) {
//			
//			for (int i = 0; i < TieFighter->size(); i++) {
//				if ((*TieFighter)[i].isAlive())
//					(*TieFighter)[i].UpdateTrajet((*TieFighter)[i].getCoordX() - 1, (*TieFighter)[i].getCoordY());
//				else
//					SquadronMembers--;
//			}
//			BeforeUpdate = std::chrono::high_resolution_clock::now();
//		}
//		else
//			SDL_Delay(1);
//
//	}
//	//((GameWorld*)(FactoryData->data2))->RemoveFromGameWorld(TieFighter);
//
//	return 1;
//}

int TieThread(void *ptr) 
{
	GameWorld *tdata = (GameWorld*)ptr;

	Ennemis *Tiefighter = new Ennemis(ennemis_simple, empire, 250, 250, 1, 0, 0);
	Tiefighter = tdata->AddToGameWorld(Tiefighter);

	while(true) {
		Tiefighter->UpdateTrajet(250,250);
	}
	return 1;
}

//----TieFactoryThread----------------------------------------------------------------
=======
//----TieFactoryThread-------------------------------------------------------
>>>>>>> 76468fa82e19a5c65a4b0e846297ffdb53dfd84d

int TieFactoryThread(void *ptr)
{
	//On traduit le pointeur en GameWorld
	vector<CEsquadronTie*> Vagues;
<<<<<<< HEAD
	//GameWorld *tdata = (GameWorld*)ptr;
	//vector<Ennemis> Recrus;
=======
	vector<Ennemis> Recrus;
>>>>>>> 76468fa82e19a5c65a4b0e846297ffdb53dfd84d

	while (!quit) {
		SDL_Delay(5000);
		vector<Ennemis> Recrus;
		for (int i = 0; i < 6; i++) {
			Recrus.push_back(Ennemis(ennemis_simple, empire, 
				             1100 + (rand() % 4 * 50), 
				             (i *100) + 50, 1, 0, 0));
		}
		CEsquadronTie* temp = new CEsquadronTie(Recrus);
<<<<<<< HEAD
		GameWorld::AddToGameWorld(temp);
		//Vagues.push_back(tdata->AddToGameWorld(*temp));
			
		//ThreadData *FactoryMessage = new ThreadData{ Esquadron, tdata };
		//TieTH.push_back(SDL_CreateThread(TieThread, "TieThread", FactoryMessage));
=======
		GameWorld::AddToGameWorld(*temp);
>>>>>>> 76468fa82e19a5c65a4b0e846297ffdb53dfd84d
		SDL_Delay(1000);
	}
	return 1;
}

int ThreadKeyboard(void* ptr)
{
	//On traduit le pointeur en GameWorld
	bool CheckUpFirst = true;
	bool CheckRightFirst = true;
	//Initialise un Falcon
	//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de 
	//l'objet
	Joueur *MilleniumFalcon = new Joueur(joueur, republic, 50, 250, 1, 0, 0);
<<<<<<< HEAD
	MilleniumFalcon = GameWorld::AddToGameWorld(MilleniumFalcon);

=======
	MilleniumFalcon = GameWorld::AddToGameWorld(*MilleniumFalcon);
>>>>>>> 76468fa82e19a5c65a4b0e846297ffdb53dfd84d
	auto interval = std::chrono::milliseconds(500);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (!quit) 
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_Q]) {
				SDL_Event user_event;
				user_event.type = SDL_QUIT;
				SDL_PushEvent(&user_event);
		}

		if (CheckUpFirst) {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN])
				MilleniumFalcon->MouvUp();
			else 
				if (state[SDL_SCANCODE_UP]) {
				MilleniumFalcon->MouvUp();
				CheckUpFirst = false;
			} 
			else
				if (state[SDL_SCANCODE_DOWN])
					MilleniumFalcon->MouvDown();
			}
		else
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN])
				MilleniumFalcon->MouvDown();
			else
				if (state[SDL_SCANCODE_DOWN]) {
					MilleniumFalcon->MouvDown();
					CheckUpFirst = true;
				}
			else
				if (state[SDL_SCANCODE_UP])
					MilleniumFalcon->MouvUp();

		if (CheckRightFirst) {
			if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT])
				MilleniumFalcon->MouvRight();
			else
				if (state[SDL_SCANCODE_RIGHT]) {
					MilleniumFalcon->MouvRight();
					CheckRightFirst = false;
				}
				else
					if (state[SDL_SCANCODE_LEFT])
						MilleniumFalcon->MouvLeft();
		}
		else
			if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT])
				MilleniumFalcon->MouvLeft();
			else
				if (state[SDL_SCANCODE_LEFT]) {
					MilleniumFalcon->MouvLeft();
					CheckRightFirst = true;
				}
				else
					if (state[SDL_SCANCODE_RIGHT])
						MilleniumFalcon->MouvRight();

		if (state[SDL_SCANCODE_W])
		{
			if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - 
				BeforeUpdate) >= interval)
			{
<<<<<<< HEAD
				if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
				{
					Projectile* Tir = new Projectile(tir_joueur, republic, MilleniumFalcon->getCoordX() + 150, MilleniumFalcon->getCoordY() + 65, 1, 10, 0);
					Tir = GameWorld::AddToGameWorld(Tir);
					BeforeUpdate = std::chrono::high_resolution_clock::now();
					
					//----Play bref song----
					Mix_PlayChannel(-1, gMusicBref[0], 0);
				}
=======
				Projectile* Tir = new Projectile(tir_joueur, republic, 
					                  MilleniumFalcon->getCoordX() + 150, 
					                  MilleniumFalcon->getCoordY() + 65,
					                             1, 10, 0);
				Tir = GameWorld::AddToGameWorld(*Tir);
				BeforeUpdate = std::chrono::high_resolution_clock::now();
				
				//----Play bref song----
				Mix_PlayChannel(-1, gMusicBref[0], 0);
>>>>>>> 76468fa82e19a5c65a4b0e846297ffdb53dfd84d
			}
		}
		SDL_Delay(3);
	}
	return 1;
}

//----Main-------------------------------------------------------------------

int main(int argc, char* args[])
{
	string score;
	//----Variables pour nos thread-------
	SDL_Thread *thread[10];
	int threadReturnValue[10];
	//------------------------------------

	//----Variables pour la gestion du FPS----------
	//std::chrono::steady_clock::time_point end;
	auto Main_interval = std::chrono::milliseconds(16); //16666666
	auto Main_Timestamp = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds Main_elapsed;
	//------------------------------------------------

	//----Objet GameWorld et variable pour contenir les adresses 
	//----de conteneurs
	//Englobe toute les textures, animation et le SDL renderer
	WorldRenderer SpaceRenderer(texture, GameSprites, gRenderer); 
	//GameWorld contiendra des pointeurs sur tout nos objets volant du jeu. 
	//On lui passe ici l'adresse du Renderer
	GameWorld::SetupGameWorld(&SpaceRenderer);	//Contiendra des pointeurs 
	                                            //sur tout nos objets 
	                                            //volant du jeu

	void SDL_SetWindowMinimumSize(SDL_Window* window, int min_w, int min_h);
	int BackgroundMusic = true;

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
			//The current input text.
			string inputText = "Some Text";

			Mix_PlayMusic(gMusic, -1);
			Mix_ResumeMusic();

			//----Execute thread---------------------------------------------
			thread[1] = SDL_CreateThread(TieFactoryThread, 
				                         "TieFactoryThread", ((void*)1) );
			thread[2] = SDL_CreateThread(ThreadKeyboard,
				                         "ThreadKeyboard", ((void*)1) );

			int T = 0;
			int R = -gBackgroundTexture.getWidth();
			bool M = true;

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
				//Wait until Main_interval milliseconds have passed.
				Main_elapsed = DURATION_IN_MS(std::chrono::
					           high_resolution_clock::now() - 
					           Main_Timestamp);

				if (Main_elapsed < Main_interval) 
				{
					SDL_Delay(1);
					//SDL_Delay(DURATION_IN_MS(Main_interval - 
					//Main_elapsed).count());
				}

				else 
				{
					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 
						                   0xFF);
					SDL_RenderClear(gRenderer);

<<<<<<< HEAD
					//Bench pour tester l'interval de temp. Total devrait donner 16 ms +/- 1 ms
					/*end = std::chrono::high_resolution_clock::now();
					double total = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
					start = std::chrono::high_resolution_clock::now();*/
=======
					//Bench pour tester l'interval de temp. Total devrait 
					//donner 30 ms +/- 1 ms
					//end = std::chrono::high_resolution_clock::now();
					//double total = std::chrono::duration_cast<std::chrono::
					//nanoseconds>(end - start).count();
					//start = std::chrono::high_resolution_clock::now();
>>>>>>> 76468fa82e19a5c65a4b0e846297ffdb53dfd84d

					//SDL_Delay(16);

					Main_Timestamp = std::chrono::
						             high_resolution_clock::now();

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 
						                   0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					//Loops the background and Render texture to screen
					if (T <= gBackgroundTexture.getWidth() + SCREEN_WIDTH) {
						gBackgroundTexture.render(-T, 0);
					}

					if (R >= -SCREEN_WIDTH && R <= gBackground2Texture.
						getWidth())
						gBackgroundTexture.render(-R, 0);


					if (R == gBackground2Texture.getWidth() - 
						SCREEN_WIDTH && T >= 0)
						T = -SCREEN_WIDTH;

					if (R >= gBackground2Texture.getWidth())
						R = -gBackgroundTexture.getWidth();
					T++;
					R++;
					
					score = to_string(GameWorld::GameScore());

					//----Message----
					TTF_Font* Arial = TTF_OpenFont("./style/Arial.ttf", 12);
					SDL_Color White = { 255, 255, 255 };
					SDL_Surface* surfaceMessage = TTF_RenderText_Solid
					(Arial, ("Score "+ score).c_str(), White); 
					SDL_Texture* Message = SDL_CreateTextureFromSurface
					(gRenderer, surfaceMessage);
					SDL_Rect Message_rect; //create a rect
					Message_rect.x = 25;  //controls the rect's x coordinate 
					Message_rect.y = 650; // controls the rect's y coordinte
					Message_rect.w = 75; // controls the width of the rect
					Message_rect.h = 25; // controls the height of the rect
					SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
					//----Message----

					GameWorld::RenderWorld();

					texture[4].render(700, 300);

					////Update screen
					SDL_RenderPresent(gRenderer);
				}
			}
		}
	}
	//Free resources and close SDL
	close();
	SDL_WaitThread(thread[1], &threadReturnValue[1]); //Wait for 
	                                                  //the thread 
	                                                  //to complete.
	SDL_WaitThread(thread[2], &threadReturnValue[2]);
	GameWorld::DeleteGameWorld();
	return 0;
}

#include"loadFromFile.h"

#include"loadtexture.h"

#include"boolinit.h"

#include"loadmedia.h"

#include"close.h"