#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

using namespace std;

// Constantes varias
// ----------------------------------------------------------------------------
const float FPS = 60;
const int SCREEN_W = 300;
const int SCREEN_H = 300;
const int TILE_SIZE = 30;
const int CHAR_STEP = 3;	
const char CHAR_PALETTE[] = "dante_palette.png";//"chars_palette.png";
const char TILESET_PALETTE[] = "tilesetTest.png";

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

enum MOUSE_BUTTONS {
	BTN_LEFT, BTN_RIGHT, BTN_CENTER
};

enum DIRECTIONS {
	DIR_NONE, DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT
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
// ----------------------------------------------------------------------------

// Flags de pintado y salida
bool redraw = true;
bool doexit = false;

// Estado de teclado y mouse
bool key[4] = { false, false, false, false };
bool mouse[3] = { false, false, false };

// Display de la aplicación
ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_BITMAP *bmpTileset = NULL;

// Posición del personaje (En tiles)
int posTileX = 0;
int posTileY = 0;
int posNextTileX = 0;
int posNextTileY = 0;
int posX = 0;
int posY = 0;

bool bIsAdvancing;
DIRECTIONS charMoveDirection = DIR_NONE;
DIRECTIONS charFaceDirection = DIR_DOWN;

// Personaje
ALLEGRO_BITMAP *bmpChar = NULL;
// Paleta de personajes
ALLEGRO_BITMAP *bmpChars = NULL;
// Código del personaje activo
int nActiveSpriteX = 0;
int nActiveSpriteY = 0;

// Declaración de funciones
// ----------------------------------------------------------------------------
void pintarMapa(ALLEGRO_DISPLAY *display);
void moverPersonajePredictivo();
void moverPersonajeCorrectivo();
void onKeyDown(ALLEGRO_KEYBOARD_EVENT ev);
void onKeyUp(ALLEGRO_KEYBOARD_EVENT ev);
void animateCharacter();
void setCharSprite();

// Main
// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
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
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	bmpChars = al_load_bitmap(CHAR_PALETTE);

	bmpTileset = al_load_bitmap(TILESET_PALETTE);
	// Creo el bitmap del personaje
	/*bmpChar = al_create_bitmap(TILE_SIZE, TILE_SIZE);
	if(!bmpChar) {
		fprintf(stderr, "failed to create bmpChar bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_target_bitmap(bmpChar);
	al_clear_to_color(al_map_rgba(255, 255, 255, 0));
	al_draw_bitmap_region(bmpChars, (30 * nActiveSprite), 0, TILE_SIZE, TILE_SIZE, 0, 0, 0);

	al_set_target_bitmap(al_get_backbuffer(display));*/
	setCharSprite();

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(bmpChar);
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
		std::cout << endl;
		for(a=0; (a<10 && b==0); a++){
			std::cout << MAPA[i][a] << " ";
			if(MAPA[i][a] == 2){
				posX = a * 30;
				posY = i * 30;

				posTileX = a;
				posTileY = i;
				//b=1;
			}
		}
	}

	std::cout << endl;

	while(!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if (bIsAdvancing) {
				animateCharacter();
			}
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
			al_draw_bitmap(bmpChar, posX/*(posTileX * 30)*/, posY/*(posTileY * 30)*/, 0);
			al_flip_display();
		}
	}

	al_destroy_bitmap(bmpChar);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}


// pintarMapa
// ----------------------------------------------------------------------------
void pintarMapa(ALLEGRO_DISPLAY *display) {
	ALLEGRO_BITMAP *tile;
	int nTileX, nTileY;

	for(int i=0; i < 10 ; i++){
		for(int a=0; a < 10; a++){
			tile = al_create_bitmap(TILE_SIZE, TILE_SIZE);
			al_set_target_bitmap(tile);

			if (MAPA[i][a] == 1){
				//al_draw_bitmap(bmpTileset, posX/*(posTileX * 30)*/, posY/*(posTileY * 30)*/, 0);
				al_draw_bitmap_region(bmpTileset, 30, 0, TILE_SIZE, TILE_SIZE, 0, 0, 0);
				//al_clear_to_color(al_map_rgb(255, 0, 0));
			} else {
				al_draw_bitmap_region(bmpTileset, 0, 0, TILE_SIZE, TILE_SIZE, 0, 0, 0);
				//al_clear_to_color(al_map_rgb(0, 255, 0));
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
// ----------------------------------------------------------------------------
void moverPersonajePredictivo() {

	if(key[KEY_UP] && posTileY - 1 >= 0 && MAPA[posTileY-1][posTileX] != 1) {
		posTileY--;
	}

	if(key[KEY_DOWN] && posTileY + 1 < MAP_H && MAPA[posTileY+1][posTileX] != 1) {
		posTileY++;
	}

	if(key[KEY_LEFT] && posTileX - 1 >= 0 && MAPA[posTileY][posTileX-1] != 1) {
		posTileX--;
	}

	if(key[KEY_RIGHT] && posTileX + 1 < MAP_W && MAPA[posTileY][posTileX+1] != 1) {
		posTileX++;
	}


	redraw = true;
}

// moverPersonajeCorrectivo
// ----------------------------------------------------------------------------
void moverPersonajeCorrectivo() {
	int nXPreliminar = posTileX;
	int nYPreliminar = posTileY;
	bool bMoved = false;

	if (charMoveDirection != DIR_NONE) {
		return;
	}

	if (key[KEY_UP] && posTileY - 1 >= 0) {
		nYPreliminar = posTileY - 1;
		charMoveDirection = DIR_UP;
		bMoved = true;
	} else if (key[KEY_DOWN] && posTileY + 1 < MAP_H) {
		nYPreliminar = posTileY + 1;
		charMoveDirection = DIR_DOWN;
		bMoved = true;
	} else if (key[KEY_LEFT]  && posTileX - 1 >= 0) {
		nXPreliminar = posTileX - 1;
		charMoveDirection = DIR_LEFT;
		bMoved = true;
	} else if (key[KEY_RIGHT] && posTileX + 1 < MAP_W) {
		nXPreliminar = posTileX + 1;
		charMoveDirection = DIR_RIGHT;
		bMoved = true;
	}

	if (bMoved) {
		int nPosPreliminar = MAPA[nYPreliminar][nXPreliminar];
		/*
		std::cout << "_____________________" << endl;
		std::cout << "ACTUAL X: " << posTileX << endl;
		std::cout << "ACTUAL Y: " << posTileY << endl;
		std::cout << "TILE ACTUAL: " << MAPA[posTileX][posTileY] << endl;
		std::cout << "PRELIMINAR X: " << nXPreliminar << endl;
		std::cout << "PRELIMINAR Y: " << nYPreliminar << endl;
		std::cout << "TILE PRELIMINAR: " << nPosPreliminar << endl;
		*/

		if (nPosPreliminar != 1) {
			posNextTileX = nXPreliminar;
			posNextTileY = nYPreliminar;
		
			bIsAdvancing = true;
			setCharSprite();
			//redraw = true;
		} else {
			charMoveDirection = DIR_NONE;
		}
	}
}

// animateCharacter
// ----------------------------------------------------------------------------
void animateCharacter() {
	cout << "______________________" << endl;
	cout << "posX: " << posX << " | tileX: " << posTileX << endl;
	cout << "posY: " << posY << " | tileY: " << posTileY << endl;

	double charTilePosX = posX / 30;
	double charTilePosY = posY / 30;

	if (charTilePosX == posNextTileX && charTilePosY == posNextTileY
		&& posX % 30 == 0 && posY % 30 == 0) {
		posTileX = posNextTileX;
		posTileY = posNextTileY;
		bIsAdvancing = false;
		charMoveDirection = DIR_NONE;
		return;
	}

	switch (charMoveDirection) {
		case DIR_UP:
			posY -= CHAR_STEP;
			break;
		case DIR_DOWN:
			posY += CHAR_STEP;
			break;
		case DIR_LEFT:
			posX -= CHAR_STEP;
			break;
		case DIR_RIGHT:
			posX += CHAR_STEP;
			break;
	}

	/*if (charMoveDirection == DIR_UP) {
		posY -= CHAR_STEP;
	} else if (charMoveDirection == DIR_DOWN) {
		posY += CHAR_STEP;
	} else if (charMoveDirection == DIR_LEFT) {
		posX -= CHAR_STEP;
	}else if (charMoveDirection == DIR_RIGHT) {
		posX += CHAR_STEP;
	}*/

	redraw = true;
}

// setCharSprite
// ----------------------------------------------------------------------------
void setCharSprite() {
		switch (charFaceDirection)
		{
			case DIR_UP:
				nActiveSpriteX = 3;
				nActiveSpriteY = 0;
				break;
			case DIR_DOWN:
				nActiveSpriteX = 0;
				nActiveSpriteY = 0;
				break;
			case DIR_LEFT:
				nActiveSpriteX = 0;
				nActiveSpriteY = 1;
				break;
			case DIR_RIGHT:
				nActiveSpriteX = 3;
				nActiveSpriteY = 1;
				break;
		}

		if (bmpChar) {
			al_destroy_bitmap(bmpChar);
		}

		bmpChar = al_create_bitmap(TILE_SIZE, TILE_SIZE);

		if(!bmpChar) {
			fprintf(stderr, "failed to create bmpChar bitmap!\n");
			al_destroy_display(display);
			//al_destroy_timer(timer);
			return; //-1;
		}
		al_set_target_bitmap(bmpChar);
		al_clear_to_color(al_map_rgba(255, 255, 255, 0));
		al_draw_bitmap_region(bmpChars, (30 * nActiveSpriteX), (30 * nActiveSpriteY), TILE_SIZE, TILE_SIZE, 0, 0, 0);

		al_set_target_bitmap(al_get_backbuffer(display));
		redraw = true;
}

// onKeyDown
// ----------------------------------------------------------------------------
void onKeyDown(ALLEGRO_KEYBOARD_EVENT ev) {
	switch(ev.keycode) {
		case ALLEGRO_KEY_UP:
			key[KEY_UP] = true;
			charFaceDirection = DIR_UP;
			if (!bIsAdvancing) {
				setCharSprite();
			}
			break;

		case ALLEGRO_KEY_DOWN:
			key[KEY_DOWN] = true;
			charFaceDirection = DIR_DOWN;
			if (!bIsAdvancing) {
				setCharSprite();
			}
			break;

		case ALLEGRO_KEY_LEFT: 
			key[KEY_LEFT] = true;
			charFaceDirection = DIR_LEFT;
			if (!bIsAdvancing) {
				setCharSprite();
			}
			break;

		case ALLEGRO_KEY_RIGHT:
			key[KEY_RIGHT] = true;
			charFaceDirection = DIR_RIGHT;
			if (!bIsAdvancing) {
				setCharSprite();
			}
			break;
		}

}


// onKeyUp
// ----------------------------------------------------------------------------
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
				
			/*std::cout << "pos x: "<< posTileX << " pos y: " << posTileY << " valor actual: "<< MAPA[posTileX][posTileY] <<endl
				<< "\tvalor del que esta arriba: " << MAPA[posTileY-1][posTileX]<< endl
				<< "\tvalor del que esta abajo: " << MAPA[posTileY+1][posTileX]<< endl
				<< "\tvalor del que esta derecha: " << MAPA[posTileY][posTileX+1]<< endl
				<< "\tvalor del que esta izquierda: " << MAPA[posTileY][posTileX-1]<< endl
			<<endl;*/
			/*strcat(szMensaje, "X=");
			_itoa(posTileX, szBufferCoordenada, 10);
			strcat(szMensaje, szBufferCoordenada);

			strcat(szMensaje, "|Y=");
			_itoa(posTileY, szBufferCoordenada, 10);
			strcat(szMensaje, szBufferCoordenada);
			strcat(szMensaje, "\n");

			printf(szMensaje);

			strcpy(szMensaje, "");*/
			break;
		/*case ALLEGRO_KEY_SPACE:
			if (nActiveChar < 3) {
				nActiveChar++;
			} else {
				nActiveChar = 0;
			}
			al_destroy_bitmap(bmpChar);
			bmpChar = al_create_bitmap(TILE_SIZE, TILE_SIZE);
			al_set_target_bitmap(bmpChar);
			al_clear_to_color(al_map_rgba(255, 255, 255, 0));
			al_draw_bitmap_region(bmpChars, (30 * nActiveChar), 0, TILE_SIZE, TILE_SIZE, 0, 0, 0);

			redraw = true;

			break;*/
		case ALLEGRO_KEY_ESCAPE:
			doexit = true;
			break;
		}
}