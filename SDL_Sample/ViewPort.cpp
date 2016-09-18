#include "ViewPort.h"

	int ViewPort::Main() {
		if (!init())return -1;
		if (!loadMedia())return -1;

		SDL_Event ev;
		bool quit = false;

		//Set up viewports
		SDL_Rect topLeftViewport = {0, 0, screenWidth/2, screenHeight/2};
		SDL_Rect topRightViewport = { screenWidth / 2, 0, screenWidth / 2, screenHeight / 2 };
		SDL_Rect bottomViewport = { 0, screenHeight / 2 , screenWidth,  screenHeight / 2 };

		while (!quit) {
			while (SDL_PollEvent(&ev) != 0) {
				if (ev.type == SDL_QUIT) {
					quit = true;
				}
			}
			SDL_RenderClear(vpRenderer);

			//for each viewport, we do setViewport and RenderCopy
			SDL_RenderSetViewport(vpRenderer, &topLeftViewport);
			SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);

			SDL_RenderSetViewport(vpRenderer, &topRightViewport);
			SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);

			SDL_RenderSetViewport(vpRenderer, &bottomViewport);
			SDL_RenderCopy(vpRenderer, vpTexture, 0, 0);

			//When all done, we present
			SDL_RenderPresent(vpRenderer);
		}
		close();
		return 0;
	}

	bool ViewPort::init() {
		if (SDL_Init(SDL_INIT_VIDEO)<0) {
			return false;
		}

		if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)) {
			return false;
		}

		vpWindow = SDL_CreateWindow("SDL_Sample_Viewport", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (!vpWindow) {
			return false;
		}
		vpWindowSurface = SDL_GetWindowSurface(vpWindow);
		if (!vpWindowSurface) {
			return false;
		}

		vpRenderer = SDL_CreateRenderer(vpWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!vpRenderer) {
			return false;
		}
		return true;
	}

	bool ViewPort::loadMedia() {
		SDL_Surface* tempSurface = NULL;
		tempSurface = IMG_Load("Data/viewport.png");
		vpTexture = SDL_CreateTextureFromSurface(vpRenderer, tempSurface);
		if (!vpTexture) {
			SDL_FreeSurface(tempSurface);
			return false;
		}
		SDL_FreeSurface(tempSurface);
		return true;
	}

	void ViewPort::close() {

		SDL_DestroyRenderer(vpRenderer);
		SDL_DestroyTexture(vpTexture);
		IMG_Quit();
		SDL_Quit();
	}
