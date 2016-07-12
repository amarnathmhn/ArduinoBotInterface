/*
 * utilities.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include<math.h>
#include<cstdlib>
#include <cstdio>
enum MotorRotationType {
	FORWARD, BACKWARD, NONE
};

#define MOVEFORWARD 0;
#define TURNLEFT    1;
#define TURNRIGHT   2;

enum obstacle_shape_t {
	RECTANGLE, CIRCLE
};
#define USLEFT  = 0;
#define USLEFT45 = 1;
#define USFRONT = 2;
#define USRIGHT45 = 3;
#define USRIGHT = 4;

class Point {
public:
	float x;
	float y;

public:
	Point() {
		this->x = 0.0;
		this->y = 0.0;

	}

	Point(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void set(float x, float y) {

		this->x = x;
		this->y = y;
	}
	void copy(Point& P){
		this->x = P.x;
		this->y = P.y;
	}
	float getSquareDist(Point P){
		return (x - P.x)*(x - P.x) + (y - P.y)*(y - P.y);
	}
	void print(){
		printf("( %f, %f )\n", x, y);
	}

};


#endif /* UTILITIES_H_ */
