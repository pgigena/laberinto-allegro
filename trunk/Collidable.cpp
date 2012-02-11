#include "Collidable.h"


CCollidable::CCollidable(void)
{
}

CCollidable::~CCollidable(void)
{
}

Point CCollidable::getPos()
{
	return m_pos;
}

Rect CCollidable::getContainer()
{
	return m_container;
}

void CCollidable::setPos(Point pos)
{
	m_pos = pos;
}

void CCollidable::setPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void CCollidable::setContainer(Rect container)
{
	m_container = container;
}

void CCollidable::setContainer(int w, int h)
{
	m_container.w = w;
	m_container.h = h;
}

bool CCollidable::isColliding(CCollidable *c)
{
	return isColliding(c->getPos(), c->getContainer());
}

bool CCollidable::isColliding(Point p, Rect r)
{
	if(m_pos.y + m_container.h < p.y)
		return false;
	if(m_pos.y > p.y + r.h)
		return false;
	if(m_pos.x + m_container.w < p.x)
		return false;
	if(m_pos.x > p.x + r.w)	
		return false;

	return true;
}