#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#if 1
enum MouseTexture
{
	MOUSE_OUT,
	MOUSE_OVER,
	MOUSE_DOWN,
	MOUSE_UP,
	TOTAL_SPRITE
};

class spriteTexture {
public:
	spriteTexture();
	~spriteTexture();
	bool loadTexture(SDL_Renderer* renderer, std::string path);
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip);
	void free();
    int getWidth();
    int getHeight();
private:
	int spriteWidth;
	int spriteHeight;
	SDL_Texture* texture;
};
class screenButton {
public:
	screenButton();
	void handleEvent(SDL_Event* event);
	void render(spriteTexture* texture, SDL_Renderer* renderer, SDL_Rect spriteClip[]);
	void setPosition(int x, int y);
	int getButtonWidth();
	int getButtonHeight();
private:
	int buttonWidth = 300;
	int buttonHeight = 200;
	SDL_Point position;
	MouseTexture currentTexture;
};
class MouseEvent {
public:
	bool Main();
	bool init();
	bool loadMedia();
	void close();
private:
	const int screenWidth = 640;
	const int screenHeight = 480;
	const int buttonNumber = 4;
	SDL_Window* meWindow;
	SDL_Renderer* meRenderer;
	SDL_Rect spriteClip[TOTAL_SPRITE];
	screenButton meButton[TOTAL_SPRITE];
	spriteTexture meTexture;
};
#endif
