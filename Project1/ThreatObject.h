#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include"CommonFunc.h"
#include"BaseObject.h"
#include"MainObject.h"
#include"BulletObject.h"

#define THREAT_FRAME_MAX 1
#define THREAT_SPEED 1
#define MAX_DISTANCE_BULLET 200


class ThreatObject :public BaseObject {
public:
	ThreatObject();
	~ThreatObject();

	enum TYPE_MOVE {
		THREAT_MOVE_RIGHT = 1,
		THREAT_MOVE_LEFT = 2,
		THREAT_MOVE_UP = 3,
		THREAT_MOVE_DOWN = 4,
		TOTAL_THREAT_MOVE = 5
	};

	void setXVal(const float& x) { xVal = x; }
	void setYVal(const float& y) { yVal = y; }

	void setXPos(const float& x) { xPos = x; }
	void setYPos(const float& y) { yPos = y; }

	float getXPos()const { return xPos; }
	float getYPos()const { return yPos; }

	void setMapXY(const int& x, const int& y) { xMap = x; yMap = y; }

	void setClips();
	bool loadImg(std::string path, SDL_Renderer* screen);

	void show(SDL_Renderer* des);
	int getWidthFrame() { return widthFrame; }
	int getHeightFrame() { return heightFrame; }

	int getTypeMove() { return typeMove; }
	
	void doThreat(Map& dataMap);

	void checkMap(Map& dataMap);

	void setTypeMove(const int& typeMove) { this->typeMove = typeMove; }
	void handleMoveType(SDL_Renderer* screen, MainObject& player, Map& mapData);

	/*std::vector<BulletObject*> getBulletList() const { return bulletList; }
	void setBulletList(std::vector<BulletObject*>& list) { bulletList = list; }
	void MakeBullet(SDL_Renderer* screen, MainObject , Map& dataMap);
	void InitBullet(BulletObject* pBullet, SDL_Renderer* screen);*/

	SDL_Rect getRectFrame();

	void removeThreat();

private:
	int frameIndex;
	int widthFrame;
	int heightFrame;
	SDL_Rect frameClip[THREAT_FRAME_MAX];
	float xPos;
	float yPos;
	float xVal;
	float yVal;
	int xMap;
	int yMap;
	int typeMove;

	std::vector<BulletObject*> bulletList;

};


std::vector<ThreatObject*> createThreat(Map& dataMap, SDL_Renderer* screen);


#endif // !THREAT_OBJECT_H_
