#ifndef TMX_TILE_LAYER_H
#define TMX_TILE_LAYER_H

#include "Util.h"
#include "TmxLayer.h"
#include "Tile.h"
#include "TmxPropertyList.h"

class CTmxTileLayer :
		CTmxLayer
{
public:
	CTmxTileLayer(void);
	~CTmxTileLayer(void);

	int parseTmx(TiXmlNode *xmlnLayer);

	int getWidth();
	int getHeight();

	string getName();

	TileGrid *getTileGrid();

private:
	// Map containing all the tiles in "Tile Coordinate" => "Tile" pairs
	TileGrid *m_mapTiles;

	CTmxPropertyList *m_mProperties;

	int parseLayerData(TiXmlNode *xmlnLayerNode);
};

#endif	// TMX_TILE_LAYER_H