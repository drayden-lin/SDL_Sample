#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class CTexture {
public:
	CTexture();
	~CTexture();
	bool loadTexture(SDL_Renderer* r, std::string path);
	bool render(SDL_Renderer* r,  int x, int y, SDL_Rect* clip);
	void free();
private:
	SDL_Texture* cTexture = NULL;
	int tHeight;
	int tWidth;
};


class ClipRendering {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();

private:
	SDL_Window* cWindow = NULL;
	SDL_Renderer* cRenderer = NULL;
	SDL_Rect spriteClips[4];
	CTexture spriteTexture;

	const int screenWidth = 640;
	const int screenHeight = 480;
};