#include "Include/BlitRendering.h"

int BlitRendering::Main() {
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

	imageSurface = loadMediaSurface("Data/hello_world.bmp");
	SDL_Delay(3000);
	firstThree();

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
			//Select surfaces based on key press
				switch (event.key.keysym.sym)
				{
				case SDLK_KP_1:
				case SDLK_1:
					imageSurface = pressedSurface[printResult(KEYPRESSED_1)];
					break;
				case SDLK_KP_2:
				case SDLK_2:
					imageSurface = pressedSurface[printResult(KEYPRESSED_2)];
					break;
				case SDLK_KP_3:
				case SDLK_3:
					imageSurface = pressedSurface[printResult(KEYPRESSED_3)];
					break;
				case SDLK_KP_4:
				case SDLK_4:
					imageSurface = pressedSurface[printResult(KEYPRESSED_4)];
					break;
				case SDLK_KP_5:
				case SDLK_5:
					imageSurface = pressedSurface[printResult(KEYPRESSED_5)];
					break;
				case SDLK_KP_6:
				case SDLK_6:
					imageSurface = pressedSurface[printResult(KEYPRESSED_6)];
					break;
				case SDLK_KP_7:
				case SDLK_7:
					imageSurface = pressedSurface[printResult(KEYPRESSED_7)];
					break;
				case SDLK_KP_8:
				case SDLK_8:
					imageSurface = pressedSurface[printResult(KEYPRESSED_8)];
					break;
				case SDLK_s:
					imageSurface = pressedSurface[getNext()];
					printf("random\n");
					break;
				case SDLK_p:
					imageSurface = loadPNGSurface("Data/loaded.png");
					break;
				default:
					imageSurface = loadMediaSurface("Data/hello_world.bmp");
					break;
				}
			}

		}
		//SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
		//Apply the image stretched
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(imageSurface, NULL, windowSurface, NULL);

		SDL_UpdateWindowSurface(window);


	}

	close();
	return 0;

}

bool BlitRendering::init() {

	pos = 0;

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

	windowSurface = SDL_GetWindowSurface(window);
	srand(SDL_GetTicks());
	return true;
}

bool BlitRendering::loadMedia() {
	pressedSurface[DEFAULT] = loadMediaSurface("Data/hello_world.bmp");
	if (!pressedSurface[DEFAULT])return false;
	pressedSurface[KEYPRESSED_1] = loadMediaSurface("Data/1.bmp");
	if (!pressedSurface[KEYPRESSED_1])return false;
	pressedSurface[KEYPRESSED_2] = loadMediaSurface("Data/2.bmp");
	if (!pressedSurface[KEYPRESSED_2])return false;
	pressedSurface[KEYPRESSED_3] = loadMediaSurface("Data/3.bmp");
	if (!pressedSurface[KEYPRESSED_3])return false;
	pressedSurface[KEYPRESSED_4] = loadMediaSurface("Data/4.bmp");
	if (!pressedSurface[KEYPRESSED_4])return false;
	pressedSurface[KEYPRESSED_5] = loadMediaSurface("Data/5.bmp");
	if (!pressedSurface[KEYPRESSED_5])return false;
	pressedSurface[KEYPRESSED_6] = loadMediaSurface("Data/6.bmp");
	if (!pressedSurface[KEYPRESSED_6])return false;
	pressedSurface[KEYPRESSED_7] = loadMediaSurface("Data/7.bmp");
	if (!pressedSurface[KEYPRESSED_7])return false;
	pressedSurface[KEYPRESSED_8] = loadMediaSurface("Data/8.bmp");
	if (!pressedSurface[KEYPRESSED_8])return false;

	return true;
}

void BlitRendering::close() {
	for (int i = 0; i < KEYPRESSED_TOTAL; ++i) {
		SDL_FreeSurface(pressedSurface[i]);
		pressedSurface[i] = NULL;
	}
	//SDL_FreeSurface(imageSurface);
	SDL_DestroyWindow(window);

	SDL_Quit();
	IMG_Quit();
}

SDL_Surface* BlitRendering::loadMediaSurface(std::string path) {

	SDL_Surface* optimized = NULL;
	SDL_Surface* tempSurface = SDL_LoadBMP(path.c_str());
	if (!tempSurface) return NULL;

	optimized = SDL_ConvertSurface(tempSurface, windowSurface->format, 0);
	if (!optimized) {
		printf("loadMediaSurface() Error: Cannot optimize Surface");
	}
	SDL_FreeSurface(tempSurface);

	return optimized;
}


SDL_Surface* BlitRendering::loadPNGSurface(std::string path) {

	SDL_Surface* optimizedSurface = NULL;

	optimizedSurface = IMG_Load(path.c_str());
	if (!optimizedSurface) {
		printf("IMG_Load failed: %s\n", IMG_GetError());
		return NULL;
	}
	optimizedSurface = SDL_ConvertSurface(optimizedSurface, windowSurface->format, NULL);
	if (!optimizedSurface) {
		printf("SDL_ConvertSurface failed: %s\n", IMG_GetError());
		return NULL;
	}
	return optimizedSurface;

}


void BlitRendering::firstThree() {

	for (int i = 0; i < 3; i++) {

		int randNum = getNext();

		arr[i] = randNum;
		pos++;

		imageSurface = pressedSurface[randNum];

		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(imageSurface, NULL, windowSurface, NULL);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(1000);
	}
	pos = 0;
}

int BlitRendering::getNext() {
	return (rand() % 8)+1;
}

int BlitRendering::printResult(int keyPressed) {
	printf("Displayed: %d \t Entered: %d \t", arr[pos], keyPressed);
	(arr[pos] == keyPressed) ? printf("Correct") : printf("Wrong");
	printf("\n");
	int ret = getNext();
	arr[pos] = ret;

	pos++;
	if (pos >= length)
		pos = 0;
	return ret;
}