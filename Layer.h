#ifndef LAYER_H
#define LAYER_H

#include "Util.h"
#include "Tile.h"

class CLayer
{
public:
	CLayer(void);
	~CLayer(void);

	int initialize(TiXmlNode *xmlnLayer);

	int getWidth();
	int getHeight();

	string getName();

	TileGrid *getTileGrid();

private:
	int m_nWidth, m_nHeight;
	string m_sName;

	TileGrid *m_mapTiles;

	int parseLayerData(TiXmlNode *xmlnLayerNode);
};

#endif	// LAYER_H