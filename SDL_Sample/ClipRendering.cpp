#include "ClipRendering.h"

CTexture::CTexture() {
	cTexture = NULL;
	tHeight = 0;
	tWidth = 0;
}

CTexture::~CTexture() {
	free();
}

bool CTexture::loadTexture(SDL_Renderer* r, std::string path) {
	//TODO:
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (!tempSurface) { 
		printf("IMG_Load() Failed\n");
		return false; 
	}

	// Set the color cyan to be transparent
	SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));
	cTexture = SDL_CreateTextureFromSurface(r, tempSurface);

	if (!cTexture) {
		printf("CreateTexture Failed\n");
		return false;
	}
	tHeight = tempSurface->h;
	tWidth = tempSurface->w;

	SDL_FreeSurface(tempSurface);
	return true;

}
	

bool CTexture::render(SDL_Renderer* r, int x, int y, SDL_Rect* clip) {
	// renderQuad is the area to be rendered
	// We set it to be the width and height of the whole texture first
	// Then we check if we're doing clip rendering
	SDL_Rect renderQuad = { x, y, tWidth, tHeight};

	//if we're doing Clip Rendering, we only want to render a small corner per call
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(r, cTexture, clip, &renderQuad);
	return true;
}

void CTexture::free() {
	if (cTexture != NULL) {
		SDL_DestroyTexture(cTexture);
		cTexture = NULL;
		tHeight = 0;
		tWidth = 0;
	}
}

bool ClipRendering::init() {
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		printf("SDL_Init failed\n");
		return false;
	}
	cWindow = SDL_CreateWindow(
		"Clip Rendering",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (!cWindow) {
		printf("SDL_CreateWindow Failed\n");
		return false;
	}

	cRenderer = SDL_CreateRenderer(cWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!cRenderer) {
		printf("SDL_CreateRenderer Failed\n");
		return false;
	}

	if (!IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) {
		printf("IMG_Init Failed");
		return false;
	}

	return true;
}

bool ClipRendering::loadMedia() {
	if (!(spriteTexture.loadTexture(cRenderer, "Data/dots.png"))) {
		printf("loadTexture Failed\n");
		return false;
	}

	//spriteClips split the PNG into 4 parts
	spriteClips[0].x = 0;
	spriteClips[0].y = 0;
	spriteClips[0].w = 100;
	spriteClips[0].h = 100;

	spriteClips[1].x = 100;
	spriteClips[1].y = 0;
	spriteClips[1].w = 100;
	spriteClips[1].h = 100;

	spriteClips[2].x = 0;
	spriteClips[2].y = 100;
	spriteClips[2].w = 100;
	spriteClips[2].h = 100;

	spriteClips[3].x = 100;
	spriteClips[3].y = 100;
	spriteClips[3].w = 100;
	spriteClips[3].h = 100;


	return true;
}

void ClipRendering::close() {
	spriteTexture.free();
	SDL_DestroyWindow(cWindow);
	SDL_DestroyRenderer(cRenderer);
	SDL_Quit();
	IMG_Quit();
}


bool ClipRendering::Main() {
	if (!init()) return false;
	if (!loadMedia()) return false;

	SDL_Event event;
	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(cRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(cRenderer);
		//do the rendering work here		
		// For each spriteClip we do a render call.
		spriteTexture.render(cRenderer, 0, 0, &spriteClips[0]);
		spriteTexture.render(cRenderer, screenWidth - spriteClips[1].w, 0, &spriteClips[1]);
		spriteTexture.render(cRenderer, 0, screenHeight - spriteClips[2].h, &spriteClips[2]);
		spriteTexture.render(cRenderer, screenWidth - spriteClips[3].w, screenHeight - spriteClips[3].h, &spriteClips[3]);

		SDL_RenderPresent(cRenderer);
	}

	close();
	return true;
}



