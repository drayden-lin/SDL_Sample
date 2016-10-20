#pragma once
#include <SDL.h>
#include <SDL_image.h>

class ViewPort {
public:
	int Main();
	bool init();
	bool loadMedia();
	void close();

private:
	const int screenHeight = 800;
	const int screenWidth = 600;

	SDL_Renderer* vpRenderer = NULL;
	SDL_Window* vpWindow = NULL;
	SDL_Texture* vpTexture = NULL;
	SDL_Surface* vpWindowSurface = NULL;
};