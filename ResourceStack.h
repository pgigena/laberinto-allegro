#ifndef RESOURCE_STACK_H
#define RESOURCE_STACK_H

#include "Util.h"
#include "Resource.h"

// TODO: Definir si la clave del mapa va a ser un string
typedef map<string, CResource*> ResMap;

// TODO: Definir si el ResourceStack va a ser estático
class CResourceStack
{
public:
	CResourceStack(void);
	~CResourceStack(void);

	CResource * getResource(string sResId);

	void addResource(string sResId, CResource *rcRes);

private:
	ResMap m_mapResources;
};

#endif // RESOURCE_STACK_H