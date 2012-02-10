#include "TileMap.h"
#include "Factory.h"

CTileMap::CTileMap()
{
	m_bmpMapBuffer = NULL;
	m_mProperties = NULL;
}

CTileMap::~CTileMap(void)
{
	delete m_xmlMapFile;
	if (m_bmpMapBuffer) {
		al_destroy_bitmap(m_bmpMapBuffer);
	}

	if (m_mProperties) {
		delete m_mProperties;
	}

	m_vLayers.clear();
	m_vObjLayers.clear();
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
	// Check that the map buffer exists
	if (!m_bmpMapBuffer) {
		drawBuffer(display);
	}
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(m_bmpMapBuffer, 0, 0, 0);

	CTmxObjectLayer *lyrCurrentLayer = NULL;
	CTileset *tlsCurrentTileset = NULL;
	CTilesetImg *tliPalette = NULL;
	ALLEGRO_BITMAP *bmpMesh = NULL;
	TmxObjectVector *vObjects = NULL;
	CTmxObject *obj = NULL;
	int nObjGId;

	for (ObjLayerVector::iterator itObjLayer = m_vObjLayers.begin(); itObjLayer != m_vObjLayers.end(); ++itObjLayer)
	{
		lyrCurrentLayer = (*itObjLayer);

		vObjects = lyrCurrentLayer->getLayerObjects();
		for (TmxObjectVector::iterator itObjects = vObjects->begin(); itObjects != vObjects->end(); ++itObjects)
		{
			obj = (*itObjects);
			nObjGId = obj->getGId();

			if (!nObjGId) {
				continue;
			}

			// Iterate backwards through the available tilesets for the map in order to find the one corresponding to the current GId
			for (TilesetVector::reverse_iterator itTileset = m_vTilesets.rbegin(); itTileset != m_vTilesets.rend(); ++itTileset)
			{
				tlsCurrentTileset = (*itTileset);

				// If the GId is within the current tileset, draw it
				if (nObjGId >= tlsCurrentTileset->getFirstGId()) {
					tliPalette = tlsCurrentTileset->getTilePalette();

					// TODO: HANDLE EXPLICIT TRANSPARENCY
					//nTranspColor = tliPalette->getTransparentColor();
					bmpMesh = tliPalette->getImage();
					// TODO: IMPLEMENT RESOURCE STACK CORRECTLY
					//bmpMesh = tliPalette->getImage()->getResource();

					al_draw_bitmap_region(bmpMesh,
									tlsCurrentTileset->getTileX(nObjGId),
									tlsCurrentTileset->getTileY(nObjGId),
									tlsCurrentTileset->getTileW(),
									tlsCurrentTileset->getTileH(),
									obj->getPos().x, obj->getPos().y - tlsCurrentTileset->getTileH(), 0);

					// End the loop in order to avoid the object from being overwritten by an empty image
					break;
				}
			}
		}
	}
}


void CTileMap::drawBuffer(ALLEGRO_DISPLAY *display)
{
	TileCoord tc;
	TileGrid *tgTiles = NULL;
	CTmxTileLayer *lyrCurrentLayer = NULL;
	CTileset *tlsCurrentTileset = NULL;
	CTilesetImg *tliPalette = NULL;
	ALLEGRO_BITMAP *bmpMesh = NULL;
	int nTileIndex;
//	int nTranspColor;

	al_set_target_backbuffer(display);
	m_bmpMapBuffer = al_create_bitmap(m_nWidth * m_nTileWidth, m_nHeight * m_nTileHeight);
	al_set_target_bitmap(m_bmpMapBuffer);

	// Check if this applies to al_draw_bitmap_region!
	//al_hold_bitmap_drawing(true);

	// Iterate through the layers from bottom to top painting each one
	for (LayerVector::iterator itLayer = m_vLayers.begin(); itLayer != m_vLayers.end(); ++itLayer) {
		lyrCurrentLayer = (*itLayer);

		tgTiles = lyrCurrentLayer->getTileGrid();

		// Iterate through the rows of the current layer
		for (int x = 0; x < lyrCurrentLayer->getWidth(); x++)
		{
			tc.x = x;

			// Iterate through the columns of the current row of the layer
			for (int y = 0; y < lyrCurrentLayer->getHeight(); y++)
			{
				tc.y = y;

				// If the coordinate has no Tile element, skip to the next
				if (tgTiles->find(tc) == tgTiles->end()) {
					continue;
				}

				nTileIndex = tgTiles->at(tc)->getGId();

				// Iterate backwards through the available tilesets for the map in order to find the one corresponding to the current GId
				for (TilesetVector::reverse_iterator itTileset = m_vTilesets.rbegin(); itTileset != m_vTilesets.rend(); ++itTileset)
				{
					tlsCurrentTileset = (*itTileset);

					// If the GId is within the current tileset, draw it
					if (nTileIndex >= tlsCurrentTileset->getFirstGId()) {
						tliPalette = tlsCurrentTileset->getTilePalette();

						// TODO: HANDLE EXPLICIT TRANSPARENCY
						//nTranspColor = tliPalette->getTransparentColor();
						bmpMesh = tliPalette->getImage();
						// TODO: IMPLEMENT RESOURCE STACK CORRECTLY
						//bmpMesh = tliPalette->getImage()->getResource();

						al_draw_bitmap_region(bmpMesh,
										tlsCurrentTileset->getTileX(nTileIndex),
										tlsCurrentTileset->getTileY(nTileIndex),
										tlsCurrentTileset->getTileW(),
										tlsCurrentTileset->getTileH(),
										(m_nTileWidth * x), (m_nTileHeight * y), 0);

						// End the loop in order to avoid the tile from being overwritten by an empty image
						break;
					}
				}
			}
		}
	}

	//al_hold_bitmap_drawing(false);
}

int CTileMap::parseTmx()
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

	parseProperties(xmlnMap);
	parseTilesets(xmlnMap);
	parseLayers(xmlnMap);
	parseObjectLayers(xmlnMap);

	return 0;
}

int CTileMap::parseTilesets(TiXmlNode *xmlnMap) {
	TiXmlNode *xmlnTileset = xmlnMap->FirstChild("tileset");

	while (xmlnTileset) {

		m_vTilesets.push_back(CFactory::createTileset());
		m_vTilesets.back()->parseTmx(xmlnTileset);

		xmlnTileset = xmlnMap->IterateChildren("tileset", xmlnTileset);
	}

	return 0;
}

int CTileMap::parseLayers(TiXmlNode *xmlnMap) {
	TiXmlNode *xmlnLayer = xmlnMap->FirstChild("layer");

	while (xmlnLayer) {

		m_vLayers.push_back(CFactory::createLayer());
		m_vLayers.back()->parseTmx(xmlnLayer);

		xmlnLayer = xmlnMap->IterateChildren("layer", xmlnLayer);
	}
	return 0;
}

int CTileMap::parseObjectLayers(TiXmlNode *xmlnMap) {
	TiXmlNode *xmlnObjLayer = xmlnMap->FirstChild("objectgroup");

	while (xmlnObjLayer) {

		m_vObjLayers.push_back(CFactory::createObjectLayer());
		m_vObjLayers.back()->parseTmx(xmlnObjLayer);

		xmlnObjLayer = xmlnMap->IterateChildren("objectgroup", xmlnObjLayer);
	}
	return 0;
}

int CTileMap::parseProperties(TiXmlNode *xmlnMap) {
	// Search for a property list
	TiXmlNode *xmlnProperties = xmlnMap->FirstChild("properties");

	if (xmlnProperties) {
		// If the property list has not been created, create it
		if (!m_mProperties) {
			m_mProperties = new CTmxPropertyList();
		}

		// Parse the properties
		m_mProperties->parseTmx(xmlnProperties);
	}
	return 0;
}

void CTileMap::loadResources()
{
	CTileset *tls;

	for (TilesetVector::reverse_iterator it = m_vTilesets.rbegin(); it != m_vTilesets.rend(); ++it)
	{
		tls = (*it);
		tls->loadResources();
	}
}