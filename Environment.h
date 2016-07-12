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
	int dispWidth;
	int dispHeight;
	int slotSize;
	int withGrid;
	std::list<Obstacle> obstacles;

public:
	Environment(int width, int height, int dispWidth, int dispHeight);
	virtual ~Environment();

	void setObstacle(Point p, int w, int h);

	void draw();

	// return actual location of a grid location
	// 0,0 is bottom left, 0,1 is upwards, 1,0 is rightwards
	Point getGridSlotCenter( int x, int y);

	void setGrid(bool enable=true, int slotSize=100);

	void drawGrid(bool showCenter=false);
	// returns the grid center in grid co-ordinates for a point
	// belonging to that slot
	Point getContainingSlotCenter(Point P);

	bool hasGrid();
};

#endif /* ENVIRONMENT_H_ */
