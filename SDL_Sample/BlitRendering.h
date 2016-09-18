#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class BlitRendering{
public:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	int Main();
	bool init();
	bool loadMedia();
	void close();
	SDL_Surface* loadPNGSurface(std::string path);
	SDL_Surface* loadMediaSurface(std::string path);

private:
	enum keyPressed {
		KEYPRESSED_DEFAULT,
		KEYPRESSED_UP,
		KEYPRESSED_DOWN,
		KEYPRESSED_LEFT,
		KEYPRESSED_RIGHT,
		KEYPRESSED_TOTAL
	};
	SDL_Window* window = NULL;
	SDL_Surface* windowSurface = NULL;
	SDL_Surface* imageSurface = NULL;
	SDL_Surface* pressedSurface[KEYPRESSED_TOTAL];

};
