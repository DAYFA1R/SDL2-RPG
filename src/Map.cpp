/*
 * Map.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: sieg
 */

#include "Map.h"

Map::Map(string path) :
		mMapWidth(0), mMapHeight(0), mTotalTiles(0), mMapData(0) {

	// get map size from header.map
	ifstream mapHeader("src/assets/maps/" + path + "/header.map");
	mapHeader >> mMapWidth;
	mapHeader >> mMapHeight;

	mapHeader.close();

	// get total tiles for max tile index
	mTotalTiles = mMapWidth * mMapHeight;

	// get map data from tiles.map
	ifstream mapFile("src/assets/maps/" + path + "/tiles.map");

	mMapData = new Uint16[mTotalTiles];

	for (int i = 0; i < mTotalTiles; i++) {
		mapFile >> hex >> mMapData[i];
	}

	mapFile.close();

}

Map::~Map() {
	delete[] mMapData;
	mMapData = NULL;
}

int Map::getMapWidth() {
	return mMapWidth;
}
int Map::getMapHeight() {
	return mMapHeight;
}
int Map::getTotalTiles() {
	return mMapHeight;
}

Uint16* Map::getMapData() {
	return mMapData;
}

void Map::drawTiles(Tileset& tileset) {
	int xCounter = 0;
	int yCounter = 0;

	for (int i = 0; i < mTotalTiles; i++) {

		if (xCounter == mMapWidth) {
			xCounter = 0;
			yCounter++;
		}

		Uint16 tile = mMapData[i];
		Uint16 mask = 0x000F;

		Uint16 baseX = tile & mask;
		tile >>= 4;
		Uint16 modX = tile & mask;
		tile >>= 4;
		Uint16 baseY = tile & mask;
		tile >>= 4;
		Uint16 modY = tile & mask;

		//printf("%d %d %d %d\n", modY, baseY, modX, baseX); //for logging map Data

		int tileX = modX * baseX;
		int tileY = modY * baseY;

		tileset.renderTile(xCounter, yCounter, tileX, tileY);

		xCounter++;
	}
}
