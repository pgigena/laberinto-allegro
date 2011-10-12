#ifndef TILE_H
#define TILE_H

#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class CTile
{
public:
	// Agregar ide
	CTile(int nTileIndex);
	//CTile(void);
	~CTile(void);

	ALLEGRO_BITMAP * getTileImage();
	//bool getWalkable();
	void setTileImage(ALLEGRO_BITMAP *bmpTileImg);
	int getTileIndex();

private:
	// C�digo que representa adem�s del indice si es pisable o no
	int m_nTileIndex;
	// Puntero a la im�gen que le corresponde al tile
	ALLEGRO_BITMAP *m_bmpTileImg;

	// No tiene que tener un Width y un Height?
};

#endif // TILE_H