#pragma once
#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

const int TR_SCREEN_WIDTH = 800;
const int TR_SCREEN_HEIGHT = 600;

int TRMain();
bool TRinit();
bool TRloadMedia();
void TRclose();

SDL_Texture* loadMediaTexture(std::string path);
