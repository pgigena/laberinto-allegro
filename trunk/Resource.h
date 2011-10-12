#ifndef RESOURCE_H
#define RESOURCE_H

#include "Util.h"

class CResource
{
public:
	CResource(void);
	~CResource(void);

	virtual int load() { return 0; };
	virtual int unload() { return 0; };
	void setPath(string sPath);

protected:
	string m_sPath;
};

#endif // RESOURCE_H