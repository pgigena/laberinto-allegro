#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#pragma once
class CTile
{
public:
	// Agregar ide
	CTile(int nTileIndex, ALLEGRO_BITMAP *bmpTileImage);
	~CTile(void);

	ALLEGRO_BITMAP * getTileImage();
	bool getWalkable();

private:
	// C�digo que representa adem�s del indice si es pisable o no
	int m_nTileIndex;
	// Puntero a la im�gen que le corresponde al tile
	ALLEGRO_BITMAP *m_bmpTileImg;

	// No tiene que tener un Width y un Height?
};

