#include "Include/ColorModulation.h"

cmTexture::cmTexture() {
	texture = NULL;
	cmWidth = 0;
	cmHeight = 0;
}
cmTexture::~cmTexture() {
	free();
}
bool cmTexture::loadTexture(SDL_Renderer* renderer, std::string path) {
	free();
	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(path.c_str());
	if (!tempSurface) {
		printf("IMG_Load Failed\n");
		return false;
	}

	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture) {
		printf("CreateTextureFromSurface Failed\n");
		return false;
	}
	cmHeight = tempSurface->h;
	cmWidth = tempSurface->w;

	SDL_FreeSurface(tempSurface);
	return true;
}
void cmTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(texture, red, green, blue);
}
void cmTexture::render(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect renderQuad = { x, y, cmWidth, cmHeight };
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
void cmTexture::free() {
	if (!texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		cmWidth = 0;
		cmHeight = 0;
	}
}
bool ColorModulation::init() {
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init Failed\n");
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}
	// Create Window
	cmWindow = SDL_CreateWindow(
		"Color Modulation",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!cmWindow) { return false; }
	// Create Renderer
	cmRenderer = SDL_CreateRenderer(cmWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!cmRenderer) { return false; }

	// Init SDL_Image
	if (!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) {
		printf("IMG_Init Failed\n");
		return false;
	}
	return true;
}
bool ColorModulation::loadMedia() {
	bool ret = spriteTexture.loadTexture(cmRenderer, "Data/colors.png");
	return ret;
}
void ColorModulation::close() {
	spriteTexture.free();
	SDL_DestroyWindow(cmWindow);
	SDL_DestroyRenderer(cmRenderer);
	IMG_Quit();
	SDL_Quit();
}
bool ColorModulation::Main() {
	if (!init()) {
		printf("init() Failed\n");
		return false;
	}
	if (!loadMedia()) {
		printf("loadMedia() Failed\n");
		return false;
	}

	SDL_Event event;
	bool quit = false;
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			//Other Events
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					// increase red
				case SDLK_q:
					r += 10;
					break;
					// increase green
				case SDLK_w:
					g += 10;
					break;
					// increase blue
				case SDLK_e:
					b += 10;
					break;
					// decrease red
				case SDLK_a:
					r -= 10;
					break;
					// decrease green
				case SDLK_s:
					g -= 10;
					break;
					// decrease blue
				case SDLK_d:
					b -= 10;
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(cmRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(cmRenderer);

		spriteTexture.setColor(r, g, b);
		spriteTexture.render(cmRenderer, 0, 0);

		SDL_RenderPresent(cmRenderer);
	}
	close();
	return true;
}









