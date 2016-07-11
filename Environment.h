/*
 * Environment.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include<list>
#include "Obstacle.h"

class Environment {

public:
	int width;
	int height;
	std::list<Obstacle> obstacles;

public:
	Environment(int width, int height);
	virtual ~Environment();

	void setObstacle(Point p, int w, int h);

	void draw();
};

#endif /* ENVIRONMENT_H_ */
