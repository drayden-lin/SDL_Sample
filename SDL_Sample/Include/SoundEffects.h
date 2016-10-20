#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

enum soundFiles {
	SCRATCH,
	HIGH,
	MEDIUM,
	LOW,
	MUSIC
};

class SoundManager {
public:
	bool loadSound();
	void play(int soundfiles);
	void halt();
	void free();
private:
	Mix_Chunk* sHigh = NULL;
	Mix_Chunk* sMedium = NULL;
	Mix_Chunk* sLow = NULL;
	Mix_Chunk* sScratch = NULL;
	Mix_Music* sMusic = NULL;
};

class SoundEffects {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	const int screenWidth = 640;
	const int screenHeight = 480;
	SDL_Window* seWindow;
	SDL_Renderer* seRenderer;
	SDL_Texture* background;
	SoundManager sound;
};