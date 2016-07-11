#include <iostream>
#include <cstdio>

#include "Utilities.h"

#include "Agent.h"

#include "Environment.h"

#include "carlsim.h"

#include "Brain.h"

using namespace std;

int main() {

	int display_width = 1200;
	int display_height = 600;

	float FPS = 10;
	// declare allegro display pointer
	ALLEGRO_DISPLAY *display = NULL;

	if (!al_init()) {
		al_show_native_message_box(NULL, NULL, NULL,
				"failed to initialize allegro!", NULL, 0);
		return -1;
	}
	display = al_create_display(display_width, display_height);
	if (!(display)) {
		printf("failed to create display!\n");
		return -1;
	}

	// use image addon
	if (!al_init_image_addon()) {
		al_show_native_message_box(display, "Error", "Error",
				"Failed to initialize al_init_image_addon!",
				NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	// register keyboard to the queue
	// install keyboard
	al_install_keyboard();

	// init font
	al_init_font_addon();
	al_init_ttf_addon();

	// declare event queue
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	// declare timer
	ALLEGRO_TIMER *timer = NULL;

	// create event_queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//******************************************* CREATE ENVIRONMENT ********************************************
	int woffset = 200;
	int hoffset = 0;
	int envWidth = display_width - woffset; // leave room for monitoring
	int envHeight = display_height - hoffset;
	Environment* pEnv = new Environment(envWidth, envHeight, display_width,
			display_height);
	if (!pEnv) {
		printf("Error:main(): Environment Couldn't be Created\n");
		return -1;
	}

	Point obs1(0, 0);
	Point obs2(display_width / 2, display_height / 2);

	pEnv->setObstacle(obs1, 50, 50);
	pEnv->setObstacle(obs2, 50, 50);

	pEnv->setGrid();

	pEnv->draw();

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	//******************************************* CREATE AGENT **************************************************
	Point initPos(woffset + 50, hoffset + envHeight - 50);
	float initAngle = 0.0;
	int nSens = 5;
	ALLEGRO_BITMAP* img = al_load_bitmap("boe.png");

	if (!img) {
		printf("Error: main(): img could not be loaded\n");
		return -1;
	}

	Agent* pAgent = new Agent(initPos, initAngle, nSens, img);

	if (!pAgent) {
		printf("Error:main(): Agent Couldn't be Created\n");
		return -1;
	}
	pAgent->setEnv(pEnv);
	pAgent->draw();
	pAgent->setTrail(true);

	//******************************************* CREATE ALLEGRO EVENTS *****************************************

	float prob = 0.0;
	// to keep game loop running
	bool done = false;
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	//********************************************* GAME LOOP *******************************************
	while (!done) {
		ALLEGRO_EVENT ev;

		bool pos_update = false;

		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			pos_update = true;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				prob += 10;
				if (prob > 100)
					prob = 100;
				break;
			case ALLEGRO_KEY_DOWN:
				prob -= 10;
				if (prob < 0)
					prob = 0;
				break;
			case ALLEGRO_KEY_PAD_PLUS:
				if (FPS + 10 <= 60)
					FPS += 10;
				al_set_timer_speed(timer, 1.0 / FPS);
				break;
			case ALLEGRO_KEY_PAD_MINUS:
				if (FPS - 10 >= 10)
					FPS -= 10;
				al_set_timer_speed(timer, 1.0 / FPS);
				break;
			}
		}

		if (pos_update) {
			// Add Controller Here
			pEnv->draw();
			pAgent->updatePosition();
			//#include "controller_collisionCheck.h"

		}

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

	}

	// destroy all dynamically created objects

	if (pEnv)
		delete pEnv;
	if (pAgent)
		delete pAgent;
	if (img)
		al_destroy_bitmap(img);
	if (display)
		al_destroy_display(display);

}
