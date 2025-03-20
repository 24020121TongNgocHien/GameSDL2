#include"TextObject.h"

TextObject::TextObject() {
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	texture = nullptr;
}

TextObject::~TextObject() {

}

bool TextObject::loadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
	SDL_Surface* textsurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textsurface) {
		texture = SDL_CreateTextureFromSurface(screen, textsurface);
		width = textsurface->w;
		height = textsurface->h;
		SDL_FreeSurface(textsurface);
		textsurface = nullptr;
	}

	return texture != nullptr;
}

void TextObject::free() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void TextObject::setColor(int type) {
	if (type == RED_TEXT) {
		SDL_Color color = { 255, 0, 0 };
		textColor = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Color color = { 255, 255, 255 };
		textColor = color;
	}
	else if (type == BLACK_TEXT) {
		SDL_Color color = { 0, 0, 0 };
		textColor = color;
	}
}

void TextObject::RenderText(SDL_Renderer* screen, int x, int y) {
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy(screen, texture, nullptr, &renderQuad);


}

void loadDetail(SDL_Renderer* screen, int numDied) {
	BaseObject coin;
	BaseObject heart;
	BaseObject mark;
	coin.loadImage("image/coin.png", screen);
	coin.setRect(SCREEN_WIDTH - 100, 0);
	coin.renderImage(screen);

	for (int i = 0; i < MAX_DIE - numDied; i++) {
		heart.loadImage("image/heart.png", screen);
		heart.setRect(10 + 32*i, 0);
		heart.renderImage(screen);
	}

	mark.loadImage("image/tile_201.png", screen);
	mark.setRect(SCREEN_WIDTH - 100, 35);
	mark.renderImage(screen);
}

void loadGameOver(SDL_Renderer* screen) {
	TTF_Font* font = TTF_OpenFont("font/dlxfont_.ttf", 150);
	TextObject over;
	over.setText("GAME");
	over.loadFromRenderText(font, screen);
	over.RenderText(screen, SCREEN_WIDTH/2 - over.getWidth()/2, SCREEN_HEIGHT/5 );

	over.setText("OVER");
	over.loadFromRenderText(font, screen);
	over.RenderText(screen, SCREEN_WIDTH / 2 - over.getWidth() / 2, SCREEN_HEIGHT / 2  );
}