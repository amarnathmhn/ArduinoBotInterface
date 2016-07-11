/*
 * Obstacle.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "Utilities.h"

class Obstacle {
public:
	// top left corner location
	Point tlc;
	int width;
	int height;
	obstacle_shape_t shape;
	ALLEGRO_COLOR color;

	// reward upon colliding with this obstacle
	double reward;

	// Check if this obstacle encloses ( x , y)
	bool hasPoint(double x, double y);
	// get reward for this obstacle
	double getReward();

public:
	Obstacle();
	virtual ~Obstacle();
};

#endif /* OBSTACLE_H_ */
