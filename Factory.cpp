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

CTilesetImg * CFactory::createTilesetImg(int nSpriteW, int nSpriteH, int nMargin, int nSpacing)
{
	return new CTilesetImg(nSpriteW, nSpriteH, nMargin, nSpacing);
}

CTmxTileLayer * CFactory::createLayer()
{
	return new CTmxTileLayer();
}

CTmxObjectLayer * CFactory::createObjectLayer()
{
	return new CTmxObjectLayer();
}

CTile * CFactory::createTile(int nIndex)
{
	return new CTile(nIndex);
}

CTmxObject * CFactory::createObject()
{
	return new CTmxObject();
}

CTmxPropertyList * CFactory::createPropertiesList()
{
	return new CTmxPropertyList();
}