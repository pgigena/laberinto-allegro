#include "TileMap.h"

CTileMap::CTileMap(int nWidth, int nHeight, int nTileWidth, int nTileHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nTileWidth = nTileWidth;
	m_nTileHeight = nTileHeight;

	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			TileCoord tc;
			tc.x = x;
			tc.y = y;

			m_mMap.insert(TileGrid::value_type(tc, new CTile()));
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
	ALLEGRO_BITMAP *bmpMesh = NULL;
	ALLEGRO_COLOR colTileColor = al_map_rgb(0, 255, 0);
	bool bIsGreen = false;

	for (int y = 0; y < m_nWidth; y++)
	{
		for (int x = 0; x < m_nHeight; x++)
		{
			if (bmpMesh != NULL) {
				al_destroy_bitmap(bmpMesh);
			}

			bmpMesh = al_create_bitmap(15, 15);
			al_set_target_bitmap(bmpMesh);

			if (!bIsGreen) {
				colTileColor = al_map_rgb(0, 0, 255);
				bIsGreen = true;
			}
			else {
				colTileColor = al_map_rgb(0, 255, 0);
				bIsGreen = false;
			}

			al_clear_to_color(colTileColor);

			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(bmpMesh, (x * m_nTileWidth), (y * m_nTileHeight), 0);
		}
		if (!bIsGreen) {
			colTileColor = al_map_rgb(0, 0, 255);
			bIsGreen = true;
		}
		else {
			colTileColor = al_map_rgb(0, 255, 0);
			bIsGreen = false;
		}
	}
}