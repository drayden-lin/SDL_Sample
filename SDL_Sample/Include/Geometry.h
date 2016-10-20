#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Geometry {
public:
	bool init();
	void close();
	int Main();


private:
	int screenHeight = 600;
	int screenWidth = 800;
	SDL_Surface* gSurface = NULL;
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
};