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

//CTileMap * CFactory::createTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight)
CTileMap * CFactory::createTileMap()
{
	//return new CTileMap(nWidth, nHeight, nTileWidth, nTileHeight);
	return new CTileMap();
}

CTile * CFactory::createTile(int nIndex)
{
	return new CTile(nIndex);
}