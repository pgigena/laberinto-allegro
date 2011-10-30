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

	//ALLEGRO_BITMAP * getTileImage();
	//bool getWalkable();
	//void setTileImage(ALLEGRO_BITMAP *bmpTileImg);
	int getTileIndex();

private:
	// Código que representa además del indice si es pisable o no
	int m_nTileIndex;
	// Puntero a la imágen que le corresponde al tile
	//ALLEGRO_BITMAP *m_bmpTileImg;

	// No tiene que tener un Width y un Height?
};

typedef unordered_map<TileCoord, CTile*, TileCoordHash> TileGrid;

#endif // TILE_H