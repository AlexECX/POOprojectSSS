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

	if (!texture[4].loadFromFile("./Image/Asteroid.png"))
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

//----Load sprite----------------------------------------------------------

//Load sprite sheet texture
	if (!GameSprites[0].SpriteTexture.loadFromFile("./Image/Explosion.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		
		//GameSprites[0].SpriteClips = &gSpriteClips[9];
		//Set sprite clips

		//----Ligne 1:----

		gSpriteClips[0].x = 10;
		gSpriteClips[0].y = 10;
		gSpriteClips[0].w = 60;
		gSpriteClips[0].h = 60;

		gSpriteClips[1].x = 75;
		gSpriteClips[1].y = 10;
		gSpriteClips[1].w = 60;
		gSpriteClips[1].h = 60;

		gSpriteClips[2].x = 150;
		gSpriteClips[2].y = 10;
		gSpriteClips[2].w = 60;
		gSpriteClips[2].h = 60;

		//----Ligne 2:----

		gSpriteClips[3].x = 10;
		gSpriteClips[3].y = 75;
		gSpriteClips[3].w = 60;
		gSpriteClips[3].h = 60;

		gSpriteClips[4].x = 75;
		gSpriteClips[4].y = 75;
		gSpriteClips[4].w = 60;
		gSpriteClips[4].h = 60;

		gSpriteClips[5].x = 150;
		gSpriteClips[5].y = 75;
		gSpriteClips[5].w = 60;
		gSpriteClips[5].h = 60;

		//----Ligne 3:----

		gSpriteClips[6].x = 10;
		gSpriteClips[6].y = 150;
		gSpriteClips[6].w = 60;
		gSpriteClips[6].h = 60;

		gSpriteClips[7].x = 75;
		gSpriteClips[7].y = 150;
		gSpriteClips[7].w = 60;
		gSpriteClips[7].h = 60;

		gSpriteClips[8].x = 150;
		gSpriteClips[8].y = 150;
		gSpriteClips[8].w = 60;
		gSpriteClips[8].h = 60;

		GameSprites[0].SpriteClips = gSpriteClips;
	}

//----Load sprite----------------------------------------------------------

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