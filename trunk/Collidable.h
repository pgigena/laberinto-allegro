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

	void setPos(Point pos);
	void setPos(int x, int y);
	void setContainer(Rect container);
	void setContainer(int w, int h);

	virtual bool isColliding(CCollidable *c);
	virtual bool isColliding(Point p, Rect r);

protected:
	Point m_pos;
	Rect m_container;
};

#endif	// COLLIDABLE_H