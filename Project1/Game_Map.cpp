#include"Game_Map.h"
#include"ThreatObject.h"
void gameMap::loadMap(const char* name) {
	std::fstream file;
	file.open(name, std::ios:: in);

	game_map_.maxX = 0;
	game_map_.maxY = 0;

	if (file.is_open()) {
		for (int i = 0; i < MAX_MAP_Y; i++) {
			for (int j = 0; j < MAX_MAP_X; j++) {
				file >> game_map_.tile[i][j];
				int value = game_map_.tile[i][j];
				if (value >= 0) {
					if (j > game_map_.maxX) {
						game_map_.maxX = j;
					}

					if (i > game_map_.maxY) {
						game_map_.maxY = i;
					}

				}
			}
		}

		game_map_.maxX = (game_map_.maxX + 1) * TILE_SIZE;
		game_map_.maxY = (game_map_.maxY + 1) * TILE_SIZE;

		game_map_.startX = 0;
		game_map_.startY = 0;
	}

	file.close();
	//game_map_.fileName = name;
}

void gameMap::loadTiles(SDL_Renderer* screen) {
	char imagePath[MAX_LENGTH_IMAGE_FILE];

	for (int i = 0; i < MAX_TILES; i++) {
		if (i < 10) {
		sprintf_s(imagePath, "Tiles/tile_000%d.png", i);
		}
		else if(i >= 10 && i < 100) {
			sprintf_s(imagePath, "Tiles/tile_00%d.png", i);
		}
		else
		{
			sprintf_s(imagePath, "Tiles/tile_0%d.png", i);
		}
		std::fstream file;
		file.open(imagePath, std::ios::in);
		if (!file.is_open()) {
			continue;
		}
		else {
			file.close();
			tileMat[i].loadImage(imagePath, screen);
		}
	}
}

void gameMap::drawMap(SDL_Renderer* screen) {
	
	int x1 = 0;
	int x2 = 0;
	int map_x = 0;

	int y1 = 0;
	int y2 = 0;
	int map_y = 0;

	x1 = (game_map_.startX % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
	map_x = game_map_.startX / TILE_SIZE;

	y1 = (game_map_.startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);
	map_y = game_map_.startY / TILE_SIZE;

	for (int i = y1; i < y2; i += TILE_SIZE) {
		map_x = game_map_.startX / TILE_SIZE;

		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = game_map_.tile[map_y][map_x];
	
			if (val >= 0 && THREAT_TILES.find(val) == THREAT_TILES.end()) {
				tileMat[val].setRect(j, i);
				tileMat[val].renderImage(screen);
			}

			map_x++;
		}
		map_y++;
	}
}