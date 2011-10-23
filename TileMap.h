#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Util.h"
#include "Tile.h"

typedef unordered_map<TileCoord, CTile*, TileCoordHash> TileGrid;

class CTileMap
{
public:
	//CTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight);
	CTileMap();
	~CTileMap();

	void paintMap(ALLEGRO_DISPLAY *disp);

	int setSpritePalette(ALLEGRO_BITMAP * bmpSpritePalette);

	void setTmxFile(TiXmlDocument *xdocFile);

	// Carga y parseo de TMX
	int initialize();
	int parseTileset(TiXmlNode *xmlnMapNode);
	int parseTilesetImages(TiXmlNode *xmlnTilesetNode);
	int parseLayers(TiXmlNode *xmlnMapNode);
	int parseLayerData(TiXmlNode *xmlnLayerNode);

	int getWidth();
	int getHeight();
	int getTileWidth();
	int getTileHeight();

private:
	int m_nWidth;
	int m_nHeight;

	int m_nTileWidth;
	int m_nTileHeight;

	// ID / ResBitmap / ALLEGRO_BITMAP * / ResSpritePalette ?
	ALLEGRO_BITMAP *m_bmpSpritePalette;
	TiXmlDocument *m_xmlMapFile;

	TileGrid m_mMap;
};

#endif // TILE_MAP_H