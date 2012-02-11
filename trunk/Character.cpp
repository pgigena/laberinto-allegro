#include "Character.h"


CCharacter::CCharacter(void)
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_nSpeed = 8;
}


CCharacter::~CCharacter(void)
{
}

void CCharacter::draw(ALLEGRO_DISPLAY *disp)
{
	al_set_target_bitmap(al_get_backbuffer(disp));
	al_draw_bitmap(m_bmpPalette, m_pos.x, m_pos.y, NULL);
}

void CCharacter::setPalette(ALLEGRO_BITMAP *bmp)
{
	m_bmpPalette = bmp;
}

void CCharacter::move(Direction d)
{
	m_previousPos = m_pos;
	if (d == UP) {
		m_pos.y -= m_nSpeed;
	}

	if (d == DOWN) {
		m_pos.y += m_nSpeed;
	}

	if (d == LEFT) {
		m_pos.x -= m_nSpeed;
	}

	if (d == RIGHT) {
		m_pos.x += m_nSpeed;
	}
}

bool CCharacter::checkCollision(CCollidable *c)
{
	bool bIsColliding = isColliding(c);

	if (bIsColliding) {
		m_pos = m_previousPos;
	}

	return bIsColliding;
}