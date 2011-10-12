#include <conio.h>

#include "Util.h"
#include "Tile.h"

// Main
// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	typedef std::map <int, CTile*> MapType;
    MapType *data;

	data = new MapType();

    // let's declare some initial values to this map
	for (int i = 0; i < 4; i++) {
		data->insert(MapType::value_type(i, new CTile(i)));
	}
    
    // Iterate over the map and print out all key/value pairs.
    // Using a const_iterator since we are not going to change the values.
    /*MapType::const_iterator end = data.end(); 
    for (MapType::const_iterator it = data.begin(); it != end; ++it) {
		std::cout << "Key: " << it->first;
		std::cout << " Value: " << it->second << '\n';
    }*/
 
	_getch();
    return 0;
}