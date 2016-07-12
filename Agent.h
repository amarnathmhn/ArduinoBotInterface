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
#include "Brain.h"

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
	Brain* pBrain;  // brain of this agent -> implemented as SNN in Brain.cpp
	Point refOrigin;
	Point jumpVelocity; // velocity vector for jumps
	bool withJump;
	float immReward; // immediate reward
public:

	Agent(Point ref, Point iP, float iA, int nsens, ALLEGRO_BITMAP* image );
	Agent(Point ref, Point iP, float iA, int nsens, float width, float height);
	virtual ~Agent();
	Point getCurrentPosition();
	float getCurrentAngle();
	void draw();
	void setEnv(Environment* pEnv);
	void updatePosition();


	// Motor Controlled Movements
	void moveForward(float runTime);
	void moveLeft(float runTime);
	void moveRight(float runTime);
	void turnLeft(float runTime);
	void turnRight(float runTime);

	// Abstracted Movements - To Jump North-East-West at will |-> <-
	void setJump(bool en, float Vx, float Vy);
	void jumpNorth();
	void jumpWest();
	void jumpEast();

	void setTrail(bool tr);
	bool hasCollided();
	void setBrain(Brain* brain);
	void mapPlaceCells();
};

#endif /* AGENT_H_ */
