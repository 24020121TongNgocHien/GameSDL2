#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include"CommonFunc.h"

class BaseObject {
public:
	BaseObject();
	~BaseObject();

	void setRect(const int& x, const int& y);
	SDL_Rect getRect()const;
	SDL_Texture* getObject() const;

	virtual bool loadImage(std::string, SDL_Renderer* screen);
	void renderImage(SDL_Renderer* des, const SDL_Rect* = nullptr);

	void free();

protected:
	SDL_Texture* pObj;
	SDL_Rect rect;

};

#endif // !BASE_OBJECT_H_
