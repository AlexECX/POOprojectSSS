#pragma once

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
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

	//Load background texture
	if (!gBackgroundTexture.loadFromFile("./Image/background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	return success;
}