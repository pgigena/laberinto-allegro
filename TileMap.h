#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Util.h"
#include "Tile.h"

typedef map<TileCoord, CTile*> TileGrid;

class CTileMap
{
public:
	CTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight);
	~CTileMap();

	void paintMap(ALLEGRO_DISPLAY *disp);

private:
	int m_nWidth;
	int m_nHeight;

	int m_nTileWidth;
	int m_nTileHeight;

	TileGrid m_mMap;
};

#endif // TILE_MAP_H