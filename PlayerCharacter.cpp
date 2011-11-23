#include "PlayerCharacter.h"


CPlayerCharacter::CPlayerCharacter(void)
{
	m_nSpeed = 2;
	m_ptPos.x = 48;
	m_ptPos.y = 48;
	m_bmpSprite = NULL;
}


CPlayerCharacter::~CPlayerCharacter(void)
{
}

void CPlayerCharacter::moveUp()
{
	m_ptPos.y -= m_nSpeed;
}

void CPlayerCharacter::moveDown()
{
	m_ptPos.y += m_nSpeed;
}

void CPlayerCharacter::moveLeft()
{
	m_ptPos.x -= m_nSpeed;
}

void CPlayerCharacter::moveRight()
{
	m_ptPos.x += m_nSpeed;
}

void CPlayerCharacter::paint(ALLEGRO_DISPLAY *disp)
{
	if (!m_bmpSprite) {
		m_bmpSprite = al_load_bitmap("char_test.png");
	}

	al_set_target_bitmap(al_get_backbuffer(disp));
	al_draw_bitmap(m_bmpSprite, m_ptPos.x, m_ptPos.y, 0);
}