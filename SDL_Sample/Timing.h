#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

class textTexture {
public:
	textTexture();
	~textTexture();
	bool putStringInTexture(SDL_Renderer* renderer, SDL_Font* font, SDL_Color textColor);
	void render(SDL_Renderer* renderer, int x, int y);
	void free();
	int getWidth();
	int getHeight();
	void setText(std::string text);
private:
	int ttWidth;
	int ttHeight;
	SDL_Texture* texture;
	std::string textString;
};

class Timing {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	const int screenWidth = 640;
	const int screenHeight = 480;
	SDL_Window* tWindow;
	SDL_Renderer* tRenderer;
	SDL_Font* tFont;
	textTexture textSprite;
	textTexture prompt;
};