#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class cmTexture {
public:
	cmTexture();
	~cmTexture();
	bool loadTexture(SDL_Renderer* renderer, std::string path);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void render(SDL_Renderer* renderer, int x, int y);
	void free();
private:
	int cmWidth;
	int cmHeight;
	SDL_Texture* texture;
};

class ColorModulation {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	SDL_Window* cmWindow = NULL;
	SDL_Renderer* cmRenderer = NULL;
	const int screenWidth = 640;
	const int screenHeight = 480;
	cmTexture spriteTexture;
};