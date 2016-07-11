/*
 * Obstacles.cpp
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#include "Obstacle.h"

Obstacle::Obstacle() {
	// TODO Auto-generated constructor stub
	tlc.x = 0;
	tlc.y = 0;
	width = 0;
	height = 0;
	color = al_map_rgb(0, 0, 0); // black color
	this->shape = RECTANGLE;
	this->reward = 1.0;
}

Obstacle::~Obstacle(){

}
bool Obstacle::hasPoint(double x, double y) {
	if (tlc.x <= x && tlc.y <= y
			&& tlc.x + width >= x
			&& tlc.y + height >= y) {
		return true;
	} else
		return false;
}

double Obstacle::getReward() {
	return reward;
}

