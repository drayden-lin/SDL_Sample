#include "RenderTexture.h"

class Dot{
	public:
		Dot();
		void handleEvent(SDL_Event* event);
		void moveint (maxWidth, int maxHeight);
		void render(RenderTexture* texture, SDL_Renderer* renderer);
		
		setVelocityInterval(int v);
	private:
		int xVelocity, yVelocity;
		int xPosition, yPosition;
		int velocityInterval;
		int dotWidth = 20;
		int dotHeight = 20;
	
};

class Motion{
	public:
		bool Main();
		bool init();
		bool loadMedia();
		void close();
	private:
		const int screenWidth = 640;
		const int screenHeight = 480;
		SDL_Window* mWindow = NULL;
		SDL_Renderer* mRenderer = NULL;
		RenderTexture dotTexture;
};
