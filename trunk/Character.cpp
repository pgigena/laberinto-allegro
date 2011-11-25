#include "Character.h"


CCharacter::CCharacter(void)
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_nSpeed = 3;
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
	if (d == UP)
		m_pos.y -= m_nSpeed;

	if (d == DOWN)
		m_pos.y += m_nSpeed;

	if (d == LEFT)
		m_pos.x -= m_nSpeed;

	if (d == RIGHT)
		m_pos.x += m_nSpeed;
}