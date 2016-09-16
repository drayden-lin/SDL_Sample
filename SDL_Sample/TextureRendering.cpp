#include "TextureRendering.h"

SDL_Texture* TRsurfaceTexture = NULL;
SDL_Window* TRwindow = NULL;
SDL_Surface* TRwindowSurface = NULL;
SDL_Surface* TRimageSurface = NULL;

SDL_Renderer* textureRender = NULL;


int TRMain() {
	bool quit = false;
	SDL_Event event;

	if (TRinit() == false) {
		return -1;
		printf("init() Returned False\n");
	}
	if (TRloadMedia() == false) {
		return -1;
		printf("loadMedia() Returned False\n");
	}


	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_RenderClear(textureRender);
		SDL_RenderCopy(textureRender, TRsurfaceTexture, 0, 0);
		SDL_RenderPresent(textureRender);

	}

	TRclose();
	return 0;

}

bool TRinit() {

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

	TRwindow = SDL_CreateWindow("SDL Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TR_SCREEN_WIDTH, TR_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (TRwindow == NULL) { return false; }

	textureRender = SDL_CreateRenderer(TRwindow, -1, SDL_RENDERER_ACCELERATED);
	if (textureRender == NULL) { return false; }

	SDL_SetRenderDrawColor(textureRender, 0x00, 0x00, 0x00, 0x00);

	TRwindowSurface = SDL_GetWindowSurface(TRwindow);

	return true;
}

bool TRloadMedia() {

	TRsurfaceTexture = loadMediaTexture("Data/texture.png");
	if (!TRsurfaceTexture)return false;

	return true;
}

void TRclose() {

	//SDL_FreeSurface(imageSurface);
	SDL_DestroyWindow(TRwindow);
	SDL_DestroyRenderer(textureRender);
	SDL_DestroyTexture(TRsurfaceTexture);
	SDL_Quit();
	IMG_Quit();
}



SDL_Texture* loadMediaTexture(std::string path) {
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* returnTexture = NULL;

	tempSurface = IMG_Load(path.c_str());
	if (!tempSurface) { return NULL; }

	returnTexture = SDL_CreateTextureFromSurface(textureRender, tempSurface);
	if (!returnTexture) { return NULL; }

	SDL_FreeSurface(tempSurface);

	return returnTexture;

}