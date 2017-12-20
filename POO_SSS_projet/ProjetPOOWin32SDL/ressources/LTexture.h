#pragma once

#include "SDL_render.h"
#include <string>

//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();
	LTexture(SDL_Texture*, int, int);

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	//bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Gets image dimensions
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }
	SDL_Texture* getTexture() { return mTexture; }
	//void operator = (SDL_Texture* pointer) {
	//	if (pointer != NULL)
	//		mTexture = pointer;
	//}
	void AssignTexture(SDL_Texture* newTexture, int newWidth, int newHeight);
private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

