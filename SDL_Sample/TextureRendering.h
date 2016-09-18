#pragma once
#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class TextureRandering{
public:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	int Main();
	bool init();
	bool loadMedia();
	void close();

private:
	SDL_Texture* surfaceTexture = NULL;
	SDL_Window* window = NULL;
	SDL_Surface* windowSurface = NULL;
	SDL_Surface* imageSurface = NULL;

	SDL_Renderer* textureRender = NULL;

	SDL_Texture* loadMediaTexture(std::string path);
};