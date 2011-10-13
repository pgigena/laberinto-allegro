#include "Factory.h"


CFactory::CFactory(void)
{
}


CFactory::~CFactory(void)
{
}

CResBitmap * CFactory::createBitmap()
{
	return CFactory::createBitmap(NULL);
}

CResBitmap * CFactory::createBitmap(string sPath)
{
	return new CResBitmap();
}

CTileMap * CFactory::createTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight)
{
	return new CTileMap(nWidth, nHeight, nTileWidth, nTileHeight);
}

CTile * CFactory::createTile(int nIndex)
{
	return new CTile(nIndex);
}