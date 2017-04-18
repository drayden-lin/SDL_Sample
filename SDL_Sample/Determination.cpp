#include "Include/Determination.h"

int Determination::Main() {
	bool quit = false;
	int delay = 1000;
	SDL_Event event;

	if (init() == false) {
		return -1;
		printf("init() Returned False\n");
	}
	if (loadMedia() == false) {
		return -1;
		printf("loadMedia() Returned False\n");
	}

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		int num = getNext();
		imageSurface = pressedSurface[num];
		if (80<num && num<91) {
			Mix_PlayChannel(-1, Mix_LoadWAV("Data/Determination/Sounds/high.wav"), 0);
		}
		if (70<num && num<81) {
			Mix_PlayChannel(-1, Mix_LoadWAV("Data/Determination/Sounds/low.wav"), 0);
		}

		//Apply the image stretched
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(imageSurface, NULL, windowSurface, &stretchRect);

		SDL_UpdateWindowSurface(window);
		SDL_Delay(delay);
		if (delay > 750) {
			delay--;
			printf("Delay: %d\n", delay);
		}
	}

	close();
	return 0;

}

bool Determination::init() {

	if (SDL_Init(SDL_INIT_VIDEO)<0) { return false; }

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	window = SDL_CreateWindow("SDL Sample", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) { return false; }

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)< 0) {
		printf("Mix_OpenAudio() Failed\n");
		return false;
	}

	windowSurface = SDL_GetWindowSurface(window);
	srand(SDL_GetTicks());
	return true;
}

void Determination::close() {
	for (int i = 0; i < 91; ++i) {
		SDL_FreeSurface(pressedSurface[i]);
		pressedSurface[i] = NULL;
	}
	SDL_DestroyWindow(window);

	SDL_Quit();
	Mix_Quit();
}

SDL_Surface* Determination::loadMediaSurface(std::string path) {

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

int Determination::getNext() {
	return (rand() % 90) + 1;
}

bool Determination::loadMedia() {
	pressedSurface[0] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[1] = loadMediaSurface("Data/Determination/blue1.bmp");
	pressedSurface[2] = loadMediaSurface("Data/Determination/blue2.bmp");
	pressedSurface[3] = loadMediaSurface("Data/Determination/blue3.bmp");
	pressedSurface[4] = loadMediaSurface("Data/Determination/blue4.bmp");
	pressedSurface[5] = loadMediaSurface("Data/Determination/blue5.bmp");
	pressedSurface[6] = loadMediaSurface("Data/Determination/blue6.bmp");
	pressedSurface[7] = loadMediaSurface("Data/Determination/blue7.bmp");
	pressedSurface[8] = loadMediaSurface("Data/Determination/blue8.bmp");
	pressedSurface[9] = loadMediaSurface("Data/Determination/blue9.bmp");
	pressedSurface[10] = loadMediaSurface("Data/Determination/blue10.bmp");
	pressedSurface[11] = loadMediaSurface("Data/Determination/red1.bmp");
	pressedSurface[12] = loadMediaSurface("Data/Determination/red2.bmp");
	pressedSurface[13] = loadMediaSurface("Data/Determination/red3.bmp");
	pressedSurface[14] = loadMediaSurface("Data/Determination/red4.bmp");
	pressedSurface[15] = loadMediaSurface("Data/Determination/red5.bmp");
	pressedSurface[16] = loadMediaSurface("Data/Determination/red6.bmp");
	pressedSurface[17] = loadMediaSurface("Data/Determination/red7.bmp");
	pressedSurface[18] = loadMediaSurface("Data/Determination/red8.bmp");
	pressedSurface[19] = loadMediaSurface("Data/Determination/red9.bmp");
	pressedSurface[20] = loadMediaSurface("Data/Determination/red10.bmp");
	pressedSurface[21] = loadMediaSurface("Data/Determination/green1.bmp");
	pressedSurface[22] = loadMediaSurface("Data/Determination/green2.bmp");
	pressedSurface[23] = loadMediaSurface("Data/Determination/green3.bmp");
	pressedSurface[24] = loadMediaSurface("Data/Determination/green4.bmp");
	pressedSurface[25] = loadMediaSurface("Data/Determination/green5.bmp");
	pressedSurface[26] = loadMediaSurface("Data/Determination/green6.bmp");
	pressedSurface[27] = loadMediaSurface("Data/Determination/green7.bmp");
	pressedSurface[28] = loadMediaSurface("Data/Determination/green8.bmp");
	pressedSurface[29] = loadMediaSurface("Data/Determination/green9.bmp");
	pressedSurface[30] = loadMediaSurface("Data/Determination/green10.bmp");
	pressedSurface[31] = loadMediaSurface("Data/Determination/yellow1.bmp");
	pressedSurface[34] = loadMediaSurface("Data/Determination/yellow2.bmp");
	pressedSurface[35] = loadMediaSurface("Data/Determination/yellow3.bmp");
	pressedSurface[36] = loadMediaSurface("Data/Determination/yellow4.bmp");
	pressedSurface[33] = loadMediaSurface("Data/Determination/yellow5.bmp");
	pressedSurface[32] = loadMediaSurface("Data/Determination/yellow6.bmp");
	pressedSurface[37] = loadMediaSurface("Data/Determination/yellow7.bmp");
	pressedSurface[38] = loadMediaSurface("Data/Determination/yellow8.bmp");
	pressedSurface[39] = loadMediaSurface("Data/Determination/yellow9.bmp");
	pressedSurface[40] = loadMediaSurface("Data/Determination/yellow10.bmp");
	pressedSurface[41] = loadMediaSurface("Data/Determination/white1.bmp");
	pressedSurface[42] = loadMediaSurface("Data/Determination/white2.bmp");
	pressedSurface[43] = loadMediaSurface("Data/Determination/white3.bmp");
	pressedSurface[44] = loadMediaSurface("Data/Determination/white4.bmp");
	pressedSurface[45] = loadMediaSurface("Data/Determination/white5.bmp");
	pressedSurface[46] = loadMediaSurface("Data/Determination/white6.bmp");
	pressedSurface[47] = loadMediaSurface("Data/Determination/white7.bmp");
	pressedSurface[48] = loadMediaSurface("Data/Determination/white8.bmp");
	pressedSurface[49] = loadMediaSurface("Data/Determination/white9.bmp");
	pressedSurface[50] = loadMediaSurface("Data/Determination/white10.bmp");

	pressedSurface[51] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[52] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[53] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[54] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[55] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[56] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[57] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[58] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[59] = loadMediaSurface("Data/Determination/right_pedal.bmp");
	pressedSurface[60] = loadMediaSurface("Data/Determination/right_pedal.bmp");

	pressedSurface[61] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[62] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[63] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[64] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[65] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[66] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[67] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[68] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[69] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	pressedSurface[70] = loadMediaSurface("Data/Determination/left_pedal.bmp");
	// Low Sounds
	pressedSurface[71] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[72] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[73] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[74] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[75] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[76] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[77] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[78] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[79] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[80] = loadMediaSurface("Data/Determination/empty.bmp");
	//High Sounds
	pressedSurface[81] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[82] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[83] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[84] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[85] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[86] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[87] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[88] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[89] = loadMediaSurface("Data/Determination/empty.bmp");
	pressedSurface[90] = loadMediaSurface("Data/Determination/empty.bmp");

	for (int i = 0; i < 91; i++) {
		if (!pressedSurface[i]) {
			printf("LoadMedia failed! array number: %d\n", i);
			return false;
		}
	}

	return true;
}
