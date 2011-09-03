#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

using namespace std;

// Constantes varias
// ------------------------------------------------
const float FPS = 15;
const int SCREEN_W = 300;
const int SCREEN_H = 300;
const int BOUNCER_SIZE = 30;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

enum MOUSE_BUTTONS {
	BTN_LEFT, BTN_RIGHT, BTN_CENTER
};

// Mapa
const int MAPA [10][10] = {
	{1,1,1,1,1,0,1,1,1,1},
	{0,0,0,1,0,0,0,1,2,1},
	{0,1,0,0,0,1,0,0,0,1},
	{0,0,1,1,0,0,1,1,1,1},
	{1,0,0,1,1,0,0,0,0,0},
	{1,1,0,0,1,1,1,0,1,0},
	{0,1,1,0,1,1,0,0,1,1},
	{0,0,1,0,0,1,0,1,0,0},
	{1,0,1,1,0,1,0,1,1,0},
	{1,0,0,0,0,1,0,0,0,0}
};

// Declaración de variables
// ------------------------------------------------

// Flags de pintado y salida
bool redraw = true;
bool doexit = false;

// Estado de teclado y mouse
bool key[4] = { false, false, false, false };
bool mouse[3] = { false, false, false };


// Declaración de funciones
// ------------------------------------------------
void pintarMapa(ALLEGRO_DISPLAY *display);
void onKeyDown(ALLEGRO_KEYBOARD_EVENT ev);
void onKeyUp(ALLEGRO_KEYBOARD_EVENT ev);


// Main
// ------------------------------------------------
int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;

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

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	// Cargo bitmap del personaje
	char szPath[] = "char_test.png";
	bouncer = al_load_bitmap(szPath);
	/*bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);*/
	if(!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	//al_set_target_bitmap(bouncer);

	//al_clear_to_color(al_map_rgb(0, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	// Registra fuentes de eventos
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_clear_to_color(al_map_rgb(0,0,0));

	al_flip_display();

	al_start_timer(timer);

	//char szBufferCoordenada[5];
	char szMensaje[500] = "";

	int i=0;
	int a=0;
	int b=0;
	int pos_m = 0; //columnas
	int pos_n = 0; //filas

	for(i=0; (i < 10 && b==0); i++){
		std::cout << "\n";
		for(a=0; (a<10 && b==0); a++){
			std::cout << MAPA[i][a] << " ";
			if(MAPA[i][a] == 2){
				bouncer_x = ((a)*30);
				bouncer_y = ((i)*30);
				pos_m = a;
				pos_n = i;

				//b=1;
			}
		}
	}

	while(!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			pos_m = bouncer_x / 30;
			pos_n = bouncer_y / 30;

			if(key[KEY_UP] && pos_n-1 >= 0 && MAPA[pos_n-1][pos_m] != 1 && bouncer_y >= 30 ) {
				bouncer_y -= 30;
				pos_n = bouncer_y / 30;
			}

			if(key[KEY_DOWN] && pos_n+1 <= 10 && MAPA[pos_n+1][pos_m] != 1 && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 30 ) {
				bouncer_y += 30;
				pos_n = bouncer_y / 30;
			}

			if(key[KEY_LEFT] && pos_m-1 >= 0 && MAPA[pos_n][pos_m-1] != 1 && bouncer_x >= 30) {
				bouncer_x -= 30;
				pos_m = bouncer_x / 30;
			}

			if(key[KEY_RIGHT] && pos_m+1 <= 10 && MAPA[pos_n][pos_m+1] != 1 && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 30) {
				bouncer_x += 30;
				pos_m = bouncer_x / 30;
			}


			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			onKeyDown(ev.keyboard);
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			onKeyUp(ev.keyboard);
		}
		/*else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (ev.mouse.button == 1) {
		mouse[BTN_LEFT] = true;
		} else if (ev.mouse.button == 2) {
		mouse[BTN_RIGHT] = true;

		bouncer_x = (SCREEN_W / 2) - (BOUNCER_SIZE / 2);
		bouncer_y = (SCREEN_H / 2) - (BOUNCER_SIZE / 2);

		redraw = true;

		} 
		} else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if (ev.mouse.button == 1) {
		mouse[BTN_LEFT] = false;
		} else if (ev.mouse.button == 2) {
		mouse[BTN_RIGHT] = false;
		} else if (ev.mouse.button == 3) {
		mouse[BTN_CENTER] = false;
		}
		} else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES ||
		ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {

		if (mouse[BTN_LEFT]) {
		bouncer_x = ev.mouse.x - (BOUNCER_SIZE / 2);
		bouncer_y = ev.mouse.y - (BOUNCER_SIZE / 2);

		if (bouncer_x <= 0) {
		bouncer_x = 1;
		} else if (bouncer_x + BOUNCER_SIZE >= SCREEN_W) {
		bouncer_x = SCREEN_W - BOUNCER_SIZE;
		}

		if (bouncer_y <= 0) {
		bouncer_y = 1;
		} else if (bouncer_y + BOUNCER_SIZE >= SCREEN_H) {
		bouncer_y = SCREEN_H - BOUNCER_SIZE;
		}
		}
		}*/

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			pintarMapa(display);
			//al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
			al_flip_display();
		}
	}

	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}


// pintarMapa
// ------------------------------------------------
void pintarMapa(ALLEGRO_DISPLAY *display) {
	ALLEGRO_BITMAP *tile;
	int nTileX, nTileY;

	for(int i=0; i < 10 ; i++){
		for(int a=0; a < 10; a++){
			tile = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
			al_set_target_bitmap(tile);

			if (MAPA[i][a] == 1){
				al_clear_to_color(al_map_rgb(255, 0, 0));
			} else {
				al_clear_to_color(al_map_rgb(0, 255, 0));
			}

			al_set_target_bitmap(al_get_backbuffer(display));

			nTileX = a * 30;
			nTileY = i * 30;

			al_draw_bitmap(tile, nTileX, nTileY, 0);
			al_destroy_bitmap(tile);
		}
	}
}


// onKeyDown
// ------------------------------------------------
void onKeyDown(ALLEGRO_KEYBOARD_EVENT ev) {
	switch(ev.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = true;
			break;

		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = true;
			break;

		case ALLEGRO_KEY_LEFT: 
			key[KEY_LEFT] = true;
			break;

		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = true;
			break;
		}	
}


// onKeyUp
// ------------------------------------------------
void onKeyUp(ALLEGRO_KEYBOARD_EVENT ev) {
	switch(ev.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = false;
			break;

		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = false;
			break;

		case ALLEGRO_KEY_LEFT: 
			key[KEY_LEFT] = false;
			break;

		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = false;
			break;
		case ALLEGRO_KEY_P:
			system("PAUSE");
			break;
		case ALLEGRO_KEY_ENTER:
				
			/*std::cout << "pos x: "<< pos_m << " pos y: " << pos_n << " valor actual: "<< MAPA[pos_m][pos_n] <<endl
				<< "\tvalor del que esta arriba: " << MAPA[pos_n-1][pos_m]<< endl
				<< "\tvalor del que esta abajo: " << MAPA[pos_n+1][pos_m]<< endl
				<< "\tvalor del que esta derecha: " << MAPA[pos_n][pos_m+1]<< endl
				<< "\tvalor del que esta izquierda: " << MAPA[pos_n][pos_m-1]<< endl
			<<endl;*/
			/*strcat(szMensaje, "X=");
			_itoa(pos_m, szBufferCoordenada, 10);
			strcat(szMensaje, szBufferCoordenada);

			strcat(szMensaje, "|Y=");
			_itoa(pos_n, szBufferCoordenada, 10);
			strcat(szMensaje, szBufferCoordenada);
			strcat(szMensaje, "\n");

			printf(szMensaje);

			strcpy(szMensaje, "");*/
			break;
		case ALLEGRO_KEY_ESCAPE:
			doexit = true;
			break;
		}
}