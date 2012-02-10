#include "Tile.h"


CTile::CTile(int nGId)
{
	m_nGId = nGId;
}

CTile::CTile(void)
{
}

CTile::~CTile(void)
{
	// TODO: Destruyo el bitmap de acá o le pido al ResourceStack que lo haga?
}

int CTile::getGId()
{
	return m_nGId;
}

/*bool CTile::getWalkable()
{
	// TODO: Verificar documentación
	// http://www.gamedev.net/page/resources/_/reference/programming/isometric-and-tile-based-games/298/tile-based-games-faq-version-12-r728
	return m_nTileIndex;
}*/
