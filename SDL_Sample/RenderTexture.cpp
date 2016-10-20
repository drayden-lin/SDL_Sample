#include "Include/RenderTexture.h"

RenderTexture::RenderTexture(){
	textureWidth = 0;
	textureHeight = 0;
	texture = NULL;
}

RenderTexture::~RenderTexture(){
	free();
}

bool RenderTexture::loadFontTexture(SDL_Renderer* renderer, TTF_Font* font, std::string str,  SDL_Color textColor ){
	free();
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, str.c_str(), textColor);
	if(!tempSurface){
		printf("TTF_RenderText_Solid() Failed\n");
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(!texture){
		printf("SDL_CreateTextureFromSurface() Failed\n");
		return false;
	}
	
	textureHeight = tempSurface->h;
	textureWidth = tempSurface->w;
	
	SDL_FreeSurface(tempSurface);
	return true;
}

bool RenderTexture::loadTexture(SDL_Renderer* renderer, std::string str){
	free();
	SDL_Surface* tempSurface = IMG_Load(str.c_str());
	if(!tempSurface){
		printf("TTF_RenderText_Solid() Failed\n");
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if(!texture){
		printf("SDL_CreateTextureFromSurface() Failed\n");
		return false;
	}
	
	textureHeight = tempSurface->h;
	textureWidth = tempSurface->w;
	
	SDL_FreeSurface(tempSurface);
	return true;	
}

void RenderTexture::setAlpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(texture, alpha);
}
void RenderTexture::setBlendMode(SDL_BlendMode blending){
	SDL_SetTextureBlendMode(texture, blending);
}
void RenderTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void RenderTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_Rect renderQuad = {x, y, textureWidth, textureHeight};
	
	if(clip){
		renderQuad.h = clip->h;
		renderQuad.w = clip->w;
	}
	
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int RenderTexture::getWidth(){
	return textureWidth;
}
int RenderTexture::getHeight(){
	return textureHeight;
}
void RenderTexture::free(){
	if(texture){
		SDL_DestroyTexture(texture);
		texture = NULL;
		textureWidth = 0;
		textureHeight = 0;
	}
}
