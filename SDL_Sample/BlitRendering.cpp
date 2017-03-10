#include "Include/BlitRendering.h"

int BlitRendering::Main() {
	bool quit = false;
	SDL_Event event;

	if (init() == false) {
		return -1;
		printf("init() Returned False\n");
	}
	if (loadMedia() == false) {
		return -1;
		printf("loadMedia() Returned False\n");
	}

	imageSurface = pressedSurface[KEYPRESSED_DEFAULT];

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
			imageSurface = pressedSurface[KEYPRESSED_UP];
			break;
			case SDLK_DOWN:
			imageSurface = pressedSurface[KEYPRESSED_DOWN];
			break;
			case SDLK_LEFT:
			imageSurface = pressedSurface[KEYPRESSED_LEFT];
			break;
			case SDLK_RIGHT:
			imageSurface = pressedSurface[KEYPRESSED_RIGHT];
			break;
			case SDLK_s:
			imageSurface = loadMediaSurface("Data/stretch.bmp");
			break;
			case SDLK_p:
			imageSurface = loadPNGSurface("Data/loaded.png");
			break;
			default:
			imageSurface = pressedSurface[KEYPRESSED_DEFAULT];
			break;
			}
			}

		}
		//SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
		//Apply the image stretched
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(imageSurface, NULL, windowSurface, &stretchRect);

		SDL_UpdateWindowSurface(window);


	}

	close();
	return 0;

}

bool BlitRendering::init() {

	if (SDL_Init(SDL_INIT_VIDEO)<0) { return false; }

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	int imageFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlag) & imageFlag)) {
		printf("Image Initialization Failed: %s\n", IMG_GetError());
		return false;
	}

	window = SDL_CreateWindow("SDL Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) { return false; }

	windowSurface = SDL_GetWindowSurface(window);

	return true;
}

bool BlitRendering::loadMedia() {
	pressedSurface[KEYPRESSED_DEFAULT] = loadMediaSurface("Data/press.bmp");
	if (!pressedSurface[KEYPRESSED_DEFAULT])return false;
	pressedSurface[KEYPRESSED_UP] = loadMediaSurface("Data/up.bmp");
	if (!pressedSurface[KEYPRESSED_UP])return false;
	pressedSurface[KEYPRESSED_DOWN] = loadMediaSurface("Data/down.bmp");
	if (!pressedSurface[KEYPRESSED_DOWN])return false;
	pressedSurface[KEYPRESSED_LEFT] = loadMediaSurface("Data/left.bmp");
	if (!pressedSurface[KEYPRESSED_LEFT])return false;
	pressedSurface[KEYPRESSED_RIGHT] = loadMediaSurface("Data/right.bmp");
	if (!pressedSurface[KEYPRESSED_RIGHT])return false;


	return true;
}

void BlitRendering::close() {
	for (int i = 0; i < KEYPRESSED_TOTAL; ++i) {
		SDL_FreeSurface(pressedSurface[i]);
		pressedSurface[i] = NULL;
	}
	//SDL_FreeSurface(imageSurface);
	SDL_DestroyWindow(window);

	SDL_Quit();
	IMG_Quit();
}

SDL_Surface* BlitRendering::loadMediaSurface(std::string path) {

	SDL_Surface* optimized = NULL;
	SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str());
	if (!tempSurface) return NULL;

	optimized = SDL_ConvertSurface(tempSurface, windowSurface->format, 0);
	if (!optimized) {
		printf("loadMediaSurface() Error: Cannot optimize Surface");
	}
	SDL_FreeSurface(tempSurface);

	return optimized;
}


SDL_Surface* BlitRendering::loadPNGSurface(std::string path) {

	SDL_Surface* optimizedSurface = NULL;

	optimizedSurface = IMG_Load(path.c_str());
	if (!optimizedSurface) {
		printf("IMG_Load failed: %s\n", IMG_GetError());
		return NULL;
	}
	optimizedSurface = SDL_ConvertSurface(optimizedSurface, windowSurface->format, NULL);
	if (!optimizedSurface) {
		printf("SDL_ConvertSurface failed: %s\n", IMG_GetError());
		return NULL;
	}
	return optimizedSurface;

}
