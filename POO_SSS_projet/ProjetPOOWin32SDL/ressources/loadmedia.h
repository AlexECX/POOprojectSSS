#pragma once

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	if (!gFooTexture.loadFromFile("./Image/falcon.png"))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	if (!gFooTexture2.loadFromFile("./Image/tiefighter.png"))
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