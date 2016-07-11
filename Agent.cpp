/*
 * Agent.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "Agent.h"
#include <cstdio>

Agent::Agent(Point iP, float iA, int nsens, ALLEGRO_BITMAP* image) {
	// TODO Auto-generated constructor stub
	this->initialAngle = iA;

	this->currentAngle = iA;

	this->initialPosition.set(iP.x, iP.y);

	this->initialGridPosition.set(0.0, 0.0);

	this->currentPosition.set(iP.x, iP.y);

	this->currentGridPosition.set(0.0, 0.0);

	this->image = image;

	this->width = al_get_bitmap_width(image);

	this->height = al_get_bitmap_height(image);

	this->numOfSensors = nsens;

	this->US = new UltrasonicSensor[nsens];

	this->dSens = ALLEGRO_PI / (nsens - 1);

	// initialize sensors
	for (int i = 0; i < nsens; i++) {

		US[i].setIndex(i - nsens / 2);
		US[i].setDSens(dSens);
	}

}

Agent::Agent(Point iP, float iA, int nsens, float width, float height) {
	// TODO Auto-generated constructor stub
	this->initialAngle = iA;

	this->currentAngle = iA;

	this->initialPosition.set(iP.x, iP.y);

	this->initialGridPosition.set(0.0, 0.0);

	this->currentPosition.set(iP.x, iP.y);

	this->currentGridPosition.set(0.0, 0.0);

	this->image = image;

	this->width = width;

	this->height = height;

	this->numOfSensors = nsens;

	this->US = new UltrasonicSensor [nsens];

	this->dSens = 3.14 / (nsens - 1);

	// initialize sensors
	for (int i = 0; i < nsens; i++) {

		US[i].setIndex(i - nsens / 2);
		US[i].setDSens(dSens);
	}

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
	delete[] US;
}

void Agent::draw(){
	if(image){
		al_draw_rotated_bitmap(image, width / 2, height / 2,
			/*float dx*/currentPosition.x, /*float dy*/currentPosition.y,
			/*float radian angle*/currentAngle,
			/*int flags*/0);
	}
}
