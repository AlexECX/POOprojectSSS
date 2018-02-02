#include "GameText.h"

std::vector<TTF_Font*> GameText::Fonts;

bool GameText::TextSuccess;
bool GameText::TextReady;



GameText::GameText()
{
	TextSuccess = true;
	TextReady = false;
	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		TextSuccess = false;
	}
}


GameText::~GameText()
{
	//Free fonts from memory
	for (int i = 0; i < Fonts.size(); i++) {
		TTF_CloseFont(Fonts[i]);
		Fonts[i] = nullptr;
	}

	TTF_Quit();
}

GameText & GameText::Get()
{
	static GameText *text = &GameMedia::Get();
	return *text;
}

bool GameText::LoadFonts()
{
	if (!TextReady)
	{
		//Arial
		Fonts.push_back(TTF_OpenFont("./style/Arial.ttf", 12));
		if (Fonts.back() == nullptr)
		{
			printf("Failed to load Arial font!\n");
			TextSuccess = false;
		}

		if (TextSuccess)
			TextReady = true;
	}
	

	return TextSuccess;
}
