#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class Ltexture {
public:
	bool loadTexture(SDL_Renderer* renderer, std::string path);
	bool render(SDL_Renderer* renderer, int x, int y);
	void free();

private:
	int tWidth = 0;
	int tHeight = 0;

	SDL_Texture* tTexture = NULL;

};

class ColorKeying {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();

	const int screenHeight = 600;
	const int screenWidth = 800;

	Ltexture* backgroundTexture;
	Ltexture* fooTexture;

	SDL_Renderer* tRenderer = NULL;
	SDL_Surface* tSurface = NULL;
	SDL_Window* tWindow = NULL;

};

