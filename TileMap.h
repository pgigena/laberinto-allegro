#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Util.h"
#include "Tile.h"

typedef map<TileCoord, CTile*> TileGrid;
typedef pair<TileCoord, CTile*> TileGridCell;

class CTileMap
{
public:
	CTileMap(int nWidth, int nHeight);
	~CTileMap();

	void pintarMapa(ALLEGRO_DISPLAY *disp);

private:
	int m_nWidth;
	int m_nHeight;
	TileGrid m_mMap;

	//ALLEGRO_BITMAP *m_bmpTerrainPalette;
};

#endif // TILE_MAP_H