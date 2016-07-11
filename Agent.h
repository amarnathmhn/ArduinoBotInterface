/*
 * Agent.h
 *
 *  Created on: Jul 10, 2016
 *      Author: amarnath
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "UltrasonicSensor.h"
#include "Motor.h"
#include "Environment.h"

class Agent {

private:
	// Angle w.r.t the vertical
	float initialAngle;
	float currentAngle;
	Point initialPosition;
	Point initialGridPosition;
	Point currentPosition;
	Point currentGridPosition;
	float width;
	float height;
	int numOfSensors;
	float dSens;          // Angle between sensors
	UltrasonicSensor* US;
	ALLEGRO_BITMAP* image;
	Motor ML;  // left motor
	Motor MR;  // right motor
	Wheel WL;  // left wheel
	Wheel WR;  // right wheel
	Environment* pEnv;  // pointer to environment
	bool withTrail;
	std::list<Point> trail;
public:

	Agent(Point iP, float iA, int nsens, ALLEGRO_BITMAP* image );
	Agent(Point iP, float iA, int nsens, float width, float height);
	virtual ~Agent();
	Point getCurrentPosition();
	float getCurrentAngle();
	void draw();
	void setEnv(Environment* pEnv);
	void updatePosition();
	void moveForward(float runTime);
	void turnLeft(float runTime);
	void turnRight(float runTime);
	void setTrail(bool tr);
	bool hasCollided();
};

#endif /* AGENT_H_ */
