#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include"CommonFunc.h"
#include"BaseObject.h"

const int BULLET_SPEED = 20;
const int BULLET_THREAT_SPEED = 10;

class BulletObject : public BaseObject {

public:
	BulletObject();
	~BulletObject();

	enum Bullet_Dir {
		DIR_RIGHT = 1,
		DIR_LEFT = 2,
		DIR_UP = 3,
		DIR_DOWN = 4
	};
	
	
	void setX(const int _x) { x = _x; }
	void setY(const int _y) { y = _y; }
	int getX() { return x; };
	int getY() { return y; };

	void setIsMove(const bool _isMove) {
		isMove = _isMove;
	}

	bool getIsMove() { return isMove; }

	void handleMove(const int& xBorder, const int& yBorder);

	void setBulletDir(const int& dir) {
		bulletDir = dir;
	}

	int getBulletDir() { return bulletDir; }

	void checkBullet(Map& dataMap);

	void setXPos(int x) { x_pos = x; }
	int getXPos() { return x_pos; }
	void setYPos(int y) { y_pos = y; }
	int getYPos() { return y_pos;}
	void setMapX(int x) { mapX = x; }
	void setMapY(int y) { mapY = y; }
	int getMapX() { return mapX; }
	int getMapY() { return mapY; }

	/*void setBulletType(const int type) { bulletType = type; }
	int getBulletType(){ return bulletType; }*/


private:
	// speed bullet
	int x;
	int y;
	bool isMove;
	int x_pos;
	int y_pos;
	int mapX;
	int mapY;
	
	int bulletDir;
	//int bulletType;
};

#endif // !BULLET_OBJECT_H_
