#ifndef CHARACTER_H
#define CHARACTER_H

#include "Util.h"
#include "Collidable.h"

class CCharacter :
	public CCollidable
{
public:
	CCharacter(void);
	~CCharacter(void);

	void draw(ALLEGRO_DISPLAY *disp);
	void move(Direction d);

	void setPalette(ALLEGRO_BITMAP *bmp);

protected:
	ALLEGRO_BITMAP *m_bmpPalette;
	int m_nSpeed;
};

#endif	// CHARACTER_H