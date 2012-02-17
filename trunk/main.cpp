#include <conio.h>
	
#include "Util.h"
#include "Factory.h"
#include "Character.h"

// Constantes
const float FPS = 60;

// Variables
bool bKeys[] = { false, false, false, false };
bool bRedraw = true;
bool bExit = false;
ALLEGRO_BITMAP *bmp = NULL;

// Funciones
void onKeyDown(int nKeycode);
void onKeyUp(int nKeycode);

void checkCollisions();

CCharacter *player = new CCharacter();
CCharacter *enemy = NULL;

short nMoveDirection = 0;

// Main
// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_TIMER *fpsTimer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_BITMAP *bmpFPSCount = NULL;
	char szFPSText[15];

	player = new CCharacter();
	enemy = new CCharacter();

	int nFrames = 0;

	CTileMap *tmMap = NULL;

	tmMap = CFactory::createTileMap();

	if (!argv[1]) {
		tmMap->setTmxFile(new TiXmlDocument("untitled.tmx"));
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

	al_init_font_addon();

	if (!al_init_ttf_addon()) {
		fprintf(stderr, "failed to initialize the ttf addon!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	fpsTimer = al_create_timer(1.0);

	if(!timer || !fpsTimer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	tmMap->parseTmx();

	int nScreenWidth =  tmMap->getWidth() * tmMap->getTileWidth();
	int nScreenHeight = tmMap->getHeight() * tmMap->getTileHeight();

	display = al_create_display(nScreenWidth, nScreenHeight);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	al_set_target_backbuffer(display);
	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);

	tmMap->loadResources();

	font = al_load_ttf_font("arial.ttf", 10,0 );

	if (!font) {
		fprintf(stderr, "failed to create the font!\n");
		return -1;
	}

	bmpFPSCount = al_create_bitmap(45, 10);
	al_set_target_bitmap(bmpFPSCount);
	al_clear_to_color(al_map_rgb(0,0,0));
	al_set_target_bitmap(al_get_backbuffer(display));
	player->setPalette(al_load_bitmap("rect1.png"));
	player->setContainer(0, 0, 20, 30);
	enemy->setPalette(al_load_bitmap("rect2.png"));
	enemy->setContainer(50, 50, 20, 30);
	
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(fpsTimer));
 	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
 
	al_clear_to_color(al_map_rgb(0,0,0));
 	al_flip_display();

	al_start_timer(timer);
	al_start_timer(fpsTimer);

	while(!bExit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
 
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if (ev.timer.source == fpsTimer) {
				sprintf(szFPSText, "FPS: %i", nFrames);

				nFrames = 0;
				bRedraw = true;
			}

			if (ev.timer.source == timer) {
				bRedraw = true;
			}
		} else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			bExit = true;
		} else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			bExit = true;
		} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			onKeyDown(ev.keyboard.keycode);
		} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			onKeyUp(ev.keyboard.keycode);
		}
 
		if(bRedraw && al_is_event_queue_empty(event_queue)) {
			bRedraw = false;

			player->move(nMoveDirection);
			// Check collisions
			checkCollisions();

			// Draw everything
			tmMap->paint(display);
			enemy->draw(display);
			player->draw(display);
			al_draw_bitmap(bmpFPSCount, 2, 2, 0);
			al_draw_text(font, al_map_rgb(255, 0, 255), 2, 1, 0, szFPSText);
			al_flip_display();
			nFrames++;
		}
	}
 
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	delete tmMap;

	return 0;
}

void onKeyDown(int nKeycode) {
	switch (nKeycode)
	{
		case ALLEGRO_KEY_UP:
			bKeys[UP] = true;
			nMoveDirection |= UP;
			break;
		case ALLEGRO_KEY_DOWN:
			bKeys[DOWN] = true;
			nMoveDirection |= DOWN;
			break;
		case ALLEGRO_KEY_LEFT:
			bKeys[LEFT] = true;
			nMoveDirection |= LEFT;
			break;
		case ALLEGRO_KEY_RIGHT:
			bKeys[RIGHT] = true;
			nMoveDirection |= RIGHT;
			break;
	}
}

void onKeyUp(int nKeycode) {
	switch (nKeycode)
	{
		case ALLEGRO_KEY_P:
			system("pause");
			break;
		case ALLEGRO_KEY_ESCAPE:
			bExit = true;
			break;
		case ALLEGRO_KEY_UP:
			bKeys[UP] = false;
			nMoveDirection ^= UP;
			break;
		case ALLEGRO_KEY_DOWN:
			bKeys[DOWN] = false;
			nMoveDirection ^= DOWN;
			break;
		case ALLEGRO_KEY_LEFT:
			bKeys[LEFT] = false;
			nMoveDirection ^= LEFT;
			break;
		case ALLEGRO_KEY_RIGHT:
			bKeys[RIGHT] = false;
			nMoveDirection ^= RIGHT;
			break;
	}
}

void checkCollisions()
{
	if (player->checkCollision(enemy)) {
		cout << "Colisiona!" << endl;
	} else {
		cout << "No colisiona!" << endl;
	}
}