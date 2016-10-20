#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class RenderTexture{
	public:
		RenderTexture();
		~RenderTexture();
		bool loadFontTexture(SDL_Renderer* renderer, TTF_Font* font, std::string str, SDL_Color textColor );
		bool loadTexture(SDL_Renderer* renderer, std::string str);
		void setAlpha(Uint8 alpha);
		void setBlendMode(SDL_BlendMode blending);
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void render(SDL_Renderer* renderer, int x, int y, 
            SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void free();
		int getWidth();
		int getHeight();
	private:
		int textureWidth;
		int textureHeight;
		SDL_Texture* texture;
};
