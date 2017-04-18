#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>

class ViewPort {
public:
	int Main();
	bool init();
	bool loadMedia(int index);
	void close();
	void setUpViewports();
	int getRand();
	void setUpNum();
	int getUniqueNum();
	void setDefaultTexture(int curr, int quad);

private:
	struct box {
		SDL_Rect location;
		int num;
		SDL_Texture* txt;
	};
	const int screenHeight = 600;
	const int screenWidth = 800;

	SDL_Renderer* vpRenderer = NULL;
	SDL_Window* vpWindow = NULL;
	SDL_Texture* vpTexture = NULL;
	SDL_Surface* vpWindowSurface = NULL;
	box viewports[4][4][2];
	int solution[32] = { 0 };
	
};