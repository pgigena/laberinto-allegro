#include "Collidable.h"


CCollidable::CCollidable(void)
{
}


CCollidable::~CCollidable(void)
{
}

Point CCollidable::getPos()
{
	return m_ptPos;
}

Rect CCollidable::getContainer()
{
	return m_rcContainer;
}

bool CCollidable::isColliding(CCollidable *c) {
	return isColliding(c->getPos(), c->getContainer());
}

bool CCollidable::isColliding(Point p, Rect r) {
	if (m_ptPos.y + m_rcContainer.h <= p.y) return false; // Arriba
	if (m_ptPos.y >= p.y + r.h) return false; // Abajo

	if (m_ptPos.x + m_rcContainer.w <= p.x) return false; // Izquierda
	if (m_ptPos.x >= p.x + r.w) return false; // Derecha

	return true;
}