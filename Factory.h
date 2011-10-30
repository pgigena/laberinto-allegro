#ifndef FACTORY_H
#define FACTORY_H

#include "Util.h"
#include "ResBitmap.h"
#include "TilesetImg.h"
#include "Tileset.h"
#include "Layer.h"
#include "TileMap.h" 

class CFactory
{
public:
	CFactory(void);
	~CFactory(void);

	// Bitmap
	static CResBitmap * createBitmap();
	static CResBitmap * createBitmap(string sPath);

	// TileMap
	static CTileMap * createTileMap();

	// Tileset
	static CTileset * createTileset();
	
	// SpritePalette
	static CTilesetImg * createTilesetImg(int nSpriteW, int nSpriteH);
	static CTilesetImg * createTilesetImg(int nSpriteW, int nSpriteH, int nMargin, int nSpacing);

	// Layer
	static CLayer * createLayer();

	// Tile
	static CTile * createTile(int nIndex);
};

#endif // FACTORY_H