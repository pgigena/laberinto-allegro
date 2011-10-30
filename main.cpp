#include <conio.h>
#include <vector>

#include "Util.h"
#include "Factory.h"

// Main
// ----------------------------------------------------------------------------
const float FPS = 1;
 
int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//ALLEGRO_BITMAP *bmpTilePalette = NULL;
	//string sTilePalettePath = "tilesetTest.png";
				
	bool bRedraw = true;
	bool bExit = false;

	/*for (int i = 1; i < argc; i ++) {
		cout << "arg[" << i << "]=" << argv[i] << endl;
	}
	return 0;*/

	CTileMap *tmMap = NULL;

	tmMap = CFactory::createTileMap();
	//tmMap->setTmxFile(new TiXmlDocument("test.tmx"));*/
	if (!argv[1]) {
		tmMap->setTmxFile(new TiXmlDocument("testa1.tmx"));
	} else {
		tmMap->setTmxFile(new TiXmlDocument(argv[1]));
	}

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}
 
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	// Addon para imágenes
	if(!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize the image addon!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	tmMap->initialize();

	int nScreenWidth =  tmMap->getWidth() * tmMap->getTileWidth();
	int nScreenHeight = tmMap->getHeight() * tmMap->getTileHeight();

	display = al_create_display(nScreenWidth, nScreenHeight);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	// Creo los objetos del juego
	//bmpTilePalette = al_load_bitmap(sTilePalettePath.c_str());
//	tmMap = CFactory::createTileMap(nMapWidth, nMapHeight, nTileWidth, nTileHeight);
	//tmMap->setSpritePalette(bmpTilePalette);
	
	/*TiXmlDocument *d = new TiXmlDocument("C:\\Projects\\test.tmx");
	d->LoadFile();*/

	/*tmMap->setTmxFile(new TiXmlDocument("test.tmx"));
	tmMap->initialize();*/

	al_set_target_bitmap(al_get_backbuffer(display));
 
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
 
	al_clear_to_color(al_map_rgb(0,0,0));
 	al_flip_display();

	al_start_timer(timer);
 
	while(!bExit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
 
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			bRedraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			bExit = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			bExit = true;
		} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_P:
					system("pause");
					break;
				case ALLEGRO_KEY_ESCAPE:
					bExit = true;
			}
		}
 
		if(bRedraw && al_is_event_queue_empty(event_queue)) {
			bRedraw = false;
 
			tmMap->paint(display);
			al_flip_display();
		}
	}
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	delete tmMap;

	return 0;
}