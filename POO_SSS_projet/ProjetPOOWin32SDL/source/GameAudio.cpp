#include "GameAudio.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <fstream>
#include <string>
#include <iostream>

std::vector<Mix_Music*> GameAudio::Music;
std::vector<Mix_Chunk*> GameAudio::SFX;

bool GameAudio::AudioSuccess;
bool GameAudio::AudioReady;



GameAudio::GameAudio()
{
	//Initialization flag
	AudioSuccess = true;
	AudioReady = false;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL audio could not initialize! SDL Error: %s\n", SDL_GetError());
		AudioSuccess = false;
	}
	else
	{
		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			AudioSuccess = false;
		}
	}
	
}

bool GameAudio::LoadAudio() {
	if (!AudioReady)
	{
		//----Load music and sound-------------------------------------------------
		std::ifstream File;
		std::string FileName;

		FileName = ".\music\Music_List.txt";
		File.open(FileName.c_str());
		if (File.fail())
			printf("Failed to open ", FileName);
		else
		{
			while (!File.eof()) {
				std::getline(File, FileName);
				Music.push_back(Mix_LoadMUS(FileName.c_str()));
				if (Music.back() == NULL)
				{
					printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
					AudioSuccess = false;
				}
			}
		}
		File.close();

		FileName = ".\music\SFX_List.txt";
		File.open(FileName.c_str());
		if (File.fail())
			printf("Failed to open ", FileName);
		else
		{
			while (!File.eof()) {
				std::getline(File, FileName);
				SFX.push_back(Mix_LoadWAV(FileName.c_str()));
				if (SFX.back() == NULL)
				{
					printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
					AudioSuccess = false;
				}
			}
		}
		File.close();
		//----Load music and end--------------------------------------------------
		if (AudioSuccess)
			AudioReady = true;
	}

	return AudioSuccess;
}


GameAudio::~GameAudio()
{
	for (int i = 0; i < Music.size(); i++) {
		Mix_FreeMusic(Music[i]);
		Music[i] = nullptr;
	}
	for (int i = 0; i < SFX.size(); i++) {
		Mix_FreeChunk(SFX[i]);
		SFX[i] = nullptr;
	}

	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

GameAudio& GameAudio::Get() {
	static GameAudio *audio = &GameMedia::Get();
	return *audio;
}

void GameAudio::PlayMusic(MusicName num)
{
	Mix_PlayMusic(Music[num], -1);
	Mix_ResumeMusic();
}
