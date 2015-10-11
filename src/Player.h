#pragma once

#include "Globals.h"
#include "Map.h"

class Player {
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	float moveSpeed;
	float animationSpeed;
	float frameCounter;
	int frameWidth, frameHeight;
	int textureWidth, textureHeight;
	bool isActive;
	SDL_Scancode keys[5];
	int originX, originY;
	int radius;

public:
	SDL_Rect positionRect;
	SDL_Rect collider;

public:
	Player(SDL_Renderer* renderTarget, string path, int x, int y, int framesX, int framesY);
	virtual ~Player();

	void update(float delta, const Uint8 *keyState, Map& map);
	void draw(SDL_Renderer* renderTarget, SDL_Rect cameraRect);
	bool intersectsWith(Player& p);
	int getOriginX();
	int getOriginY();
	int getRadius();
	void move(int direction, Map& map);
};
