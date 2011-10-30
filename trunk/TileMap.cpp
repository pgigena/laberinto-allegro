#include "TileMap.h"
#include "Factory.h"

CTileMap::CTileMap()
{
}

CTileMap::~CTileMap(void)
{
	m_vLayers.clear();
	m_vTilesets.clear();
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

void CTileMap::paint(ALLEGRO_DISPLAY *display)
{
	TileCoord tc;
	TileGrid *tgTiles = NULL;
	CLayer *lyrCurrentLayer = NULL;
	CTileset *tlsCurrentTileset = NULL;
	CTilesetImg *tliPalette = NULL;
	ALLEGRO_BITMAP *bmpMesh = NULL;
	int nTileIndex;
	int nRowSize;
//	int nTranspColor;
	int nTileRow, nTileCol;
	int nTileW, nTileH;
	int nMargin, nTileSpacing;
	int nFirstGId;

	al_set_target_bitmap(al_get_backbuffer(display));
	
	for (LayerVector::iterator itLayer = m_vLayers.begin(); itLayer != m_vLayers.end(); ++itLayer) {
		lyrCurrentLayer = (*itLayer);
		tgTiles = lyrCurrentLayer->getTileGrid();
		for (int x = 0; x < lyrCurrentLayer->getWidth(); x++)
		{
			tc.x = x;

			for (int y = 0; y < lyrCurrentLayer->getHeight(); y++)
			{
				tc.y = y;

				// If the coordinate has no elements, skip to the next
				if (tgTiles->find(tc) == tgTiles->end()) {
					continue;
				}

				nTileIndex = tgTiles->at(tc)->getTileIndex();

				for (TilesetVector::reverse_iterator itTileset = m_vTilesets.rbegin(); itTileset != m_vTilesets.rend(); ++itTileset)
				{
					tlsCurrentTileset = (*itTileset);
					if (nTileIndex >= tlsCurrentTileset->getFirstGId()) {
						nFirstGId = tlsCurrentTileset->getFirstGId();

						tliPalette = tlsCurrentTileset->getTilePalette();
						nRowSize = tliPalette->getRowSize();

						nTileRow = (nTileIndex - nFirstGId) / nRowSize;
						nTileCol = (nTileIndex - nFirstGId) % nRowSize;

						nTileW = tlsCurrentTileset->getTileW();
						nTileH = tlsCurrentTileset->getTileH();

						nTileSpacing = tlsCurrentTileset->getSpacing();
						nMargin = tlsCurrentTileset->getMargin();
						//nTranspColor = tlsCurrentTileset->getTilePalette()->getTransparentColor();

						//bmpMesh = tliPalette->getImage()->getResource();
						bmpMesh = tliPalette->getImage();

						al_draw_bitmap_region(bmpMesh,
							((nTileW + nTileSpacing)* nTileCol) + nMargin,
							((nTileH + nTileSpacing) * nTileRow) + nMargin,
							nTileW, nTileH,
									(m_nTileWidth * x), (m_nTileHeight * y), 0);
						break;
					}
				}
			}
		}
	}
}

int CTileMap::initialize()
{
	if (!m_xmlMapFile->LoadFile()) {
		return 1;
	}

	TiXmlNode *xmlnMap = m_xmlMapFile->FirstChild("map");
	TiXmlElement *xmleMap = xmlnMap->ToElement();
	string sOrient = xmleMap->Attribute("orientation");

	if (sOrient != "orthogonal") {
		return -1;
	}

	m_nWidth = atoi(xmleMap->Attribute("width"));
	m_nHeight = atoi(xmleMap->Attribute("height"));

	m_nTileWidth = atoi(xmleMap->Attribute("tilewidth"));
	m_nTileHeight = atoi(xmleMap->Attribute("tileheight"));

	parseTilesets(xmlnMap);
	parseLayers(xmlnMap);

	return 0;
}

int CTileMap::parseTilesets(TiXmlNode *xmlnMap) {
	TiXmlNode *xmlnTileset = xmlnMap->FirstChild("tileset");

	while (xmlnTileset) {

		m_vTilesets.push_back(CFactory::createTileset());
		m_vTilesets.back()->initialize(xmlnTileset);

		xmlnTileset = xmlnMap->IterateChildren("tileset", xmlnTileset);
	}

	return 0;
}

int CTileMap::parseLayers(TiXmlNode *xmlnMap) {
	TiXmlNode *xmlnLayer = xmlnMap->FirstChild("layer");

	while (xmlnLayer) {

		m_vLayers.push_back(CFactory::createLayer());
		m_vLayers.back()->initialize(xmlnLayer);

		xmlnLayer = xmlnMap->IterateChildren("layer", xmlnLayer);
	}
	return 0;
}
