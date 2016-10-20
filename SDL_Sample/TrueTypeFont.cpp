#include "Include/TrueTypeFont.h"

fontTexture::fontTexture() {
	ftWidth = 0;
	ftHeight = 0;
	texture = NULL;
}

fontTexture::~fontTexture() {
	free();
}

bool fontTexture::loadFontTexture(SDL_Renderer* renderer, TTF_Font* font, std::string str, SDL_Color textColor) {
	free();
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
	if (!tempSurface) {
		printf("TTF_RenderText_Solid() Failed\n");
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture) {
		printf("SDL_CreateTextureFromSurface() Failed\n");
		return false;
	}

	ftHeight = tempSurface->h;
	ftWidth = tempSurface->w;

	SDL_FreeSurface(tempSurface);
	return true;
}

void fontTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = { x, y, ftWidth, ftHeight };

	if (clip) {
		renderQuad.h = clip->h;
		renderQuad.w = clip->w;
	}

	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int fontTexture::getWidth() {
	return ftWidth;
}
int fontTexture::getHeight() {
	return ftHeight;
}
void fontTexture::free() {
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		ftWidth = 0;
		ftHeight = 0;
	}
}
bool TrueTypeFont::init() {
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init() Failed\n");
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("SDL_SetHint() Failed\n");
	}

	ttfWindow = SDL_CreateWindow(
		"True Type Font",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);

	if (ttfWindow == NULL) {
		printf("SDL_CreateWindow Failed\n");
		return false;
	}

	ttfRenderer = SDL_CreateRenderer(ttfWindow, -1, SDL_RENDERER_ACCELERATED);
	if (ttfRenderer == NULL) {
		printf("SDL_CreateRenderer Failed");
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("IMG_Init() Failed\n");
		return false;
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init() Failed\n");
		return false;
	}
	return true;
}

bool TrueTypeFont::loadMedia() {
	//Load the Font file first
	font = TTF_OpenFont("Data/lazy.ttf", 28);
	if (!font) {
		printf("TTF_OpenFont() Failed\n");
		return false;
	}
	//Input the String we want to display with the Font loaded
	SDL_Color textColor = { 0, 0, 0 };
	bool ret = ftTexture.loadFontTexture(ttfRenderer, font, "The quick brown fox jumps over the lazy dog", textColor);
}

void TrueTypeFont::close() {

	ftTexture.free();
	TTF_CloseFont(font);
	SDL_DestroyRenderer(ttfRenderer);
	SDL_DestroyWindow(ttfWindow);

	font = NULL;
	ttfRenderer = NULL;
	ttfWindow = NULL;

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

bool TrueTypeFont::Main() {
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

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				quit = true;
		}
		SDL_SetRenderDrawColor(ttfRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ttfRenderer);


		ftTexture.render(ttfRenderer, (screenWidth - ftTexture.getWidth()) / 2, (screenHeight - ftTexture.getHeight()) / 2, NULL);


		SDL_RenderPresent(ttfRenderer);
	}
	close();
	return true;
}


