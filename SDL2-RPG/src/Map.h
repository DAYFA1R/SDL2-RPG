#pragma once

#include "Globals.h"
#include "Tileset.h"
#include <iomanip>

class Map {
private:
	int mMapWidth;
	int mMapHeight;
	int mTotalTiles;
	Uint16* mMapData;
public:
	Map(string path);
	virtual ~Map();
	int getMapWidth();
	int getMapHeight();
	int getTotalTiles();
	Uint16* getMapData();
	void drawTiles(Tileset& tileset);
};
