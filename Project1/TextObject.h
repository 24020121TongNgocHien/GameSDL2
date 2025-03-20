#pragma once

#include"CommonFunc.h"
#include"BaseObject.h"

class TextObject {
public:
	TextObject();
	~TextObject();

	enum TextColor {
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2
	};

	bool loadFromRenderText(TTF_Font*, SDL_Renderer*);
	void free();
	void setColor(int type);

	void RenderText(SDL_Renderer*, int, int);
	int getWidth()const { return width; }
	int getHeight()const { return height; }

	void setText(const std::string str) {
		text = str;
	}
private:
	std::string text;
	SDL_Color textColor;
	SDL_Texture* texture;
	int width;
	int height;
};

void loadDetail(SDL_Renderer* screen, int numDied);
void loadGameOver(SDL_Renderer* screen);