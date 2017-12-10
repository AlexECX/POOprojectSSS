#pragma once

struct LSprite {
	LTexture SpriteTexture;
	SDL_Rect *SpriteClips;
	int CurrentFrame;
	int TotalFrames;
	int OnScreenX;
	int OnScreenY;
};