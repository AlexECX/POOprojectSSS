#pragma once
#include "GameMedia.h"
#include <vector>
#include <SDL_mixer.h>

enum SfxName { falcon_fire, tie_fire, tie_explosion };
enum MusicName { background_music};

class GameAudio
{
private:
	GameAudio();
	GameAudio(const GameAudio&) = delete;
	GameAudio(GameAudio&&) = delete;
	void operator=(const GameAudio&) = delete;
	void operator=(GameAudio&&) = delete;

protected:
	static std::vector<Mix_Music*> Music;
	static std::vector<Mix_Chunk*> SFX;

	static bool AudioSuccess;
	static bool AudioReady;
	
public:
	
	~GameAudio();
	static GameAudio& Get();
	bool LoadAudio();
	void PlayMusic(MusicName);
	void PlaySFX(int sound);
};

