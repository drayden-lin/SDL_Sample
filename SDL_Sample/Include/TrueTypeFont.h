#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class fontTexture {
public:
	fontTexture();
	~fontTexture();
	bool loadFontTexture(SDL_Renderer* renderer, TTF_Font* font, std::string str, SDL_Color textColor);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);
	void free();
	int getWidth();
	int getHeight();
private:
	int ftWidth;
	int ftHeight;
	SDL_Texture* texture;
};

class TrueTypeFont {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	SDL_Window* ttfWindow;
	SDL_Renderer* ttfRenderer;
	const int screenWidth = 640;
	const int screenHeight = 480;
	TTF_Font* font = NULL;
	fontTexture ftTexture;
};