#pragma once
#include <vector>

struct LSprite {
	LTexture SpriteTexture;
	std::vector<SDL_Rect> SpriteClips;
	//SDL_Rect *SpriteClips;
	int CurrentFrame;
	int TotalFrames;
	int OnScreenX;
	int OnScreenY;
};