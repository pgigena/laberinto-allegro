#ifndef RES_BITMAP_H
#define RES_BITMAP_H

#include "Util.h"
#include "Resource.h"

class CResBitmap :
	public CResource
{

public:
	CResBitmap();
	~CResBitmap();

	int load();
	int unload();

	ALLEGRO_BITMAP * getResource();

private:
	ALLEGRO_BITMAP *m_bmpImage;
};

#endif // RES_BITMAP_H