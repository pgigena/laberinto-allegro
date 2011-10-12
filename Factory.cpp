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
	CResBitmap *c = new CResBitmap();
	return c;
}

CTileMap * CFactory::CreateTileMap(int nWidth, int nHeight)
{
	return NULL;
}