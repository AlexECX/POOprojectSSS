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
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;

#include"initialise.h"
#include "Plateau.h"
#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"

#define DURATION_IN_MS(Time_Interval) std::chrono::duration_cast<std::chrono::milliseconds>(Time_Interval)
////#define ENTIEVOLANTE_CAST std::_List_iterator<std::_List_val<std::_List_simple_types<EntiteVolante>>>
//#define GENERIC_KEY Key
//#define ASSIGN_TO_GENERIC_KEY(AccessKey) std::list<EntiteVolante> *GENERIC_KEY = (std::list<EntiteVolante>*)AccessKey;

//---Functions Declarations---
void RenderTextures(LTexture ToRender[], std::list<EntiteVolante>* Generic_AccessKey);

//----------------------------



typedef struct {
	Joueur *PtrJoueur;
} ThreadData;

//----Thread Funtions----------------------------------------------------------------------------

int TestThread(void *ptr)
{
	//On traduit le pointeur en GameWorld
	GameWorld *tdata = (GameWorld*)ptr; 
	//Initialise un Tie Fighter
	//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet

	Ennemis *TieFighter = tdata->AddToGameWorld(Ennemis(ennemis_simple, empire, 500, 250, 1, 0, 0));
	std::list<Joueur>* AccessKey;


	//trucs pour le timer et le deplacement
	auto interval = std::chrono::milliseconds(10);
	std::chrono::milliseconds TieFighterFlightTime;
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();
	auto BeforeUTurn = std::chrono::high_resolution_clock::now();
	int flying = 9000;
	int H = 1;
	////

	while (flying)
	{
		TieFighterFlightTime = DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUpdate);
		
		if (TieFighterFlightTime >= interval) {
			//Ici le thread vas Accede a sont objet dans la liste PlayerHolder the GameWorld

			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			TieFighter->UpdateTrajet(TieFighter->getCoordX() + H, TieFighter->getCoordY());
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)
			BeforeUpdate = std::chrono::high_resolution_clock::now();

			if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - BeforeUTurn) >= interval * 50) {
				H *= -1;
				BeforeUTurn = std::chrono::high_resolution_clock::now();
			}
		}
		else
			SDL_Delay(DURATION_IN_MS(interval - TieFighterFlightTime).count() - 1);

	}

	return 1;
}


//----TieFactoryThread----------------------------------------------------------------

int TieFactoryThread(void *ptr)
{
	//On traduit le pointeur en GameWorld
	GameWorld *tdata = (GameWorld*)ptr;
	return 1;
}


int ThreadKeyboard(void* ptr)
{
	//On traduit le pointeur en GameWorld
	GameWorld *tdata = (GameWorld*)ptr;
	//Initialise un Tie Fighter
	//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet
	Joueur *MilleniumFalcon = tdata->AddToGameWorld(Joueur(joueur, republic, 50, 250, 1, 0, 0));
	list<Joueur>* AccessKey;

	while (true) 
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() - 1, MilleniumFalcon->getCoordY() - 1);
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)
		}

		else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() - 1, MilleniumFalcon->getCoordY() + 1);
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)

			/**
				MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() - 1,
				MilleniumFalcon->getCoordY() + 1);
			/**/
		}

		else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1, MilleniumFalcon->getCoordY() - 1);
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)

			/**
				MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1,
				MilleniumFalcon->getCoordY() - 1);
			/**/

		}

		else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1, MilleniumFalcon->getCoordY() + 1);
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)

			//MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1,
			//	MilleniumFalcon->getCoordY() + 1);

		}

		else if (state[SDL_SCANCODE_DOWN]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX(), MilleniumFalcon->getCoordY() + 1);
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)

			//MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX(),
			//	MilleniumFalcon->getCoordY() + 1);
		}
		else if (state[SDL_SCANCODE_UP]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX(), MilleniumFalcon->getCoordY() - 1);
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)

			//MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX(),
			//	MilleniumFalcon->getCoordY() - 1);

		}
		else if (state[SDL_SCANCODE_RIGHT]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1, MilleniumFalcon->getCoordY());
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)

			//MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() + 1,
			//	MilleniumFalcon->getCoordY());

		}
		else if (state[SDL_SCANCODE_LEFT]) {
			AccessKey = tdata->AccessPlayerHolder(); //RecupÈre une clé d'Accès au bon conteneur
			MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() - 1, MilleniumFalcon->getCoordY());
			tdata->ReleaseContainer(AccessKey);	//libÈre la clé (important)

			//MilleniumFalcon->UpdateTrajet(MilleniumFalcon->getCoordX() - 1,
			//	MilleniumFalcon->getCoordY());
		}
		SDL_Delay(1);
	}
	return 1;
}

//----Main----------------------------------------------------------------------------

int main(int argc, char* args[])
{

	//----Variables pour nos thread-------
	SDL_Thread *thread;
	SDL_Thread *thread2;
	int         threadReturnValue;
	int        threadReturnValue2;
	//------------------------------------

	//------Variables pour la gestion du FPS----------
	/*auto start = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point end;*/
	auto Main_interval = std::chrono::milliseconds(16); //16666666
	auto Main_Timestamp = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds Main_elapsed;
	//------------------------------------------------


	//-Objet GameWorld et variable pour contenir les adresses de conteneurs---
	GameWorld Space;	//Contiendra tout nos objets volant du jeu
	std::list<Joueur>* PlayerHolder_AccessKey;
	std::list<Ennemis>* EnnemieSimple_AccessKey;
	std::list<std::vector<Ennemis>>* EnnemisMultiple_AccessKey;
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

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//On initilise le Faucon.
			//On push un nouvelle objet dans le gameworld, et on reçoit l'adresse de l'objet
			//Joueur *MilleniumFalcon = Space.AddToGameWorld(Joueur(joueur, republic, 50, 250, 1, 0, 0));//Remore = pas affichage falcon
																									   //Le thread ne suffit pas a faire afficher le falcon 
																									  
			/**/
			//printf("\nSimple SDL_CreateThread test:");

			//Simply create a thread 
			GameWorld *World_ptr = &Space; //On envoie GameWorld en parametre, on devra le traduire avec (GameWorld*)
			thread = SDL_CreateThread(TestThread, "TestThread", World_ptr);
			
			thread2 = SDL_CreateThread(ThreadKeyboard, "ThreadKeyboard", World_ptr);

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
					SDL_Delay(DURATION_IN_MS(Main_interval - Main_elapsed).count() - 1);

				}

				//else {

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


					texture[2].render(200, 300);

					texture[3].render(350, 300);

					//Update screen
					SDL_RenderPresent(gRenderer);
				//}

				//----Keyboard detect----

			}
			SDL_WaitThread(thread, &threadReturnValue); //Wait for the thread to complete.		
			SDL_WaitThread(thread2, &threadReturnValue2); //Wait for the thread to complete.
		}
	}

	//Free resources and close SDL

	close();

	return 0;
}

//----Fonctions----------------------------------------------------------------------------

void RenderTextures(LTexture ToRender[], std::list<EntiteVolante>* Generic_AccessKey) {
	std::list<EntiteVolante>::iterator S = Generic_AccessKey->begin();
	while (S != Generic_AccessKey->end()) {
		texture[S->getCategorie()].render(S->getCoordX(), S->getCoordY());
		S++;
	}
}

#include"loadFromFile.h"

#include"loadtexture.h"

#include"boolinit.h"

#include"loadmedia.h"

#include"close.h"