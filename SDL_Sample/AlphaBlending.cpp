#include "AlphaBlending.h"

abTexture::abTexture() {
	texture = NULL;
	abWidth = 0;
	abHeight = 0;
}
abTexture::~abTexture() {
	free();
}
bool abTexture::loadTexture(SDL_Renderer* renderer, std::string path) {
	free();
	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(path.c_str());
	if (!tempSurface) return false;

	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture) { return false; }

	abWidth = tempSurface->w;
	abHeight = tempSurface->h;

	SDL_FreeSurface(tempSurface);
	return true;
}
void abTexture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}
void abTexture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(texture, blending);
}
void abTexture::render(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect renderQuad = { x, y, abWidth, abHeight };
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
void abTexture::free() {
	if (!texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		abWidth = 0;
		abHeight = 0;
	}
}

bool AlphaBlending::init() {
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init() Failed\n");
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: SetHint Failed\n");
	}

	abWindow = SDL_CreateWindow(
		"Alpha Blending",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!abWindow) {
		return false;
	}
	abRenderer = SDL_CreateRenderer(abWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!abRenderer) return false;

	if (!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) {
		printf("IMG_Init() Failed\n");
		return false;
	}

	return true;
}

bool AlphaBlending::loadMedia() {
	bool ret = true;
	if (!spriteTexture.loadTexture(abRenderer, "Data/fadeout.png")) {
		printf("load sprite failed\n");
		ret = false;
	}
	else {
		spriteTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}
	if (!backgroundTexture.loadTexture(abRenderer, "Data/fadein.png")) {
		ret = false;
		printf("load background failed\n");
	}

	return ret;
}

void AlphaBlending::close() {
	spriteTexture.free();
	backgroundTexture.free();

	SDL_DestroyWindow(abWindow);
	SDL_DestroyRenderer(abRenderer);
	SDL_Quit();
	IMG_Quit();
}

bool AlphaBlending::Main() {
	if (!init()) {
		printf("init() Failed\n");
		return false;
	}
	if (!loadMedia()) {
		printf("loadMedia() Failed\n");
		return false;
	}

	SDL_Event event;
	Uint8 alpha = 255;
	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					// increase alpha
				case SDLK_r:
					if (alpha + 10 > 255)
						alpha = 255;
					else
						alpha += 10;
					break;
					// decrease alpha
				case SDLK_f:
					if (alpha - 10 < 0) {
						alpha = 0;
					}
					else {
						alpha -= 10;
					}
					break;

				}
			}
		}
		// do the render work
		SDL_SetRenderDrawColor(abRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(abRenderer);

		backgroundTexture.render(abRenderer, 0, 0);

		spriteTexture.setAlpha(alpha);
		spriteTexture.render(abRenderer, 0, 0);

		SDL_RenderPresent(abRenderer);
	}
	close();
	return true;
}
