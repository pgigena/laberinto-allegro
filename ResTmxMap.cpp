#include "ResTmxMap.h"


CResTmxMap::CResTmxMap()
{
}


CResTmxMap::~CResTmxMap()
{
	delete m_xmlMapFile;
}

int CResTmxMap::load()
{
	m_xmlMapFile = new TiXmlDocument(m_sPath.c_str());

	// Falló la carga
	if (!m_xmlMapFile->LoadFile()) {
		return 1;
	}

	return 0;
}

/*int CResTmxMap::unload()
{
	return 0;
}*/