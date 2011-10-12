#include "TileMap.h"

CTileMap::CTileMap(int nWidth, int nHeight)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	for (int x = 0; x < nWidth; x++)
	{
		for (int y = 0; y < nHeight; y++)
		{
			TileCoord tc;
			tc.x = x;
			tc.y = y;
			CTile *t = new CTile(x);

			//cout << "X" << x << "=" << tgc.first.x << "\t";
			//cout << "Y" << y << "=" << tgc.first.y << endl;
			//m_mMap.insert(TileGrid::value_type(tc, t));
		}
	}
}

CTileMap::~CTileMap(void)
{
}

/*int CTileMap::SetTerrainPalette(char *szPath)
{
	m_bmpTerrainPalette = al_load_bitmap(szPath);

	if (!m_bmpTerrainPalette) {
		return 1;
	}
	return 0;
}*/

void CTileMap::pintarMapa(ALLEGRO_DISPLAY *disp)
{
	ALLEGRO_BITMAP *bmpMesh = NULL;
	al_set_target_bitmap(al_get_backbuffer(disp));

	for (int i = 0; i < 10; i++)
	{
		for (int j=0; j < 10; j++) {
			//m_tlMapa[i][j].getTileIndex();

			/*bmpMesh = m_tlMapa[i][j].getTileImage();
			al_draw_bitmap(bmpMesh, (i * 30), (j * 30), 0);*/
		}
	}
}