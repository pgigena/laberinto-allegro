#include "TilesetImg.h"
#include "Factory.h"

CTilesetImg::CTilesetImg(int nSpriteW, int nSpriteH)
{
	CTilesetImg(nSpriteW, nSpriteH, 0, 0);
}

CTilesetImg::CTilesetImg(int nSpriteW, int nSpriteH, int nMargin, int nSpacing)
{
	m_nTransparentColor = -1;

	m_nSpriteW = nSpriteW;
	m_nSpriteH = nSpriteH;
	m_nMargin = nMargin;
	m_nSpacing = nSpacing;
}

CTilesetImg::~CTilesetImg(void)
{
	//delete m_bmpPalette;
	al_destroy_bitmap(m_bmpPalette);
}

//CResBitmap * CTilesetImg::getImage()
ALLEGRO_BITMAP * CTilesetImg::getImage()
{
	return m_bmpPalette;
}

int CTilesetImg::getRowSize()
{
	return m_nRowSize;
}

int CTilesetImg::getTransparentColor()
{
	return m_nTransparentColor;
}

int CTilesetImg::parseTmx(TiXmlNode * xmlnImage)
{
	TiXmlElement *xmleImage = xmlnImage->ToElement();
	m_sPath = xmleImage->Attribute("source");

	m_nWidth = atoi(xmleImage->Attribute("width"));
	m_nHeight = atoi(xmleImage->Attribute("height"));

	m_nRowSize = m_nWidth / (m_nSpriteW + m_nSpacing);

	// Optional attribute
	char *sTrans = (char *) xmleImage->Attribute("trans");

	if (sTrans != NULL) {
		m_nTransparentColor = atoi(sTrans);
	}

	return 0;
}

void CTilesetImg::loadResources()
{
	m_bmpPalette = al_load_bitmap(m_sPath.c_str());
	/*m_bmpPalette = CFactory::createBitmap(xmleImage->Attribute("source"));

	if (!m_bmpPalette->load()) {
		return 1;
	}*/
}