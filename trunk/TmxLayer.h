#ifndef TMX_LAYER_H
#define TMX_LAYER_H

#include "Util.h"

class CTmxLayer
{
public:
	CTmxLayer(void);
	~CTmxLayer(void);

protected:
	// Width and height of the layer (Tiles)
	// Deprecated, all layers' size is the same as the map size
	int m_nWidth, m_nHeight;

	// Layer name
	string m_sName;
};

#endif	// TMX_LAYER_H