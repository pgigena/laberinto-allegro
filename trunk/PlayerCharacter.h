#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "Util.h"
#include "Collidable.h"

class CPlayerCharacter :
	public CCollidable
{
public:
	CPlayerCharacter(void);
	~CPlayerCharacter(void);

	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();

	void paint(ALLEGRO_DISPLAY *disp);
private:
	int m_nSpeed;
	ALLEGRO_BITMAP *m_bmpSprite;
	
};

#endif	// PLAYER_CHARACTER_H