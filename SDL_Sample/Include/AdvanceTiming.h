#include "RenderTexture.h"
#include "Timer.h"
#include <sstream>

class AdvanceTiming{
	public:
		bool init();
		bool loadMedia();
		void close();
		bool Main();
	private:
		const int screenWidth();
		const int screenHeight();
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
		Timer timer;
		RenderTexture texture;
		RenderTexture prompt;
};