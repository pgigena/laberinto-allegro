#include "Character.h"


CCharacter::CCharacter(void)
{
	m_container.x = 0;
	m_container.y = 0;
	m_nSpeed = 1;
}


CCharacter::~CCharacter(void)
{
}

void CCharacter::draw(ALLEGRO_DISPLAY *disp)
{
	al_set_target_bitmap(al_get_backbuffer(disp));
	al_draw_bitmap(m_bmpPalette, m_container.x, m_container.y, NULL);
}

void CCharacter::setPalette(ALLEGRO_BITMAP *bmp)
{
	m_bmpPalette = bmp;
}



void CCharacter::move(int directions)
{
	m_previousPos.x = m_container.x;
	m_previousPos.y = m_container.y;

	if (directions & UP) {
		cout << "UP!" << endl;
		m_container.y -= m_nSpeed;
	}

	if (directions & DOWN) {
		cout << "DOWN!" << endl;
		m_container.y += m_nSpeed;
	}

	if (directions & LEFT) {
		cout << "LEFT!" << endl;
		m_container.x -= m_nSpeed;
	}

	if (directions & RIGHT) {
		cout << "RIGHT!" << endl;
		m_container.x += m_nSpeed;
	}
}

bool CCharacter::checkCollision(CCollidable *c)
{
	bool bIsColliding = isColliding(c);

	if (bIsColliding) {
		m_container.x = m_previousPos.x;
		m_container.y = m_previousPos.y;
	}

	return bIsColliding;
}