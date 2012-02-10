#ifndef TMX_OBJECT_H
#define TMX_OBJECT_H

#include "Util.h"
#include "TmxPropertyList.h"

class CTmxObject
{
public:
	CTmxObject(void);
	~CTmxObject(void);

	int parseTMX(TiXmlNode *xmlnObject);

	Point getPos();

	int getGId();

	int getWidth();
	int getHeight();

	string getName();
	string getType();

	CTmxPropertyList *getProperties();

private:
	// Inherit collidable?
	int m_nWidth, m_nHeight;

	// Object GId
	int m_nGId;

	// Object position (Pixels)
	Point m_pos;

	// Object name
	string m_sName;

	// Object type
	string m_sType;

	// Properties list
	CTmxPropertyList *m_mProperties;
};

#endif	// TMX_OBJECT_H