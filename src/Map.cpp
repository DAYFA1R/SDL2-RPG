/*
 * Map.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: sieg
 */

#include "Map.h"

Map::Map(string path) :
		mMapWidth(0), mMapHeight(0), mTotalTiles(0), mMapData(0), mTotalWalls(0) {

	// get map size from header.map
	ifstream mapHeader("src/assets/maps/" + path + "/header.map");
	mapHeader >> mMapWidth;
	mapHeader >> mMapHeight;

	mapHeader.close();

	// TILE MAPPING
	// get total tiles for max tile index
	mTotalTiles = mMapWidth * mMapHeight;

	// get map data from tiles.map
	ifstream mapFile("src/assets/maps/" + path + "/tiles.map");

	mMapData = new Uint16[mTotalTiles];

	for (int i = 0; i < mTotalTiles; i++) {
		mapFile >> hex >> mMapData[i];
	}

	mapFile.close();

	// WALL MAPPING
	// get total amount of walls
	ifstream wallFile("src/assets/maps/" + path + "/walls.map");

	wallFile >> mTotalWalls;

	// allocate walls
	mWallData = new Wall[mTotalWalls];

	for (int i = 0; i < mTotalWalls; i++) {
		int pullX, pullY, pullW, pullH;

		wallFile >> pullX;
		wallFile >> pullY;
		wallFile >> pullW;
		wallFile >> pullH;

		mWallData[i].setWallProperties(pullX, pullY, pullW, pullH);
	}

	wallFile.close();

}

Map::~Map() {
	delete[] mMapData;
	delete[] mWallData;
	mMapData = NULL;
	mWallData = NULL;
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

void Map::drawWalls() {
	for (int i = 0; i < mTotalWalls; i++) {
		mWallData[i].draw();
	}
}

int Map::inCollision(SDL_Rect playerRect) {

	bool isColliding = false;
	int idOfWall = NULL;

	for (int i = 0; i < mTotalWalls; i++) {
		if (checkCollision(playerRect, mWallData[i].wall)) {
			isColliding = true;
			idOfWall = i;
		}
	}

	return idOfWall;
}

Wall Map::getWall(int id) {
	return mWallData[id];
}
