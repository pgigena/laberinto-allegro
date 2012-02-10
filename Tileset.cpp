#include "Tileset.h"
#include "Factory.h"

CTileset::CTileset(void)
{
	m_nSpacing = 0;
	m_nMargin = 0;
	m_mTilesetProps = new TilesetProperties;
}


CTileset::~CTileset(void)
{
	delete m_palTilePalette;
	if (m_mTilesetProps) {
		m_mTilesetProps->clear();
		delete m_mTilesetProps;
	}
}

int CTileset::getFirstGId()
{
	return m_nFirstGId;
}

int CTileset::getTileW()
{
	return m_nTileW;
}

int CTileset::getTileH()
{
	return m_nTileH;
}

int CTileset::getMargin()
{
	return m_nMargin;
}

int CTileset::getSpacing()
{
	return m_nSpacing;
}

string CTileset::getName()
{
	return m_sName;
}

CTilesetImg * CTileset::getTilePalette()
{
	return m_palTilePalette;
}

int CTileset::getTileX(int nGId)
{
	return ((m_nTileW + m_nSpacing) * ((nGId - m_nFirstGId) % m_palTilePalette->getRowSize())) + m_nMargin;
}

int CTileset::getTileY(int nGId)
{
	return ((m_nTileH + m_nSpacing) * ((nGId - m_nFirstGId) / m_palTilePalette->getRowSize())) + m_nMargin;
}

/*Point CTileset::getTilePos(int nGId)
{
	Point p;
	p.x = getTileX(nGId);
	p.y = getTileY(nGId);
}*/

int CTileset::parseTmx(TiXmlNode *xmlnTileset)
{
	TiXmlElement *xmleTileset = NULL;
	xmleTileset = xmlnTileset->ToElement();
	char *szAux = NULL;

	m_sName = xmleTileset->Attribute("name");
	m_nFirstGId = atoi(xmleTileset->Attribute("firstgid"));
	m_nTileW = atoi(xmleTileset->Attribute("tilewidth"));
	m_nTileH = atoi(xmleTileset->Attribute("tileheight"));

	// Optional attribute
	szAux = (char *) xmleTileset->Attribute("margin");

	if (szAux) {
		m_nMargin = atoi(szAux);
		szAux = NULL;
	}

	// Optional attribute
	szAux = (char *) xmleTileset->Attribute("spacing");
	if (szAux) {
		m_nSpacing = atoi(szAux);
		szAux = NULL;
	}

	m_palTilePalette = CFactory::createTilesetImg(m_nTileW, m_nTileH, m_nMargin, m_nSpacing);
	m_palTilePalette->parseTmx(xmlnTileset->FirstChild("image"));

	parseTiles(xmlnTileset);

	return 0;
}

int CTileset::parseTiles(TiXmlNode *xmlnTileset)
{
	TiXmlNode *xmlnTile = xmlnTileset->FirstChild("tile");
	TiXmlElement * xmleTile = NULL;
	int nGId = 0;

	while (xmlnTile) {
		xmleTile = xmlnTile->ToElement();
		nGId = atoi(xmleTile->Attribute("id"));

		m_mTilesetProps->insert(TilesetProperties::value_type(nGId, CFactory::createPropertiesList()));
		m_mTilesetProps->at(nGId)->parseTmx(xmlnTile->FirstChild("properties"));
		xmlnTile = xmlnTileset->IterateChildren("tile", xmlnTile);
	}
	return 0;
}

void CTileset::loadResources()
{
	return m_palTilePalette->loadResources();
}