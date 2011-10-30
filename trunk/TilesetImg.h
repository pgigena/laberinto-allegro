#ifndef TILESET_IMG_H
#define TILESET_IMG_H

#include "Util.h"
#include "ResBitmap.h"
#include "ResourceStack.h"

class CTilesetImg
{
public:
	CTilesetImg(int nSpriteW, int nSpriteH);
	~CTilesetImg(void);

	int getRowSize();
	int getTransparentColor();
	//CResBitmap * getImage();
	ALLEGRO_BITMAP * getImage();

	int initialize(TiXmlNode * xmlnImage);
private:
	int m_nWidth, m_nHeight;
	int m_nSpriteW, m_nSpriteH;

	int m_nTransparentColor;

	// Row size in sprites
	int m_nRowSize;

	//CResBitmap * m_bmpPalette;
	ALLEGRO_BITMAP * m_bmpPalette;
};

#endif	// TILESET_IMG_H