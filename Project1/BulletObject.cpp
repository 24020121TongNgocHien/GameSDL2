#include"BulletObject.h"

BulletObject::BulletObject() {
	x = 0;
	y = 0;
	x_pos = 0;
	y_pos = 0;
	mapX = 0;
	mapY = 0;
	isMove = false;
}

BulletObject::~BulletObject() {

}

void BulletObject::handleMove(const int& xBorder, const int& yBorder) {
	
		/*rect.x = x_pos - mapX;
		rect.y = y_pos - mapY;*/
	switch (bulletDir)
	{
	case DIR_RIGHT:
	{
		//rect.x += x;
		rect.x += x;
		rect.y = y_pos - mapY + TILE_SIZE;
		if (rect.x >= xBorder) {
			isMove = false;
		}
		break;
	}

	case DIR_LEFT:
	{
		rect.x -= x;
		rect.y = y_pos - mapY + TILE_SIZE ;
		if (rect.x <= 0) {
			isMove = false;
		}
		break;
	}
	case DIR_UP:
	{
		rect.y -= y;
		rect.x = x_pos - mapX + TILE_SIZE ;
		if (rect.y <= 0) {
			isMove = false;
		}
		break;
	}
	case DIR_DOWN:
	{
		rect.y += y;
		rect.x = x_pos - mapX ;
		if (rect.y >= yBorder) {
			isMove = false;
		}
		break;
	}
	default:
		isMove = false;
		break;
	}
}

void BulletObject::checkBullet(Map& dataMap) {
	//x1y1/..................x2y1
	

	//x1y2.....................x2y2

	int x1 = (rect.x + dataMap.startX ) / TILE_SIZE;
	//int x2 = (rect.x + dataMap.startX + TILE_SIZE - 1) / TILE_SIZE;
	int y1 = (rect.y + dataMap.startY ) / TILE_SIZE;
	//int y2 = (rect.y + dataMap.startY + TILE_SIZE - 1) / TILE_SIZE;
	int val = dataMap.tile[y1][x1];
	if (BLANK_TILE.find(val) == BLANK_TILE.end()) {
		//dataMap.tile[y1][x1] = BLANK_TILE;
		isMove = false;
		std::cout << "bullet touch wall" << std::endl;
	}

	/*if (bulletDir == DIR_RIGHT) {
		if (dataMap.tile[y1][x1] == WALL_TILE) {
			dataMap.tile[y1][x1] = BLANK_TILE;
			isMove = false;
		}
	}
	else if (bulletDir == DIR_LEFT) {
		if (x1 > 0 && dataMap.tile[y1][x1 - 1] == WALL_TILE) {
			dataMap.tile[y1][x1 - 1] = BLANK_TILE;
			isMove = false;
		}
	}
	else if (bulletDir == DIR_DOWN) {
		if (dataMap.tile[y2][x1] == WALL_TILE) {
			dataMap.tile[y2][x1] = BLANK_TILE;
			isMove = false;
		}
	}
	else if (bulletDir == DIR_UP) {
		if (y1 > 0 && dataMap.tile[y1 - 1][x1] == WALL_TILE) {
			dataMap.tile[y1 - 1][x1] = BLANK_TILE;
			isMove = false;
		}
	}*/


}