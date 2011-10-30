#include "Tileset.h"
#include "Factory.h"

CTileset::CTileset(void)
{
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

string CTileset::getName()
{
	return m_sName;
}

CTilesetImg * CTileset::getTilePalette()
{
	return m_palTilePalette;
}

int CTileset::initialize(TiXmlNode *xmlnTileset)
{
	TiXmlElement *xmleTileset = NULL;
	xmleTileset = xmlnTileset->ToElement();

	m_sName = xmleTileset->Attribute("name");
	m_nFirstGId = atoi(xmleTileset->Attribute("firstgid"));
	m_nTileW = atoi(xmleTileset->Attribute("tilewidth"));
	m_nTileH = atoi(xmleTileset->Attribute("tileheight"));

	m_palTilePalette = CFactory::createTilesetImg(m_nTileW, m_nTileH);
	m_palTilePalette->initialize(xmlnTileset->FirstChild("image"));

	return 0;
}