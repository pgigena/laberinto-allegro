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
const int MAP_W = 10;
const int MAP_H = 10;

const int MAPA [MAP_W][MAP_H] = {
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

// Posición del personaje (En tiles)
int posTilesX = 0;
int posTilesY = 0;

// Personaje
ALLEGRO_BITMAP *bouncer = NULL;
// Paleta de personajes
ALLEGRO_BITMAP *bmpChars = NULL;
// Código del personaje activo
int nActiveChar = 1;

// Declaración de funciones
// ------------------------------------------------
void pintarMapa(ALLEGRO_DISPLAY *display);
void moverPersonajePredictivo();
void moverPersonajeCorrectivo();
void onKeyDown(ALLEGRO_KEYBOARD_EVENT ev);
void onKeyUp(ALLEGRO_KEYBOARD_EVENT ev);


// Main
// ------------------------------------------------
int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

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

	// Seteo el blender para que funcionen las transparencias
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	// Cargo bitmap de la paleta de personajes
	char szPath[] = "chars_palette.png";
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	bmpChars = al_load_bitmap(szPath);

	// Creo el bitmap del personaje
	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	if(!bouncer) {
		fprintf(stderr, "failed to create bouncer bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgba(255, 255, 255, 0));
	al_draw_bitmap_region(bmpChars, (30 * nActiveChar), 0, BOUNCER_SIZE, BOUNCER_SIZE, 0, 0, 0);

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

	for(i=0; (i < 10 && b==0); i++){
		std::cout << "\n";
		for(a=0; (a<10 && b==0); a++){
			std::cout << MAPA[i][a] << " ";
			if(MAPA[i][a] == 2){
				posTilesX = a;
				posTilesY = i;
				//b=1;
			}
		}
	}

	while(!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			//moverPersonajePredictivo();
			moverPersonajeCorrectivo();
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

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			pintarMapa(display);
			al_draw_bitmap(bouncer, (posTilesX * 30), (posTilesY * 30), 0);
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

// moverPersonajePredictivo
// ------------------------------------------------
void moverPersonajePredictivo() {

	if(key[KEY_UP] && posTilesY - 1 >= 0 && MAPA[posTilesY-1][posTilesX] != 1) {
		posTilesY--;
	}

	if(key[KEY_DOWN] && posTilesY + 1 < MAP_H && MAPA[posTilesY+1][posTilesX] != 1) {
		posTilesY++;
	}

	if(key[KEY_LEFT] && posTilesX - 1 >= 0 && MAPA[posTilesY][posTilesX-1] != 1) {
		posTilesX--;
	}

	if(key[KEY_RIGHT] && posTilesX + 1 < MAP_W && MAPA[posTilesY][posTilesX+1] != 1) {
		posTilesX++;
	}


	redraw = true;
}

// moverPersonajeCorrectivo
// ------------------------------------------------
void moverPersonajeCorrectivo() {
	int nXPreliminar = posTilesX;
	int nYPreliminar = posTilesY;
	bool bMoved = false;

	if (key[KEY_UP] && posTilesY - 1 >= 0) {
		nYPreliminar = posTilesY - 1;
		bMoved = true;
	}

	if (key[KEY_DOWN] && posTilesY + 1 < MAP_H) {
		nYPreliminar = posTilesY + 1;
		bMoved = true;
	}

	if (key[KEY_LEFT]  && posTilesX - 1 >= 0) {
		nXPreliminar = posTilesX - 1;
		bMoved = true;
	}

	if (key[KEY_RIGHT] && posTilesX + 1 < MAP_W) {
		nXPreliminar = posTilesX + 1;
		bMoved = true;
	}

	if (bMoved) {
		int nPosPreliminar = MAPA[nYPreliminar][nXPreliminar];
		/*
		std::cout << "_____________________" << endl;
		std::cout << "ACTUAL X: " << posTilesX << endl;
		std::cout << "ACTUAL Y: " << posTilesY << endl;
		std::cout << "TILE ACTUAL: " << MAPA[posTilesX][posTilesY] << endl;
		std::cout << "PRELIMINAR X: " << nXPreliminar << endl;
		std::cout << "PRELIMINAR Y: " << nYPreliminar << endl;
		std::cout << "TILE PRELIMINAR: " << nPosPreliminar << endl;
		*/

		if (nPosPreliminar != 1) {
			posTilesX = nXPreliminar;
			posTilesY = nYPreliminar;

			redraw = true;
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
				
			/*std::cout << "pos x: "<< posTilesX << " pos y: " << posTilesY << " valor actual: "<< MAPA[posTilesX][posTilesY] <<endl
				<< "\tvalor del que esta arriba: " << MAPA[posTilesY-1][posTilesX]<< endl
				<< "\tvalor del que esta abajo: " << MAPA[posTilesY+1][posTilesX]<< endl
				<< "\tvalor del que esta derecha: " << MAPA[posTilesY][posTilesX+1]<< endl
				<< "\tvalor del que esta izquierda: " << MAPA[posTilesY][posTilesX-1]<< endl
			<<endl;*/
			/*strcat(szMensaje, "X=");
			_itoa(posTilesX, szBufferCoordenada, 10);
			strcat(szMensaje, szBufferCoordenada);

			strcat(szMensaje, "|Y=");
			_itoa(posTilesY, szBufferCoordenada, 10);
			strcat(szMensaje, szBufferCoordenada);
			strcat(szMensaje, "\n");

			printf(szMensaje);

			strcpy(szMensaje, "");*/
			break;
		case ALLEGRO_KEY_SPACE:
			if (nActiveChar < 3) {
				nActiveChar++;
			} else {
				nActiveChar = 0;
			}
			al_destroy_bitmap(bouncer);
			bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
			al_set_target_bitmap(bouncer);
			al_clear_to_color(al_map_rgba(255, 255, 255, 0));
			al_draw_bitmap_region(bmpChars, (30 * nActiveChar), 0, BOUNCER_SIZE, BOUNCER_SIZE, 0, 0, 0);

			redraw = true;

			break;
		case ALLEGRO_KEY_ESCAPE:
			doexit = true;
			break;
		}
}