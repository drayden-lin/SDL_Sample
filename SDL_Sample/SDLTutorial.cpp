
#include "BlitRendering.h"
#include "TextureRendering.h"
#include "ViewPort.h"
#include "Geometry.h"
#include "ColorKeying.h"
#include "ClipRendering.h"
#include "ColorModulation.h"
#include "AlphaBlending.h"
#include "MouseEvent.h"
#include "SpriteAnimation.h"
#include "RotationFlipping.h"
#include "TrueTypeFont.h"
#include "Timing.h"
#include "SoundEffects.h"

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

