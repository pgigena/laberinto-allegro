#include "Util.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#pragma once
class CEnvironment
{
public:
	CEnvironment(void);
	~CEnvironment(void);

	virtual void paint(ALLEGRO_DISPLAY *disp) { return; };

	TileCoord getElementPos();

private:
	TileCoord tcPos;
};

