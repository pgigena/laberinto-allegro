#include "ResourceStack.h"

CResourceStack::CResourceStack(void)
{
}

CResourceStack::~CResourceStack(void)
{
}

void CResourceStack::addResource(string sResId, CResource *rcRes)
{
	m_mapResources.insert(ResMap::value_type(sResId, rcRes));
}

CResource * CResourceStack::getResource(string sResId)
{
	return m_mapResources[sResId];
}