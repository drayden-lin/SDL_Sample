#include "Include/ColorKeying.h"

bool ColorKeying::Main() {
	printf("Main()\n");
	if (!init()) {
		printf("init failed\n");
		return false; }
	if (!loadMedia()) {
		printf("init failed\n");
		return false;
	}

	SDL_Event event;
	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				quit = true;
		}
		SDL_SetRenderDrawColor(tRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(tRenderer);

		/*SDL_SetRenderDrawColor(tRenderer, 0xFF, 0x00, 0xFF, 0xFF);
		SDL_Rect rect = { screenHeight / 4, screenWidth / 4, screenHeight / 2, screenWidth / 2 };
		SDL_RenderDrawRect(tRenderer, &rect);*/
		backgroundTexture.render(tRenderer, 0, 0);
		fooTexture.render(tRenderer, 240, 190);

		SDL_RenderPresent(tRenderer);
	}

	close();
	return true;
}
bool ColorKeying::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))return false;

	tWindow = SDL_CreateWindow("Color Keying", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (!tWindow)return false;

	tSurface = SDL_GetWindowSurface(tWindow);
	if (!tSurface)return false;

	tRenderer = SDL_CreateRenderer(tWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!tRenderer)return false;

	return true;

}
bool ColorKeying::loadMedia() {
	fooTexture.loadTexture(tRenderer, "Data/foo.png");
	
	if (!(backgroundTexture.loadTexture(tRenderer, "Data/background.png")))return false;
	return true;

}
void ColorKeying::close() {

	fooTexture.free();
	backgroundTexture.free();
	
	SDL_FreeSurface(tSurface);
	SDL_DestroyRenderer(tRenderer);
	SDL_DestroyWindow(tWindow);
	IMG_Quit();
	SDL_Quit();
}

Ltexture::Ltexture() {
	tHeight = 0;
	tWidth = 0;
	tTexture = NULL;
}

bool Ltexture::loadTexture(SDL_Renderer* renderer, std::string path) {

	free();
	SDL_Texture* tempTexture = NULL;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) { 
		printf("loadTexture Failed\n");
		return false; 
	}

	tHeight = tempSurface->h;
	tWidth = tempSurface->w;

	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

	tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!tempTexture)return false;
	SDL_FreeSurface(tempSurface);
	tTexture = tempTexture;
	return true;

}
bool Ltexture::render(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect rect = { x, y, tWidth, tHeight };
	SDL_RenderCopy(renderer, tTexture, NULL, &rect);
	return true;
}
void Ltexture::free() {
	if (tTexture != NULL) {
		SDL_DestroyTexture(tTexture);
		tTexture = NULL;
		tHeight = 0;
		tWidth = 0;
	}
	return;
}