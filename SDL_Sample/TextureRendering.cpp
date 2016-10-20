#include "Include/TextureRendering.h"

int TextureRandering::Main() {
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


	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		SDL_RenderClear(textureRender);
		SDL_RenderCopy(textureRender, surfaceTexture, 0, 0);
		SDL_RenderPresent(textureRender);

	}

	close();
	return 0;

}

bool TextureRandering::init() {

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

	textureRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (textureRender == NULL) { return false; }

	SDL_SetRenderDrawColor(textureRender, 0x00, 0x00, 0x00, 0x00);

	windowSurface = SDL_GetWindowSurface(window);

	return true;
}

bool TextureRandering::loadMedia() {

	surfaceTexture = loadMediaTexture("Data/texture.png");
	if (!surfaceTexture)return false;

	return true;
}

void TextureRandering::close() {

	//SDL_FreeSurface(imageSurface);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(textureRender);
	SDL_DestroyTexture(surfaceTexture);
	SDL_Quit();
	IMG_Quit();
}



SDL_Texture* TextureRandering::loadMediaTexture(std::string path) {
	SDL_Surface* tempSurface = NULL;
	SDL_Texture* returnTexture = NULL;

	tempSurface = IMG_Load(path.c_str());
	if (!tempSurface) { return NULL; }

	returnTexture = SDL_CreateTextureFromSurface(textureRender, tempSurface);
	if (!returnTexture) { return NULL; }

	SDL_FreeSurface(tempSurface);

	return returnTexture;

}