#pragma once
#include "GameMedia.h"
#include <SDL_ttf.h>
#include <vector>

//enum FontName { arial };

class GameText
{
private:
	GameText();
	GameText(const GameText&) = delete;
	GameText(GameText&&) = delete;
	void operator=(const GameText&) = delete;
	void operator=(GameText&&) = delete;

protected:
	static bool TextSuccess;
	static bool TextReady;

public:
	~GameText();
	static GameText& Get();
	virtual bool LoadFonts() = 0;
};

