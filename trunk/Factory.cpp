#include "Factory.h"


CFactory::CFactory(void)
{
}


CFactory::~CFactory(void)
{
}

CResBitmap * CFactory::CreateBitmap()
{
	return CFactory::CreateBitmap(NULL);
}

CResBitmap * CFactory::CreateBitmap(string sPath)
{
	return new CResBitmap();
}

CTileMap * CFactory::CreateTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight)
{
	return new CTileMap(nWidth, nHeight, nTileWidth, nTileHeight);
}