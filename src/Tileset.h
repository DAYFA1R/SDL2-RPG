#pragma once

#include "Globals.h"

class Tileset {
private:
	SDL_Texture* mTexture;
	int mTextureWidth, mTextureHeight;
	int mTileWidth, mTileHeight;
	int mTotalTilesX, mTotalTilesY;
public:
	Tileset(string path, int tilesX, int tilesY);
	virtual ~Tileset();
	int getTileWidth();
	int getTileHeight();
	void renderTile(int positionX, int positionY, int tileX, int tileY);
};
