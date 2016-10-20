#include "Include/RotationFlipping.h"

rtTexture::rtTexture() {
	texture = NULL;
	rtWidth = 0;
	rtHeight = 0;
}
rtTexture::~rtTexture() {
	free();
}
int rtTexture::getWidth() {
	return rtWidth;
}
int rtTexture::getHeight() {
	return rtHeight;
}
bool rtTexture::loadTexture(SDL_Renderer* renderer, std::string path) {
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
	rtHeight = tempSurface->h;
	rtWidth = tempSurface->w;

	SDL_FreeSurface(tempSurface);
	return true;
}
void rtTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(texture, red, green, blue);
}
void rtTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, rtWidth, rtHeight };

	if (clip)
	{
		renderQuad.h = clip->h;
		renderQuad.w = clip->w;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}
void rtTexture::free() {
	if (!texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		rtWidth = 0;
		rtHeight = 0;
	}
}
bool RotationFlipping::init() {
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init Failed\n");
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}
	// Create Window
	rtWindow = SDL_CreateWindow(
		"Rotation & Flipping",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!rtWindow) { return false; }
	// Create Renderer
	rtRenderer = SDL_CreateRenderer(rtWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!rtRenderer) { return false; }

	// Init SDL_Image
	if (!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) {
		printf("IMG_Init Failed\n");
		return false;
	}
	return true;
}
bool RotationFlipping::loadMedia() {
	bool ret = spriteTexture.loadTexture(rtRenderer, "Data/arrow.png");
	return ret;
}
void RotationFlipping::close() {
	spriteTexture.free();
	SDL_DestroyWindow(rtWindow);
	SDL_DestroyRenderer(rtRenderer);
	IMG_Quit();
	SDL_Quit();
}
bool RotationFlipping::Main() {
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
	//Angle of rotation
	double degrees = 0;
	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			//Other Events
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					// increase blue
				case SDLK_a:
					degrees += 60;
					break;
					// decrease red
				case SDLK_d:
					degrees -= 60;
					break;
					// decrease green
				case SDLK_w:
					flipType = SDL_FLIP_HORIZONTAL;
					break;
					// decrease blue
				case SDLK_s:
					flipType = SDL_FLIP_VERTICAL;
					break;
				case SDLK_q:
					flipType = SDL_FLIP_NONE;
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(rtRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(rtRenderer);


		spriteTexture.render(rtRenderer, (screenWidth - spriteTexture.getWidth()) / 2, (screenHeight - spriteTexture.getHeight()) / 2,
			NULL, degrees, NULL, flipType);

		SDL_RenderPresent(rtRenderer);
	}
	close();
	return true;
}
