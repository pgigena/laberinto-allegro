#include "TmxTileLayer.h"
#include "Factory.h"

CTmxTileLayer::CTmxTileLayer(void)
{
	m_mapTiles = new TileGrid;
	m_mProperties = NULL;
}


CTmxTileLayer::~CTmxTileLayer(void)
{
	//delete m_mapTiles;

	if (m_mProperties) {
		delete m_mProperties;
	}
}

int CTmxTileLayer::getWidth()
{
	return m_nWidth;
}

int CTmxTileLayer::getHeight()
{
	return m_nHeight;
}

string CTmxTileLayer::getName()
{
	return m_sName;
}

TileGrid * CTmxTileLayer::getTileGrid()
{
	return m_mapTiles;
}

int CTmxTileLayer::parseTmx(TiXmlNode *xmlnLayer)
{
	TiXmlElement *xmleLayer = xmlnLayer->ToElement();
	TiXmlNode *xmlnProperties = NULL;

	m_sName = xmleLayer->Attribute("name");
	m_nWidth = atoi(xmleLayer->Attribute("width"));
	m_nHeight = atoi(xmleLayer->Attribute("height"));

	// Search for a property list
	xmlnProperties = xmlnLayer->FirstChild("properties");

	if (xmlnProperties) {
		// If the property list has not been created, create it
		if (!m_mProperties) {
			m_mProperties = new CTmxPropertyList();
		}

		// Parse the properties
		m_mProperties->parseTmx(xmlnProperties);
	}

	parseLayerData(xmlnLayer);
	return 0;
}

int CTmxTileLayer::parseLayerData(TiXmlNode *xmlnLayer)
{
	TiXmlNode *xmlnData = xmlnLayer->FirstChild("data");
	TiXmlNode *xmlnTile = xmlnData->FirstChild("tile");
	TiXmlElement *xmleTile = NULL;
	CTile *tlTile = NULL;
	TileCoord tc;
	int nTileGId;

	tc.x = 0;
	tc.y = 0;

	while (xmlnTile) {
		xmleTile = xmlnTile->ToElement();
		nTileGId = atoi(xmleTile->Attribute("gid"));

		// If no valid GId is assigned, skip insertion
		if (nTileGId != 0) {
			m_mapTiles->insert(TileGrid::value_type(tc, CFactory::createTile(nTileGId)));
		}

		xmlnTile = xmlnData->IterateChildren("tile", xmlnTile);

		if (tc.x == m_nWidth - 1) {
			tc.y += 1;
			tc.x = 0;
		} else {
			tc.x += 1;
		}
	}

	return 0;
}