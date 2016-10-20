#include "Include/Motion.h"

Dot::Dot(){
	xVelocity = 0;
	yVelocity = 0;
	xPosition = 0;
	yPosition = 0;
	velocityInterval = 10;
}

void Dot::handleEvent(SDL_Event* event){
	if(event->type == SDL_KEYDOWN && event->key.repeat == 0){
		switch(event->key.keysym.sym){
		    case SDLK_UP: 
				yVelocity -= velocityInterval; 
				break;
            case SDLK_DOWN: 
				yVelocity += velocityInterval; 
				break;
            case SDLK_LEFT: 
				xVelocity -= velocityInterval; 
				break;
            case SDLK_RIGHT: 
				xVelocity += velocityInterval; 
				break;
		}
	}
	else if(event->type == SDL_KEYUP && event->key.repeat == 0){
		switch(event->key.keysym.sym){
		    case SDLK_UP: 
				yVelocity += velocityInterval; 
				break;
            case SDLK_DOWN: 
				yVelocity -= velocityInterval; 
				break;
            case SDLK_LEFT: 
				xVelocity += velocityInterval; 
				break;
            case SDLK_RIGHT: 
				xVelocity -= velocityInterval; 
				break;
		}
	}
}

void Dot::move(int maxWidth, int maxHeight){
	xPosition+=xVelocity;
	if(xPosition<0 || xPosition + dotWidth > maxWidth)
		xPosition-=xVelocity;
	
	yPosition+=yVelocity;
	if(yPosition < 0 || yPosition + dotHeight > maxHeight)
		yPosition-=yVelocity;
}

void Dot::render(RenderTexture* texture, SDL_Renderer* renderer){
	texture->render(renderer, xPosition, yPosition);
}

void Dot::setVelocityInterval(int v){
	velocityInterval = v;
}

//===================================================
void Motion::close(){
	dotTexture.free();

	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
	IMG_Quit();
}

bool Motion::init(){
	
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL_Init() failed\n");
		return false;
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
		printf("SetHint Failed\n");
	}	
	mWindow = SDL_CreateWindow(
		"Motion",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if(!mWindow){
		printf("SDL_CreateWindow Failed\n");
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(!mRenderer){
		printf("SDL_CreateRenderer Failed\n");
		return false;
	}
	if(! IMG_Init(IMG_INIT_PNG) & (IMG_INIT_PNG)){
		printf("IMG_INIT() Failed\n");
		return false;
	}
	return true;
}

bool Motion::loadMedia(){
	if(!dotTexture.loadTexture(mRenderer, "Data/dot.bmp")){
		printf("loadTexture Failed\n");
		return false;
	}	
	return true;
}

bool Motion::Main(){
	if(!init()){
		printf("init() Failed\n");
		return false;
	}
	if(!loadMedia()){
		printf("loadMedia() Failed\n");
		return false;
	}
	
	bool quit = false;
	SDL_Event event;
	Dot dot;
	
	while(!quit){
		while(SDL_PollEvent(&event)!=0){
			if(event.type == SDL_QUIT){
				quit = true;
			}
			dot.handleEvent(&event);
		}
		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(mRenderer);
		
		dot.move(screenWidth, screenHeight);
		dot.render(&dotTexture, mRenderer);
		
		SDL_RenderPresent(mRenderer);
	}
	close();
	return true;
}

