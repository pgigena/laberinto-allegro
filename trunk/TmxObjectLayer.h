#ifndef TMX_OBJECT_LAYER_H
#define TMX_OBJECT_LAYER_H

#include "Util.h"
#include "TmxObject.h"

typedef vector<CTmxObject *> TmxObjectVector;

class CTmxObjectLayer
{
public:
	CTmxObjectLayer(void);
	~CTmxObjectLayer(void);

	int parseTmx(TiXmlNode *xmlnObjectLayer);

	TmxObjectVector *getLayerObjects();
//	void paint(ALLEGRO_DISPLAY *display);

private:
	// Deprecated, all layers' size is the same as the map size
	//int m_nWidth, m_nHeight;

	// The object layer's name
	string m_sName;

	vector<CTmxObject *> *m_vObjects;

	CTmxPropertyList *m_mProperties;

	int parseLayerObjects(TiXmlNode *xmlnObjectLayer);
};

#endif	// TMX_OBJECT_LAYER_H