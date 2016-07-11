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

	this->US = new UltrasonicSensor[nsens];

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

void Agent::draw() {
	if (image) {
		al_draw_rotated_bitmap(image, width / 2, height / 2,
		/*float dx*/currentPosition.x, /*float dy*/currentPosition.y,
		/*float radian angle*/currentAngle,
		/*int flags*/0);
	}

}

Point Agent::getCurrentPosition() {
	return this->currentPosition;
}
float Agent::getCurrentAngle() {
	return this->currentAngle;
}

void Agent::setEnv(Environment* pEnv) {
	this->pEnv = pEnv;
}

void Agent::updatePosition() {

	//this->moveForward(0.1);

	this->turnRight(0.01);
	// update Sensor values while drawing them
	if (pEnv) {
		for (int i = 0; i < numOfSensors; i++)
			this->US[i].calcDistance(pEnv, currentPosition, currentAngle);
	}
	draw();

}

void Agent::moveForward(float runTime) {

	this->ML.setRunTime(runTime);
	this->ML.setRPM(1200);
	this->ML.setRotationType(FORWARD);
	this->ML.rotateWheel(&WL);

	this->MR.setRunTime(runTime);
	this->MR.setRPM(1200);
	this->MR.setRotationType(FORWARD);
	this->MR.rotateWheel(&WR);
	// calculate wheel travel distance here
	// noOfRotations*circumference
	float DLW = (this->WL.getAngleRotated()) * (this->WL.getDiameter()) / 2; // left wheel distance
	float DRW = (this->WR.getAngleRotated()) * (this->WR.getDiameter()) / 2; // right wheel distance

	float dTheta = (DLW - DRW) / this->width;  // rotation about C.O.M

	float dx = 0.5 * (DLW + DRW) * sin(currentAngle);
	float dy = 0.5 * (DLW + DRW) * cos(currentAngle);

	currentPosition.x += dx;
	currentPosition.y -= dy;
	currentAngle += dTheta;
}
void Agent::turnLeft(float runTime) {
	this->ML.setRunTime(runTime);
	this->ML.setRPM(1200);
	this->ML.setRotationType(BACKWARD);
	this->ML.rotateWheel(&WL);

	this->MR.setRunTime(runTime);
	this->MR.setRPM(1200);
	this->MR.setRotationType(FORWARD);
	this->MR.rotateWheel(&WR);
	// calculate wheel travel distance here
	// noOfRotations*circumference
	float DLW = (this->WL.getAngleRotated()) * (this->WL.getDiameter()) / 2; // left wheel distance
	float DRW = (this->WR.getAngleRotated()) * (this->WR.getDiameter()) / 2; // right wheel distance

	float dTheta = (DLW - DRW) / this->width;  // rotation about C.O.M

	float dx = 0.5 * (DLW + DRW) * sin(currentAngle);
	float dy = 0.5 * (DLW + DRW) * cos(currentAngle);

	currentPosition.x += dx;
	currentPosition.y -= dy;
	currentAngle += dTheta;
}
void Agent::turnRight(float runTime) {
	this->ML.setRunTime(runTime);
	this->ML.setRPM(1200);
	this->ML.setRotationType(FORWARD);
	this->ML.rotateWheel(&WL);

	this->MR.setRunTime(runTime);
	this->MR.setRPM(1200);
	this->MR.setRotationType(BACKWARD);
	this->MR.rotateWheel(&WR);
	// calculate wheel travel distance here
	// noOfRotations*circumference
	float DLW = (this->WL.getAngleRotated()) * (this->WL.getDiameter()) / 2; // left wheel distance
	float DRW = (this->WR.getAngleRotated()) * (this->WR.getDiameter()) / 2; // right wheel distance

	float dTheta = (DLW - DRW) / this->width;  // rotation about C.O.M

	float dx = 0.5 * (DLW + DRW) * sin(currentAngle);
	float dy = 0.5 * (DLW + DRW) * cos(currentAngle);

	currentPosition.x += dx;
	currentPosition.y -= dy;
	currentAngle += dTheta;
}
