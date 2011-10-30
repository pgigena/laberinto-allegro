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

CTileset * CFactory::createTileset()
{
	return new CTileset();
}

CTilesetImg * CFactory::createTilesetImg(int nSpriteW, int nSpriteH)
{
	return new CTilesetImg(nSpriteW, nSpriteH);
}

CLayer * CFactory::createLayer()
{
	return new CLayer();
}

CTile * CFactory::createTile(int nIndex)
{
	return new CTile(nIndex);
}