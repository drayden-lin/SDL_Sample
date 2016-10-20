#include "RenderTexture.h"
#include "Timer.h"
#include <sstream>

class Framerate{
	public:
		bool init();
		bool loadMedia();
		void close();
		bool Main();
	private:
		const int screenWidth = 640;
		const int screenHeight = 480;
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Timer timer;
		RenderTexture texture;
};