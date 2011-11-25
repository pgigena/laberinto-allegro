#ifndef TILE_H
#define TILE_H

#include "Util.h"

class CTile
{
public:
	CTile(int nTileIndex);
	CTile(void);
	~CTile(void);

	//bool getWalkable();
	int getTileIndex();

private:
	// Index that indicates the sprite (from the palette) to be used when drawing
	int m_nTileIndex;
	// Does it need Width and Height?
};

// TileGrid map definition
typedef unordered_map<TileCoord, CTile*, TileCoordHash> TileGrid;

#endif // TILE_H