#pragma once

#include "Globals.h"
#include "Tileset.h"
#include "Wall.h"
#include <iomanip>

class Map {
private:
	int mMapWidth;
	int mMapHeight;
	int mTotalTiles;
	Uint16* mMapData;
	Wall* mWallData;
	int mTotalWalls;
public:
	Map(string path);
	virtual ~Map();
	int getMapWidth();
	int getMapHeight();
	int getTotalTiles();
	Uint16* getMapData();
	Wall getWall(int id);
	void drawTiles(Tileset& tileset);
	void drawWalls();
	int inCollision(SDL_Rect playerRect);
};
