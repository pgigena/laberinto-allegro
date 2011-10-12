#ifndef UTIL_H
#define UTIL_H

#include <map>
#include <iostream>
#include <string>

using namespace std;

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

typedef struct TileCoord
{
	int x;
	int y;

	bool operator < (const TileCoord& tc) const
    {
        if (x < tc.x && y < tc.y) {
			return true;
		}
		else {
			return false;
		}
    }

} TileCoord;

#endif // UTIL_H