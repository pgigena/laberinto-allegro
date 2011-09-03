#include "Tile.h"


CTile::CTile(int nTileIndex, ALLEGRO_BITMAP *bmpTileImage)
{
	m_bmpTileImg = bmpTileImage;
}


CTile::~CTile(void)
{
}

ALLEGRO_BITMAP * CTile::getTileImage()
{
	return m_bmpTileImg;
}

bool CTile::getWalkable()
{
	// TODO: Verificar documentación
	// http://www.gamedev.net/page/resources/_/reference/programming/isometric-and-tile-based-games/298/tile-based-games-faq-version-12-r728
	return m_nTileIndex;
}