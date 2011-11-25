#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Util.h"
#include "Tileset.h"
#include "Layer.h"

typedef vector<CTileset *> TilesetVector;
typedef vector<CLayer *> LayerVector;

class CTileMap
{
public:
	CTileMap();
	~CTileMap();

	void paint(ALLEGRO_DISPLAY *disp);

	void setTmxFile(TiXmlDocument *xdocFile);

	// TMX Loading and parsing
	int parseTmx();

	// Load of all the resources needed to draw the map
	void loadResources();

	int getWidth();
	int getHeight();

	int getTileWidth();
	int getTileHeight();

private:
	// Width and height of the map (Pixels)
	int m_nWidth, m_nHeight;

	// Width and height of each tile (Pixels)
	int m_nTileWidth, m_nTileHeight;

	// XML document containing the information of the map
	TiXmlDocument *m_xmlMapFile;

	// Tilesets used in the map
	TilesetVector m_vTilesets;

	// Contains the information of each layer 
	LayerVector m_vLayers;

	// Buffer where the drawn map is kept
	ALLEGRO_BITMAP *m_bmpMapBuffer;

	int parseTilesets(TiXmlNode *xmlnMap);
	int parseLayers(TiXmlNode *xmlnMap);

	void drawBuffer(ALLEGRO_DISPLAY *disp);
};

#endif // TILE_MAP_H