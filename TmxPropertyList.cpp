#include "TmxPropertyList.h"


CTmxPropertyList::CTmxPropertyList(void)
{
}


CTmxPropertyList::~CTmxPropertyList(void)
{
}

string CTmxPropertyList::getProperty(string sName)
{
	if (m_properties.find(sName) == m_properties.end()) {
		return NULL;
	}

	return m_properties[sName];
}

int CTmxPropertyList::parseTmx(TiXmlNode *xmlnPropertiesList)
{
	TiXmlNode *xmlnProperty = xmlnPropertiesList->FirstChild("property");

	while (xmlnProperty) {
		parseProperty(xmlnProperty);
		xmlnProperty = xmlnPropertiesList->IterateChildren("property", xmlnProperty);
	}
	return 0;
}

int CTmxPropertyList::parseProperty(TiXmlNode *xmlnProperty)
{
	TiXmlElement *xmleProperty = xmlnProperty->ToElement();
	string  sName, sValue;

	sName = xmleProperty->Attribute("name");
	sValue = xmleProperty->Attribute("value");

	m_properties[sName] = sValue;
	cout << sName << "=" << sValue << endl << "____________" << endl;

	return 0;
}