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
	void move(int directions);

	void setPalette(ALLEGRO_BITMAP *bmp);

	bool checkCollision(CCollidable *c);

protected:
	ALLEGRO_BITMAP *m_bmpPalette;
	int m_nSpeed;
	Point m_previousPos;
};

#endif	// CHARACTER_H