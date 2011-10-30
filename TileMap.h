#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Util.h"
#include "Tileset.h"
#include "Layer.h"

typedef vector<CTileset *> TilesetVector;
typedef vector<CLayer *> LayerVector;

class CTileMap
{
public:
	//CTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight);
	CTileMap();
	~CTileMap();

	void paint(ALLEGRO_DISPLAY *disp);

	void setTmxFile(TiXmlDocument *xdocFile);

	// Carga y parseo de TMX
	int initialize();

	int getWidth();
	int getHeight();

	int getTileWidth();
	int getTileHeight();

private:
	int m_nWidth, m_nHeight;

	int m_nTileWidth;
	int m_nTileHeight;

	TiXmlDocument *m_xmlMapFile;

	TilesetVector m_vTilesets;
	LayerVector m_vLayers;

	int parseTilesets(TiXmlNode *xmlnMap);
	int parseLayers(TiXmlNode *xmlnMap);
};

#endif // TILE_MAP_H