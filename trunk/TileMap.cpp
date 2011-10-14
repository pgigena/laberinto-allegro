#include "TileMap.h"
#include "Factory.h"

CTileMap::CTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nTileWidth = nTileWidth;
	m_nTileHeight = nTileHeight;
	bool bGreenTile = false;
	int nTileType = 0;
	TileCoord tc;

	for (int x = 0; x < m_nWidth; x++)
	{
		tc.x = x;
		for (int y = 0; y < m_nHeight; y++)
		{
			tc.y = y;

			if (bGreenTile) {
				nTileType = 1;
				bGreenTile = false;
			} else {
				nTileType = 0;
				bGreenTile = true;
			}

			m_mMap.insert(TileGrid::value_type(tc, CFactory::createTile(nTileType)));
			//cout << "Ref[" << tc.x << "," << tc.y << "]=" << &m_mMap[tc] << endl;
		}
		if (bGreenTile) {
			nTileType = 1;
			bGreenTile = false;
		} else {
			nTileType = 0;
			bGreenTile = true;
		}
	}
}

CTileMap::~CTileMap(void)
{
	m_mMap.clear();
}

/*int CTileMap::SetTerrainPalette(char *szPath)
{
	m_bmpTerrainPalette = al_load_bitmap(szPath);

	if (!m_bmpTerrainPalette) {
		return 1;
	}
	return 0;
}*/

void CTileMap::paintMap(ALLEGRO_DISPLAY *display)
{
	ALLEGRO_BITMAP *bmpGreenMesh = NULL;
	ALLEGRO_BITMAP *bmpBlueMesh = NULL;
	TileCoord tc;

	bmpGreenMesh = al_create_bitmap(m_nTileWidth, m_nTileHeight);
	al_set_target_bitmap(bmpGreenMesh);
	al_clear_to_color(al_map_rgb(0, 255, 0));

	bmpBlueMesh = al_create_bitmap(m_nTileWidth, m_nTileHeight);
	al_set_target_bitmap(bmpBlueMesh);
	al_clear_to_color(al_map_rgb(0, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	for (int y = 0; y < m_nWidth; y++)
	{
		tc.y = y;

		for (int x = 0; x < m_nHeight; x++)
		{
			tc.x = x;

			if (m_mMap[tc]->getTileIndex() == 1) {
				al_draw_bitmap(bmpGreenMesh, (x * m_nTileWidth), (y * m_nTileHeight), 0);
			} else {
				al_draw_bitmap(bmpBlueMesh, (x * m_nTileWidth), (y * m_nTileHeight), 0);
			}
		}
	}
}