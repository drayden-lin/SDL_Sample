#include "SpriteAnimation.h"

aTexture::aTexture() {
	aWidth = 0;
	aHeight = 0;
	texture = NULL;
}
aTexture::~aTexture() {
	free();
}
void aTexture::free() {
	if (!texture) {
		SDL_DestroyTexture(texture);
		texture = NULL;
		aWidth = 0;
		aHeight = 0;
	}
}
bool aTexture::loadTexture(SDL_Renderer* renderer, std::string path) {
	SDL_Surface* tempSurface = NULL;
	tempSurface = IMG_Load(path.c_str());
	if (!tempSurface) {
		printf("IMG_Load() Failed\n");
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture) {
		printf("CreateTextureFromSurface Failed\n");
		return false;
	}
	aWidth = tempSurface->w;
	aHeight = tempSurface->h;

	SDL_FreeSurface(tempSurface);
	return true;
}
void aTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = { x, y, aWidth, aHeight };

	if (clip!=NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

void SpriteAnimation::close() {
	spriteTexture.free();

	SDL_DestroyWindow(aWindow);
	SDL_DestroyRenderer(aRenderer);
	SDL_Quit();
	IMG_Quit();
}

bool SpriteAnimation::init() {

	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init() failed\n");
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("SetHint Failed\n");
	}
	aWindow = SDL_CreateWindow(
		"Sprite Animation",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!aWindow) {
		printf("SDL_CreateWindow Failed\n");
		return false;
	}
	aRenderer = SDL_CreateRenderer(aWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!aRenderer) {
		printf("SDL_CreateRenderer Failed\n");
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("IMG_INIT() Failed\n");
		return false;
	}
	return true;
}

bool SpriteAnimation::loadMedia() {
	if (!spriteTexture.loadTexture(aRenderer, "Data/fooSprite.png")) {
		printf("loadTexture Failed\n");
		return false;
	}

	renderClips[0].x = 0;
	renderClips[0].y = 0;
	renderClips[0].w = 64;
	renderClips[0].h = 205;

	renderClips[1].x = 64;
	renderClips[1].y = 0;
	renderClips[1].w = 64;
	renderClips[1].h = 205;

	renderClips[2].x = 128;
	renderClips[2].y = 0;
	renderClips[2].w = 64;
	renderClips[2].h = 205;

	renderClips[3].x = 196;
	renderClips[3].y = 0;
	renderClips[3].w = 64;
	renderClips[3].h = 205;

	return true;
}

bool SpriteAnimation::Main() {
	if (!init()) {
		printf("init() Failed\n");
		return false;
	}
	if (!loadMedia()) {
		printf("loadMedia Failed\n");
		return false;
	}

	bool quit = false;
	SDL_Event event;
	int frame = 0;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(aRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(aRenderer);
		SDL_Rect* currentClip = &renderClips[frame / 4];
		spriteTexture.render(aRenderer, (screenWidth - currentClip->w) / 2, (screenHeight - currentClip->h) / 2, currentClip);
		++frame;
		if (frame / 4 >= 4) frame = 0;

		SDL_RenderPresent(aRenderer);
	}
	close();
	return true;
}


