#include"MainObject.h"

MainObject::MainObject() {
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	widthFrame = 0;
	heightFrame = 0;
	frameIndex = 0;
	status = MOVE_RIGHT;

	inputType.left = 0;
	inputType.right = 0;
	inputType.down = 0;
	inputType.up = 0;

	mapX = 0;
	mapY = 0;

	moneyCount = 0;
}

MainObject::~MainObject() {

}

bool MainObject::loadImage(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	if (ret == true) {
		widthFrame = rect.w / MAX_FRAME;
		heightFrame = rect.h;

	}

	return ret;
}

void MainObject::setClip() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < MAX_FRAME; i++) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;

		}
	}
}

void MainObject::show(SDL_Renderer* screen) {
	if (status == MOVE_LEFT) {
		loadImage("image/sprite_left.png", screen);
	}
	else if (status == MOVE_DOWN) {
		loadImage("image/sprite_down.png", screen);
	}
	else if (status == MOVE_UP) {
		loadImage("image/sprite_up.png", screen);
	}
	else {
		loadImage("image/sprite_right.png", screen);
	}
	


	if (frameIndex >= MAX_FRAME) {
		frameIndex = 0;
	}
	if (inputType.left == 1 || inputType.right == 1 || inputType.down == 1 || inputType.up == 1) {
		frameIndex++;
	}
	else {
		frameIndex = 0;
	}

	rect.x = x_pos - mapX;
	rect.y = y_pos - mapY;

	SDL_Rect* currentClip = &frameClip[frameIndex];
	SDL_Rect renderQuad = { rect.x, rect.y, widthFrame, heightFrame };

	SDL_RenderCopy(screen, pObj, currentClip, &renderQuad);

}

void MainObject::HandleInputAction(SDL_Event event, SDL_Renderer* screen) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			status = MOVE_RIGHT;
			inputType.right = 1;
			break;
		case SDLK_LEFT:
			status = MOVE_LEFT;
			inputType.left = 1;
			break;
		case SDLK_UP:
			status = MOVE_UP;
			inputType.up = 1;
			break;
		case SDLK_DOWN:
			status = MOVE_DOWN;
			inputType.down = 1;
			break;
		case SDLK_SPACE:
		{
			BulletObject* newBullet = new BulletObject();
			std::cout << "Number bullets: " << BulletList.size() << std::endl;

			switch(status)
			{
				case MOVE_RIGHT: {
					newBullet->loadImage("image/bullet_right.png", screen);
					newBullet->setBulletDir(BulletObject::DIR_RIGHT);
					newBullet->setRect(rect.x + widthFrame / 2, rect.y + heightFrame/2);
					newBullet->setXPos(x_pos);
					newBullet->setYPos(y_pos);

					break;
				}
				case MOVE_LEFT: {
					newBullet->loadImage("image/bullet_left.png", screen);
					newBullet->setBulletDir(BulletObject::DIR_LEFT);
					newBullet->setRect(rect.x, rect.y + heightFrame / 2);
					newBullet->setXPos(x_pos);
					newBullet->setYPos(y_pos);

					break;
				}
				case MOVE_UP: {
					newBullet->loadImage("image/bullet_up.png", screen);
					newBullet->setBulletDir(BulletObject::DIR_UP);
					newBullet->setRect(rect.x + widthFrame/2, rect.y);
					newBullet->setXPos(x_pos);
					newBullet->setYPos(y_pos);

					break;
				}
				case MOVE_DOWN:{
					newBullet->loadImage("image/bullet_down.png", screen);
					newBullet->setBulletDir(BulletObject::DIR_DOWN);
					newBullet->setRect(rect.x - widthFrame / 2, rect.y + heightFrame / 2);
					newBullet->setXPos(x_pos);
					newBullet->setYPos(y_pos);

					break;
				}
			
				default:
				break;
			}
			
			newBullet->setX(BULLET_SPEED);
			newBullet->setY(BULLET_SPEED);
			newBullet->setIsMove(true);

			BulletList.push_back(newBullet);
			break;
		}
		default:
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			inputType.right = 0;
			break;
		case SDLK_LEFT:
			inputType.left = 0;
			break;
		case SDLK_UP:
			inputType.up = 0;
			break;
		case SDLK_DOWN:
			inputType.down = 0;
			break;
		default:
			break;
		}
	}
}


void MainObject::doPlayer(Map &mapData) {
	x_val = 0;
	y_val = 0;
	
	if (inputType.right == 1) {
		x_val += PLAYER_SPEED;
	}
	else if (inputType.left == 1) {
		x_val -= PLAYER_SPEED;
	}
	else if (inputType.down == 1) {
		y_val += PLAYER_SPEED;
	}
	else if (inputType.up == 1) {
		y_val -= PLAYER_SPEED;
	}


	checkMap(mapData);

	centerOnMap(mapData);
}

void MainObject::checkMap(Map& mapData) {
	
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	//check right left

	int minHeight = min(heightFrame, TILE_SIZE);
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + widthFrame - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + minHeight - 1) / TILE_SIZE;
	
	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (x_val >= 0) {
			int val1 = mapData.tile[y1][x2];
			int val2 = mapData.tile[y2][x2];

			if (val1 == MONEY_TILE || val2 == MONEY_TILE) {
				mapData.tile[y1][x2] = 0;
				mapData.tile[y2][x2] = 0;
				increaseMoney();
			}
			else {
				if ( BLANK_TILE.find(val1) == BLANK_TILE.end() || BLANK_TILE.find(val2) == BLANK_TILE.end()) {
					x_pos = x2 * TILE_SIZE;
					x_pos -= widthFrame + 1;
					x_val = 0;
					std::cout << "player touch obstacle" << std::endl;
				}
			}
			
		}
		else if (x_val < 0) {
			int val1 = mapData.tile[y1][x1];
			int val2 = mapData.tile[y2][x1];
			
			if (val1 == MONEY_TILE || val2 == MONEY_TILE) {
				mapData.tile[y1][x1] = 0;
				mapData.tile[y2][x1] = 0;
				increaseMoney();

			}
			else if (BLANK_TILE.find(val1) == BLANK_TILE.end() || BLANK_TILE.find(val2) == BLANK_TILE.end()) {
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
				std::cout << "player touch obstacle" << std::endl;
			}
		}
			
	}

	// check up down

	int minWidth = min(widthFrame, TILE_SIZE);
	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + minWidth - 1) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + heightFrame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (y_val >= 0) {
			int val1 = mapData.tile[y2][x1];
			int val2 = mapData.tile[y2][x2];

			if (val1 == MONEY_TILE || val2 == MONEY_TILE) {
				mapData.tile[y2][x1] = 0;
				mapData.tile[y2][x2] = 0;
				increaseMoney();
			}
			else if (BLANK_TILE.find(val1) == BLANK_TILE.end() || BLANK_TILE.find(val2) == BLANK_TILE.end()) {
				y_pos = y2 * TILE_SIZE;
				y_pos -= heightFrame + 1;
				y_val = 0;
				std::cout << "player touch obstacle" << std::endl;
			}
		}
		else if (y_val < 0) {
			int val1 = mapData.tile[y1][x1];
			int val2 = mapData.tile[y1][x2];
			if (val1 == MONEY_TILE || val2 == MONEY_TILE) {
				mapData.tile[y1][x1] = 0;
				mapData.tile[y1][x2] = 0;
				increaseMoney();
			}
			if (BLANK_TILE.find(val1) == BLANK_TILE.end() || BLANK_TILE.find(val2) == BLANK_TILE.end()) {
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
				std::cout << "player touch obstacle" << std::endl;
			}
		}
	}

	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0) {
		x_pos = 0;
	}
	if (y_pos < 0) {
		y_pos = 0;
	}

	if (x_pos + widthFrame > mapData.maxX) {
		x_pos = mapData.maxX - widthFrame - 1;
	}
	if (y_pos + heightFrame > mapData.maxY) {
		y_pos = mapData.maxY - heightFrame - 1;
	}
}

void MainObject::centerOnMap(Map& mapData) {
	mapData.startX = (x_pos - SCREEN_WIDTH / 2);
	if (mapData.startX < 0) {
		mapData.startX = 0;
	}
	else if (mapData.startX + SCREEN_WIDTH >= mapData.maxX) {
		mapData.startX = mapData.maxX - SCREEN_WIDTH;
	}

	mapData.startY = (y_pos - SCREEN_HEIGHT / 2);
	if (mapData.startY < 0) {
		mapData.startY = 0;
	}
	else if (mapData.startY + SCREEN_HEIGHT >= mapData.maxY) {
		mapData.startY = mapData.maxY - SCREEN_HEIGHT;
	}

}


void MainObject::HandleBullet(SDL_Renderer* screen, Map& dataMap) {
	
	for (int i = 0; i < BulletList.size(); i++) {
		BulletObject* currentBullet = BulletList[i];
		if (currentBullet != nullptr) {
			if (currentBullet->getIsMove() == true) {
				currentBullet->setMapX(dataMap.startX);
				currentBullet->setMapY(dataMap.startY);
				currentBullet->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				//std::cout << dataMap.startX << "  " << dataMap.startY << std::endl;
				currentBullet->renderImage(screen);
				currentBullet->checkBullet(dataMap);
			}
		else {
			BulletList.erase(BulletList.begin() + i);
			if (currentBullet != nullptr) {
				delete currentBullet;
				currentBullet = nullptr;
			}
		}
		}
	}
}

void MainObject::increaseMoney() {
	moneyCount++;
}

void MainObject::removeBullet(const int& index) {
	int size = BulletList.size();
	if (size > 0 && index < size) {
		BulletObject* pBullet = BulletList[index];
		BulletList.erase(BulletList.begin() + index);
		if (pBullet) {
			delete	pBullet;
			pBullet = nullptr;
		}
	}
}


SDL_Rect MainObject::getRectFrame() {
	SDL_Rect rectFrame;
	rectFrame.x = rect.x;
	rectFrame.y = rect.y;
	rectFrame.w = widthFrame;
	rectFrame.h = heightFrame;
	return rectFrame;
}