
#include "Include/BlitRendering.h"
#include "Include/TextureRendering.h"
#include "Include/ViewPort.h"
#include "Include/Geometry.h"
#include "Include/ColorKeying.h"
#include "Include/ClipRendering.h"
#include "Include/ColorModulation.h"
#include "Include/AlphaBlending.h"
#include "Include/MouseEvent.h"
#include "Include/SpriteAnimation.h"
#include "Include/RotationFlipping.h"
#include "Include/TrueTypeFont.h"
#include "Include/Timing.h"
#include "Include/SoundEffects.h"

#define BLIT 1

int main(int argc, char *args[]) {

	TextureRandering tr;
	BlitRendering br;
	ViewPort vp;
	Geometry gm;
	ColorKeying ck;
	ClipRendering cr;
	ColorModulation cm;
	AlphaBlending ab;
	SpriteAnimation sa;
	RotationFlipping rf;
	TrueTypeFont ttf;
	Timing t;
	SoundEffects se;
	MouseEvent me;
	

	if (!me.Main()) {
		SDL_Delay(3000);
		return -1;
	}

	return 0;
}

