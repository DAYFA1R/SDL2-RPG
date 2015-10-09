/*
 * Tileset.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: sieg
 */

#include "Tileset.h"

Tileset::Tileset(string path, int tilesX, int tilesY) {
	// load sprite map
	mTexture = makeTexture(path.c_str());
	mTotalTilesX = tilesX;
	mTotalTilesY = tilesY;

	//get texture dimensions
	SDL_QueryTexture(mTexture, NULL, NULL, &mTextureWidth, &mTextureHeight);

	mTileWidth = mTextureWidth / mTotalTilesX;
	mTileHeight = mTextureHeight / mTotalTilesY;

}

Tileset::~Tileset() {
	// TODO Auto-generated destructor stub
	SDL_DestroyTexture(mTexture);
}

void Tileset::renderTile(int positionX, int positionY, int tileX, int tileY) {
	SDL_Rect positionRect = {positionX * mTileWidth, positionY * mTileHeight, mTileWidth, mTileHeight};
	SDL_Rect cropRect = {tileX * mTileWidth, tileY * mTileHeight, mTileWidth, mTileHeight };

	if (checkCollision(cameraRect, positionRect)) {
		positionRect.x -= cameraRect.x;
		positionRect.y -= cameraRect.y;
		SDL_RenderCopy(gRenderer, mTexture, &cropRect, &positionRect);
	}

}

int Tileset::getTileWidth() {
	return mTileWidth;
}

int Tileset::getTileHeight() {
	return mTileHeight;
}
