#include "AdvanceTiming.h"

bool AdvanceTiming::init() {
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
		"AdvanceTiming",
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

bool AdvanceTiming::loadMedia() {
	font = TTF_OpenFont("Data/lazy.ttf", 28);
	if (font == NULL) {
		printf("SDL_OpenFont() Failed\n");
		return false;
	}
	//prompt.setText("Press Enter To Reset Timer!");
	SDL_Color textColor = { 0,0,0,255 };
	if (!prompt.loadFontTexture(renderer, font, "Press S to Start/Stop, Press P to Pause/Resume.",textColor)) {
		printf("prompt.loadFontTexture() Failed\n");
		return false;
	}
	return true;
}

void AdvanceTiming::close() {
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

bool AdvanceTiming::Main() {
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

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			//Other Event Handling
			else if (event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_s){
					if(timer.isStarted()){
						timer.stop();
					}
					else{
						timer.start();
					}
				}
				else if(event.key.keysym.sym == SDLK_p){
					if(timer.isPaused()){
						timer.resume();
					}
					else{
						timer.pause();
					}					
				}
			}
		}

		timeText.str("");
		timeText << "Milliseconds since start time " << timer.getTicks();
		//textSprite.setText(timeText.str().c_str());
		texture.loadFontTexture(renderer, tFont, timeText.str().c_str(), textColor);


		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//Other Render Work
		prompt.render(renderer, (screenWidth - prompt.getWidth()) / 2, 0);
		texture.render(renderer, (screenWidth - texture.getWidth()) / 2, (screenHeight - texture.getHeight()) / 2);

		SDL_RenderPresent(renderer);
	}

	return true;
}