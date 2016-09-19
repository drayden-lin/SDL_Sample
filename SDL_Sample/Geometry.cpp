#include "Geometry.h"

int Geometry::Main() {
	if (!init())return -1;
	bool quit = false;
	SDL_Event event;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				quit = true;
		}
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		SDL_Rect rect = { screenWidth / 4, screenHeight / 4, screenWidth / 2, screenHeight / 2 };
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(gRenderer, &rect);

		SDL_Rect fillRect = { screenWidth / 6, screenHeight / 6, screenWidth * 2 / 3, screenHeight * 2 / 3 };
		SDL_SetRenderDrawColor(gRenderer, 0x0, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(gRenderer, &fillRect);


		SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0xFF, 0xFF);
		SDL_RenderDrawLine(gRenderer, 0, screenHeight / 2, screenWidth, screenHeight / 2);

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x0, 0xFF, 0xFF);
		for (int i = 0; i < screenHeight; i += 4) {
			SDL_RenderDrawPoint(gRenderer, screenWidth / 2, i);
		}



		SDL_RenderPresent(gRenderer);
	}

	close();
	return 0;
}

bool Geometry::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

	gWindow = SDL_CreateWindow("Geometry Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (!gWindow)return false;

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!gRenderer)return false;

	gSurface = SDL_GetWindowSurface(gWindow);
	if (!gSurface)return false;

	return true;
}

void Geometry::close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(gSurface);
	SDL_Quit();
}