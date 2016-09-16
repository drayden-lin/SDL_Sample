
#include "BlitRendering.h"
#include "TextureRendering.h"
#define BLIT 0
#define TEXTURE 0



int main(int argc, char *args[]) {

	if (BLIT) {
		if (blitMain())
			return -1;
	}
	else {
		if (TRMain())
			return -1;
	}

	return 0;
}

