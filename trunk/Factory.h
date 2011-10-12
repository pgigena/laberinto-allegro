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
	static CResBitmap * CreateBitmap();
	static CResBitmap * CreateBitmap(string sPath);

	// TileMap
	static CTileMap * CreateTileMap(int nWidth, int nHeight);
};

#endif // FACTORY_H