
#include "BlitRendering.h"
#include "TextureRendering.h"
#include "ViewPort.h"
#include "Geometry.h"
#include "ColorKeying.h"

#define BLIT 1




int main(int argc, char *args[]) {

	TextureRandering* tr = new TextureRandering();
	BlitRendering* br = new BlitRendering();
	ViewPort* vp = new ViewPort();
	Geometry* gm = new Geometry();
	ColorKeying* ck = new ColorKeying();

	printf("Begin! \n");

	if (!ck->Main()) return -1;
	//gm->Main();
	//vp->Main();
	/*if (BLIT) {
		if (br->Main())
			return -1;
	}
	else {
		if (tr->Main())
			return -1;
	}*/

	return 0;
}

