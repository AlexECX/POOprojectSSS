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

#include "../ressources/LTexture.h"
#include "..\ressources\LSprite.h"
#include "GameMedia.h"
#include "WorldRenderer.h"
//#include "initialise.h"
#include "GameWorld.h"

#include "EntiteVolante.h"
#include "Joueur.h"
#include "Ennemis.h"
#include "EsquadronTie.h"
#include "Projectile.h"

#define DURATION_IN_MS(Time_Interval) std::chrono::\
        duration_cast<std::chrono::milliseconds>(Time_Interval)\


//Globally used font
TTF_Font *gFont = NULL;
TTF_Font* Arial = TTF_OpenFont("./style/Arial.ttf", 12);
//Scene Texte
LTexture gPromptTextTexture;

//The music that will be played
Mix_Music *gMusic = NULL;

//The bref song that will be played

Mix_Chunk *gMusicBref[10];

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
	//On traduit le pointeur en GameWorld
	vector<CEsquadronTie*> Vagues;
	vector<Ennemis> Recrus;

	while (!quit) {
		SDL_Delay(5000);
		vector<Ennemis> Recrus;
		for (int i = 0; i < 6; i++) {
			Recrus.push_back(Ennemis(ennemis_simple, empire, 
				             1100 + (rand() % 4 * 50), 
				             (i *100) + 50, 1, 0, 0));
		}
		CEsquadronTie* temp = new CEsquadronTie(Recrus);
		GameWorld::AddToGameWorld(temp);
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
	//On push un nouvelle objet dans le gameworld, et on re�oit l'adresse de 
	//l'objet
	Joueur *MilleniumFalcon = new Joueur(joueur, republic, 50, 250, 1, 0, 0);
	MilleniumFalcon = GameWorld::AddToGameWorld(MilleniumFalcon);
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
				if (DURATION_IN_MS(std::chrono::high_resolution_clock::now()
												- BeforeUpdate) >= interval)
				{
					Projectile* Tir = new Projectile(tir_joueur, republic,
						MilleniumFalcon->getCoordX() + 150,
						MilleniumFalcon->getCoordY() + 65,
						1, 10, 0);
					Tir = GameWorld::AddToGameWorld(Tir);
					BeforeUpdate = std::chrono::high_resolution_clock::now();
					
					//----Play bref song----
					Mix_PlayChannel(-1, gMusicBref[0], 0);
				}
			}
		}
		SDL_Delay(3);
	}
	return 1;
}

//----Main-----------------------------------------------------------
void close();

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

	//----Objet GameWorld et variable pour contenir les adresses 
	//----de conteneurs
	//Englobe toute les textures, animation et le SDL renderer
	//GameWorld contiendra des pointeurs sur tout nos objets volant du jeu. 
	//On lui passe ici l'adresse du Renderer
	
	
	int BackgroundMusic = true;

	//Start up SDL and create window
	if (!GameMedia::Initialise())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!GameMedia::LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//The current input text.
			string inputText = "Some Text";

			Mix_PlayMusic(GameMedia::Music, -1);
			Mix_ResumeMusic();

			//----Execute thread---------------------------------------------
			thread[1] = SDL_CreateThread(TieFactoryThread, "TieFactoryThread", ((void*)1));
				                         
			thread[2] = SDL_CreateThread(ThreadKeyboard, "ThreadKeyboard", ((void*)1));
				                         

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

					//Bench pour tester l'interval de temp. Total devrait 
					//donner 16 ms +/- 1 ms
					//end = std::chrono::high_resolution_clock::now();
					//double total = std::chrono::duration_cast<std::chrono::
					//nanoseconds>(end - start).count();
					//start = std::chrono::high_resolution_clock::now();


					//SDL_Delay(16);

					Main_Timestamp = std::chrono::
						             high_resolution_clock::now();

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
					
					//----Message----
					//string score = to_string(GameWorld::GameScore());
					//TTF_Font* Arial = TTF_OpenFont("./style/Arial.ttf", 12);
					//SDL_Color White = { 255, 255, 255 };
					//SDL_Surface* surfaceMessage = TTF_RenderText_Solid
					//(Arial, ("Score "+ score).c_str(), White); 
					//SDL_Texture* Message = SDL_CreateTextureFromSurface
					//(gRenderer, surfaceMessage);
					//SDL_Rect Message_rect; //create a rect
					//Message_rect.x = 25;  //controls the rect's x coordinate 
					//Message_rect.y = 650; // controls the rect's y coordinte
					//Message_rect.w = 75; // controls the width of the rect
					//Message_rect.h = 25; // controls the height of the rect
					//SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
					//----Message----

					GameWorld::RenderWorld();

					WorldRenderer::Render(WorldRenderer::Textures[0], 150, 150);

					//GameMedia::texture[4].render(700, 300);

					
				}
			}
		}
	}
	//Free resources and close SDL
	close();
	GameMedia::Close();
	//Wait for the thread to complete.
	SDL_WaitThread(thread[1], &threadReturnValue[1]); 
	SDL_WaitThread(thread[2], &threadReturnValue[2]);
	GameWorld::DeleteGameWorld();
	return 0;
}

void close()
{
	//Free loaded images
	//GameSprites[0].SpriteTexture.free();

	////Free loaded images
	//texture[0].free();
	//texture[1].free();
	//texture[2].free();
	//texture[3].free();
	//gBackgroundTexture.free();
	//gBackground2Texture.free();

	//Free loaded images
	gPromptTextTexture.free();

	//Free global font
	TTF_CloseFont(Arial);
	gFont = NULL;

	//Free the music
	Mix_FreeMusic(GameMedia::Music);
	GameMedia::Music = NULL;

	Mix_FreeChunk(GameMedia::SFX[0]);
	Mix_FreeChunk(GameMedia::SFX[1]);
	Mix_FreeChunk(GameMedia::SFX[2]);
	GameMedia::SFX[0] = NULL;
	GameMedia::SFX[1] = NULL;
	GameMedia::SFX[2] = NULL;

	//Destroy window	
	/*SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;*/

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

//#include"loadFromFile.h"
//
//#include"loadtexture.h"
//
//#include"boolinit.h"
//
//#include"loadmedia.h"

