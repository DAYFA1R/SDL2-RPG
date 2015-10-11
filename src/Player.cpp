/*
 * Player.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: sieg
 */

#include "Player.h"

Player::Player(SDL_Renderer* renderTarget, string path, int x, int y, int framesX, int framesY) {
	texture = makeTexture(path.c_str());

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;
	textureHeight = cropRect.h;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameCounter = 0;
	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;
	radius = frameWidth / 2;

	moveSpeed = 250.0f;
	animationSpeed = 0.25;

	collider.x = positionRect.x;
	collider.y = positionRect.y;
	collider.w = positionRect.w;
	collider.h = positionRect.h;

	isActive = false;

	static int playerNumber = 0;
	playerNumber++;

	if (playerNumber == 1) {
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
		keys[4] = SDL_SCANCODE_LSHIFT;
	}
}

Player::~Player() {
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Player::update(float delta, const Uint8* keyState, Map& map) {
	isActive = true;

	if (keyState[keys[4]]) {
		moveSpeed = 350.0f;
		animationSpeed = 0.10;
	} else {
		moveSpeed = 250.0f;
		animationSpeed = 0.25;
	}

	if (keyState[keys[0]] && keyState[keys[2]]) {
		move(0, map);
		move(2, map);
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[0]] && keyState[keys[3]]) {
		move(0, map);
		move(3, map);
		cropRect.y = frameHeight * 2;
	}
	else if (keyState[keys[1]] && keyState[keys[2]]) {
		move(1, map);
		move(2, map);
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[1]] && keyState[keys[3]]) {
		move(1, map);
		move(3, map);
		cropRect.y = frameHeight * 2;
	}
	else if (keyState[keys[0]]) {
		move(0, map);
		cropRect.y = frameHeight * 3;
	}
	else if (keyState[keys[1]]) {
		move(1, map);
		cropRect.y = 0;
	}
	else if (keyState[keys[2]]) {
		move(2, map);
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[3]]) {
		move(3, map);
		cropRect.y = frameHeight * 2;
	} else {
		isActive = false;
	}

	if (isActive) {
		frameCounter += delta;

		if (frameCounter >= animationSpeed) {
			frameCounter = 0;
			cropRect.x += frameWidth;

			if (cropRect.x >= textureWidth) {
				cropRect.x = 0;
			}
		}
	} else {
		frameCounter = 0;
		cropRect.x = frameWidth;
	}
}

void Player::draw(SDL_Renderer* renderTarget, SDL_Rect cameraRect) {
	SDL_Rect drawingRect = {positionRect.x - cameraRect.x, positionRect.y - cameraRect.y, positionRect.w, positionRect.h};

	collider.x = drawingRect.x;
	collider.y = drawingRect.y;
	collider.w = drawingRect.w;
	collider.h = drawingRect.h;

	if (DEBUG == true) {
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);
		SDL_RenderFillRect(gRenderer, &positionRect);
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
		SDL_RenderFillRect(gRenderer, &collider);
	}
	SDL_RenderCopy(gRenderer, texture, &cropRect, &drawingRect);
}

bool Player::intersectsWith(Player& p) {

	if (sqrt(pow(getOriginX() - p.getOriginX(), 2) + pow(getOriginY() - p.getOriginY(), 2)) >= radius + p.getRadius()) {
		SDL_SetTextureColorMod(texture, 255, 255, 255);
		return false;
	}
	SDL_SetTextureColorMod(texture, 255, 0, 0);
	return true;
}

int Player::getOriginX() {
	return positionRect.x + originX;
}

int Player::getOriginY() {
	return positionRect.y + originY;
}

int Player::getRadius() {
	return radius;
}

void Player::move(int direction, Map& map) {
	//get the difference between the collider and your actual position (offset due to camera)
	int positionGapX = positionRect.x - collider.x;
	int positionGapY = positionRect.y - collider.y;

	// getting the original positions of the collider before move projection. This is done so that
	// the collider can be reset before the next move is checked (implemented for diagonal movement)
	int originalY = collider.y;
	int originalX = collider.x;

	// holder var for wall ID returned from projected collision
	int wallInCollision;

	//commenting first direction only, others follow the same concept
	switch (direction) {
	case 0:
		// project the collision box to what the character position would
		// theoretically be moving to
		collider.y = roundf(((float)collider.y - (moveSpeed * delta)));

		// check if there is a wall in collision
		wallInCollision = map.inCollision(collider);

		//move character only if there is no collision from the projected move
		if (!wallInCollision) {
			positionRect.y = roundf(((float)positionRect.y - (moveSpeed * delta)));
		} else {
			// position character at the edge of the wall
			SDL_Rect wall = map.getWall(wallInCollision).wall;
			positionRect.y = wall.y + wall.h + positionGapY;
		}

		// reset the collider to the original position so next move can be checked clean
		// (this needs to be done for diagonal movement where two move functions are run
		// in the same event.
		collider.y = originalY;
		break;
	case 1:
		collider.y = roundf(((float)collider.y + (moveSpeed * delta)));
		wallInCollision = map.inCollision(collider);
		if (!wallInCollision) {
			positionRect.y = roundf(((float)positionRect.y + (moveSpeed * delta)));
		} else {
			SDL_Rect wall = map.getWall(wallInCollision).wall;
			positionRect.y = wall.y - positionRect.h + positionGapY;
		}
		collider.y = originalY;
		break;
	case 2:
		collider.x = roundf(((float)collider.x - (moveSpeed * delta)));
		wallInCollision = map.inCollision(collider);
		if (!wallInCollision) {
			positionRect.x = roundf(((float)positionRect.x - (moveSpeed * delta)));
		} else {
			SDL_Rect wall = map.getWall(wallInCollision).wall;
			positionRect.x = wall.x + wall.w + positionGapX;
		}
		collider.y = originalX;
		break;
	case 3:
		collider.x = roundf(((float)collider.x + (moveSpeed * delta)));
		wallInCollision = map.inCollision(collider);
		if (!wallInCollision) {
			positionRect.x = roundf(((float)positionRect.x + (moveSpeed * delta)));
		} else {
			SDL_Rect wall = map.getWall(wallInCollision).wall;
			positionRect.x = wall.x - positionRect.w + positionGapX;
		}
		collider.y = originalX;
		break;
	}
}
