#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include<Windows.h>
#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<vector>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<fstream>
#include<ctime>
#include<cmath>
#include<set>

static SDL_Window* g_window = nullptr;
static SDL_Renderer* g_screen = nullptr;
static SDL_Event g_event;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 0xff;
const int COLOR_KEY_G = 0xff;
const int COLOR_KEY_B = 0xff;

const int RENDERER_DRAW_COLOR = 0xff;

const std::string BACKGROUND_PATH = "image/background.png";


#define TILE_SIZE 16
#define MONEY_TILE 93
//#define WALL_TILE -1
//#define THREAT_TILE 200
#define MAX_DIE 3
const std::set<int> THREAT_TILES = {200, 201, 202, 203, 204, 205, 206, 207, 208, 209};

#define MAX_MAP_X 100
#define MAX_MAP_Y 100

#define FRAME_PER_SECOND 25

const  std::set<int> BLANK_TILE = { 0, 43, 1, 2, 12, 13, 14, 24, 25, 26, 36, 37, 38, 93};



typedef struct Map
{
	int startX, startY;

	int maxX, maxY;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* fileName;

};


typedef struct Input {
	int left;
	int right;
	int up;
	int down; 
};



bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

#endif // !COMMON_FUNC_H_
