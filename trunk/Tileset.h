#ifndef TILESET_H
#define TILESET_H

#include "Util.h"
#include "TilesetImg.h"
#include "TmxPropertyList.h"

typedef map<int, CTmxPropertyList*> TilesetProperties;

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

	// Id of the first sprite on the palette (Relative to all pallettes)
	int m_nFirstGId;

	// Width and height of a tile (Pixels)
	int m_nTileW, m_nTileH;

	// Margin of the palette (Pixels)
	int m_nMargin;
	// Spacing between tiles (Pixels)
	int m_nSpacing;

	TilesetProperties *m_mTilesetProps;

	CTilesetImg *m_palTilePalette;

	int parseTiles(TiXmlNode *xmlnTileset);
};

#endif	// TILESET_H