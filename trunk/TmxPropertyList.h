#ifndef TMX_PROPERTY_LIST_H
#define TMX_PROPERTY_LIST_H

#include "Util.h"

class CTmxPropertyList
{
public:
	CTmxPropertyList(void);
	~CTmxPropertyList(void);

	int parseTmx(TiXmlNode *xmlnPropertiesList);

	string getProperty(string sName);

private:
	// Properties contained on the list
	map<string, string> m_properties;

	int parseProperty(TiXmlNode *xmlnProperty);
};

#endif	// TMX_PROPERTY_LIST_H