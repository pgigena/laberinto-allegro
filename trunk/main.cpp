#include <conio.h>

#include "Util.h"
#include "Factory.h"

// Main
// ----------------------------------------------------------------------------
const float FPS = 1;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
 
int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bmpMesh = NULL;
	ALLEGRO_COLOR color;
	int nColor = 0;
	int tileW = 15;
	int tileH = 15;

	CTileMap *tmMap = CFactory::CreateTileMap(10, 10, tileW, tileH);

	bool redraw = true;
 
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
 
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}
 
	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}
 
	al_set_target_bitmap(al_get_backbuffer(display));
 
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
 
	color = al_map_rgb(0, 0, 255);

	al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_mouse_event_source());
 
	al_clear_to_color(al_map_rgb(0,0,0));
 	al_flip_display();

	al_start_timer(timer);
 
	while(true)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
 
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			/*if (ev.mouse.button == 1) {
				system("pause");
			}
			else {
				break;
			}*/
			break;
		}
 
		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
 
			//al_clear_to_color(al_map_rgb(0,0,0));
			tmMap->paintMap(display);
			al_flip_display();
		}
	}
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}