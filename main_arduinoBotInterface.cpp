#include <iostream>
#include <cstdio>

#include "Utilities.h"

#include "Agent.h"

#include "Environment.h"

using namespace std;

int main() {
	int display_width = 800;
	int display_height = 600;

	// Frame per second to update display
	int FPS = 60;

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

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	//******************************************* CREATE ENVIRONMENT ********************************************
	Environment* pEnv = new Environment(display_width, display_height);

	Point obs1(0, 0);
	Point obs2(display_width / 2, display_height / 2);

	pEnv->setObstacle(obs1, 50, 50);
	pEnv->setObstacle(obs2, 50, 50);

	pEnv->draw();

	//******************************************* CREATE AGENT **************************************************
	Point initPos(50, display_height-50);
	float initAngle = 0.0;
	int nSens = 5;
	ALLEGRO_BITMAP* img = al_load_bitmap("boe.png");
	if(!img){
		printf("Error: main(): img could not be loaded\n");
		return -1;
	}

	Agent* pAgent = new Agent(initPos, initAngle, nSens, img);
	pAgent->draw();





	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_rest(3.0);

	cout << "hello world" << endl;

	if(pEnv) delete pEnv;
	if(pAgent)delete pAgent;
	if(img) al_destroy_bitmap(img);
	if(display) al_destroy_display(display);

}
