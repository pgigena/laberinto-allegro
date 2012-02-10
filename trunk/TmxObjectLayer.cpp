#include "TmxObjectLayer.h"
#include "Factory.h"

CTmxObjectLayer::CTmxObjectLayer(void)
{
	m_vObjects = new TmxObjectVector;
	m_mProperties = NULL;
}


CTmxObjectLayer::~CTmxObjectLayer(void)
{
	m_vObjects->clear();
	delete m_vObjects;

	if (m_mProperties) {
		delete m_mProperties;
	}
}

TmxObjectVector *CTmxObjectLayer::getLayerObjects()
{
	return m_vObjects;
}

int CTmxObjectLayer::parseTmx(TiXmlNode *xmlnObjectLayer)
{
	TiXmlElement *xmleObjLayer = xmlnObjectLayer->ToElement();
	TiXmlNode *xmlnProperties = NULL;

	m_sName = xmleObjLayer->Attribute("name");

	// DEPRECATED
	//m_nWidth = atoi(xmleLayer->Attribute("width"));
	//m_nHeight = atoi(xmleLayer->Attribute("height"));

	// Search for a property list
	xmlnProperties = xmlnObjectLayer->FirstChild("properties");

	if (xmlnProperties) {
		// If the property list has not been created, create it
		if (!m_mProperties) {
			m_mProperties = new CTmxPropertyList();
		}

		// Parse the properties
		m_mProperties->parseTmx(xmlnProperties);
	}

	parseLayerObjects(xmlnObjectLayer);
	return 0;
}

int CTmxObjectLayer::parseLayerObjects(TiXmlNode *xmlnObjectLayer)
{
	TiXmlNode *xmlnObject = xmlnObjectLayer->FirstChild("object");
	TiXmlElement *xmleObject = NULL;

	while (xmlnObject) {
		xmleObject = xmlnObject->ToElement();

		m_vObjects->push_back(CFactory::createObject());
		m_vObjects->back()->parseTMX(xmleObject);

		xmlnObject = xmlnObjectLayer->IterateChildren("object", xmlnObject);
	}

	return 0;
}