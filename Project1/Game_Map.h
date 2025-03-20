#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#define MAX_TILES 300
#define MAX_LENGTH_IMAGE_FILE 30


#include"CommonFunc.h"
#include"BaseObject.h"

class tileMap : public BaseObject {
public:
	tileMap() {
		pObj = nullptr;
	};
	~tileMap() {};

};


class gameMap {
public:
	gameMap() {};
	~gameMap() {};

	void loadMap(const char* name);
	void loadTiles(SDL_Renderer* screen);
	void drawMap(SDL_Renderer* screen);
	Map getMapData() { return game_map_; }
	void setMap(Map& mapData) { game_map_ = mapData; }

private:
	Map game_map_;
	tileMap tileMat[MAX_TILES];

};
#endif // !GAME_MAP_H_
