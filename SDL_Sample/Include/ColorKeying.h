#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class Ltexture {
public:
	Ltexture();
	bool loadTexture(SDL_Renderer* renderer, std::string path);
	bool render(SDL_Renderer* renderer, int x, int y);
	void free();

	int tWidth;
	int tHeight;

	SDL_Texture* tTexture;

};

class ColorKeying {


public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();

	const int screenHeight = 480;
	const int screenWidth = 640;

	Ltexture backgroundTexture;
	Ltexture fooTexture;

	SDL_Renderer* tRenderer = NULL;
	SDL_Surface* tSurface = NULL;
	SDL_Window* tWindow = NULL;

};

