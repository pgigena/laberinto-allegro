#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Util.h"

class CCollidable
{
public:
	CCollidable(void);
	~CCollidable(void);

	bool isColliding(CCollidable *col);
	bool isColliding(Point p, Rect r);
	Point getPos();
	Rect getContainer();

protected:
	Rect m_rcContainer;
	Point m_ptPos;
};

#endif	// COLLIDABLE_H