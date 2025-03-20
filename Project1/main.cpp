#include"CommonFunc.h"
#include"BaseObject.h"
#include"Game_Map.h"
#include"MainObject.h"
#include"ImpTimer.h"
#include"ThreatObject.h"
#include"TextObject.h"
#include"Music.h"


BaseObject g_background;
TTF_Font* Font = nullptr;
bool initData();
bool loadBackground(SDL_Renderer* screen,const std::string path);
void close();


int main(int argc, char* args[]) {

	srand(time(0));

	ImpTimer Timer;
	
	if (initData() == false) return -1;

	if (loadBackground(g_screen, BACKGROUND_PATH) == false) {
		return -1;
	}

	bool IS_QUIT = false;
	int numberDie = 0;

	//text
	TextObject markGame;
	markGame.setColor(TextObject::WHITE_TEXT);

	TextObject moneyCount;
	moneyCount.setColor(TextObject::WHITE_TEXT);
	int markVale = 0;

	
	gameMap game_map;
	game_map.loadMap("map/map.txt");	
	game_map.loadTiles(g_screen);


	Map mapData = game_map.getMapData();

	MainObject player;
	player.loadImage("image/sprite_right.png", g_screen);
	player.setClip();


	std::vector<ThreatObject*> listThreat = createThreat(mapData, g_screen);
	//std::cout << listThreat.size() << std::endl;

	// music
	Music bgMusic("Music/musicBackground.mp3");
	bgMusic.play();
	while (!IS_QUIT) {
		Timer.start();

		while (SDL_PollEvent(&g_event)) {
			if (g_event.type == SDL_QUIT) {
				IS_QUIT = true;
			}

			player.HandleInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(g_screen);

		g_background.renderImage(g_screen);

		game_map.drawMap(g_screen);
		player.HandleBullet(g_screen, mapData);
		player.setMapXY(mapData.startX, mapData.startY);
		player.doPlayer(mapData);
		player.show(g_screen);

		game_map.setMap(mapData);

		for (int i = 0; i < listThreat.size(); i++) {
			ThreatObject* pThreat = listThreat[i];
			if (pThreat != nullptr && pThreat->getXPos() >= mapData.startX && pThreat->getXPos() <= mapData.startX + SCREEN_WIDTH && pThreat->getYPos() >= mapData.startY && pThreat->getYPos() <= mapData.startY + SCREEN_HEIGHT) {
				pThreat->setMapXY(mapData.startX, mapData.startY);
				pThreat->handleMoveType(g_screen, player, mapData);
				pThreat->doThreat(mapData);
				//pThreat->MakeBullet(g_screen, player, mapData);
				pThreat->show(g_screen);

				SDL_Rect rectPlayer = player.getRectFrame();
				SDL_Rect rectThreat = pThreat->getRectFrame();
				bool bcol2 = CheckCollision(rectPlayer, rectThreat);
				if (bcol2) {
					numberDie++;
					if (numberDie < MAX_DIE) {
						player.setRect(0, 0);
						listThreat.erase(listThreat.begin() + i);
						pThreat->removeThreat();
						SDL_Delay(500);
					}
					else{
						IS_QUIT = true;
					}
				}
			}
		}

		std::vector<BulletObject*> bulletArr = player.getBulletList();
	
		for (int i = 0; i < bulletArr.size(); i++) {
			BulletObject* pBullet = bulletArr[i];
			if (pBullet != nullptr) {
				for (int j = 0; j < listThreat.size(); j++) {
					ThreatObject* objThreat = listThreat[j];
				
					if (objThreat != nullptr && objThreat->getXPos() >= mapData.startX && objThreat->getXPos() <= mapData.startX + SCREEN_WIDTH && objThreat->getYPos() >= mapData.startY && objThreat->getYPos() <= mapData.startY + SCREEN_HEIGHT) {
						SDL_Rect tRect;
						tRect.x = objThreat->getRect().x;
						tRect.y = objThreat->getRect().y;
						tRect.w = objThreat->getWidthFrame();
						tRect.h = objThreat->getHeightFrame();

						SDL_Rect bRect = pBullet->getRect();

						bool bCol = CheckCollision(bRect, tRect);
						if (bCol) {
							markVale++;
							player.removeBullet(i);
							objThreat->free();
							listThreat.erase(listThreat.begin() + j);
						}
					}
				}
			}
		}
	
		player.show(g_screen);


		// show text
		loadDetail(g_screen, numberDie);

	
		std::string coinVal = std::to_string(player.getMoney());
		moneyCount.setText(coinVal);
		moneyCount.loadFromRenderText(Font, g_screen);
		moneyCount.RenderText(g_screen, SCREEN_WIDTH - 65, 10);

		markGame.setText(std::to_string(markVale));
		markGame.loadFromRenderText(Font, g_screen);
		markGame.RenderText(g_screen, SCREEN_WIDTH - 65, 45);
 
		SDL_RenderPresent(g_screen);

		int realImpTime= Timer.getTicks();
		int timePerFrame = 1000 / FRAME_PER_SECOND;
		if (realImpTime < timePerFrame) {
			int timeDelay = timePerFrame - realImpTime;
			SDL_Delay(timeDelay);
		}
	}
	
	loadGameOver(g_screen);
	SDL_RenderPresent(g_screen);
	SDL_Delay(2000);
	for (int i = 0; i < listThreat.size(); i++) {
		ThreatObject* pthreat = listThreat[i];
		pthreat->free();
		pthreat = nullptr;
	}
	listThreat.clear();
	close();
	return 0;
}

bool initData() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("24020121 Tong Ngoc Hien", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (g_window == nullptr) {
		return false;
	}

	g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (g_screen == nullptr) {
		return false;
	}

	SDL_SetRenderDrawColor(g_screen, 0xff, 0xff, 0xff, 0xff);


	int imgFlag = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlag) & imgFlag)) {
		return false;
	}
	if (TTF_Init() == -1) {
		return false;
	}
	Font = TTF_OpenFont("font/dlxfont_.ttf", 15);
	if (Font == nullptr) {
		return false;
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0) return false;

	return true;
}


bool loadBackground(SDL_Renderer* screen,const std::string path ) {

	if (g_background.loadImage(path.c_str(), screen) == false) {
		return false;
	}
	return true;
}

void close() {

	g_background.free();

	SDL_DestroyRenderer(g_screen);
	g_screen = nullptr;

	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	SDL_Quit();
	IMG_Quit();
	
}

