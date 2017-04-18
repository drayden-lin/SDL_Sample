#pragma once
#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

class Determination {
public:
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 600;
	//const int DELAY = 1000;

	int Main();
	bool init();
	bool loadMedia();
	void close();
	SDL_Surface* loadMediaSurface(std::string path);
	int getNext();

private:
	SDL_Window* window = NULL;
	SDL_Surface* windowSurface = NULL;
	SDL_Surface* imageSurface = NULL;
	SDL_Surface* pressedSurface[91];
};
