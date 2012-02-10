#include "TmxObject.h"

CTmxObject::CTmxObject(void)
{
	m_nGId = 0;
	m_mProperties = NULL;
}


CTmxObject::~CTmxObject(void)
{
	delete m_mProperties;
}

int CTmxObject::getGId()
{
	return m_nGId;
}

int CTmxObject::getWidth()
{
	return m_nWidth;
}

int CTmxObject::getHeight()
{
	return m_nHeight;
}

Point CTmxObject::getPos()
{
	return m_pos;
}

CTmxPropertyList *CTmxObject::getProperties()
{
	return m_mProperties;
}

int CTmxObject::parseTMX(TiXmlNode *xmlnObject) {
	TiXmlElement *xmleObject = xmlnObject->ToElement();
	TiXmlNode *xmlnProperties = NULL;

	char *szAux = NULL;

	szAux = (char *) xmleObject->Attribute("name");

	if (szAux) {
		m_sName = szAux;
		szAux = NULL;
	}

	szAux = (char *) xmleObject->Attribute("type");

	if (szAux) {
		m_sType = szAux;
		szAux = NULL;
	}

	m_pos.x = atoi(xmleObject->Attribute("x"));
	m_pos.y = atoi(xmleObject->Attribute("y"));

	// Read object associated tile GId (Optional Property)
	szAux = (char *) xmleObject->Attribute("gid");

	if (szAux) {
		m_nGId = atoi(szAux);
		szAux = NULL;
	}


	// Read Object Width (Optional property)
	szAux = (char *) xmleObject->Attribute("width");

	if (szAux) {
		m_nWidth = atoi(szAux);
		szAux = NULL;
	}

	// Read Object Height (Optional property)
	szAux = (char *) xmleObject->Attribute("height");

	if (szAux) {
		m_nHeight = atoi(szAux);
		szAux = NULL;
	}

	// Search for a property list
	xmlnProperties = xmlnObject->FirstChild("properties");

	if (xmlnProperties) {
		// If the property list has not been created, create it
		if (!m_mProperties) {
			m_mProperties = new CTmxPropertyList();
		}

		// Parse the properties
		m_mProperties->parseTmx(xmlnProperties);
	}

	return 0;
}