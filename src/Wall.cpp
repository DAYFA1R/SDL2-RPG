/*
 * Wall.cpp
 *
 *  Created on: Oct 7, 2015
 *      Author: sieg
 */

#include "Wall.h"

Wall::Wall(int x, int y, int w, int h) {
	//debug = false;

	if (DEBUG == true) {
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	}

	originalX = x;
	originalY = y;
	originalW = w;
	originalH = h;

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
		SDL_RenderFillRect(gRenderer, &wall);
	}
}
