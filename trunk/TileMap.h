#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "Util.h"
#include "Tileset.h"
#include "TmxLayer.h"
#include "TmxTileLayer.h"
#include "TmxObjectLayer.h"

typedef vector<CTileset *> TilesetVector;
typedef vector<CTmxTileLayer *> LayerVector;
typedef vector<CTmxObjectLayer *> ObjLayerVector;

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

	// Contains the information of each object layer
	ObjLayerVector m_vObjLayers;

	// Buffer where the drawn map is kept
	ALLEGRO_BITMAP *m_bmpMapBuffer;

	// Properties list
	CTmxPropertyList *m_mProperties;

	int parseTilesets(TiXmlNode *xmlnMap);
	int parseLayers(TiXmlNode *xmlnMap);
	int parseObjectLayers(TiXmlNode *xmlnMap);
	int parseProperties(TiXmlNode *xmlnMap);

	void drawBuffer(ALLEGRO_DISPLAY *display);
};

#endif // TILE_MAP_H