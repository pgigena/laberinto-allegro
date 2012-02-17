#ifndef UTIL_H
#define UTIL_H

#include <map>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>

#include "TinyXML\tinyxml.h"

enum Direction { UP = 1, DOWN = 2, LEFT = 4, RIGHT = 8 };

typedef struct TileCoord
{
	int x;
	int y;

	bool operator == (const TileCoord & tc) const
    {
        if (x == tc.x && y == tc.y) {
			return true;
		}

		return false;
		
    }
} TileCoord;


typedef struct Point
{
	int x;
	int y;
} Point;


typedef struct Rect
{
	int x;
	int y;
	int w;
	int h;
} Rect;


class TileCoordHash{

public:
    long operator()(const TileCoord &tc) const{
		string s = "";
		s += tc.x;
		s += tc.y;

		return atoi(s.c_str());
    }
};


// TMX Only
typedef pair<const char*, const char*> TmxProperty;
typedef map<TmxProperty::first_type, TmxProperty::second_type> TmxPropertyList;

#endif // UTIL_H