/*#include "tinyxml.h"
#include <conio.h>
#include <iostream>

using namespace std;

void parseTileset(TiXmlNode *mapNode);
void parseTilesetImages(TiXmlNode *tilesetNode);
void parseLayers(TiXmlNode *mapNode);
void parseLayerData(TiXmlNode *layerNode);

int main() {

	TiXmlDocument doc("C:\\Projects\\test.tmx");
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("Parsing %s:\n\n", "C:\\Projects\\test.tmx");

		TiXmlNode *mapNode = doc.FirstChild("map");
		TiXmlElement* mapElem = mapNode->ToElement();

		cout << "______MAP DATA______" << endl;
		cout << endl;

		cout << "Orientation=" << mapElem->Attribute("orientation") << endl;
		cout << "Width=" << mapElem->Attribute("width") << endl;
		cout << "Height=" << mapElem->Attribute("height") << endl;
		cout << "TileW=" << mapElem->Attribute("tilewidth") << endl;
		cout << "TileH=" << mapElem->Attribute("tileheight") << endl;

		parseTileset(mapNode);
		parseLayers(mapNode);
	}
	else
	{
		printf("Failed to load file \"%s\"\n", "C:\\Projects\\test.tmx");
	}

	cout << "_________________________________" << endl;
	cout << "FIN" << endl;
	_getch();
}

void parseTileset(TiXmlNode *mapNode) {
		TiXmlNode *tilesetNode = mapNode->FirstChild("tileset");
		TiXmlElement *tilesetElem = NULL;

		while (tilesetNode) {
			cout << endl;
			cout << "______TileSet - START______" << endl;
			cout << endl;

			tilesetElem = tilesetNode->ToElement();

			cout << "Name=" << tilesetElem->Attribute("name") << endl;
			cout << "FirstGID=" << tilesetElem->Attribute("firstgid") << endl;
			cout << "TileW=" << tilesetElem->Attribute("tilewidth") << endl;
			cout << "TileH=" << tilesetElem->Attribute("tileheight") << endl;

			parseTilesetImages(tilesetNode);

			cout << endl;
			cout << "______TileSet - END______" << endl;
			tilesetNode = mapNode->IterateChildren("tileset", tilesetNode);
		}

		cout << endl;
}

void parseTilesetImages(TiXmlNode *tilesetNode) {

	cout << endl;
	cout << "______Image______" << endl;
	cout << endl;

	TiXmlNode *imgNode = tilesetNode->FirstChild("image");
	TiXmlElement *imgElem = NULL;

	while (imgNode) {
		imgElem = imgNode->ToElement();

		cout << "Source=" << imgElem->Attribute("source") << endl;
		cout << "Width=" << imgElem->Attribute("width") << endl;
		cout << "Height=" << imgElem->Attribute("height") << endl;
		char *sTrans = (char *) imgElem->Attribute("trans");
		if (sTrans != NULL) {
			cout << "Trans=" << sTrans << endl;
		}

		imgNode = tilesetNode->IterateChildren("image", imgNode);
	}
}

void parseLayers(TiXmlNode *mapNode) {
	TiXmlNode *layerNode = mapNode->FirstChild("layer");
	TiXmlElement *layerElem = NULL;

	while (layerNode) {
		cout << endl;
		cout << "______Layer - START______" << endl;
		cout << endl;

		layerElem = layerNode->ToElement();

		cout << "Name=" << layerElem->Attribute("name") << endl;
		cout << "Width=" << layerElem->Attribute("width") << endl;
		cout << "Height=" << layerElem->Attribute("height") << endl;

		parseLayerData(layerNode);

		cout << endl;
		cout << "______Layer - END______" << endl;
		layerNode = mapNode->IterateChildren("layer", layerNode);
	}

	cout << endl;
}

void parseLayerData(TiXmlNode *layerNode) {

	TiXmlNode *dataNode = layerNode->FirstChild("data");
	TiXmlNode *tileNode = dataNode->FirstChild("tile");
	TiXmlElement *tileElem = NULL;

	cout << endl;
	cout << "______Tiles - START______" << endl;

	while (tileNode) {
		cout << endl;

		tileElem = tileNode->ToElement();

		cout << "gid[" << "]" << tileElem->Attribute("gid") << endl;

		tileNode = dataNode->IterateChildren("tile", tileNode);
	}

	cout << endl;
	cout << "______Tiles - END______" << endl;
	cout << endl;
}*/