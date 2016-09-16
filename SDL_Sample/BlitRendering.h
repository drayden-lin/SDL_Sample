#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int blitMain();
bool init();
bool loadMedia();
void close();
SDL_Surface* loadPNGSurface(std::string path);
SDL_Surface* loadMediaSurface(std::string path);

enum keyPressed {
	KEYPRESSED_DEFAULT,
	KEYPRESSED_UP,
	KEYPRESSED_DOWN,
	KEYPRESSED_LEFT,
	KEYPRESSED_RIGHT,
	KEYPRESSED_TOTAL
};


