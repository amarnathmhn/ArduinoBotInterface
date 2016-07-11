/*
 * UltrasonicSensor.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor() {
	// TODO Auto-generated constructor stub
	this->range = 200; // pixels in simulation
	this->index = 0;
	this->val = 0;
}

UltrasonicSensor::UltrasonicSensor(int idx) {
	// TODO Auto-generated constructor stub
	this->range = 200; // pixels in simulation
	this->index = idx;
	this->val = 0;
}

UltrasonicSensor::~UltrasonicSensor() {
	// TODO Auto-generated destructor stub
}

void UltrasonicSensor::setRange(float rg) {
	this->range = rg;
}

void UltrasonicSensor::setIndex(int idx) {
	this->index = idx;
}

void UltrasonicSensor::setDSens(float dSens) {
	this->dSens = dSens;
}
float UltrasonicSensor::getRange() {
	return this->range;
}

int UltrasonicSensor::getIndex() {
	return this->index;
}

void UltrasonicSensor::calcDistance() {
	// write NewPing Code for Arduino
}

void UltrasonicSensor::calcDistance(Environment* pEnv, Point position, float angle) {
	// write range sensing code for allegro environment
	bool brkObsLoop = false;
	double dl = 0.0;
	double maxDiag = sqrt(pEnv->width * pEnv->width + pEnv->height*pEnv->height);
	// Check the sensor distance for each obstacle
	for (dl = 0.0; dl < maxDiag; dl += 1) {

		// find a point in the path of ultrasonic ray
		double x = position.x + dl * sin(angle + index * dSens);
		double y = position.y - dl * cos(angle + index * dSens);

		std::list<Obstacle>::iterator itr = pEnv->obstacles.begin();

		while ( itr != pEnv->obstacles.end()) {

			if (itr->hasPoint(x, y)) {
				al_draw_line(/*float x1*/position.x, /*float y1*/position.y,
				/*float x2*/x, /*float y2*/y,
				/*ALLEGRO_COLOR color*/al_map_rgb(255, 0, 0),
				/*float thickness*/0);

				brkObsLoop = true;
				break;

			}

			itr++;

		}

		if (brkObsLoop)
			break;
		else {
			if (x <= (pEnv->dispWidth - pEnv->width) || x >= pEnv->width || y <= (pEnv->dispHeight - pEnv->height) || y >= pEnv->height) {
				al_draw_line(/*float x1*/position.x, /*float y1*/position.y,
				/*float x2*/x, /*float y2*/y,
				/*ALLEGRO_COLOR color*/al_map_rgb(255, 0, 0),
				/*float thickness*/0);

				brkObsLoop = true;
				break;
			}
		}
	}

	val = dl;
}

float UltrasonicSensor::getDistance() {
	return this->val;
}

