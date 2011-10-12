#ifndef RESOURCE_STACK_H
#define RESOURCE_STACK_H

#include "Util.h"
#include "Resource.h"

// TODO: Definir si la clave del mapa va a ser un entero
typedef map<int, CResource> MapRes;

class CResourceStack
{
public:
	CResourceStack(void);
	~CResourceStack(void);

private:
	MapRes m_mRecursos;
};

#endif // RESOURCE_STACK_H