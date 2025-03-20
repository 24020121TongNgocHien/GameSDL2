#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include"CommonFunc.h"
#include"BaseObject.h"
#include"Game_Map.h"
#include"BulletObject.h"



#define MAX_FRAME 3

#define PLAYER_SPEED 10



class MainObject : public BaseObject {
public:

	MainObject();
	~MainObject();

	enum moveType {
		MOVE_LEFT = 0,
		MOVE_RIGHT = 1,
		MOVE_UP = 2,
		MOVE_DOWN = 3
	};
	bool loadImage(std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* screen);
	void HandleInputAction(SDL_Event event, SDL_Renderer* screen);

	void setClip();
	void doPlayer(Map &mapData);
	void checkMap(Map& mapData);

	void setMapXY(const int map_x, int map_y) {
		mapX = map_x;
		mapY = map_y;
	}

	void centerOnMap(Map& mapData);

	void SetBulletList(std::vector<BulletObject*> list) {
		BulletList = list;
	}

std::vector<BulletObject*> getBulletList() { return BulletList; }

void HandleBullet(SDL_Renderer* screen, Map& dataMap);

void removeBullet(const int& index);

void increaseMoney();
int getMoney() { return moneyCount; }

float getXPos() { return x_pos; }
float getYPos() { return y_pos; }

float getXVal() { return x_val; }
float getYVal() { return y_val; }

SDL_Rect getRectFrame();
private:
	// amount change x, y
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int widthFrame;
	int heightFrame;

	SDL_Rect frameClip[MAX_FRAME];

	Input inputType;
	int frameIndex;

	int status;

	int mapX;
	int mapY;

	std::vector<BulletObject*> BulletList;

	int moneyCount;

};

#endif // 
