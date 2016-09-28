#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class aTexture {
public:
	aTexture();
	~aTexture();
	bool loadTexture(SDL_Renderer* renderer, std::string path);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);
	void free();
private:
	int aWidth;
	int aHeight;
	SDL_Texture* texture;
};

class SpriteAnimation {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	const int screenWidth = 640;
	const int screenHeight = 480;
	SDL_Window* aWindow = NULL;
	SDL_Renderer* aRenderer = NULL;
	aTexture spriteTexture;
	SDL_Rect renderClips[4];
};
