#include "Layer.h"
#include "Factory.h"

CLayer::CLayer(void)
{
	m_mapTiles = new TileGrid;
}


CLayer::~CLayer(void)
{
	//delete m_mapTiles;
}

int CLayer::getWidth()
{
	return m_nWidth;
}

int CLayer::getHeight()
{
	return m_nHeight;
}

string CLayer::getName()
{
	return m_sName;
}

TileGrid * CLayer::getTileGrid()
{
	return m_mapTiles;
}

int CLayer::initialize(TiXmlNode *xmlnLayer)
{
	TiXmlElement *xmleLayer = xmlnLayer->ToElement();

	m_sName = xmleLayer->Attribute("name");
	m_nWidth = atoi(xmleLayer->Attribute("width"));
	m_nHeight = atoi(xmleLayer->Attribute("height"));

	parseLayerData(xmlnLayer);
	return 0;
}

int CLayer::parseLayerData(TiXmlNode *xmlnLayer)
{
	TiXmlNode *xmlnData = xmlnLayer->FirstChild("data");
	TiXmlNode *xmlnTile = xmlnData->FirstChild("tile");
	TiXmlElement *xmleTile = NULL;
	CTile *tlTile = NULL;
	TileCoord tc;

	tc.x = 0;
	tc.y = 0;

	while (xmlnTile) {
		xmleTile = xmlnTile->ToElement();

		m_mapTiles->insert(TileGrid::value_type(tc, CFactory::createTile(atoi(xmleTile->Attribute("gid")))));

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