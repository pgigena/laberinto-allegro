#ifndef FACTORY_H
#define FACTORY_H

#include "Util.h"
#include "ResBitmap.h"
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
	//static CTileMap * createTileMap(int nWidth, int nHeight, int nTileWidh, int nTileHeight);
	static CTileMap * createTileMap();

	// Tile
	static CTile * createTile(int nIndex);
};

#endif // FACTORY_H