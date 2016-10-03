spriteTexture::spriteTexture() {
	spriteWidth = 0;
	spriteHeight = 0;
	texture = NULL;
}
spriteTexture::~spriteTexture() {
	free();
}
bool spriteTexture::loadTexture(SDL_Renderer* renderer, std::string path) {
	free();
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL) {
		printf("IMG_Load Failed\n");
		return false;
	}
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (texture == NULL) {
		printf("SDL_CreateTextureFromSurface() Failed\n");
		return false;
	}
	spriteWidth = tempSurface->w;
	spriteHeight = tempSurface->h;

	SDL_FreeSurface(tempSurface);
	return true;
}
void spriteTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
	SDL_Rect renderQuad = { x, y, spriteWidth, spriteHeight };

	if (clip) {
		renderQuad.h = clip->h;
		renderQuad.w = clip->w;
	}
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}
void spriteTexture::free() {
	if (texture) {
		SDL_DestroyTexture(texture);
		spriteWidth = 0;
		spriteHeight = 0;
	}
}

screenButton::screenButton() {
	position.x = 0;
	position.y = 0;
}
