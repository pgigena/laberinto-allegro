#include "TileMap.h"
#include "Factory.h"

//CTileMap::CTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight)
CTileMap::CTileMap()
{
/*	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nTileWidth = nTileWidth;
	m_nTileHeight = nTileHeight;
/*	bool bGreenTile = false;
	int nTileType = 0;
	TileCoord tc;

	for (int x = 0; x < m_nWidth; x++)
	{
		tc.x = x;
		for (int y = 0; y < m_nHeight; y++)
		{
			tc.y = y;

			if (bGreenTile) {
				nTileType = 1;
				bGreenTile = false;
			} else {
				nTileType = 0;
				bGreenTile = true;
			}

			m_mMap.insert(TileGrid::value_type(tc, CFactory::createTile(nTileType)));
		}

		if (bGreenTile) {
			nTileType = 1;
			bGreenTile = false;
		} else {
			nTileType = 0;
			bGreenTile = true;
		}
	}*/
}

CTileMap::~CTileMap(void)
{
	m_mMap.clear();
}

int CTileMap::setSpritePalette(ALLEGRO_BITMAP * bmpSpritePalette)
{
	if (!bmpSpritePalette) {
		return 1;
	}

	m_bmpSpritePalette = bmpSpritePalette;
	return 0;
}

void CTileMap::setTmxFile(TiXmlDocument *xmlMapFile)
{
	m_xmlMapFile = xmlMapFile;
}

int CTileMap::getWidth()
{
	return m_nWidth;
}

int CTileMap::getHeight()
{
	return m_nHeight;
}

int CTileMap::getTileWidth()
{
	return m_nTileWidth;
}

int CTileMap::getTileHeight()
{
	return m_nTileHeight;
}

void CTileMap::paintMap(ALLEGRO_DISPLAY *display)
{
	TileCoord tc;
	int nSpriteIndex = 0;
	int nSpriteX = 0;
	int nSpriteY = 0;

	al_set_target_bitmap(al_get_backbuffer(display));

	for (int y = 0; y < m_nHeight; y++)
	{
		tc.y = y;

		for (int x = 0; x < m_nWidth; x++)
		{
			tc.x = x;
			nSpriteIndex = m_mMap[tc]->getTileIndex() - 1;
			

			al_draw_bitmap_region(m_bmpSpritePalette, (m_nTileWidth * nSpriteIndex), (m_nTileHeight * 0), m_nTileWidth, m_nTileHeight, (m_nTileWidth * x), (m_nTileHeight * y), 0);
		}
	}
}

int CTileMap::initialize()
{
	if (!m_xmlMapFile->LoadFile()) {
		return 1;
	}

	TiXmlNode *mapNode = m_xmlMapFile->FirstChild("map");
	TiXmlElement* mapElem = mapNode->ToElement();
	string sOrient = mapElem->Attribute("orientation");

	if (sOrient != "orthogonal") {
		return -1;
	}

	m_nWidth = atoi(mapElem->Attribute("width"));
	m_nHeight = atoi(mapElem->Attribute("height"));

	m_nTileWidth = atoi(mapElem->Attribute("tilewidth"));
	m_nTileHeight = atoi(mapElem->Attribute("tileheight"));

	parseTileset(mapNode);
	parseLayers(mapNode);

	return 0;
}

int CTileMap::parseTileset(TiXmlNode *xmlnMapNode) {
	TiXmlNode *tilesetNode = xmlnMapNode->FirstChild("tileset");
	TiXmlElement *tilesetElem = NULL;

//	while (tilesetNode) {
		tilesetElem = tilesetNode->ToElement();

		string sTilesetName = tilesetElem->Attribute("name");
		int nFirstGId = atoi(tilesetElem->Attribute("firstgid"));
		int nTileW = atoi(tilesetElem->Attribute("tilewidth"));
		int nTileH = atoi(tilesetElem->Attribute("tileheight"));

		parseTilesetImages(tilesetNode);

	//	tilesetNode = xmlnMapNode->IterateChildren("tileset", tilesetNode);
	//}
	return 0;
}

int CTileMap::parseTilesetImages(TiXmlNode *xmlnTilesetNode) {

	TiXmlNode *imgNode = xmlnTilesetNode->FirstChild("image");
	TiXmlElement *imgElem = NULL;

	//while (imgNode) {
		imgElem = imgNode->ToElement();
		string s = imgElem->Attribute("source");
		m_bmpSpritePalette = al_load_bitmap(s.c_str());

		int nImgWidth = atoi(imgElem->Attribute("width"));
		int nImgHeight = atoi(imgElem->Attribute("height"));

		char *sTrans = (char *) imgElem->Attribute("trans");

		if (sTrans != NULL) {
			int nTransColor = atoi(sTrans);
		}

		//imgNode = xmlnTilesetNode->IterateChildren("image", imgNode);
	//}
	return 0;
}

int CTileMap::parseLayers(TiXmlNode *xmlnMapNode) {
	TiXmlNode *layerNode = xmlnMapNode->FirstChild("layer");
	TiXmlElement *layerElem = NULL;

//	while (layerNode) {
		layerElem = layerNode->ToElement();

		string sLayerName = layerElem->Attribute("name");
		int nLayerWidth = atoi(layerElem->Attribute("width"));
		int nLayerHeight = atoi(layerElem->Attribute("height"));

		parseLayerData(layerNode);

		//layerNode = mapNode->IterateChildren("layer", layerNode);
	//}
	return 0;
}

int CTileMap::parseLayerData(TiXmlNode *xmlnLayerNode) {

	TiXmlNode *dataNode = xmlnLayerNode->FirstChild("data");
	TiXmlNode *tileNode = dataNode->FirstChild("tile");
	TiXmlElement *tileElem = NULL;
	CTile *tlTile = NULL;
	int nTileGid = 0;
	TileCoord tc;
	tc.x = 0;
	tc.y = 0;

	while (tileNode) {
		tileElem = tileNode->ToElement();

		nTileGid = atoi(tileElem->Attribute("gid"));

		tileNode = dataNode->IterateChildren("tile", tileNode);

		m_mMap.insert(TileGrid::value_type(tc, CFactory::createTile(nTileGid)));

		if (tc.x == m_nWidth - 1) {
			tc.y += 1;
			tc.x = 0;
		} else {
			tc.x += 1;
		}
	}

	return 0;
}