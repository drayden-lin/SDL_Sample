#include "MouseEvent.h"
#if 1
spriteTexture::spriteTexture() {
	spriteWidth = 0;
	spriteHeight = 0;
	texture = NULL;
}
spriteTexture::~spriteTexture() {
	free();
}
bool spriteTexture::loadTexture(SDL_Renderer* renderer, std::string path) {
	free();
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) {
		printf("IMG_Load Failed\n");
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == NULL) {
		printf("SDL_CreateTextureFromSurface() Failed\n");
		return false;
	}
	spriteWidth = tempSurface->w;
	spriteHeight = tempSurface->h;

	SDL_FreeSurface(tempSurface);
	return true;
}
void spriteTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = { x, y, spriteWidth, spriteHeight };

	if (clip) {
		renderQuad.h = clip->h;
		renderQuad.w = clip->w;
	}
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}
void spriteTexture::free() {
	if (texture) {
		SDL_DestroyTexture(texture);
		spriteWidth = 0;
		spriteHeight = 0;
	}
}
int spriteTexture::getWidth(){
    return spriteWidth;
}
int spriteTexture::getHeight(){
    return spriteHeight;
}

//ScreenButton

screenButton::screenButton() {
	position.x = 0;
	position.y = 0;
    currentTexture = MOUSE_OUT;
}

int screenButton::getButtonHeight() {
	return buttonHeight;
}
int screenButton::getButtonWidth() {
	return buttonWidth;
}
void screenButton::handleEvent(SDL_Event* event){
    if(event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP ){
        int mouseX, mouseY;
        bool isInside = true;
        SDL_GetMouseState(&mouseX, &mouseY);
        
        //see if mouse is inside the button
        if(mouseX < position.x)
            isInside = false;
        else if(mouseX > position.x + buttonWidth)
            isInside = false;
        else if(mouseY < position.y)
            isInside = false;
        else if(mouseY > position.y + buttonHeight)
            isInside = false;

        if(!isInside){
            // mouse falls outside of the button
            currentTexture = MOUSE_OUT;
        }
        else{
            switch(event->type)
            {
            case SDL_MOUSEMOTION:
                currentTexture = MOUSE_OVER;
                break;
            case SDL_MOUSEBUTTONDOWN:
                currentTexture = MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                currentTexture = MOUSE_UP;
                break;
            }        
        }
    }
}

void screenButton::render(spriteTexture* texture, SDL_Renderer* renderer, SDL_Rect spriteClip[]){
    texture->render(renderer, position.x, position.y, &spriteClip[currentTexture]);
}

void screenButton::setPosition(int x, int y){
    position.x = x;
    position.y = y;
}

//Mouse Event

bool MouseEvent::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL_Init() Failed\n");
		return false;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("SDL_SetHint() Failed\n");
	}

	meWindow = SDL_CreateWindow("Mouse Event", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (meWindow == NULL) {
		printf("SDL_CreateWindow Failed\n");
		return false;
	}

	meRenderer = SDL_CreateRenderer(meWindow, -1, SDL_RENDERER_ACCELERATED);
	if (meRenderer == NULL) {
		printf("SDL_CreateRenderer() Failed\n");
		return false;
	}

	if (! (IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)) {
		printf("IMG_Init() Failed\n");
		return false;
	}

	return true;
}

bool MouseEvent::loadMedia() {
	meTexture.loadTexture(meRenderer, "Data/button.png");

	for (int i = 0; i < TOTAL_SPRITE; i++) {
		spriteClip[i].x = 0;
		spriteClip[i].y = i * 200;
		spriteClip[i].w = meButton[i].getButtonWidth();
		spriteClip[i].h = meButton[i].getButtonHeight();
	}

	meButton[0].setPosition(0,0);
	meButton[1].setPosition(screenWidth - 300, 0);
	meButton[2].setPosition(0, screenHeight - 200);
	meButton[3].setPosition(screenWidth - 300, screenHeight - 200);
	return true;
}

void MouseEvent::close() {
	meTexture.free();

	SDL_DestroyRenderer(meRenderer);
	SDL_DestroyWindow(meWindow);
	meRenderer = NULL;
	meWindow = NULL;

	SDL_Quit();
	IMG_Quit();
}

bool MouseEvent::Main() {
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

	while (!quit){
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			for (int i = 0; i < TOTAL_SPRITE; i++) {
				meButton[i].handleEvent(&event);
			}

		}
		SDL_SetRenderDrawColor(meRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(meRenderer);

		for (int i = 0; i < TOTAL_SPRITE; i++) {
			meButton[i].render(&meTexture, meRenderer, spriteClip);
		}

		SDL_RenderPresent(meRenderer);
	}
	return true;
}
#endif
