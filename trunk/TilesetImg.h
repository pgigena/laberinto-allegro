#ifndef TILESET_IMG_H
#define TILESET_IMG_H

#include "Util.h"
#include "ResBitmap.h"
#include "ResourceStack.h"

class CTilesetImg
{
public:
	CTilesetImg(int nSpriteW, int nSpriteH, int nMargin, int nSpacing);
	CTilesetImg(int nSpriteW, int nSpriteH);
	~CTilesetImg(void);

	int getRowSize();
	int getTransparentColor();
	//CResBitmap * getImage();
	ALLEGRO_BITMAP * getImage();

	int parseTmx(TiXmlNode * xmlnImage);
	void loadResources();

private:
	// Width and height of the Image (Pixels)
	int m_nWidth, m_nHeight;
	// Width and height of each sprite (Pixels)
	int m_nSpriteW, m_nSpriteH;
	// Margin of the palette and spacing between tiles (Pixels)
	int m_nMargin, m_nSpacing;

	int m_nTransparentColor;

	// Tiles per row
	int m_nRowSize;

	string m_sPath;

	//CResBitmap * m_bmpPalette;
	ALLEGRO_BITMAP * m_bmpPalette;
};

#endif	// TILESET_IMG_H