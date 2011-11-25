#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Util.h"

class CCollidable
{
public:
	CCollidable(void);
	~CCollidable(void);

	Point getPos();
	Rect getContainer();

	bool isColliding(CCollidable *c);
	bool isColliding(Point p, Rect r);

protected:
	Point m_pos;
	Rect m_container;
};

#endif	// COLLIDABLE_H