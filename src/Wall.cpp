/*
 * Wall.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: sieg
 */

#include "Wall.h"

Wall::Wall(): originalX(0), originalY(0), originalW(0), originalH(0) {
	//debug = false;

	if (DEBUG == true) {
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	}

	wall.x = originalX;
	wall.y = originalY;
	wall.w = originalW;
	wall.h = originalH;
}

Wall::~Wall() {
	// TODO Auto-generated destructor stub
}

void Wall::draw() {
	wall.x = originalX;
	wall.y = originalY;
	wall.w = originalW;
	wall.h = originalH;

	if (checkCollision(cameraRect, wall)) {
		wall.x -= cameraRect.x;
		wall.y -= cameraRect.y;

		if (DEBUG == true) {
			SDL_RenderFillRect(gRenderer, &wall);
		}
	}
}

void Wall::setWallProperties(int x, int y, int w, int h) {
	originalX = x;
	originalY = y;
	originalW = w;
	originalH = h;
}
