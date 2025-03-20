#include"ThreatObject.h"

ThreatObject::ThreatObject() {
	widthFrame = 0;
	heightFrame = 0;
	xVal = 0;
	yVal = 0;
	xPos = 0;
	yPos = 0;
	frameIndex = 0;
	typeMove = rand() % (TOTAL_THREAT_MOVE - 1) + 1;
}

ThreatObject::~ThreatObject(){}

bool ThreatObject::loadImg(std::string path, SDL_Renderer* screen) {
	bool ret = BaseObject::loadImage(path, screen);
	std::cout << SDL_GetError() << std::endl;
	if (ret == false) return false;

	widthFrame = rect.w / THREAT_FRAME_MAX;
	heightFrame = rect.h;
	return ret;
}

void ThreatObject::setClips() {
	if (widthFrame > 0 && heightFrame > 0) {
		for (int i = 0; i < THREAT_FRAME_MAX; i++) {
			frameClip[i].x = i * widthFrame;
			frameClip[i].y = 0;
			frameClip[i].w = widthFrame;
			frameClip[i].h = heightFrame;

		}
	}
}

void ThreatObject::show(SDL_Renderer* des) {
	rect.x = xPos - xMap;
	rect.y = yPos - yMap;
	frameIndex++;
	if (frameIndex >= THREAT_FRAME_MAX) {
		frameIndex = 0;
	}

	SDL_Rect* rectClip = &frameClip[frameIndex];
	SDL_Rect renderQuad = { rect.x, rect.y, widthFrame, heightFrame };
	//std::cout << SDL_GetError() << std::endl;
	SDL_RenderCopy(des, pObj, rectClip, &renderQuad);
}

void ThreatObject::doThreat(Map& dataMap) {
	if (typeMove == THREAT_MOVE_RIGHT) {
		xVal = THREAT_SPEED;
	}
	else if (typeMove == THREAT_MOVE_LEFT) {
		xVal = -THREAT_SPEED;
	}
	else if (typeMove == THREAT_MOVE_UP) {
		yVal = -THREAT_SPEED;
	}
	else if (typeMove == THREAT_MOVE_DOWN) {
		yVal = THREAT_SPEED;
	}
	//std::cout << xVal << " " << yVal << std::endl;
	checkMap(dataMap);

}

void ThreatObject::checkMap(Map& mapData) {
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	//check right left

	int minHeight = min(heightFrame, TILE_SIZE);
	x1 = (xPos + xVal) / TILE_SIZE;
	x2 = (xPos + xVal + widthFrame - 1) / TILE_SIZE;

	y1 = (yPos) / TILE_SIZE;
	y2 = (yPos + minHeight - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (xVal >= 0) {
			int val1 = mapData.tile[y1][x2];
			int val2 = mapData.tile[y2][x2];
			// BLANK_TILE.find(val1) == BLANK_TILE.end() || BLANK_TILE.find(val2) == BLANK_TILE.end()

				if ((BLANK_TILE.find(val1) == BLANK_TILE.end() && val1 != MONEY_TILE )|| (BLANK_TILE.find(val2) == BLANK_TILE.end() && val2 != MONEY_TILE)) {
					
					xVal = 0;
					typeMove = THREAT_MOVE_LEFT;
				}
			

		}
		else if (xVal < 0) {
			int val1 = mapData.tile[y1][x1];
			int val2 = mapData.tile[y2][x1];

			if ((BLANK_TILE.find(val1) == BLANK_TILE.end() && val1 != MONEY_TILE) || (BLANK_TILE.find(val2) == BLANK_TILE.end() && val2 != MONEY_TILE)) {
				
				xVal = 0;
				typeMove =THREAT_MOVE_RIGHT;
			}
		}

	}

	// check up down

	int minWidth = min(widthFrame, TILE_SIZE);
	x1 = xPos / TILE_SIZE;
	x2 = (xPos + minWidth - 1) / TILE_SIZE;

	y1 = (yPos + yVal) / TILE_SIZE;
	y2 = (yPos + yVal + heightFrame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (yVal >= 0) {
			int val1 = mapData.tile[y2][x1];
			int val2 = mapData.tile[y2][x2];

			if ((BLANK_TILE.find(val1) == BLANK_TILE.end() && val1 != MONEY_TILE) || (BLANK_TILE.find(val2) == BLANK_TILE.end() && val2 != MONEY_TILE)) {
			
				yVal = 0;
				typeMove = THREAT_MOVE_UP;
			}
		}
		else if (yVal < 0) {
			int val1 = mapData.tile[y1][x1];
			int val2 = mapData.tile[y1][x2];
			
			if ((BLANK_TILE.find(val1) == BLANK_TILE.end() && val1 != MONEY_TILE) || (BLANK_TILE.find(val2) == BLANK_TILE.end() && val2 != MONEY_TILE)) {
				
				yVal = 0;
				typeMove = THREAT_MOVE_DOWN;
			}
		}
		if (rand() % 10 == 0) {
			typeMove = rand() % TOTAL_THREAT_MOVE;
		}

	}

	xPos += xVal;
	yPos += yVal;

	if (xPos < 0) {
		xPos = 0;
	}
	if (yPos < 0) {
		yPos = 0;
	}

	if (xPos + widthFrame > mapData.maxX) {
		xPos = mapData.maxX - widthFrame - 1;
	}
	if (yPos + heightFrame > mapData.maxY) {
		yPos = mapData.maxY - heightFrame - 1;
	}

}


void ThreatObject::handleMoveType(SDL_Renderer* screen, MainObject& player, Map& mapData) {
	int threatX = getXPos();
	int threatY = getYPos();

	int playerX = player.getXPos();
	int playerY = player.getYPos();

	int dx = playerX - threatX;
	int dy = playerY - threatY;

	bool moved = false;

	
	if (abs(dx) > abs(dy)) {
		int val1 = mapData.tile[threatY / TILE_SIZE][(threatX + TILE_SIZE) / TILE_SIZE];
		int val2 = mapData.tile[threatY / TILE_SIZE][(threatX - TILE_SIZE) / TILE_SIZE];
		if (dx > 0 && BLANK_TILE.find(val1) != BLANK_TILE.end()) {
			typeMove = THREAT_MOVE_RIGHT;
			moved = true;
		}
		else if (dx < 0 && BLANK_TILE.find(val2) != BLANK_TILE.end() ) {
			typeMove = THREAT_MOVE_LEFT;
			moved = true;
		}
	}

	if (!moved) {
		int val1 = mapData.tile[(threatY + TILE_SIZE) / TILE_SIZE][threatX / TILE_SIZE];
		int val2 = mapData.tile[(threatY - TILE_SIZE) / TILE_SIZE][threatX / TILE_SIZE];
		if (dy > 0 && BLANK_TILE.find(val1) != BLANK_TILE.end() ) {
			typeMove = THREAT_MOVE_DOWN;
		}
		else if (dy < 0 && BLANK_TILE.find(val2) != BLANK_TILE.end() ) {
			typeMove = THREAT_MOVE_UP;
		}
	}

	if (rand() % 10 == 0) {
		typeMove = rand() % TOTAL_THREAT_MOVE;
	}

	/*for (int i = 0; i < bulletList.size(); i++) {
		bulletList[i]->setBulletDir(getTypeMove());
	}*/
	
}

std::vector<ThreatObject*> createThreat(Map& dataMap , SDL_Renderer* screen) {
	char path[30];
	std::vector<ThreatObject*> listThreat;
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			if (THREAT_TILES.find(dataMap.tile[i][j]) != THREAT_TILES.end()) {
				ThreatObject* newThreat = new ThreatObject;
				int val = dataMap.tile[i][j];
				dataMap.tile[i][j] = *BLANK_TILE.begin();
				sprintf_s(path, "image/tile_%d.png", val);
				newThreat->loadImg(path, screen);
				newThreat->setClips();
				newThreat->setXPos(j * TILE_SIZE);
				newThreat->setYPos(i * TILE_SIZE);
				
				BulletObject* pBullet = new BulletObject;
				//newThreat->InitBullet(pBullet, screen);

				listThreat.push_back(newThreat);
				dataMap.tile[i][j] = *BLANK_TILE.begin();
			}
		}
	}
	return listThreat;
}


//void ThreatObject::InitBullet(BulletObject* pBullet, SDL_Renderer* screen) {
//	if (pBullet != nullptr) {
//		bool ret = pBullet->loadImage("image/bullet_threat.png", screen);
//		pBullet->setIsMove(true);
//		pBullet->setBulletDir(getTypeMove());
//		pBullet->setRect(rect.x, rect.y + heightFrame / 2);
//		pBullet->setXPos(xPos);
//		pBullet->setYPos(yPos);
//		pBullet->setMapX(xMap);
//		pBullet->setMapY(yMap);
//		pBullet->setX(BULLET_THREAT_SPEED);
//		pBullet->setY(BULLET_THREAT_SPEED);
//		bulletList.push_back(pBullet);
//	}
//
//}
//void ThreatObject::MakeBullet(SDL_Renderer* screen, MainObject player, Map& dataMap) {
//	
//	for (int i = 0; i < bulletList.size(); i++) {
//		BulletObject* pBullet = bulletList[i];
//		if (pBullet != nullptr) {
//			if (pBullet->getIsMove()) {
//					pBullet->checkBullet(dataMap);
//				int bulletDistanceX = abs(rect.x - pBullet->getRect().x);
//				int bulletDistanceY = abs(rect.y - pBullet->getRect().y);
//				if (bulletDistanceX < MAX_DISTANCE_BULLET  && bulletDistanceY < MAX_DISTANCE_BULLET) {
//					pBullet->handleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
//					pBullet->renderImage(screen);
//
//				}
//				else {
//					pBullet->setIsMove(false);
//					pBullet->setRect(rect.x -= player.getXVal() + TILE_SIZE/2, rect.y -= player.getYVal() + TILE_SIZE/2);
//					//pBullet->setRect(rect.x, rect.y + heightFrame / 2);
//				}
//			}
//			else {
//				pBullet->setIsMove(true);
//				pBullet->setBulletDir(getTypeMove());
//				pBullet->setRect(rect.x -= player.getXVal() + TILE_SIZE/2, rect.y -= player.getYVal() + TILE_SIZE/2);
//				//pBullet->setRect(rect.x, rect.y + heightFrame / 2);
//			}
//		}
//	}
//}

void ThreatObject::removeThreat() {
	if (pObj != nullptr) {
		SDL_DestroyTexture(pObj);
		pObj = nullptr;
		rect.w = 0;
		rect.h = 0;
		/*for (int i = 0; i < bulletList.size(); i++) {
			bulletList[i]->free();
		}*/
	}
}

SDL_Rect ThreatObject::getRectFrame() {
	SDL_Rect rectFrame;
	rectFrame.x = rect.x;
	rectFrame.y = rect.y;
	rectFrame.w = widthFrame;
	rectFrame.h = heightFrame;
	return rectFrame;
}