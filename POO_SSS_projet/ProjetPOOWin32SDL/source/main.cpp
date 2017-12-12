//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
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

#define DURATION_IN_MS(Time_Interval) std::chrono::duration_cast<std::chrono::milliseconds>(Time_Interval)

typedef struct {
	void *data1;
	void *data2;
	void *data3;
} ThreadData;

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
	Tiefighter = tdata->AddToGameWorld(*Tiefighter);

	while(true) {
		Tiefighter->UpdateTrajet(250,250);
	}
	return 1;
}

//----TieFactoryThread----------------------------------------------------------------

int TieFactoryThread(void *ptr)
{
	//On traduit le pointeur en GameWorld
	//vector<SDL_Thread*> TieTH;
	vector<CEsquadronTie*> Vagues;
	GameWorld *tdata = (GameWorld*)ptr;
	vector<Ennemis> Recrus;

	while (!quit) {
		SDL_Delay(5000);
		vector<Ennemis> Recrus;
		for (int i = 0; i < 6; i++) {
			Recrus.push_back(Ennemis(ennemis_simple, empire, 1100 + (rand() % 4 * 50), (i *100) + 50, 1, 0, 0));
		}
		CEsquadronTie* temp = new CEsquadronTie(Recrus);
		tdata->AddToGameWorld(*temp);
		//Vagues.push_back(tdata->AddToGameWorld(*temp));
			
		//ThreadData *FactoryMessage = new ThreadData{ Esquadron, tdata };
		//TieTH.push_back(SDL_CreateThread(TieThread, "TieThread", FactoryMessage));
		SDL_Delay(1000);
	}
	/*while (!TieTH.empty())
		SDL_WaitThread(TieTH.back(), &TieReturnValue);*/
	return 1;
}

int ThreadKeyboard(void* ptr)
{
	//On traduit le pointeur en GameWorld
	GameWorld *tdata = (GameWorld*)ptr;
	bool CheckUpFirst = true;
	bool CheckRightFirst = true;
	//Initialise un Falcon
	//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet
	Joueur *MilleniumFalcon = new Joueur(joueur, republic, 50, 250, 1, 0, 0);
	MilleniumFalcon = tdata->AddToGameWorld(*MilleniumFalcon);

	auto interval = std::chrono::milliseconds(500);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (!quit) 
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		//SDL_PollEvent(&e);

		//if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		//{
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
				if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
				{
					Projectile* Tir = new Projectile(tir_joueur, republic, MilleniumFalcon->getCoordX() + 150, MilleniumFalcon->getCoordY() + 65, 1, 10, 0);
					Tir = tdata->AddToGameWorld(*Tir);
					BeforeUpdate = std::chrono::high_resolution_clock::now();
					
					//----Play bref song----
					Mix_PlayChannel(-1, gMusicBref[0], 0);
				}
			}
		//}
		SDL_Delay(3);
	}
	return 1;
}

int ThreadCollision(void* ptr)
{
	//On traduit le pointeur en GameWorld
	GameWorld *tdata = (GameWorld*)ptr;
	
	//Joueur *MilleniumFalcon;
	//MilleniumFalcon = tdata->AccessPlayerHolder();

	return 1;
}

//----Main----------------------------------------------------------------------------

int main(int argc, char* args[])
{
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

	//----Objet GameWorld et variable pour contenir les adresses de conteneurs---
	WorldRenderer SpaceRenderer(texture, GameSprites, gRenderer);
	GameWorld Space(&SpaceRenderer);	//Contiendra tout nos objets volant du jeu

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

			//Current animation frame
			int frame = 0;

			//Simply create a thread 
			GameWorld *World_ptr = &Space; //On envoie GameWorld en parametre, on devra le traduire 
			                               //avec (GameWorld*)
			
			//----Execute thread---------------------------------------------------------
			//thread[0] = SDL_CreateThread(TieThread, "ThreadTie", World_ptr);
			thread[1] = SDL_CreateThread(TieFactoryThread, "TieFactoryThread", World_ptr);
			thread[2] = SDL_CreateThread(ThreadKeyboard, "ThreadKeyboard", World_ptr);
			thread[3] = SDL_CreateThread(ThreadCollision, "ThreadCollision", World_ptr);
			//---------------------------------------------------------------------------

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
				Main_elapsed = DURATION_IN_MS(std::chrono::high_resolution_clock::now() - Main_Timestamp);

				if (Main_elapsed < Main_interval) {
					SDL_Delay(1);
					//SDL_Delay(DURATION_IN_MS(Main_interval - Main_elapsed).count());
				}

				else {
					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					//Bench pour tester l'interval de temp. Total devrait donner 30 ms +/- 1 ms
					/*end = std::chrono::high_resolution_clock::now();
					double total = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
					start = std::chrono::high_resolution_clock::now();*/

					//SDL_Delay(16);

					Main_Timestamp = std::chrono::high_resolution_clock::now();

					//Clear screen
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(gRenderer);

					//Loops the background and Render texture to screen
					if (T <= gBackgroundTexture.getWidth() + SCREEN_WIDTH) {
						gBackgroundTexture.render(-T, 0);
					}

					if (R >= -SCREEN_WIDTH && R <= gBackground2Texture.getWidth())
						gBackgroundTexture.render(-R, 0);


					if (R == gBackground2Texture.getWidth() - SCREEN_WIDTH && T >= 0)
						T = -SCREEN_WIDTH;

					if (R >= gBackground2Texture.getWidth())
						R = -gBackgroundTexture.getWidth();
					T++;
					R++;

					//----Message----
					TTF_Font* Arial = TTF_OpenFont("./style/Arial.ttf", 12);
					SDL_Color White = { 255, 255, 255 };
					SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Arial, "Score ", White); 
					SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
					SDL_Rect Message_rect; //create a rect
					Message_rect.x = 25;  //controls the rect's x coordinate 
					Message_rect.y = 650; // controls the rect's y coordinte
					Message_rect.w = 75; // controls the width of the rect
					Message_rect.h = 25; // controls the height of the rect
					SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
					//----Message----
					
					//T++;
					//if (T >= gBackgroundTexture.getWidth() - 1200 && R == 0) {
					//	R = -1200;
					//}
					//if (R <= gBackground2Texture.getWidth() - 1200)
					//	gBackground2Texture.render(-R, 0)
					//if (R >= gBackground2Texture.getWidth() && T >= 0) {
					//	T = -1200;
					//	gBackgroundTexture.render(-T, 0);
					//}
					//if (R <= gBackground2Texture.getWidth() - 1200)
					//	R = 1200;
	
					Space.RenderWorld();

					texture[4].render(700, 300);

					//----Sprite----

					//Render current frame
					//SDL_Rect* currentClip = &GameSprites[0].SpriteClips[frame / 7];
						//&gSpriteClips[frame / 5];//speed
					//GameSprites[0].SpriteTexture.renderSprite((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

					//----Sprite----

					////Update screen
					SDL_RenderPresent(gRenderer);
				}
			}
		}
	}
	//Free resources and close SDL
	close();

//	SDL_WaitThread(thread[0], &threadReturnValue[0]); //Wait for the thread to complete.		
	SDL_WaitThread(thread[1], &threadReturnValue[1]); //Wait for the thread to complete.
	SDL_WaitThread(thread[2], &threadReturnValue[2]); //Wait for the thread to complete.
//	SDL_WaitThread(thread[3], &threadReturnValue[3]); //Wait for the thread to complete.

	return 0;
}

//----Fonctions----------------------------------------------------------------------------

//void RenderTextures(LTexture ToRender[], std::list<EntiteVolante>* Generic_AccessKey) {
//	std::list<EntiteVolante>::iterator S = Generic_AccessKey->begin();
//	while (S != Generic_AccessKey->end()) {
//		texture[S->getCategorie()].render(S->getCoordX(), S->getCoordY());
//		S++;
//	}
//}
//
//void RenderTextures(LTexture ToRender[], std::list<vector<EntiteVolante>>* Generic_AccessKey) {
//	std::list<vector<EntiteVolante>>::iterator S = Generic_AccessKey->begin();
//	while (S != Generic_AccessKey->end()) {
//		for (int i = 0; i < S->size(); i++) {
//			texture[(*S)[i].getCategorie()].render((*S)[i].getCoordX(), (*S)[i].getCoordY());
//		}
//		S++;
//	}
//}

#include"loadFromFile.h"

#include"loadtexture.h"

#include"boolinit.h"

#include"loadmedia.h"

#include"close.h"