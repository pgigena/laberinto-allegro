#include "ResourceStack.h"

CResourceStack::CResourceStack(void)
{
}

CResourceStack::~CResourceStack(void)
{
}

CResource * CResourceStack::getResource(int nResId)
{
	return m_mRecursos[nResId];
}