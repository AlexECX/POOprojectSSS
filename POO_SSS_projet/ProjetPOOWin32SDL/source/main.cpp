//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
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
#include"initialise.h"
#include "Plateau.h"
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

//---Functions Declarations---
//void RenderTextures(LTexture ToRender[], std::list<EntiteVolante>* Generic_AccessKey);
//void RenderTextures(LTexture ToRender[], std::list<vector<EntiteVolante>>* Generic_AccessKey);

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

//----TieFactoryThread----------------------------------------------------------------

int TieFactoryThread(void *ptr)
{
	//On traduit le pointeur en GameWorld
	//vector<SDL_Thread*> TieTH;
	vector<CEsquadronTie*> Vagues;
	//int TieReturnValue;
	GameWorld *tdata = (GameWorld*)ptr;
	vector<Ennemis> Recrus;

	while (!quit) {
		SDL_Delay(5000);
		vector<Ennemis> Recrus;
		for (int i = 0; i < 5; i++) {
			Recrus.push_back(Ennemis(ennemis_simple, empire, 1100 + (rand() % 4 * 50), (i*100) + 50, 1, 0, 0));
		}
		CEsquadronTie* temp = new CEsquadronTie(Recrus);
		Vagues.push_back(tdata->AddToGameWorld(*temp));
			
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
	//Initialise un Falcon
	//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet
	Joueur *MilleniumFalcon = new Joueur(joueur, republic, 50, 250, 1, 0, 0);
	MilleniumFalcon = tdata->AddToGameWorld(*MilleniumFalcon);
	list<Joueur>* AccessKey;

	auto interval = std::chrono::milliseconds(2000);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (!quit) 
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_Q]) {
			SDL_Event user_event;
			user_event.type = SDL_QUIT;
			SDL_PushEvent(&user_event);
		}

		if (state[SDL_SCANCODE_SPACE])
		{
			if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate) >= interval)
			{
				Projectile* Tir = new Projectile(tir_joueur, republic, MilleniumFalcon->getCoordX() + 150, MilleniumFalcon->getCoordY() + 65, 1, 0, 0);
				Tir = tdata->AddToGameWorld(*Tir);
				BeforeUpdate = std::chrono::high_resolution_clock::now();
			}
			
		}

		if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) 
		{
			MilleniumFalcon->MouvUpLeft();
		}

		else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) 
		{
			MilleniumFalcon->MouvDownLeft();
		}

		else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) 
		{
			MilleniumFalcon->MouvUpRight();
		}

		else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) 
		{
			MilleniumFalcon->MouvDownRight();
		}

		else if (state[SDL_SCANCODE_DOWN]) 
		{
			MilleniumFalcon->MouvDown();
		}
		else if (state[SDL_SCANCODE_UP]) 
		{
			MilleniumFalcon->MouvUp();
		}
		else if (state[SDL_SCANCODE_RIGHT]) 
		{
			MilleniumFalcon->MouvRight();
		}
		else if (state[SDL_SCANCODE_LEFT]) 
		{
			MilleniumFalcon->MouvLeft();
		}

		SDL_Delay(3);
	}
	return 1;
}

//----Main----------------------------------------------------------------------------

int main(int argc, char* args[])
{
	//----Variables pour nos thread-------
	SDL_Thread *thread1;
	SDL_Thread *thread2;
	SDL_Thread *thread[10];

	int         threadReturnValue;
	int         threadReturnValue2;
	//------------------------------------

	//----Variables pour la gestion du FPS----------
	/*auto start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end;*/
	auto Main_interval = std::chrono::milliseconds(16); //16666666
	auto Main_Timestamp = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds Main_elapsed;
	//------------------------------------------------

	//----Objet GameWorld et variable pour contenir les adresses de conteneurs---
	//WorldRenderer SpaceRenderer(texture, GameSprites);
	GameWorld Space;// (&SpaceRenderer);	//Contiendra tout nos objets volant du jeu
	 
	//std::list<Joueur>* PlayerHolder_AccessKey;
	//std::list<Ennemis>* EnnemieSimple_AccessKey;
//	std::list<std::vector<Ennemis>>* EnnemisMultiple_AccessKey;
	//------------------------------------------------------------------------

	/*if (NULL == thread) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}*/

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
			Mix_PlayMusic(gMusic, -1);
			Mix_ResumeMusic();

			//Current animation frame
			int frame = 0;

			//On initilise le Faucon.
			//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet

			//printf("\nSimple SDL_CreateThread test:");

			//Simply create a thread 
			GameWorld *World_ptr = &Space; //On envoie GameWorld en parametre, on devra le traduire avec (GameWorld*)
			
			//----Execute thread---------------------------------------------------------
			thread[0] = SDL_CreateThread(TieFactoryThread, "TieFactoryThread", World_ptr);
			thread[1] = SDL_CreateThread(ThreadKeyboard, "ThreadKeyboard", World_ptr);
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

					//Render background texture to screen
					gBackgroundTexture.render(0, 0);

					//Astuce: les methodes "Access_______()" the GameWorld retourne en fait l'adresse du conteneur, 
					//apres l'avoir locké. Tu peux donc itérer dessus si nécessaire


					Space.RenderWorld(texture);

					/**Alternate Render Method//////

					//Render le Joueur
					PlayerHolder_AccessKey = Space.AccessPlayerHolder();	//On reclame un acces au conteneur
					//Ici on itere sur le conteneur PlayerHolder pour render tout les objets qu'il contient
					RenderTextures(texture, (std::list<EntiteVolante>*)PlayerHolder_AccessKey);
					Space.ReleaseContainer(PlayerHolder_AccessKey);	//Ne pas oublier de relacher le conteneur

					//Render les ennemis simple
					EnnemieSimple_AccessKey = Space.AccessEnnemieSimple();
					//Ici on itere sur le conteneur PlayerHolder pour render tout les objets qu'il contient
					RenderTextures(texture, (std::list<EntiteVolante>*)EnnemieSimple_AccessKey);
					Space.ReleaseContainer(EnnemieSimple_AccessKey);	//Ne pas oublier de relacher le conteneur


					EnnemisMultiple_AccessKey = Space.AccessEnnemisMultiple();
					RenderTextures(texture, (std::list <vector<EntiteVolante>> *)EnnemisMultiple_AccessKey);
					Space.ReleaseContainer(EnnemisMultiple_AccessKey);

					/**/////////////////////////////

					texture[2].render(200, 300);

					texture[3].render(350, 300);

					texture[4].render(700, 300);

					//----Sprite----

					//Render current frame
					SDL_Rect* currentClip = &GameSprites[0].SpriteClips[frame / 5];
						//&gSpriteClips[frame / 5];//speed
					GameSprites[0].SpriteTexture.renderSprite((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

					//----Sprite----

					//Update screen
					SDL_RenderPresent(gRenderer);

					//}

						//----Sprite----

						//Go to next frame
					++frame;

					//Cycle animation
					if (frame / 9 >= 9)
					{
						frame = 0;
					}

					//----Sprite----
				}
			}
			SDL_WaitThread(thread[0], &threadReturnValue); //Wait for the thread to complete.		
			SDL_WaitThread(thread[1], &threadReturnValue2); //Wait for the thread to complete.

		}
	}

	//Free resources and close SDL

	close();

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