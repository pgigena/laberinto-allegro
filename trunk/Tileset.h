#ifndef TILESET_H
#define TILESET_H

#include "Util.h"
#include "TilesetImg.h"

class CTileset
{
public:
	CTileset(void);
	~CTileset(void);

	string getName();

	int getFirstGId();
	int getTileW();
	int getTileH();
	int getMargin();
	int getSpacing();

	int getTileX(int nGId);
	int getTileY(int nGId);
	//Point getTilePos(int nGId);

	CTilesetImg * getTilePalette();

	int parseTmx(TiXmlNode *xmlnTileset);
	void loadResources();

private:
	// Name of the Tileset
	string m_sName;

	// Id of the first sprite on the palette
	int m_nFirstGId;

	// Width and height of a tile in pixels
	int m_nTileW, m_nTileH;

	int m_nMargin;
	int m_nSpacing;

	CTilesetImg *m_palTilePalette;
};

#endif	// TILESET_H