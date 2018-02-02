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
#include <memory>
#include <queue>

using namespace std;

//#include "GameGraphics.h"
//#include "GameAudio.h"
//#include "GameText.h"
#include "GameMedia.h"
#include "GameWorld.h"
#include "..\ressources\CPointerWraper.h"

#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"

#define DURATION_IN_MS(Time_Interval) std::chrono::\
        duration_cast<std::chrono::milliseconds>(Time_Interval)\

//Event handler
SDL_Event e;

//Main loop flag
bool quit = false;

typedef struct {
	void *data1;
	void *data2;
	void *data3;
} ThreadData;


//----TieFactoryThread-----------------------------------------

int TieFactoryThread(void *ptr)
{
	queue<CEsquadronTie> Vagues;
	vector<std::shared_ptr<Ennemis>> Recrus;

	while (!quit) {
		Recrus.clear();
		for (int i = 0; i < 6 && !quit; i++) {
			SDL_Delay(1000);
			Recrus.push_back(GameWorld::Get().AddToGameWorld(new Ennemis(empire, 
				             1300 + (rand() % 4 * 50), 
				             (i *100) + 50)));
		}
		if (!quit) {
			Vagues.push(CEsquadronTie(Recrus));
			Vagues.back().MakeFly();
			if (!Vagues.front().isAlive())
				Vagues.pop();
		}	
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
	std::shared_ptr<Joueur> MilleniumFalcon = GameWorld::Get().AddToGameWorld(new Joueur(republic, 100, 350));
	auto interval = std::chrono::milliseconds(500);
	auto BeforeUpdate = std::chrono::high_resolution_clock::now();

	while (!quit) 
	{
		int NextX = 0, NextY = 0;
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_Q]) {
				SDL_Event user_event;
				user_event.type = SDL_QUIT;
				SDL_PushEvent(&user_event);
		}

		if (CheckUpFirst) {
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN])
				MilleniumFalcon->UpdateTrajet(0,-1);
			//MilleniumFalcon->MouvUp();
			else
				if (state[SDL_SCANCODE_UP]) {
					MilleniumFalcon->UpdateTrajet(0,-1);
					//MilleniumFalcon->MouvUp();
					CheckUpFirst = false;
				}
				else
					if (state[SDL_SCANCODE_DOWN])
						MilleniumFalcon->UpdateTrajet(0,1);
			//MilleniumFalcon->MouvDown();
		}
		else
			if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_DOWN])
				MilleniumFalcon->UpdateTrajet(0,1);
		//MilleniumFalcon->MouvDown();
			else
				if (state[SDL_SCANCODE_DOWN]) {
					MilleniumFalcon->UpdateTrajet(0,1);
					//MilleniumFalcon->MouvDown();
					CheckUpFirst = true;
				}
				else
					if (state[SDL_SCANCODE_UP])
						MilleniumFalcon->UpdateTrajet(0,-1);
					//MilleniumFalcon->MouvUp();

		if (CheckRightFirst) {
			if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT])
				MilleniumFalcon->UpdateTrajet(1,0);
			//MilleniumFalcon->MouvRight();
			else
				if (state[SDL_SCANCODE_RIGHT]) {
					MilleniumFalcon->UpdateTrajet(1,0);
					//MilleniumFalcon->MouvRight();
					CheckRightFirst = false;
				}
				else
					if (state[SDL_SCANCODE_LEFT])
						MilleniumFalcon->UpdateTrajet(-1,0);
			//MilleniumFalcon->MouvLeft();
		}
		else
			if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_LEFT])
				MilleniumFalcon->UpdateTrajet(-1,0);
				//MilleniumFalcon->MouvLeft();
			else
				if (state[SDL_SCANCODE_LEFT]) {
					MilleniumFalcon->UpdateTrajet(-1,0);
					//MilleniumFalcon->MouvLeft();
					CheckRightFirst = true;
				}
				else
					if (state[SDL_SCANCODE_RIGHT])
						MilleniumFalcon->UpdateTrajet(1,0);
						//MilleniumFalcon->MouvRight();
		

		if (state[SDL_SCANCODE_W])
		{
			if (DURATION_IN_MS(std::chrono::high_resolution_clock::now() - 
				BeforeUpdate) >= interval)
			{
				if (DURATION_IN_MS(std::chrono::high_resolution_clock::now()
												- BeforeUpdate) >= interval)
				{
					
					std::shared_ptr<Projectile> Tir = GameWorld::Get().AddToGameWorld(new Projectile(republic,
																MilleniumFalcon->getCoordX() + 138 / 2,
																MilleniumFalcon->getCoordY()
																));
					BeforeUpdate = std::chrono::high_resolution_clock::now();
					
					//----Play bref song----
					GameMedia::PlaySFX(falcon_fire);
				}
			}
		}
		SDL_Delay(3);
	}
	return 1;
}


//----Main-----------------------------------------------------------
int main(int argc, char* args[])
{
	//----Variables pour la gestion du FPS----------
	//std::chrono::steady_clock::time_point end;
	auto Main_interval = std::chrono::milliseconds(16); //16666666
	auto Main_Timestamp = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds Main_elapsed;
	//------------------------------------------------

	//GameMedia a acces a tous les suport media du jeux

	//GameWorld contiendra des pointeurs sur tout nos objets volant du jeu. 
	
	bool success = true;

	GameMedia::Initialise();
	success = GameMedia::LoadAudio();
	success = GameMedia::LoadGraphics();
	success = GameMedia::LoadFonts();

	//Start up SDL and create window
	if (!success)
	{
		printf("Failed to initialize!\n");
	}
	else
	{
			//----Start Game music-------------------------------------------
			GameMedia::PlayMusic(background_music);

			//----Execute thread---------------------------------------------
			//GameWorld::AddThread(GameWorld::ReaperThread,1);
			//GameWorld::Get().AddThread(GameWorld::Get().RenderingThread,"RenderingThread", 1);
			//GameWorld::AddThread(GameWorld::ColisionThread, "ColisionThread", 1);
			GameWorld::Get().AddThread(TieFactoryThread, "TieFactoryThread", 1);
			GameWorld::Get().AddThread(ThreadKeyboard, "ThreadKeyboard", 1);

		
			//int T = 0;
			//int R = -GameMedia::Textures[5].getWidth();

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

				//GameWorld::RenderWorld();
				SDL_Delay(3);
				/*Main_elapsed = DURATION_IN_MS(std::chrono::
					           high_resolution_clock::now() - 
					           Main_Timestamp);
					Main_Timestamp = std::chrono::high_resolution_clock::now();
*/
					//Loops the background and Render texture to screen
					/*if (T <= GameMedia::texture[5].getWidth() + SCREEN_WIDTH) {
						gBackgroundTexture.render(-T, 0);
					}

					if (R >= -SCREEN_WIDTH && R <= GameMedia::texture[6]
																.getWidth())
						GameMedia::texture[5].render(-R, 0);


					if (R == GameMedia::texture[6].getWidth() -
						SCREEN_WIDTH && T >= 0)
						T = -SCREEN_WIDTH;

					if (R >= GameMedia::texture[6].getWidth())
						R = -GameMedia::texture[5].getWidth();
					T++;
					R++;*/

				//}
		}
	}
	//Free resources and close SDL
	//GameMedia::Close();
	//For now, wait on threads completion
	//GameWorld::DeleteGameWorld();

	return 0;
}