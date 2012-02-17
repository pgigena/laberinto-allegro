#include "Collidable.h"


CCollidable::CCollidable(void)
{
}

CCollidable::~CCollidable(void)
{
}

Point CCollidable::getPos()
{
	Point pos;
	pos.x = m_container.x;
	pos.y = m_container.y;

	return pos;
}

Rect CCollidable::getContainer()
{
	return m_container;
}

void CCollidable::setPos(Point pos)
{
	m_container.x = pos.x;
	m_container.y = pos.y;
}

void CCollidable::setPos(int x, int y)
{
	m_container.x = x;
	m_container.y = y;
}

void CCollidable::setContainer(Rect container)
{
	m_container = container;
}

void CCollidable::setContainer(Point pos, int w, int h)
{
	setContainer(pos.x, pos.y, w, h);
}

void CCollidable::setContainer(int x, int y, int w, int h)
{
	m_container.x = x;
	m_container.y = y;
	m_container.w = w;
	m_container.h = h;
}

bool CCollidable::isColliding(CCollidable *c)
{
	return isColliding(c->getContainer());
}

bool CCollidable::isColliding(Rect r)
{
	if(m_container.y + m_container.h < r.y)
		return false;
	if(m_container.y > r.y + r.h)
		return false;
	if(m_container.x + m_container.w < r.x)
		return false;
	if(m_container.x > r.x + r.w)
		return false;

	return true;
}