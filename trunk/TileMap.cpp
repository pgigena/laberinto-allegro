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

			cout << "TileX=" << tc.x << '\t';
			cout << "TileY=" << tc.y << '\t' << endl;
			cout << "Tile Index=" << nTileType << endl;

			m_mMap.insert(TileGrid::value_type(tc, CFactory::createTile(nTileType)));
			//m_mMap.insert(TileGrid::value_type(tc, new CTile(nTileType)));
			cout << "TileIdxReal=" << m_mMap[tc]->getTileIndex() << endl;
			cout << "_____________" << endl;
		}
	}

	for (int x = 0; x < m_nWidth; x++)
	{
		tc.x = x;
		for (int y = 0; y < m_nHeight; y++)
		{
			tc.y = y;

			cout << "TileX=" << tc.x << '\t';
			cout << "TileY=" << tc.y << '\t';
			cout << "Tile Index=" << m_mMap[tc]->getTileIndex() << endl;
			cout << "Ref=" << &m_mMap[tc] << endl;
			cout << "_____________" << endl;
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
	TileCoord tc;
	bool bIsGreen = false;

	for (int y = 0; y < m_nWidth; y++)
	{
		tc.y = y;

		for (int x = 0; x < m_nHeight; x++)
		{
			tc.x = x;

			if (bmpMesh != NULL) {
				al_destroy_bitmap(bmpMesh);
			}

			bmpMesh = al_create_bitmap(m_nTileWidth, m_nTileHeight);
			al_set_target_bitmap(bmpMesh);

			/*cout << "TileX=" << tc.x << '\t';
			cout << "TileY=" << tc.y << '\t';
			cout << "Tile Index=" << m_mMap[tc]->getTileIndex() << endl;
			cout << "_____________" << endl;*/

			if (m_mMap[tc]->getTileIndex() == 1) {
				colTileColor = al_map_rgb(0, 255, 0);
			} else {
				colTileColor = al_map_rgb(0, 0, 255);
			}

			al_clear_to_color(colTileColor);

			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(bmpMesh, (x * m_nTileWidth), (y * m_nTileHeight), 0);
		}
	}
}