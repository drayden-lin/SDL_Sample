#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class abTexture {
public:
	abTexture();
	~abTexture();
	bool loadTexture(SDL_Renderer* renderer, std::string path);
	void setAlpha(Uint8 alpha);
	void setBlendMode(SDL_BlendMode blending);
	void render(SDL_Renderer* renderer, int x, int y);
	void free();
private:
	int abWidth;
	int abHeight;
	SDL_Texture* texture;
};
class AlphaBlending {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	const int screenWidth = 640;
	const int screenHeight = 480;
	SDL_Window* abWindow = NULL;
	SDL_Renderer* abRenderer = NULL;
	abTexture spriteTexture;
	abTexture backgroundTexture;
};