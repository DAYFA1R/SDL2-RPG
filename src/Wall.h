#pragma once

#include "Globals.h"

class Wall {
private:
	int originalX;
	int originalY;
	int originalW;
	int originalH;

public:
	SDL_Rect wall;

public:
	Wall();
	virtual ~Wall();
	void draw();
	void setWallProperties(int x, int y, int w, int h);
};
