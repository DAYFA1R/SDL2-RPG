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

void Player::update(float delta, const Uint8* keyState) {
	isActive = true;

	if (keyState[keys[4]]) {
		moveSpeed = 350.0f;
		animationSpeed = 0.10;
	} else {
		moveSpeed = 250.0f;
		animationSpeed = 0.25;
	}

	if (keyState[keys[0]] && keyState[keys[2]]) {
		positionRect.y = roundf(((float) positionRect.y - (moveSpeed * delta)));
		positionRect.x = roundf(((float)positionRect.x - (moveSpeed * delta)));
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[0]] && keyState[keys[3]]) {
		positionRect.y = roundf(((float)positionRect.y - (moveSpeed * delta)));
		positionRect.x = roundf(((float)positionRect.x + (moveSpeed * delta)));
		cropRect.y = frameHeight * 2;
	}
	else if (keyState[keys[1]] && keyState[keys[2]]) {
		positionRect.y = roundf(((float)positionRect.y + (moveSpeed * delta)));
		positionRect.x = roundf(((float)positionRect.x - (moveSpeed * delta)));
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[1]] && keyState[keys[3]]) {
		positionRect.y = roundf(((float)positionRect.y + (moveSpeed * delta)));
		positionRect.x = roundf(((float)positionRect.x + (moveSpeed * delta)));
		cropRect.y = frameHeight * 2;
	}
	else if (keyState[keys[0]]) {
		positionRect.y = roundf(((float)positionRect.y - (moveSpeed * delta)));
		cropRect.y = frameHeight * 3;
	}
	else if (keyState[keys[1]]) {
		positionRect.y = roundf(((float)positionRect.y + (moveSpeed * delta)));
		cropRect.y = 0;
	}
	else if (keyState[keys[2]]) {
		positionRect.x = roundf(((float)positionRect.x - (moveSpeed * delta)));
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[3]]) {
		positionRect.x = roundf(((float)positionRect.x + (moveSpeed * delta)));
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
	// Bounding box collision
	/*if (positionRect.x + positionRect.w < p.positionRect.x
			|| positionRect.x > p.positionRect.x + p.positionRect.w
			|| positionRect.y + positionRect.h < p.positionRect.y
			|| positionRect.y > p.positionRect.y + p.positionRect.h) {
		SDL_SetTextureColorMod(texture, 255, 255, 255);
		return false;
	} else {
		SDL_SetTextureColorMod(texture, 255, 0, 0);
		return true;
	} */

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
