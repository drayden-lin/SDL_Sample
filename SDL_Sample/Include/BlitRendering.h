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
	void firstThree();
	int getNext();
	int printResult(int keyPressed);

private:
	enum keyPressed {
		DEFAULT,
		KEYPRESSED_1,
		KEYPRESSED_2,
		KEYPRESSED_3,
		KEYPRESSED_4,
		KEYPRESSED_5,
		KEYPRESSED_6,
		KEYPRESSED_7,
		KEYPRESSED_8,
		KEYPRESSED_TOTAL
	};
	SDL_Window* window = NULL;
	SDL_Surface* windowSurface = NULL;
	SDL_Surface* imageSurface = NULL;
	SDL_Surface* pressedSurface[KEYPRESSED_TOTAL];
	const int length = 3;
	int arr[3];
	int pos;
};
