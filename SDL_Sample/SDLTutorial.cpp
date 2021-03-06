
#include "Include/BlitRendering.h"
#include "Include/ViewPort.h"
#include "Include/Determination.h"
/*#include "Include/TextureRendering.h"

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
//#include "Include/Framerate.h"
//#include "Include\AdvanceTiming.h"
#include "Include\Motion.h"*/
#include <string>
#include <cstdlib>

#define BLIT 1

int main(int argc, char *args[]) {

	
	BlitRendering br;
	ViewPort vp;
	Determination dt;
	/*TextureRandering tr;
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
	//Framerate fr;
	//AdvanceTiming at;
	Motion m;*/
	
	bool twoBackCancelling = true;

	if (twoBackCancelling) {
		if (!dt.Main()) {
			SDL_Delay(3000);
			return -1;
		}
	}
	else {
		if (!vp.Main()) {
			SDL_Delay(3000);
			return -1;
		}
	}

	return 0;
}
