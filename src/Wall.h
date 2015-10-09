#pragma once

#include "Globals.h"
#include "Player.h"

class Wall {
private:
	SDL_Rect wall;
	int originalX;
	int originalY;
	int originalW;
	int originalH;
public:
	Wall(int x, int y, int w, int h);
	virtual ~Wall();
	void draw();
};
