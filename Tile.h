#ifndef TILE_H
#define TILE_H

#include "Util.h"

class CTile
{
public:
	// Agregar ide
	CTile(int nTileIndex);
	CTile(void);
	~CTile(void);

	//bool getWalkable();
	int getTileIndex();

private:
	// Código que representa además del indice si es pisable o no
	int m_nTileIndex;
	// No tiene que tener un Width y un Height?
};

// Definición del mapa TileGrid
typedef unordered_map<TileCoord, CTile*, TileCoordHash> TileGrid;

#endif // TILE_H