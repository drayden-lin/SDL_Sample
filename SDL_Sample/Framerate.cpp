#include "Framerate.h"

bool Framerate::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Init() Failed\n");
		return false;
	}
	//SDL_SetHint
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!\n");
	}

	window = SDL_CreateWindow(
		"Framerate",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!window) {
		printf("SDL_CreateWindow Failed\n");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
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

bool Framerate::loadMedia() {
	font = TTF_OpenFont("Data/lazy.ttf", 28);
	if (font == NULL) {
		printf("SDL_OpenFont() Failed\n");
		return false;
	}
	return true;
}

void Framerate::close() {
	texture.free();
	prompt.free();

	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

bool Framerate::Main() {
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
	std::stringstream timeText;
	SDL_Color textColor = { 0,0,0,255 };
	timer.start();
	float fps = 0;
	int frames = 0;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}

		}
		fps = frames/(timer.getTicks()/1000.f);
		
		if(fps > 20000)
			fps = 0;
		
		timeText.str("");
		timeText << "Average Frames Per Second:  " << fps;
		texture.loadFontTexture(renderer, tFont, timeText.str().c_str(), textColor);


		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//Other Render Work
		texture.render(renderer, (screenWidth - texture.getWidth()) / 2, (screenHeight - texture.getHeight()) / 2);

		SDL_RenderPresent(renderer);
		frames++;
	}

	return true;
}