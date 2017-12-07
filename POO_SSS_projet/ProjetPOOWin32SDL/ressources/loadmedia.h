#pragma once

bool loadMedia()
{
	//Loading success flag
	bool success = true;

//----Load image----------------------------------------------------------

	if (!texture[0].loadFromFile("./Image/falcon.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!texture[1].loadFromFile("./Image/tiefighter.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!texture[2].loadFromFile("./Image/LaserFriend.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!texture[3].loadFromFile("./Image/LaserEnnemis.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	//Load background texture
	if (!gBackgroundTexture.loadFromFile("./Image/background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

//----Load image----------------------------------------------------------

//----Load music----------------------------------------------------------

	gMusic = Mix_LoadMUS("./Music/BackgroundAsteroidField.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

//----Load music----------------------------------------------------------

	return success;
}