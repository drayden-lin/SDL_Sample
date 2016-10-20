#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class rtTexture {
public:
	rtTexture();
	~rtTexture();
	bool loadTexture(SDL_Renderer* renderer, std::string path);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();
	int getWidth();
	int getHeight();
private:
	int rtWidth;
	int rtHeight;
	SDL_Texture* texture;
};

class RotationFlipping {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	SDL_Window* rtWindow = NULL;
	SDL_Renderer* rtRenderer = NULL;
	const int screenWidth = 640;
	const int screenHeight = 480;
	rtTexture spriteTexture;
};
