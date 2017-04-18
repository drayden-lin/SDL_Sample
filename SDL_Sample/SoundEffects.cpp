#include "Include/SoundEffects.h"

bool SoundManager::loadSound() {
	free();
	sHigh = Mix_LoadWAV("Data/SoundEffects/high.wav");
	sMedium = Mix_LoadWAV("Data/SoundEffects/medium.wav");
	sLow = Mix_LoadWAV("Data/SoundEffects/low.wav");
	sScratch = Mix_LoadWAV("Data/SoundEffects/scratch.wav");

	sMusic = Mix_LoadMUS("Data/SoundEffects/beat.wav");

	if (!sHigh || !sLow || !sMedium || !sScratch) {
		printf("loadSound() Sound Effects Failed\n");
		return false;
	}

	if (!sMusic) {
		printf("loadSound() Music Failed\n");
		return false;
	}
	return true;
}

void SoundManager::play(int soundfiles) {
	switch (soundfiles) {
	case SCRATCH:
		Mix_PlayChannel(-1, sScratch, 0);
		//Mix_PlayChannel(-1, Mix_LoadWAV("Data/SoundEffects/high.wav"), 0);
		break;
	case HIGH:
		Mix_PlayChannel(-1, sHigh, 0);
		break;
	case MEDIUM:
		Mix_PlayChannel(-1, sMedium, 0);
		break;
	case LOW:
		Mix_PlayChannel(-1, sLow, 0);
		break;
	}
	if (soundfiles == MUSIC) {
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(sMusic, -1);
		}
		else {
			//Mix_PausedMusic()? Mix_ResumeMusic : Mix_PauseMusic;
			if (Mix_PausedMusic() == 1) {
				Mix_ResumeMusic();
			}
			else {
				Mix_PauseMusic();
			}
			//
		}
	}
}

void SoundManager::halt() {
	Mix_HaltMusic();
}

void SoundManager::free() {
	if (!sHigh) {
		Mix_FreeChunk(sHigh);
		sHigh = NULL;
	}
	if (!sMedium) {
		Mix_FreeChunk(sMedium);
		sMedium = NULL;
	}
	if (!sLow) {
		Mix_FreeChunk(sLow);
		sLow = NULL;
	}
	if (!sScratch) {
		Mix_FreeChunk(sScratch);
		sScratch = NULL;
	}
	if (!sMusic) {
		Mix_FreeMusic(sMusic);
		sMusic = NULL;
	}
}

bool SoundEffects::init() {
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init() Failed\n");
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("SDL_SetHint() Failed\n");
	}

	seWindow = SDL_CreateWindow(
		"Music and Sound Effects",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);

	if (seWindow == NULL) {
		printf("SDL_CreateWindow Failed\n");
		return false;
	}

	seRenderer = SDL_CreateRenderer(seWindow, -1, SDL_RENDERER_ACCELERATED);
	if (seRenderer == NULL) {
		printf("SDL_CreateRenderer Failed");
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("IMG_Init() Failed\n");
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)< 0) {
		printf("Mix_OpenAudio() Failed\n");
		return false;
	}

	return true;
}

bool SoundEffects::loadMedia() {
	SDL_Surface* tempSurface = IMG_Load("Data/prompt.png");
	if (!tempSurface) {
		printf("IMG_Load() Failed\n");
		return false;
	}
	background = SDL_CreateTextureFromSurface(seRenderer, tempSurface);
	if (!background) {
		printf("CreateTexture Failed\n");
		return false;
	}
	SDL_FreeSurface(tempSurface);

	if (!sound.loadSound()) {
		printf("loadMedia()->loadSound() Failed\n");
		return false;
	}
	return true;
}

void SoundEffects::close() {
	sound.free();

	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(seRenderer);
	SDL_DestroyWindow(seWindow);
	background = NULL;
	seRenderer = NULL;
	seWindow = NULL;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool SoundEffects::Main() {
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
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_1:
					sound.play(HIGH);
					break;
				case SDLK_2:
					sound.play(MEDIUM);
					break;
				case SDLK_3:
					sound.play(LOW);
					break;
				case SDLK_4:
					sound.play(SCRATCH);
					break;
				case SDLK_9:
					sound.play(MUSIC);
					break;
				case SDLK_0:
					sound.halt();
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(seRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(seRenderer);

		SDL_RenderCopy(seRenderer, background, 0, 0);

		SDL_RenderPresent(seRenderer);
	}
	close();
	return true;
}
