#include "Timing.h"

textTexture::textTexture() {
	ttHeight = 0;
	ttWidth = 0;
	texture = NULL;
	textString = "";
}
textTexture::~textTexture() {
	free();
}
bool textTexture::putStringInTexture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor) {
	free();

	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, textString.c_str(), textColor);
	if (!tempSurface) {
		printf("TTF_RenderText_Solid() Failed\n");
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!texture) {
		printf("SDL_CreateTextureFromSurface() Failed\n");
		return false;
	}

	ttWidth = tempSurface->w;
	ttHeight = tempSurface->h;

	SDL_FreeSurface(tempSurface);
	return true;
}
void textTexture::render(SDL_Renderer* renderer, int x, int y) {
	SDL_Rect renderQuad = { x, y, ttWidth, ttHeight };
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}
void textTexture::free() {
	if (!texture) {
		SDL_DestroyTexture(texture);
		ttWidth = 0;
		ttHeight = 0;
	}
}
int textTexture::getWidth() {
	return ttWidth;
}
int textTexture::getHeight() {
	return ttHeight;
}
void textTexture::setText(std::string text) {
	textString = text;
}

bool Timing::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Init() Failed\n");
		return false;
	}
	//SDL_SetHint
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!\n");
	}

	tWindow = SDL_CreateWindow(
		"Timing",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!tWindow) {
		printf("SDL_CreateWindow Failed\n");
		return false;
	}

	tRenderer = SDL_CreateRenderer(tWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!tRenderer) {
		printf("SDL_CreateRenderer() Failed\n");
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG)& IMG_INIT_PNG)) {
		printf("IMG_Init() Failed\n");
		return false;
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init() Failed\n");
		return false;
	}
	return true;
}
bool Timing::loadMedia() {
	tFont = TTF_OpenFont("Data/lazy.ttf", 28);
	if (tFont == NULL) {
		printf("SDL_OpenFont() Failed\n");
		return false;
	}
	prompt.setText("Press Enter To Reset Timer!");
	SDL_Color textColor = { 0,0,0,255 };
	if (!prompt.putStringInTexture(tRenderer, tFont, textColor)) {
		printf("prompt.putStringInTexture() Failed\n");
		return false;
	}
	return true;
}
void Timing::close() {
	textSprite.free();
	prompt.free();

	TTF_CloseFont(tFont);
	SDL_DestroyWindow(tWindow);
	SDL_DestroyRenderer(tRenderer);
	tWindow = NULL;
	tRenderer = NULL;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}
bool Timing::Main() {
	if (!init()) {
		printf("init() Failed\n");
		return false;
	}
	if (!loadMedia()) {
		printf("loadMedia() Failed\n");
		return false;
	}

	bool quit = false;
	SDL_Event event;
	int startTime = 0;
	std::stringstream timeText;
	SDL_Color textColor = { 0,0,0,255 };

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			//Other Event Handling
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
			{
				startTime = SDL_GetTicks();
			}
		}

		timeText.str("");
		timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;
		textSprite.setText(timeText.str().c_str());
		textSprite.putStringInTexture(tRenderer, tFont, textColor);


		SDL_SetRenderDrawColor(tRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(tRenderer);

		//Other Render Work
		prompt.render(tRenderer, (screenWidth - prompt.getWidth()) / 2, 0);
		textSprite.render(tRenderer, (screenWidth - textSprite.getWidth()) / 2, (screenHeight - textSprite.getHeight()) / 2);

		SDL_RenderPresent(tRenderer);
	}

	return true;
}



