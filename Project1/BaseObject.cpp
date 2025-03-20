#include"BaseObject.h"


BaseObject::BaseObject() {
	pObj = nullptr;
	rect.x = 0;
	rect.y = 0;
	rect.h = 0;
	rect.w = 0;
}
BaseObject::~BaseObject() {
	free();
}

void BaseObject::setRect(const int& x, const int& y) {
	rect.x = x;
	rect.y = y;
}
SDL_Rect BaseObject::getRect()const {
	return rect;
}
SDL_Texture* BaseObject::getObject() const {
	return pObj;
}

bool BaseObject::loadImage(std::string path, SDL_Renderer *screen) {
	free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedImg = nullptr;
	loadedImg = IMG_Load(path.c_str());
	if (loadedImg == nullptr) {
		std::cout << "Error:" << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetColorKey(loadedImg, SDL_TRUE, SDL_MapRGB(loadedImg->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
	
	newTexture = SDL_CreateTextureFromSurface(screen, loadedImg);
	

	if (newTexture == nullptr) {
		std::cout << "Error:" << SDL_GetError() << std::endl;
		return false;
	}
	rect.w = loadedImg->w;
	rect.h = loadedImg->h;

	SDL_FreeSurface(loadedImg);
	pObj = newTexture;

	return pObj != nullptr;
}
void BaseObject::renderImage(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderQuad = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(des, pObj, clip, &renderQuad);
}

void BaseObject::free() {
	if (pObj != nullptr) {
		SDL_DestroyTexture(pObj);
		pObj = nullptr;
		rect.w = 0;
		rect.h = 0;
	}
}