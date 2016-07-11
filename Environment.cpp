/*
 * Environment.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "Environment.h"
#include <cstdio>
Environment::Environment(int w, int h) {
	// TODO Auto-generated constructor stub
	this->width = w;
	this->height = h;
}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}

void Environment::setObstacle(Point p, int w, int h){
	Obstacle obs;
	obs.tlc.set(p.x, p.y);
 	obs.width = w;
	obs.height = h;

	obstacles.push_back(obs);

}
void Environment::draw(){

	// Check if Allegro Env is Initialized
	if( !al_init() ){
		printf("Error: Environment::draw() : Allegro Environment Not Initialized Yet\n");
		return ;
	}

	// Draw if Allegro Display exists
	std::list<Obstacle>::iterator itr = obstacles.begin();
	while(itr != obstacles.end()){
		//printf("obstacle draw called\n");
		al_draw_filled_rectangle(itr->tlc.x, itr->tlc.y, itr->tlc.x + itr->width, itr->tlc.y + itr->height, al_map_rgb(255, 255, 255));
		itr++;
	}



}

