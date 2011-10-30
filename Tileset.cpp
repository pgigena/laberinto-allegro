#include "Tileset.h"
#include "Factory.h"

CTileset::CTileset(void)
{
	m_nSpacing = 0;
	m_nMargin = 0;
}


CTileset::~CTileset(void)
{
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

int CTileset::initialize(TiXmlNode *xmlnTileset)
{
	TiXmlElement *xmleTileset = NULL;
	xmleTileset = xmlnTileset->ToElement();
	char *szAux = NULL;

	m_sName = xmleTileset->Attribute("name");
	m_nFirstGId = atoi(xmleTileset->Attribute("firstgid"));
	m_nTileW = atoi(xmleTileset->Attribute("tilewidth"));
	m_nTileH = atoi(xmleTileset->Attribute("tileheight"));

	szAux = (char *) xmleTileset->Attribute("margin");

	if (szAux) {
		m_nMargin = atoi(szAux);
		szAux = NULL;
	}

	szAux = (char *) xmleTileset->Attribute("spacing");
	if (szAux) {
		m_nSpacing = atoi(szAux);
	}

	m_palTilePalette = CFactory::createTilesetImg(m_nTileW, m_nTileH, m_nMargin, m_nSpacing);
	m_palTilePalette->initialize(xmlnTileset->FirstChild("image"));

	return 0;
}