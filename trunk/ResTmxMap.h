#ifndef RES_TMX_MAP_H
#define RES_TMX_MAP_H

#include "Util.h"
#include "Resource.h"

class CResTmxMap :
	public CResource
{
public:
	CResTmxMap();
	~CResTmxMap();

	int load();
	//int unload();

	TiXmlDocument * getResource();

private:
	TiXmlDocument *m_xmlMapFile;
};

#endif // RES_TMX_MAP_H